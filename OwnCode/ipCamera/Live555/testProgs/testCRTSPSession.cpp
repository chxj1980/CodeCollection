


/**
 *  简单分析一下流程:
1 openURL, 开始播放。
2 在openURL里面，调用sendDescribeCommand，向服务器端发请求。然后，通过回调函数处理。
3 如果没有错误的话，env->taskScheduler().doEventLoop(&eventLoopWatchVariable);这里阻塞执行。
4 DummySink，这个是数据的回调，DummySink::afterGettingFrame这里取到数据。
 **/
class CRTSPSession 
{
public:
    CRTSPSession();
    virtual ~CRTSPSession();
    int startRTSPClient(char const* progName, char const* rtspURL, int debugLevel);
    int stopRTSPClient();
    int openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, int debugLevel);


    RTSPClient* m_rtspClient;
    char eventLoopWatchVariable;


    pthread_t tid;


    bool m_running;
    string m_rtspUrl;
    string m_progName;
    int m_debugLevel;

    static void *rtsp_thread_fun (void *param);
    void rtsp_fun();

};


CRTSPSession::CRTSPSession()
{
    m_rtspClient = NULL;
    m_running = false;
    eventLoopWatchVariable = 0;
}
CRTSPSession::~CRTSPSession()
{
}
int CRTSPSession::startRTSPClient(char const* progName, char const* rtspURL, int debugLevel)
{
    m_progName = progName;
    m_rtspUrl = rtspURL;
    m_debugLevel = debugLevel;
    eventLoopWatchVariable = 0;
    int r = pthread_create(&tid, NULL, rtsp_thread_fun, this);
    if (r)
    {
        perror ("pthread_create()");
        return -1;
    }
    return 0;
}
int CRTSPSession::stopRTSPClient()
{
    eventLoopWatchVariable = 1;
    return 0;
}
void *CRTSPSession::rtsp_thread_fun(void *param)
{
    CRTSPSession *pThis = (CRTSPSession*)param;
    pThis->rtsp_fun ();
    return NULL;
}
void CRTSPSession::rtsp_fun()
{
    //::startRTSP(m_progName.c_str(), m_rtspUrl.c_str(), m_ndebugLever);
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);
    if (openURL(*env, m_progName.c_str(), m_rtspUrl.c_str(), m_debugLevel) == 0) {
        m_nStatus = 1;
        env->taskScheduler().doEventLoop(&eventLoopWatchVariable);

        m_running = false;
        eventLoopWatchVariable = 0;

        if (m_rtspClient)  {
            shutdownStream(m_rtspClient,0);
        }
        m_rtspClient = NULL;
    }

    env->reclaim(); 
    env = NULL;
    delete scheduler; 
    scheduler = NULL;
    m_nStatus = 2;
}
int CRTSPSession::openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, int debugLevel)
{
    m_rtspClient = ourRTSPClient::createNew(env, rtspURL, debugLevel, progName);
    if (m_rtspClient == NULL)  {
        env << "Failed to create a RTSP client for URL \"" << rtspURL << "\": " << env.getResultMsg() << "\n";
        return -1;
    }
    ((ourRTSPClient*)m_rtspClient)->m_nID = m_nID;
    m_rtspClient->sendDescribeCommand(continueAfterDESCRIBE); 
    return 0;
}


// A function that outputs a string that identifies each stream (for debugging output). Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const RTSPClient& rtspClient) 
{
    return env << "[URL:\"" << rtspClient.url() << "\"]: ";
}
// A function that outputs a string that identifies each subsession (for debugging output). Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const MediaSubsession& subsession) 
{
    return env << subsession.mediumName() << "/" << subsession.codecName();
}
void usage(UsageEnvironment& env, char const* progName) 
{
    env << "Usage: " << progName << "  ... \n";
    env << "\t(where each  is a \"rtsp://\" URL)\n";
}


int main()
{
    //上面class的调用：
    CRTSPSession* pRtsp = new CRTSPSession;

    if (pRtsp->startRTSPClient(progName, rtspURL, debugLevel)) {
        delete pRtsp;
        pRtsp = NULL;
        return -1;
    }

    //停止的时候：
    pRtsp->stopRTSPClient();
    delete pRtsp; 
    pRtsp = NULL;


    return 0;
}


