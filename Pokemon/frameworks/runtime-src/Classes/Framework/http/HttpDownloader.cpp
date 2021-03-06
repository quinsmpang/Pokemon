#include "HttpDownloader.h"
#include "cocos2d.h"
#include "../utils/IOUtils.h"
#include "../containers/Vector.h"
#include <time.h>
#include <new>

#include "curl/curl.h"
#include "curl/easy.h"

using namespace cocos2d;
using namespace std;

#define TEMP_FILE_SUFFIX ".tmp"
#define HTTPDOWNLOADER_SEMAPHORE_NAME "http_downloader_sem"
#define DOWNLOADING_UNRESPONSE_TIMES 10

namespace framework {
    static string g_downloaderSemName = string(HTTPDOWNLOADER_SEMAPHORE_NAME);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	DWORD WINAPI DownloadThread(LPVOID userdata)
	{
		HttpDownloader *pDownloader = (HttpDownloader*)userdata;

		while (!pDownloader->_needQuit) {
			// wait for new task
			WaitForSingleObject(pDownloader->_newTaskSem, INFINITE);

			pDownloader->_downloading = true;

			DownloadTask *pTask = nullptr;
			EnterCriticalSection(&pDownloader->_taskMutex);
			if (pDownloader->_taskQueue->getLength() > 0) {
				pTask = (DownloadTask*)pDownloader->_taskQueue->front();
				pDownloader->_taskQueue->dequeue();
			}
			LeaveCriticalSection(&pDownloader->_taskMutex);

			if (pTask) {
				pDownloader->_currentTask = pTask;
				pDownloader->executeTask();
			}
			pDownloader->_downloading = false;
		}

		return 0;
	}
#else
    void *downloadThread(void *userdata)
    {
        HttpDownloader *pDownloader = (HttpDownloader*)userdata;
        
        while (!pDownloader->_needQuit) {
            // wait for new task
            sem_wait(pDownloader->_newTaskSemPtr);
            
            pDownloader->_downloading = true;
            
            DownloadTask *pTask = nullptr;
            pthread_mutex_lock(&pDownloader->_taskMutex);
            if (pDownloader->_taskQueue->getLength() > 0) {
                pTask = (DownloadTask*)pDownloader->_taskQueue->front();
                pDownloader->_taskQueue->dequeue();
            }
            pthread_mutex_unlock(&pDownloader->_taskMutex);
            
            if (pTask) {
                pDownloader->_currentTask = pTask;
                pDownloader->executeTask();
            }
            pDownloader->_downloading = false;
        }
        
        return nullptr;
    }
#endif
    
    size_t onReceiveData(void *buffer, size_t size, size_t writeSize, void *userdata)
    {
        HttpDownloader *pDownloader = (HttpDownloader*)userdata;
        DownloadTask *pTask = pDownloader->_currentTask;
        
        size_t written = fwrite(buffer, size, writeSize, pTask->_saveFile);
        return written;
    }
    
