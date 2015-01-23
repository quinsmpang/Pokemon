#include "HttpDownloader.h"
#include "../utils/IOUtils.h"
#include <new>

using namespace cocos2d;
using namespace std;

#define TEMP_FILE_SUFFIX ".tmp"
#define HTTPDOWNLOADER_SEMAPHORE "http_downloader_sem"
#define DOWNLOADING_UNRESPONSE_TIMES 10

namespace framework {
    void *downloadThread(void *userdata)
    {
        HttpDownloader *pDownloader = (HttpDownloader*)userdata;
        
        while (!pDownloader->_needQuit) {
            // wait for new task
            sem_wait(pDownloader->_newTaskSem);
            
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
        }
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
}