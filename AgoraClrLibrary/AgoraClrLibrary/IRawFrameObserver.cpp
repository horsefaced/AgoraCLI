#include "stdafx.h"
#include "IRawFrameObserver.h"

using namespace AgoraClrLibrary;

IRawFrameObserver::IRawFrameObserver()
{

}

bool IRawFrameObserver::onRecordAudioFrame(AudioFrame & audioFrame)
{
	if (onRecordAudioFrameEvent) return onRecordAudioFrameEvent(audioFrame);
	else return true;
}

bool IRawFrameObserver::onPlaybackAudioFrame(AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameEvent) return onPlaybackAudioFrameEvent(audioFrame);
	else return true;
}

bool IRawFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameBeforeMixingEvent) return onPlaybackAudioFrameBeforeMixingEvent(uid, audioFrame);
	else return true;
}

bool IRawFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	if (onCaptureVideoFrameEvent) return onCaptureVideoFrameEvent(videoFrame);
	else return true;
}

bool IRawFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame & videoFrame)
{
	if (onRenderVideoFrameEvent) return onRenderVideoFrameEvent(uid, videoFrame);
	else return true;
}