    int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded)
    {
        HttpDownloader *pDownloader = (HttpDownloader*)userdata;
        DownloadTask *pTask = pDownloader->_currentTask;
        
        // When the nonresponse count exceeds the DOWNLOADING_UNRESPONSE_TIMES, treat this as download exception.
        if (pTask->_lastDownloadedBytes == (ssize_t)downloaded) {
            ++pTask->_unreceivedDataTimes;
        } else {
            pTask->_unreceivedDataTimes = 0;
        }
        pTask->_lastDownloadedBytes = (ssize_t)downloaded;
        
        if (pTask->_unreceivedDataTimes >= DOWNLOADING_UNRESPONSE_TIMES) {
            return 1;
        }
        
        float progress = downloaded / totalToDownload;
        if (progress < 0) {
            progress = 0;
        } else if (progress > 1) {
            progress = 1;
        }
        pDownloader->addDownloadEvent(DownloadEventType::DOWNLOAD_INPROGRESS, pTask, progress);
        
        return 0;
    }
    
    /************************ DownloadTask Implementation ************************/
    DownloadTask::DownloadTask(const string &url, const string &savePath, Ref *userdata, bool supportResume, int retryTimes)
        : _url(url)
        , _path(savePath)
        , _supportResume(supportResume)
        , _userdata(nullptr)
        , _breakpointBytes(0)
        , _saveFile(nullptr)
        , _lastDownloadedBytes(0)
        , _unreceivedDataTimes(0)
        , _retryTimes(retryTimes)
    {
        this->setUserdata(userdata);
    }
    
    DownloadTask::~DownloadTask()
    {
        CC_SAFE_RELEASE(_userdata);
    }
    
    DownloadTask *DownloadTask::create(const std::string &url, const std::string &savePath, Ref *userdata, bool supportResume, int retryTimes)
    {
        auto pTask = new (nothrow) DownloadTask(url, savePath, userdata, supportResume, retryTimes);
        if (pTask) {
            pTask->autorelease();
            return pTask;
        }
        CC_SAFE_RELEASE(pTask);
        return pTask;
    }
    
    int DownloadTask::retryOnce()
    {
        --_retryTimes;
        if (_retryTimes < 0) {
            _retryTimes = 0;
        }
        return _retryTimes;
    }
    
    void DownloadTask::setUserdata(cocos2d::Ref *userdata)
    {
        if (_userdata != userdata) {
            CC_SAFE_RELEASE(_userdata);
            CC_SAFE_RETAIN(userdata);
            _userdata = userdata;
        }
    }
    
    /************************ DownloadEvent Implementation ************************/
    DownloadEvent *DownloadEvent::create(framework::DownloadEventType eventType, framework::DownloadTask *task)
    {
        auto pEvent = new (nothrow) DownloadEvent(eventType, task);
        if (pEvent) {
            pEvent->autorelease();
            return pEvent;
        }
        CC_SAFE_RELEASE(pEvent);
        return nullptr;
    }
    
    DownloadEvent::DownloadEvent(DownloadEventType eventType, DownloadTask *task)
        : _type(eventType)
        , _task(task)
        , _progress(0.0f)
        , _errorMsg()
    {
    }
    
    DownloadEvent::~DownloadEvent()
    {
        CC_SAFE_RELEASE(_task);
    }
    
    /************************ HttpDownloader Implementation ************************/
    HttpDownloader::HttpDownloader()
        : _inited(false)
        , _taskQueue(new Queue())
        , _eventQueue(new Queue())
        , _needQuit(false)
        , _currentTask(nullptr)
        , _delegate(nullptr)
        , _downloading(false)
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        , _newTaskSemPtr(nullptr)
#endif
		, _newTaskSem()
        , _eventMutex()
    {
    }
    
    HttpDownloader::~HttpDownloader()
    {
        CC_SAFE_RELEASE(_taskQueue);
        CC_SAFE_RELEASE(_eventQueue);
    }
    
    void HttpDownloader::destroy()
    {
        Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
        
        _needQuit = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        sem_unlink(g_downloaderSemName.c_str());
        sem_close(_newTaskSemPtr);
        pthread_mutex_destroy(&_taskMutex);
        pthread_mutex_destroy(&_eventMutex);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		CloseHandle(_newTaskSem);
		DeleteCriticalSection(&_taskMutex);
		DeleteCriticalSection(&_eventMutex);
#else
        sem_destroy(_newTaskSemPtr);
        pthread_mutex_destroy(&_taskMutex);
        pthread_mutex_destroy(&_eventMutex);
#endif
        this->release();
    }
    
    void HttpDownloader::beginDownloading(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata, bool supportResume, int retryTimes)
    {
        if (url.size() == 0 || savePath.size() == 0) {
            CCLOG("Invalid url and save path.");
            return;
        }
        
        // init thread
        if (!_inited) {
            _inited = this->initThread();
            if (!_inited) {
                CCLOG("HttpDownloader init thread failed.");
                return;
            }
        }
        
        // create download task and add to the task queue.
        auto pTask = DownloadTask::create(url, savePath, userdata, supportResume, retryTimes);
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		EnterCriticalSection(&_taskMutex);
#else
        pthread_mutex_lock(&_taskMutex);
#endif
        _taskQueue->enqueue(pTask);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		LeaveCriticalSection(&_taskMutex);

		// post semaphore to the downloading thread.
		SetEvent(_newTaskSem);
#else
        pthread_mutex_unlock(&_taskMutex);

        // post semaphore to the downloading thread.
        sem_post(_newTaskSemPtr);
#endif
    }
    
    void HttpDownloader::onDownloadUpdated(float dt)
    {
        if (_delegate) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			EnterCriticalSection(&_eventMutex);
#else
            pthread_mutex_lock(&_eventMutex);
#endif
            DownloadEvent *pEvent = nullptr;
            while (_eventQueue->getLength() > 0) {
                pEvent = (DownloadEvent*)_eventQueue->front();
                _eventQueue->dequeue();
                if (pEvent->getType() == DownloadEventType::DOWNLOAD_STARTED) {
                    _delegate->onDownloadStarted(this);
                } else if (pEvent->getType() == DownloadEventType::DOWNLOAD_INPROGRESS) {
                    _delegate->onDownloading(this, pEvent->getProgress());
                } else if (pEvent->getType() == DownloadEventType::DOWNLOAD_SUCCESS) {
                    _delegate->onDownloadCompleted(this);
                } else if (pEvent->getType() == DownloadEventType::DOWNLOAD_FAILED) {
                    _delegate->onDownloadFailed(this, pEvent->getErrorMessage());
                }
            }
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			LeaveCriticalSection(&_eventMutex);
#else
            pthread_mutex_unlock(&_eventMutex);
#endif
        }
    }
    
    bool HttpDownloader::initThread()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		InitializeCriticalSection(&_taskMutex);
		InitializeCriticalSection(&_eventMutex);
