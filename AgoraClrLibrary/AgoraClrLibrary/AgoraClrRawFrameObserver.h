#pragma once
#include "..\..\agorasdk\include\IAgoraMediaEngine.h"
using namespace agora::media;

namespace AgoraClrLibrary {

	typedef bool(__stdcall * PFOnRecordAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnMixedAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrameBeforeMixing)(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);

	typedef bool(__stdcall * PFOnCaptureVideoFrame)(IVideoFrameObserver::VideoFrame & videoFrame);
	typedef bool(__stdcall* PFOnPreEncodeVideoFrame)(IVideoFrameObserver::VideoFrame&);
	typedef bool(__stdcall* PFGetSmoothRenderingEnabled)();
	typedef bool(__stdcall * PFOnRenderVideoFrame)(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);
	typedef IVideoFrameObserver::VIDEO_FRAME_TYPE(__stdcall * PFOnGetVideoFormatePreference)();
	typedef bool(__stdcall* PFOnGetRotationApplied)();
	typedef bool(__stdcall* PFOnGetMirrorApplied)();

	delegate bool NativeOnRecordAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnMixedAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameBeforeMixingDelegate(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);

	delegate bool NativeOnCaptureVideoFrameDelegate(IVideoFrameObserver::VideoFrame & videoFrame);
	delegate bool NativeOnPreEncodeVideoFrameDelegate(IVideoFrameObserver::VideoFrame&);
	delegate bool NativeGetSmoothRenderingEnabledDelegate();
	delegate bool NativeOnRenderVideoFrameDelegate(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);
	delegate IVideoFrameObserver::VIDEO_FRAME_TYPE NativeOnGetVideoFormatePreferenceDelegate();
	delegate bool NativeOnGetRotationAppliedDelegate();
	delegate bool NativeOnGetMirrorAppliedDelegate();


	public class AgoraClrRawFrameObserver : public IAudioFrameObserver, public IVideoFrameObserver
	{
	public:
		AgoraClrRawFrameObserver();

		PFOnRecordAudioFrame onRecordAudioFrameEvent = 0;
		PFOnPlaybackAudioFrame onPlaybackAudioFrameEvent = 0;
		PFOnMixedAudioFrame onMixedAudioFrameEvent = 0;
		PFOnPlaybackAudioFrameBeforeMixing onPlaybackAudioFrameBeforeMixingEvent = 0;

		PFOnCaptureVideoFrame onCaptureVideoFrameEvent = 0;
		PFOnPreEncodeVideoFrame onPreEncodeVideoFrameEvent = 0;
		PFGetSmoothRenderingEnabled getSmoothRenderingEnabledEvent = 0;
		PFOnRenderVideoFrame onRenderVideoFrameEvent = 0;
		PFOnGetVideoFormatePreference onGetVideoFormatePreferenceEvent = 0;
		PFOnGetRotationApplied onGetRotationAppliedEvent = 0;
		PFOnGetMirrorApplied onGetMirrorAppliedEvent = 0;

		// Inherited via IAudioFrameObserver
		virtual bool onRecordAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onMixedAudioFrame(AudioFrame & audioFrame) override;
		virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame & audioFrame) override;

		// Inherited via IVideoFrameObserver
		virtual bool onCaptureVideoFrame(VideoFrame & videoFrame) override;
		virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;
		virtual bool getSmoothRenderingEnabled() override;
		virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame & videoFrame) override;
		virtual VIDEO_FRAME_TYPE getVideoFormatPreference() override;
		virtual bool getRotationApplied() override;
		virtual bool getMirrorApplied() override;
	};

}