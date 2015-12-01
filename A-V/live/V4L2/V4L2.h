#ifndef  __V4L2_H_
#define  __V4L2_H_



class V4L2{
    V4L2();
    ~V4L2();
    
    int getWidth();
    int getHeight();
    bool setSize(int width, int height);
    void getSizeInfo();
    bool initDev(const char * devName, int width, int height);
    bool initMmap();
    bool startStream();
    bool readFrame(AVPicture & pPictureDes, AVPixelFormat FMT, int widht_des, int height_des);
    bool stopStream();

    
}




#endif  //__V4L2_H_