#else
        pthread_mutex_init(&_taskMutex, NULL);
		pthread_mutex_init(&_eventMutex, NULL);
#endif
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        long t = time(NULL);
        g_downloaderSemName.append(__String::createWithFormat("%ld", t)->getCString());
        _newTaskSemPtr = sem_open(g_downloaderSemName.c_str(), O_CREAT, 0644, 0);
        if (_newTaskSemPtr == SEM_FAILED) {
            CCLOG("Create new task semaphore failed, errno = %d.", errno);
            _newTaskSemPtr = nullptr;
            return false;
        }
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		long t = time(NULL);
		g_downloaderSemName.append(__String::createWithFormat("%ld", t)->getCString());
		wchar_t buffer[MAX_PATH];
		STDSTRING_TO_WCHAR(g_downloaderSemName, buffer);
		_newTaskSem = CreateEvent(NULL, false, false, buffer);
#else
		int semRet = sem_init(&_newTaskSem, 0, 0);
        if (semRet < 0) {
            CCLOG("Create complete task semaphore failed.");
            return false;
        }
		_newTaskSemPtr = &_newTaskSem;
#endif
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		DWORD threadId;
		CreateThread(NULL, 0, &DownloadThread, NULL, 0, &threadId);
#else
        pthread_create(&_networkThread, nullptr, &downloadThread, this);
        pthread_detach(_networkThread);
