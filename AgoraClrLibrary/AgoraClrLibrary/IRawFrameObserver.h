#pragma once
#include "include\IAgoraMediaEngine.h"
using namespace agora::media;

namespace AgoraClrLibrary {

	typedef bool(__stdcall * PFOnRecordAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrameBeforeMixing)(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnCaptureVideoFrame)(IVideoFrameObserver::VideoFrame & videoFrame);
	typedef bool(__stdcall * PFOnRenderVideoFrame)(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);

	delegate bool NativeOnRecordAudioFrame(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrame(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnCaptureVideoFrame(IVideoFrameObserver::VideoFrame & videoFrame);
	delegate bool NativeOnRenderVideoFrame(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);

	public class IRawFrameObserver : public IAudioFrameObserver, IVideoFrameObserver
	{
	public:
		IRawFrameObserver();

		PFOnRecordAudioFrame onRecordAudioFrameEvent = 0;
		PFOnPlaybackAudioFrame onPlaybackAudioFrameEvent = 0;
		PFOnPlaybackAudioFrameBeforeMixing onPlaybackAudioFrameBeforeMixingEvent = 0;
		PFOnCaptureVideoFrame onCaptureVideoFrameEvent = 0;
		PFOnRenderVideoFrame onRenderVideoFrameEvent = 0;

		// Inherited via IAudioFrameObserver
		virtual bool onRecordAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame & audioFrame) override;

		// Inherited via IVideoFrameObserver
		virtual bool onCaptureVideoFrame(VideoFrame & videoFrame) override;
		virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame & videoFrame) override;
	};

}