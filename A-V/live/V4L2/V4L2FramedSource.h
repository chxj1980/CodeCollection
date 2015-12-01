#ifndef __V4L2_FRAMED_SOURCE_H__
#define __V4L2_FRAMED_SOURCE_H__


class V4L2FramedSource{
    
    V4L2FramedSource(UsageEnvironment & env);
    ~V4L2FramedSource()
    
    unsigned maxFrameSize() const;
    void doGetNextFrame();
    
    
}





#endif //__V4L2_FRAMED_SOURCE_H__