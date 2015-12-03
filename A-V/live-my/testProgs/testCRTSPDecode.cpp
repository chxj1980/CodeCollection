//视频解码也简易封装


class CDecodeCB
{
public:
    virtual void videoCB(int width, int height, uint8_t* buff, int len)=0;

};







class CFfmpegDecode
{
public:
    CFfmpegDecode();
    ~CFfmpegDecode();

    int initFFMPEG();
    int openDecoder(int width, int height, CDecodeCB* pCB);
    int closeDecoder();
    int decode_rtsp_frame(uint8_t* input,int nLen,bool bWaitIFrame /*= false*/);

private:
    bool m_bInit;
    AVCodec *decode_codec;
    AVCodecContext *decode_c;
    AVFrame *decode_picture;
    struct SwsContext *img_convert_ctx;
    CDecodeCB* m_pCB;
    int m_nWidth;
    int m_nHeight;

};


static int sws_flags = SWS_BICUBIC;
static int sws_flags = SWS_BICUBIC;

CFfmpegDecode::CFfmpegDecode()
{
    m_bInit = false;
    img_convert_ctx = NULL;
}


CFfmpegDecode::~CFfmpegDecode()
{
    av_lockmgr_register(NULL);
}


int CFfmpegDecode::initFFMPEG()
{
    //m_state = RC_STATE_INIT;
    avcodec_register_all();
    av_register_all();
    //avformat_network_init();


    //if (av_lockmgr_register(lockmgr))
    {
        // m_state = RC_STATE_INIT_ERROR;
        //   return -1;
    }
    return 0;
}
int CFfmpegDecode::openDecoder(int width, int height,CDecodeCB* pCB)
{
    m_nWidth = width;
    m_nHeight = height;
    m_pCB = pCB;
    
    if (m_bInit)
        return -1;
    
    decode_codec = avcodec_find_decoder(CODEC_ID_H264);
    if (!decode_codec) {
        fprintf(stderr, "codec not found\n");
        return -2;
    }

    decode_c= avcodec_alloc_context3(decode_codec);
    decode_c->codec_id= CODEC_ID_H264;
    decode_c->codec_type = AVMEDIA_TYPE_VIDEO;
    decode_c->pix_fmt = PIX_FMT_YUV420P;

    decode_picture= avcodec_alloc_frame();

    if (avcodec_open2(decode_c, decode_codec, NULL) < 0){
        //  fprintf(stderr, "could not open codec\n");
        return -3;
    }
    m_bInit = true;
    return 0;
}


int CFfmpegDecode::closeDecoder()
{
    if(decode_c) {
        avcodec_close(decode_c);
        av_free(decode_c);
    }
    if(decode_picture)
        av_free(decode_picture);


    m_bInit = false;
}


int CFfmpegDecode::decode_rtsp_frame(uint8_t* input,int nLen,bool bWaitIFrame /*= false*/)
{
    if(!m_bInit)
        return -1;

    if(input == NULL || nLen <= 0)
        return -2;

    try{
        int got_picture;
        int size = nLen;

        AVPacket avpkt;
        av_init_packet(&avpkt);
        avpkt.size = size;
        avpkt.data = input;

        //while (avpkt.size > 0)
        {
        int len = avcodec_decode_video2(decode_c, decode_picture, &got_picture, &avpkt);

        if(len == -1)  {
            return -3;
        }

        if (got_picture) {
            int w = decode_c->width;
            int h = decode_c->height;
            int numBytes=avpicture_get_size(PIX_FMT_RGB24, w,h);
            uint8_t * buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

            AVFrame *pFrameRGB = avcodec_alloc_frame();
            avpicture_fill((AVPicture *)pFrameRGB, buffer,PIX_FMT_RGB24,  w, h);

            img_convert_ctx = sws_getCachedContext(img_convert_ctx, w, h, (PixelFormat)(decode_picture->format), w, h,PIX_FMT_RGB24, sws_flags, NULL, NULL, NULL);
            if (img_convert_ctx == NULL) {
                fprintf(stderr, "Cannot initialize the conversion context\n");
                //exit(1);
                return -4;
            }
            sws_scale(img_convert_ctx, decode_picture->data, decode_picture->linesize, 0, h, pFrameRGB->data, pFrameRGB->linesize);

            if (m_pCB)  {
                m_pCB->videoCB(w, h, pFrameRGB->data[0], numBytes*sizeof(uint8_t));
            }
            av_free(buffer);
            av_free(pFrameRGB);
            return 0;


            if (avpkt.data) {
                avpkt.size -= len;
                avpkt.data += len;
            }
        }  else {
            return -5;
        }
        //return 0;
        }
        //return 0;
        } catch(...) {
            
    }
    
    return -6;
}

