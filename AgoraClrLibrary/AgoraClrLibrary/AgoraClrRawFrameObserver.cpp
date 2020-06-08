#include "stdafx.h"
#include "AgoraClrRawFrameObserver.h"

using namespace AgoraClrLibrary;

AgoraClrAudioFrameObserver::AgoraClrAudioFrameObserver()
{

}

bool AgoraClrAudioFrameObserver::onRecordAudioFrame(AudioFrame & audioFrame)
{
	if (onRecordAudioFrameEvent) return onRecordAudioFrameEvent(audioFrame);
	return true;
}

bool AgoraClrAudioFrameObserver::onPlaybackAudioFrame(AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameEvent) return onPlaybackAudioFrameEvent(audioFrame);
	return true;
}

bool AgoraClrAudioFrameObserver::onMixedAudioFrame(AudioFrame & audioFrame)
{
	if (onMixedAudioFrameEvent) return onMixedAudioFrameEvent(audioFrame);
	return false;
}

bool AgoraClrAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame & audioFrame)
{
	if (onPlaybackAudioFrameBeforeMixingEvent) return onPlaybackAudioFrameBeforeMixingEvent(uid, audioFrame);
	return true;
}

bool AgoraClrAudioFrameObserver::isMultipleChannelFrameWanted()
{
	if (isMultipleChannelFrameWantedEvent) return isMultipleChannelFrameWantedEvent();
	return false;
}

bool AgoraClrAudioFrameObserver::onPlaybackAudioFrameBeforeMixingEx(const char* channelId, unsigned uid,
	AudioFrame& audioFrame)
{
	if (onPlaybackAudioFrameBeforeMixingExEvent) return onPlaybackAudioFrameBeforeMixingExEvent(channelId,uid, audioFrame);
	return true;
}

AgoraClrVideoFrameObserver::AgoraClrVideoFrameObserver()
{
}
bool AgoraClrVideoFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	if (onCaptureVideoFrameEvent) return onCaptureVideoFrameEvent(videoFrame);
	return true;
}

bool AgoraClrVideoFrameObserver::onPreEncodeVideoFrame(VideoFrame& videoFrame)
{
	if (onPreEncodeVideoFrameEvent) return onPreEncodeVideoFrameEvent(videoFrame);
	return true;
}

bool AgoraClrVideoFrameObserver::getSmoothRenderingEnabled()
{
	if (getSmoothRenderingEnabledEvent) return getSmoothRenderingEnabledEvent();
	return false;
}

bool AgoraClrVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame & videoFrame)
{
	if (onRenderVideoFrameEvent) return onRenderVideoFrameEvent(uid, videoFrame);
	return true;
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE AgoraClrVideoFrameObserver::getVideoFormatPreference()
{
	if (onGetVideoFormatPreferenceEvent) return onGetVideoFormatPreferenceEvent();
	return FRAME_TYPE_YUV420;
}

bool AgoraClrVideoFrameObserver::getRotationApplied()
{
	if (onGetRotationAppliedEvent) return onGetRotationAppliedEvent();
	return false;
}

bool AgoraClrVideoFrameObserver::getMirrorApplied()
{
	if (onGetMirrorAppliedEvent) return onGetMirrorAppliedEvent();
	return false;
}

bool AgoraClrVideoFrameObserver::isMultipleChannelFrameWanted()
{
	if (isMultipleChannelFrameWantedEvent) return isMultipleChannelFrameWantedEvent();
	return false;
}

bool AgoraClrVideoFrameObserver::onRenderVideoFrameEx(const char* channelId, unsigned uid, VideoFrame& videoFrame)
{
	if (onRenderVideoFrameExEvent) return onRenderVideoFrameExEvent(channelId,uid, videoFrame);
	return true;
}

UINT AgoraClrVideoFrameObserver::getObservedFramePosition()
{
	if (getObservedFramePositionEvent) return getObservedFramePositionEvent();
	return static_cast<uint32_t>(POSITION_POST_CAPTURER | POSITION_PRE_RENDERER);
}


