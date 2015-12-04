#ifndef __H264Encode_H__
#define __H264Encode_H__

class H264Encode{
    H264Encode();
    ~H264Encode();
    
    void x264_init(AVPicture picture, int width, int height);
    void x264_encode();
    
}




#endif //__H264Encode_H__