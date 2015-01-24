/******************************
 Description: Http downloader.
 Author: M.Wan
 Date: 01/23/2015
 ******************************/

#ifndef __HTTP_HTTPDOWNLOADER__
#define __HTTP_HTTPDOWNLOADER__

#include "base/CCRef.h"
#include "../containers/Queue.h"
#include <string>

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif
#include <sys/stat.h>
#include <errno.h>

namespace framework {
    class HttpDownloader;
    class DownloadTask;
    
    class HttpDownloaderDelegate
    {
    public:
        virtual ~HttpDownloaderDelegate() {}
        
        /**
         * Delegate when the download task starts.
         *
         * @param downloader Related downloader of the task.
         */
        virtual void onDownloadStarted(HttpDownloader *downloader) = 0;
        /**
         * Delegate when the download task executes.
         *
         * @param downloader Related downloader of the task.
         * @param progress Downloading progress.
         */
        virtual void onDownloading(HttpDownloader *downloader, float progress) = 0;
        /**
         * Delegate when the download task completes.
         *
         * @param downloader Related downloader of the task.
         */
        virtual void onDownloadCompleted(HttpDownloader *downloader) = 0;
        /**
         * Delegate when the download task fails.
         *
         * @param downloader Related downloader of the task.
         * @param errorMsg Encountered error message.
         */
        virtual void onDownloadFailed(HttpDownloader *downloader, const std::string &errorMsg) = 0;
    };
    
    class DownloadTask : public cocos2d::Ref
    {
        friend class HttpDownloader;
        friend size_t onReceiveData(void *, size_t size, size_t writeSize, void *userdata);
        friend int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded);
    public:
        /**
         * Create a download task.
         *
         * @param url Download url.
         * @param savePath Local file path to save.
         * @param userdata User object to store in the task.
         * @param canResume Whether support the breakpoint resuming.
         * @param retryTimes Retry count when downloading failed.
         *
         * @return DownloadTask object.
         */
        static DownloadTask *create(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata = nullptr, bool canResume = true, int retryTimes = 3);
        
        /**
         * DownloadTask constructor.
         *
         * @param url Download url.
         * @param savePath Local file path to save.
         * @param userdata User object to store in the task.
         * @param canResume Whether support the breakpoint resuming.
         * @param retryTimes Retry count when downloading failed.
         */
        explicit DownloadTask(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata = nullptr, bool canResume = true, int retryTimes = 3);
        /**
         * DownloadTask destructor.
         */
        virtual ~DownloadTask();
        
        /**
         * Get download url.
         *
         * @return Download url.
         */
        inline const char *getUrl()
        {
            return _url.c_str();
        }
        /**
         * Get local download path.
         *
         * @return Local download path.
         */
        inline const char *getPath()
        {
            return _path.c_str();
        }
        /**
         * Whether supports breakpoint resume feature.
         *
         * @return Boolean value.
         */
        inline bool supportResume()
        {
            return _supportResume;
        }
        /**
         * Get stored user object.
         *
         * @return Stored user object.
         */
        inline cocos2d::Ref *getUserdata()
        {
            return _userdata;
        }
        /**
         * Set stored user object.
         *
         * @param Stored user object.
         */
        void setUserdata(cocos2d::Ref *userdata);
        
    protected:
        int retryOnce();
        
        std::string _url;
        std::string _path;
        bool _supportResume;
        cocos2d::Ref *_userdata;
        
        int _breakpointBytes;
        FILE *_saveFile;
        size_t _lastDownloadedBytes;
        size_t _unreceivedDataTimes;
        volatile int _retryTimes;
    };
    
    enum class DownloadEventType
    {
        DOWNLOAD_STARTED = 0,
        DOWNLOAD_INPROGRESS,
        DOWNLOAD_SUCCESS,
        DOWNLOAD_FAILED,
    };
    
    class DownloadEvent : public cocos2d::Ref
    {
    public:
        /**
         * Create a download event.
         *
         * @param eventType Download event type.
         * @param task Related download task.ß
         *
         * @return DownloadEvent object.
         */
        static DownloadEvent *create(DownloadEventType eventType, DownloadTask *task);
        
        /**
         * DownloadEvent constructor.
         *
         * @param eventType Download event type.
         * @param task Related download task.ß
         */
        DownloadEvent(DownloadEventType eventType, DownloadTask *task);
        /**
         * DownloadEvent destructor.
         */
        ~DownloadEvent();
        
        /**
         * DownloadEvent getter and setter.
         */
        CC_SYNTHESIZE(DownloadEventType, _type, Type);
        /**
         * Related task getter and setter.
         */
        CC_SYNTHESIZE_RETAIN(DownloadTask*, _task, RelatedTask);
        /**
         * Download progress getter and setter.
         */
        CC_SYNTHESIZE(float, _progress, Progress);
        /**
         * Error message getter and setter.
         */
        CC_SYNTHESIZE_PASS_BY_REF(std::string, _errorMsg, ErrorMessage);
    };
    
    class HttpDownloader : public cocos2d::Ref
    {
        friend size_t onReceiveData(void *, size_t size, size_t writeSize, void *userdata);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		friend DWORD WINAPI DownloadThread(LPVOID);
#else
        friend void *downloadThread(void *data);
#endif
        friend int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded);
    public:
        /**
         * HttpDownloader constructor.
         */
        HttpDownloader();
        /**
         * HttpDownloader destructor.
         */
        virtual ~HttpDownloader();
        
        /**
         * Downloader delegate getter and setter.
         */
        CC_SYNTHESIZE(HttpDownloaderDelegate*, _delegate, Delegate);
        
        /**
         * Destroy all tasks.
         */
        void destroy();
        
        /**
         * Begin a download task.
         *
         * @param url Download url.
         * @param savePath Local file path to save.
         * @param userdata User object to store in the task.
         * @param canResume Whether support the breakpoint resuming.
         * @param retryTimes Retry count when downloading failed.
         */
        void beginDownloading(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata, bool supportResume, int retryTimes);
        
        /**
         * Retry failed task.
         *
         * @param userdata User object.
         *
         * @return Whether the operation is supported.
         */
        bool retryTask(cocos2d::Ref *userdata);
        
        /**
         * Whether the downloader is downloading.
         *
         * @return Boolean value.
         */
        inline bool isDownloading()
        {
            return _downloading;
        }
        
        void onDownloadUpdated(float dt);
        
    protected:
        bool initThread();
        void executeTask();
        
        bool initTask();
        bool download();
        bool finishDownloading();
        
        void addDownloadEvent(DownloadEventType eventType, DownloadTask *task, float progress, const std::string &error = "");
        
        bool _inited;       // whether inited.
        Queue *_taskQueue;
        Queue *_eventQueue;
        
        bool _needQuit;
        DownloadTask *_currentTask;
        bool _downloading;
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		HANDLE _networkThread;
		CRITICAL_SECTION _taskMutex;
		CRITICAL_SECTION _eventMutex;
		HANDLE _newTaskSem;
#else
        pthread_t _networkThread;
        pthread_mutex_t _taskMutex;
        pthread_mutex_t _eventMutex;
        sem_t *_newTaskSemPtr;
        sem_t _newTaskSem;
#endif
    };
}

#endif /* defined(__HTTP_HTTPDOWNLOADER__) */
