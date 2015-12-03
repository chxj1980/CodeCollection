/*
 * H264Encode.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */

#include <H264Encode.h>

H264Encode::H264Encode()
{
	i_pts = 0;
	x264EnCoder = NULL;
	pPicOut = NULL;
	nnal=0;
	nals=NULL;
}

H264Encode::~H264Encode()
{
}

void H264Encode::x264_init(AVPicture picture, int width, int height)
{
	x264_param_default_preset(¶m, "veryfast", "zerolatency");

	param.i_width = width;
	param.i_height = height;
	param.i_fps_num = 25;
	param.i_fps_den = 1;

	param.i_keyint_max = 25;
	param.b_intra_refresh = 1;

	param.b_annexb = 1;

	x264_param_apply_profile(¶m, "baseline");
	x264EnCoder = x264_encoder_open(¶m);

	x264_picture_alloc(&xPic, X264_CSP_I420, width, height);

	xPic.img.plane[0] = picture.data[0];
	xPic.img.plane[1] = picture.data[1];
	xPic.img.plane[2] = picture.data[2];
	pPicOut = new x264_picture_t;
}

void H264Encode::x264_encode()
{
	xPic.i_pts = i_pts++;
	x264_encoder_encode(x264EnCoder, &nals, &nnal, &xPic, pPicOut);
}

