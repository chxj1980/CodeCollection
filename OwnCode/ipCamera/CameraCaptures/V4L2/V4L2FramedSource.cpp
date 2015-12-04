/*
 * V4L2FramedSource.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */
//V4L2FramedSource类继承了FramedSource类。
//V4L2FramedSource是我们自定义的类，主要实现了我们的视频数据如何进入到live555里面去。
//首先在构造函数里面，我们对v4l2进行了初始化以及x264编码初始化。
//这个类最重要的就是doGetNextFrame函数，live555就是通过这个函数将我们的一个nal数据加载到live555里面，然后消息循环发送出去的。
//我们先是将v4l2捕捉的视频数据进行H264压缩编码，这里面值得注意的是一帧图像可能压缩成几个nal的，所以我这里面在确保一帧数据完全发送完了才向v4l2要数据。
//然后就是数据的般移了，其中数据存在fTo里面。然后就是消息了。

#include <V4L2FramedSource.h>

int V4L2FramedSource::nalIndex = 0;

V4L2FramedSource::V4L2FramedSource(UsageEnvironment & env) :
		FramedSource(env)
{
	v4l2 = new V4L2();
	pEncode = new H264Encode();
	mp_token = NULL;
	printf("creater\n");
	v4l2->initDev("/dev/video0", 640, 480);
	avpicture_alloc(&Picture, PIX_FMT_YUV420P, v4l2->getWidth(),
			v4l2->getHeight());
	v4l2->startStream();

	pEncode->x264_init(Picture, 640, 480);

}

V4L2FramedSource::~V4L2FramedSource()
{
}

unsigned V4L2FramedSource::maxFrameSize() const
{
	return 40 * 1024;
}

void V4L2FramedSource::doGetNextFrame()
{
	/*double delay = 1000.0 / 25;
	 int to_delay = delay * 1000;    // us
	 mp_token = envir().taskScheduler().scheduleDelayedTask(to_delay,
	 getNextFrame, this);*/
	if (V4L2FramedSource::nalIndex == pEncode->nnal)
	{
		v4l2->readFrame(Picture, PIX_FMT_YUV420P, v4l2->getWidth(),
				v4l2->getHeight());
		pEncode->x264_encode();
		V4L2FramedSource::nalIndex = 0;
		gettimeofday(&fPresentationTime, NULL);
	}
	memmove(fTo, pEncode->nals[V4L2FramedSource::nalIndex].p_payload,
			pEncode->nals[V4L2FramedSource::nalIndex].i_payload);
	fFrameSize = pEncode->nals[V4L2FramedSource::nalIndex].i_payload;
	V4L2FramedSource::nalIndex++;
	afterGetting(this);
}

void V4L2FramedSource::getNextFrame1()
{

}
