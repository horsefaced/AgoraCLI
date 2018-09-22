#include "stdafx.h"
#include "AgoraClrRawFrameObserver.h"

using namespace AgoraClrLibrary;

AgoraClrRawFrameObserver::AgoraClrRawFrameObserver()
{

}

bool AgoraClrRawFrameObserver::onRecordAudioFrame(AudioFrame & audioFrame)
{
	if (onRecordAudioFrameEvent) return onRecordAudioFrameEvent(audioFrame);
	else return true;
}

bool AgoraClrRawFrameObserver::onPlaybackAudioFrame(AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameEvent) return onPlaybackAudioFrameEvent(audioFrame);
	else return true;
}

bool AgoraClrLibrary::AgoraClrRawFrameObserver::onMixedAudioFrame(AudioFrame & audioFrame)
{
	if (onMixedAudioFrameEvent) return onMixedAudioFrameEvent(audioFrame);
	else return false;
}

bool AgoraClrRawFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* uid, AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameBeforeMixingEvent) return onPlaybackAudioFrameBeforeMixingEvent(uid, audioFrame);
	else return true;
}

bool AgoraClrRawFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	if (onCaptureVideoFrameEvent) return onCaptureVideoFrameEvent(videoFrame);
	else return true;
}

bool AgoraClrRawFrameObserver::onRenderVideoFrame(const char* uid, VideoFrame & videoFrame)
{
	if (onRenderVideoFrameEvent) return onRenderVideoFrameEvent(uid, videoFrame);
	else return true;
}
