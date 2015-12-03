#ifndef  __H264OnDemandServerMediaSubsession_H__
#define  __H264OnDemandServerMediaSubsession_H__


class H264OnDemandServerMediaSubsession{
    H264OnDemandServerMediaSubsession( UsageEnvironment& env, FramedSource * source);
    ~H264OnDemandServerMediaSubsession();
    
    void chkForAuxSDPLine1();
    const char * getAuxSDPLine(RTPSink *sink, FramedSource *source);
    RTPSink * createNewRTPSink( Groupsock *rtpsock, unsigned char type, FramedSource *source);
    FramedSource * createNewStreamSource( unsigned sid, unsigned &bitrate);
    char const* sdpLines();
    
}

#endif  //__H264OnDemandServerMediaSubsession_H__