/*
 * Application.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */

 //这是我们程序的主程序，主要是参考了live555的testOnDemandRTSPServer.cpp。
 //主要是区别是我们自己指定了rtsp链接了，以及我们自己实现的framesource。
 //这样本地的视频采集发送服务器就完成了，可以用开源的VLC播放进行播放了，live555支持1对多的，已经测试过可以在ipad，iphone，android同步播放，延迟在1s以内。
 //不过要VLC设置缓存时间在200ms就可以了。

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "H264OnDemandServerMediaSubsession.h"
#include "V4L2FramedSource.h"

#include <live/liveMedia.hh>
#include <live/BasicUsageEnvironment.hh>
#include <live/UsageEnvironment.hh>

UsageEnvironment* env;
static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
		char const* streamName, char const* inputFileName = "Live"); // fwd
int main()
{
	// 设置使用环境。Begin by setting up our usage environment:
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);
	UserAuthenticationDatabase* authDB = NULL;

	RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554, authDB);
	if (rtspServer == NULL)
	{
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}

	char const* descriptionString =
			"Session streamed by \"testOnDemandRTSPServer\"";

	char const* streamName = "live";
	ServerMediaSession* sms = ServerMediaSession::createNew(*env, streamName,
			streamName, descriptionString);
	sms->addSubsession(
			new H264OnDemandServerMediaSubsession(*env,
					new V4L2FramedSource(*env)));
	rtspServer->addServerMediaSession(sms);
	announceStream(rtspServer, sms, streamName);
	env->taskScheduler().doEventLoop(); // does not return

	return 0;
}
static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
		char const* streamName, char const* inputFileName)
{
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env << "\n\"" << streamName << "\" stream, from the file \""
			<< inputFileName << "\"\n";
	env << "Play this stream using the URL \"" << url << "\"\n";
	delete[] url;
}