#endif
        
        Director::getInstance()->getScheduler()->schedule(schedule_selector(HttpDownloader::onDownloadUpdated), this, 0, false);
        
        return true;
    }
    
    bool HttpDownloader::initTask()
    {
        string tmpFullPath = _currentTask->getPath();
        
        // the save path should be a file path.
        if (tmpFullPath[tmpFullPath.size() - 1] == '/') {
            CCLOG("Not a directory save path, use file path instead.");
            return false;
        }
        
        // create directory
        tmpFullPath = tmpFullPath.substr(0, tmpFullPath.find_last_of('/'));
        if (!IOUtils::getInstance()->createDirectory(tmpFullPath)) {
            CCLOG("Create download directory failed.");
            return false;
        }
        
        tmpFullPath.append(TEMP_FILE_SUFFIX);
        
        // delete old tmp file when not in breakpoint resume mode.
        if (!this->_currentTask->_supportResume && IOUtils::getInstance()->fileExists(tmpFullPath)) {
            bool res = IOUtils::getInstance()->removeFile(tmpFullPath);
            if (!res) {
                CCLOG("Encounter an error when try to delete old .tmp file");
                return false;
            }
        }
        
        FILE *pFile = fopen(tmpFullPath.c_str(), "ab");
        if (!pFile) {
            CCLOG("Create downloading file error.");
            return false;
        }
        
        // breakpoint resume mode, it requires to get file size.
        fseek(pFile, 0, SEEK_END);
        _currentTask->_breakpointBytes = ftell(pFile);
        _currentTask->_saveFile = pFile;
        
        return true;
    }
    
    void HttpDownloader::executeTask()
    {
        CCLOG("Begin downloading file: [%s]", _currentTask->getUrl());
        
        this->addDownloadEvent(DownloadEventType::DOWNLOAD_STARTED, _currentTask, 0);
        
        bool ret = true;
        do {
            ret = this->initTask();
            if (!ret) {
                this->addDownloadEvent(DownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, "Error code: 1001. Init task failed.");
                break;
            }
            ret = this->download();
            if (!ret) {
                this->addDownloadEvent(DownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, "Error code: 1002. Download failed.");
                break;
            }
            ret = this->finishDownloading();
            if (!ret) {
                this->addDownloadEvent(DownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, "Error code: 1003. Rename downloaded file failed.");
                break;
            }
        } while (false);
        
        if (_currentTask->_saveFile) {
            // close the file handle.
            fclose(_currentTask->_saveFile);
            _currentTask->_saveFile = nullptr;
        }
        
        if (ret) {
            this->addDownloadEvent(DownloadEventType::DOWNLOAD_SUCCESS, _currentTask, 1);
        }
    }
    
    bool HttpDownloader::download()
    {
        // use curl.
        CURL *curl = curl_easy_init();
        if (!curl) {
            CCLOG("Curl initialization failed.");
            return false;
        }
        
        char *errorBuffer = (char*)malloc(CURL_ERROR_SIZE);
        CURLcode res;
        
        curl_easy_setopt(curl, CURLOPT_URL, _currentTask->getUrl());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceiveData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        
        // breakpoint resume
        if (_currentTask->_supportResume && _currentTask->_breakpointBytes != 0) {
            char buffer[1000] = { 0 };
            sprintf(buffer, "%d-", _currentTask->_breakpointBytes);
            string str(buffer);
            curl_easy_setopt(curl, CURLOPT_RANGE, str.c_str());
        }
        
        // no timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        
        // download progress
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onProgress);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
        
        // forbid alarm timeout, dns timeout depends on this, so there is no timeout check.
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        
        // dns cache, 6 hours
        static CURLSH *shareHandle = nullptr;
        if (!shareHandle) {
            shareHandle = curl_share_init();
            curl_share_setopt(shareHandle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
        }
        curl_easy_setopt(curl, CURLOPT_SHARE, shareHandle);
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 3600 * 6);
        
        res = curl_easy_perform(curl);
        
        int responseCode;
        CURLcode code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        // 206 is breakpoing resuming.
        if (code != CURLE_OK || (responseCode != 200 && responseCode != 206)) {
            code = CURLE_HTTP_RETURNED_ERROR;
        }
        
        curl_easy_cleanup(curl);
        
        if (res != 0 || code != CURLE_OK || (responseCode != 200 && responseCode != 206)) {
            string errorMsg;
            errorMsg.append("Download failed: ").append(errorBuffer);
            CCLOG("Download error: %s", errorMsg.c_str());
            return false;
        }
        free(errorBuffer);
        
        return true;
    }
    
    bool HttpDownloader::finishDownloading()
    {
        string tmpFullPath = _currentTask->getPath();
        tmpFullPath.append(TEMP_FILE_SUFFIX);
        
        if (!IOUtils::getInstance()->moveFile(tmpFullPath, _currentTask->getPath())) {
            CCLOG("Rename downloaded file failed.");
            return false;
        }
        
        return true;
    }
    
    void HttpDownloader::addDownloadEvent(framework::DownloadEventType eventType, framework::DownloadTask *task, float progress, const std::string &error)
    {
        auto pEvent = DownloadEvent::create(eventType, task);
        pEvent->setProgress(progress);
        pEvent->setErrorMessage(error);
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		EnterCriticalSection(&_eventMutex);
#else
        pthread_mutex_lock(&_eventMutex);
#endif
        _eventQueue->enqueue(pEvent);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		LeaveCriticalSection(&_eventMutex);
#else
        pthread_mutex_unlock(&_eventMutex);
#endif
    }
}