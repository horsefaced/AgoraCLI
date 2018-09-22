#pragma once
#include "..\..\agorasdk\include\IAgoraMediaEngine.h"
using namespace agora::media;

namespace AgoraClrLibrary {

	typedef bool(__stdcall * PFOnRecordAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnMixedAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrameBeforeMixing)(const char* uid, IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnCaptureVideoFrame)(IVideoFrameObserver::VideoFrame & videoFrame);
	typedef bool(__stdcall * PFOnRenderVideoFrame)(const char* uid, IVideoFrameObserver::VideoFrame & videoFrame);

	delegate bool NativeOnRecordAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnMixedAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameBeforeMixingDelegate(const char* uid, IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnCaptureVideoFrameDelegate(IVideoFrameObserver::VideoFrame & videoFrame);
	delegate bool NativeOnRenderVideoFrameDelegate(const char* uid, IVideoFrameObserver::VideoFrame & videoFrame);

	public class AgoraClrRawFrameObserver : public IAudioFrameObserver, public IVideoFrameObserver
	{
	public:
		AgoraClrRawFrameObserver();

		PFOnRecordAudioFrame onRecordAudioFrameEvent = 0;
		PFOnPlaybackAudioFrame onPlaybackAudioFrameEvent = 0;
		PFOnMixedAudioFrame onMixedAudioFrameEvent = 0;
		PFOnPlaybackAudioFrameBeforeMixing onPlaybackAudioFrameBeforeMixingEvent = 0;
		PFOnCaptureVideoFrame onCaptureVideoFrameEvent = 0;
		PFOnRenderVideoFrame onRenderVideoFrameEvent = 0;

		// Inherited via IAudioFrameObserver
		virtual bool onRecordAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onMixedAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrameBeforeMixing(const char* uid, AudioFrame & audioFrame) override;

		// Inherited via IVideoFrameObserver
		virtual bool onCaptureVideoFrame(VideoFrame & videoFrame) override;
		virtual bool onRenderVideoFrame(const char* uid, VideoFrame & videoFrame) override;
	};

}