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

#include <pthread.h>
#include <semaphore.h>
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
         */
        virtual void onDownloading(HttpDownloader *downloader) = 0;
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
         */
        virtual void onDownloadFailed(HttpDownloader *downloader) = 0;
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
    
    class HttpDownloader : public cocos2d::Ref
    {
        friend size_t onReceiveData(void *, size_t size, size_t writeSize, void *userdata);
        friend void *downloadThread(void *data);
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
        
    protected:
        bool initThread();
        bool initTasks();
        void executeTask();
        
        bool download();
        
        bool _inited;       // whether inited.
        Queue *_taskQueue;
        
        bool _needQuit;
        DownloadTask *_currentTask;
        bool _downloading;
        
        pthread_t _networkThread;
        pthread_mutex_t _taskMutex;
        pthread_mutex_t _eventMutex;
        sem_t *_newTaskSem;
        sem_t _completeTaskSem;
    };
}

#endif /* defined(__HTTP_HTTPDOWNLOADER__) */
