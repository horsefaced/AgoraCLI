#pragma once
#include "..\..\agorasdk\include\IAgoraMediaEngine.h"
using namespace agora::media;

namespace AgoraClrLibrary {

	typedef bool(__stdcall * PFOnRecordAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnMixedAudioFrame)(IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrameBeforeMixing)(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);
	typedef bool(__stdcall * PFOnPlaybackAudioFrameBeforeMixingEx)(const char* channelId, unsigned uid,  IAudioFrameObserver::AudioFrame & audioFrame);

	typedef bool(__stdcall * PFOnCaptureVideoFrame)(IVideoFrameObserver::VideoFrame & videoFrame);
	typedef bool(__stdcall* PFOnPreEncodeVideoFrame)(IVideoFrameObserver::VideoFrame&);
	typedef bool(__stdcall* PFGetSmoothRenderingEnabled)();
	typedef bool(__stdcall * PFOnRenderVideoFrame)(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);
	typedef IVideoFrameObserver::VIDEO_FRAME_TYPE(__stdcall * PFOnGetVideoFormatPreference)();
	typedef bool(__stdcall* PFOnGetRotationApplied)();
	typedef bool(__stdcall* PFOnGetMirrorApplied)();
	typedef bool(__stdcall* PFIsMultipleChannelFrameWanted)();
	typedef bool(__stdcall* PFOnRenderVideoFrameEx)(const char* channelId, unsigned uid, IVideoFrameObserver::VideoFrame& videoFrame);
	typedef UINT(__stdcall* PFGetObservedFramePosition)();

	delegate bool NativeOnRecordAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnMixedAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameDelegate(IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameBeforeMixingDelegate(unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);
	delegate bool NativeOnPlaybackAudioFrameBeforeMixingExDelegate(const char* channelId,unsigned int uid, IAudioFrameObserver::AudioFrame & audioFrame);

	delegate bool NativeOnCaptureVideoFrameDelegate(IVideoFrameObserver::VideoFrame & videoFrame);
	delegate bool NativeOnPreEncodeVideoFrameDelegate(IVideoFrameObserver::VideoFrame&);
	delegate bool NativeGetSmoothRenderingEnabledDelegate();
	delegate bool NativeOnRenderVideoFrameDelegate(unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);
	delegate IVideoFrameObserver::VIDEO_FRAME_TYPE NativeOnGetVideoFormatePreferenceDelegate();
	delegate bool NativeOnGetRotationAppliedDelegate();
	delegate bool NativeOnGetMirrorAppliedDelegate();
	delegate bool NativeIsMultipleChannelFrameWantedDelegate();
	delegate UINT NativeGetObservedFramePositionDelegate();
	delegate bool NativeOnRenderVideoFrameExDelegate(const char* channelId,unsigned int uid, IVideoFrameObserver::VideoFrame & videoFrame);


	public class AgoraClrAudioFrameObserver : public IAudioFrameObserver
	{
	public:
		virtual ~AgoraClrAudioFrameObserver() = default;
		AgoraClrAudioFrameObserver();

		PFOnRecordAudioFrame onRecordAudioFrameEvent = nullptr;
		PFOnPlaybackAudioFrame onPlaybackAudioFrameEvent = nullptr;
		PFOnMixedAudioFrame onMixedAudioFrameEvent = nullptr;
		PFOnPlaybackAudioFrameBeforeMixing onPlaybackAudioFrameBeforeMixingEvent = nullptr;
		PFIsMultipleChannelFrameWanted isMultipleChannelFrameWantedEvent=nullptr;
		PFOnPlaybackAudioFrameBeforeMixingEx onPlaybackAudioFrameBeforeMixingExEvent = nullptr;
		
		// Inherited via IAudioFrameObserver
		bool onRecordAudioFrame(AudioFrame & audioFrame) override;
		bool onPlaybackAudioFrame(AudioFrame & audioFrame) override;
		bool onMixedAudioFrame(AudioFrame & audioFrame) override;
		bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame & audioFrame) override;
		bool isMultipleChannelFrameWanted() override;
		bool onPlaybackAudioFrameBeforeMixingEx(const char* channelId, unsigned uid, AudioFrame& audioFrame) override;
	};

	public class AgoraClrVideoFrameObserver :  public IVideoFrameObserver
	{
	public:
		virtual ~AgoraClrVideoFrameObserver() = default;
		AgoraClrVideoFrameObserver();

		PFOnCaptureVideoFrame onCaptureVideoFrameEvent = nullptr;
		PFOnPreEncodeVideoFrame onPreEncodeVideoFrameEvent = nullptr;
		PFGetSmoothRenderingEnabled getSmoothRenderingEnabledEvent = nullptr;
		PFOnRenderVideoFrame onRenderVideoFrameEvent = nullptr;
		PFOnGetVideoFormatPreference onGetVideoFormatPreferenceEvent = nullptr;
		PFOnGetRotationApplied onGetRotationAppliedEvent = nullptr;
		PFOnGetMirrorApplied onGetMirrorAppliedEvent = nullptr;
		PFIsMultipleChannelFrameWanted isMultipleChannelFrameWantedEvent=nullptr;
		PFOnRenderVideoFrameEx onRenderVideoFrameExEvent = nullptr;
		PFGetObservedFramePosition getObservedFramePositionEvent =nullptr;
		
		// Inherited via IVideoFrameObserver
		bool onCaptureVideoFrame(VideoFrame & videoFrame) override;
		bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;
		bool getSmoothRenderingEnabled() override;
		bool onRenderVideoFrame(unsigned int uid, VideoFrame & videoFrame) override;
		VIDEO_FRAME_TYPE getVideoFormatPreference() override;
		bool getRotationApplied() override;
		bool getMirrorApplied() override;
		bool isMultipleChannelFrameWanted() override;
		bool onRenderVideoFrameEx(const char* channelId, unsigned uid, VideoFrame& videoFrame) override;
		UINT getObservedFramePosition() override;
	};

}