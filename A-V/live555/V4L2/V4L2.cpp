/*
 * V4L2.cpp
 *
 *  Created on: 2013年12月17日
 *      Author: ny
 */

#include "V4L2.h"

V4L2::V4L2()
{
	fd = -1;
	buffers = NULL;
	width = 0;
	height = 0;
	CLEAR(fmt);       //设置帧格式
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; //V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
}

V4L2::~V4L2()
{
	close(fd);
}

int V4L2::getWidth()
{
	return width;
}

int V4L2::getHeight()
{
	return height;
}

bool V4L2::setSize(int width, int height)
{
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
	{
		printf("Can not VIDIOC_S_FMT\n");
		return false;
	}
	getSizeInfo();
	return true;
}

void V4L2::getSizeInfo()
{
	if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)
	{
		printf("Can not VIDIOC_G_FMT\n");
		return;
	}
	this->width = fmt.fmt.pix.width;
	this->height = fmt.fmt.pix.height;
}

bool V4L2::initDev(const char * devName, int width, int height)
{
	v4l2_capability cap;

	fd = open(devName, O_RDWR, 0); //打开设备
	if (fd == -1)
	{
		printf("Can not open %s\n", devName);
		return false;
	}
	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) //查询设备的功能
	{
		printf("Can not get Capability\n");
		return false;
	}
	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		printf("Can not capture video\n");
		return false;
	}
	if (!(cap.capabilities & V4L2_CAP_STREAMING))
	{
		printf("does not support streaming\n");
	}
	if (!setSize(width, height))
		return false;
	printf("fmt.fmt.pix.bytesperline:%d\n", fmt.fmt.pix.bytesperline);
	printf("format:%c%c%c%c\n", (fmt.fmt.pix.pixelformat & 0xff),
			((fmt.fmt.pix.pixelformat >> 8) & 0xff),
			((fmt.fmt.pix.pixelformat >> 16) & 0xff),
			((fmt.fmt.pix.pixelformat >> 24) & 0xff));

	return initMmap();
}
bool V4L2::initMmap()
{
	struct v4l2_requestbuffers req;
	unsigned int n_buffers;
	CLEAR(req);

	req.count = 4; //先要向内核申请buffer缓冲，一般选择4个缓冲，最多是5个
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if (-1 == ioctl(fd, VIDIOC_REQBUFS, &req)) //向内核里面设置buffer
	{ //分配内存
		if (EINVAL == errno)
		{
			printf("%s does not support memory mapping\n", "ss");
			exit(EXIT_FAILURE);
		} else
			printf("VIDIOC_REQBUFS\n");
	}

	buffers = (buffer *) calloc(req.count, sizeof(buffer)); //分配缓存
	if (!buffers)
	{
		printf("Out of memory\n");
		exit(EXIT_FAILURE);
	}

	for (n_buffers = 0; n_buffers < req.count; n_buffers++) //将buffer添加到QUERTBUF的队列里面去
	{
		struct v4l2_buffer buf;
		CLEAR(buf);

		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;

		if (-1 == ioctl(fd, VIDIOC_QUERYBUF, &buf))
			printf("VIDIOC_QUERYBUF");

		buffers[n_buffers].length = buf.length;   //设置映射方式为mmap
		printf("buf.length %d\n", buffers[n_buffers].length);
		buffers[n_buffers].start = mmap(NULL, buf.length,
		PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, buf.m.offset);

		if (MAP_FAILED == buffers[n_buffers].start)
			printf("fail mmap\n");
	}
	return 1;
}
bool V4L2::startStream()
{
	unsigned int n_buffers;
	enum v4l2_buf_type type;
	/*将申请到的帧缓冲全部入队列，以便存放采集到的数据*/
	for (n_buffers = 0; n_buffers < 4; n_buffers++)
	{
		v4l2_buffer buf;
		CLEAR(buf);

		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;

		if (-1 == ioctl(fd, VIDIOC_QBUF, &buf))   //放入缓存
		{
			printf("fail VIDIOC_QBUF");
			return false;
		}
	}

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (-1 == ioctl(fd, VIDIOC_STREAMON, &type))   //打开视频流
	{
		printf("fail VIDIOC_STREAMON\n");
		return false;
	} else
		printf("StreamOn success!\n");
	return true;
}
//摄像头数据 主要是YUYV格式数据，所以需要进行对格式进行转化，转化后的数据保存在AVPicture里面，
//格式是由FMT制定的，输出图像尺寸也是widht_des，height_des决定的
bool V4L2::readFrame(AVPicture & pPictureDes, AVPixelFormat FMT, int widht_des,
		int height_des)
{
	v4l2_buffer buf;
	AVPicture pPictureSrc;
	SwsContext * pSwsCtx;
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	if (-1 == ioctl(fd, VIDIOC_DQBUF, &buf))   //读取
	{
		printf("fail VIDIOC_DQBUF\n");
		return false;
	}
	pPictureSrc.data[0] = (unsigned char *) buffers[buf.index].start;
	pPictureSrc.data[1] = pPictureSrc.data[2] = pPictureSrc.data[3] = NULL;
	pPictureSrc.linesize[0] = fmt.fmt.pix.bytesperline;
	int i = 0;
	for (i = 1; i < 8; i++)
	{
		pPictureSrc.linesize[i] = 0;
	}
	pSwsCtx = sws_getContext(width, height, PIX_FMT_YUYV422, widht_des,
			height_des, FMT,
			SWS_BICUBIC, 0, 0, 0);
	int rs = sws_scale(pSwsCtx, pPictureSrc.data, pPictureSrc.linesize, 0,
			height, pPictureDes.data, pPictureDes.linesize);
	if (rs == -1)
	{
		printf("Can open to change to des image");
		return false;
	}
	sws_freeContext(pSwsCtx);
	if (-1 == ioctl(fd, VIDIOC_QBUF, &buf))    //放回缓存
	{
		printf("fail VIDIOC_QBUF\n");
		return false;
	}
	return true;
}

bool V4L2::stopStream()
{
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type))
	{
		perror("Fail to ioctl 'VIDIOC_STREAMOFF'");
		//exit(EXIT_FAILURE);
		return false;
	}
	return true;
}
