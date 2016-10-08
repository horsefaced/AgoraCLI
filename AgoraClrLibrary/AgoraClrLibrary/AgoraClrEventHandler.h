#pragma once
#include "include\IAgoraRtcEngine.h"

using namespace agora::rtc;

namespace AgoraClrLibrary {
	//Native Function Pointer
	typedef void(__stdcall * PFOnJoinChannelSuccess)(const char* channel, uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnRejoinChannelSuccess)(const char* channel, uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnWarning)(int warn, const char* msg);
	typedef void(__stdcall * PFOnError)(int err, const char* msg);
	typedef void(__stdcall * PFOnAudioQuality)(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	typedef void(__stdcall * PFOnAudioVolumeIndication)(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	typedef void(__stdcall * PFOnLeaveChannel)(const agora::rtc::RtcStats& stats);
	typedef void(__stdcall * PFOnRtcStats)(const agora::rtc::RtcStats& stats);
	typedef void(__stdcall * PFOnAudioDeviceStateChanged)(const char* deviceId, int deviceType, int deviceState);
	typedef void(__stdcall * PFOnVideoDeviceStateChanged)(const char* deviceId, int deviceType, int deviceState);
	typedef void(__stdcall * PFOnLastmileQuality)(int quality);
	typedef void(__stdcall * PFOnFirstLocalVideoFrame)(int width, int height, int elapsed);
	typedef void(__stdcall * PFOnFirstRemoteVideoDecoded)(uid_t uid, int width, int height, int elapsed);
	typedef void(__stdcall * PFOnFirstRemoteVideoFrame)(uid_t uid, int width, int height, int elapsed);
	typedef void(__stdcall * PFOnUserJoined)(uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnUserOffline)(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
	typedef void(__stdcall * PFOnUserMuteAudio)(uid_t uid, bool muted);
	typedef void(__stdcall * PFOnUserMuteVideo)(uid_t uid, bool muted);
	typedef void(__stdcall * PFOnUserEnableVideo)(uid_t uid, bool enabled);
	typedef void(__stdcall * PFOnApiCallExecuted)(const char* api, int error);
	typedef void(__stdcall * PFOnLocalVideoStats)(const agora::rtc::LocalVideoStats& stats);
	typedef void(__stdcall * PFOnRemoteVideoStats)(const agora::rtc::RemoteVideoStats& stats);
	typedef void(__stdcall * PFOnCameraReady)();
	typedef void(__stdcall * PFOnVideoStopped)();
	typedef void(__stdcall * PFOnConnectionLost)();
	typedef void(__stdcall * PFOnConnectionInterrupted)();
	typedef void(__stdcall * PFOnRefreshRecordingServiceStatus)(int status);
	typedef void(__stdcall * PFOnStreamMessage)(uid_t uid, int streamId, const char* data, size_t length);
	typedef void(__stdcall * PFOnStreamMessageError)(uid_t uid, int streamId, int code, int missed, int cached);

	//Native delegate	
	delegate void NativeOnJoinChannelSuccessDelegate(const char* channel, uid_t uid, int elapsed);
	delegate void NativeOnRejoinChannelSuccessDelegate(const char* channel, uid_t uid, int elapsed);
	delegate void NativeOnWarningDelegate(int warn, const char* msg);
	delegate void NativeOnErrorDelegate(int err, const char* msg);
	delegate void NativeOnAudioQualityDelegate(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	delegate void NativeOnAudioVolumeIndicationDelegate(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	delegate void NativeOnLeaveChannelDelegate(const agora::rtc::RtcStats& stats);
	delegate void NativeOnRtcStatsDelegate(const agora::rtc::RtcStats& stats);
	delegate void NativeOnAudioDeviceStateChangedDelegate(const char* deviceId, int deviceType, int deviceState);
	delegate void NativeOnVideoDeviceStateChangedDelegate(const char* deviceId, int deviceType, int deviceState);
	delegate void NativeOnLastmileQualityDelegate(int quality);
	delegate void NativeOnFirstLocalVideoFrameDelegate(int width, int height, int elapsed);
	delegate void NativeOnFirstRemoteVideoDecodedDelegate(uid_t uid, int width, int height, int elapsed);
	delegate void NativeOnFirstRemoteVideoFrameDelegate(uid_t uid, int width, int height, int elapsed);
	delegate void NativeOnUserJoinedDelegate(uid_t uid, int elapsed);
	delegate void NativeOnUserOfflineDelegate(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
	delegate void NativeOnUserMuteAudioDelegate(uid_t uid, bool muted);
	delegate void NativeOnUserMuteVideoDelegate(uid_t uid, bool muted);
	delegate void NativeOnUserEnableVideoDelegate(uid_t uid, bool enabled);
	delegate void NativeOnApiCallExecutedDelegate(const char* api, int error);
	delegate void NativeOnLocalVideoStatsDelegate(const agora::rtc::LocalVideoStats& stats);
	delegate void NativeOnRemoteVideoStatsDelegate(const agora::rtc::RemoteVideoStats& stats);
	delegate void NativeOnCameraReadyDelegate();
	delegate void NativeOnVideoStoppedDelegate();
	delegate void NativeOnConnectionLostDelegate();
	delegate void NativeOnConnectionInterruptedDelegate();
	delegate void NativeOnRefreshRecordingServiceStatusDelegate(int status);
	delegate void NativeOnStreamMessageDelegate(uid_t uid, int streamId, const char* data, size_t length);
	delegate void NativeOnStreamMessageErrorDelegate(uid_t uid, int streamId, int code, int missed, int cached);

	public class AgoraClrEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:
		AgoraClrEventHandler();
		~AgoraClrEventHandler();

		PFOnJoinChannelSuccess onJoinChannelSuccessEvent = 0;
		PFOnRejoinChannelSuccess onRejoinChannelSuccessEvent = 0;
		PFOnWarning onWarningEvent = 0;
		PFOnError onErrorEvent = 0;
		PFOnAudioQuality onAudioQualityEvent = 0;
		PFOnAudioVolumeIndication onAudioVolumeIndicationEvent = 0;
		PFOnLeaveChannel onLeaveChannelEvent = 0;
		PFOnRtcStats onRtcStatsEvent = 0;
		PFOnAudioDeviceStateChanged onAudioDeviceStateChangedEvent = 0;
		PFOnVideoDeviceStateChanged onVideoDeviceStateChangedEvent = 0;
		PFOnLastmileQuality onLastmileQualityEvent = 0;
		PFOnFirstLocalVideoFrame onFirstLocalVideoFrameEvent = 0;
		PFOnFirstRemoteVideoDecoded onFirstRemoteVideoDecodedEvent = 0;
		PFOnFirstRemoteVideoFrame onFirstRemoteVideoFrameEvent = 0;
		PFOnUserJoined onUserJoinedEvent = 0;
		PFOnUserOffline onUserOfflineEvent = 0;
		PFOnUserMuteAudio onUserMuteAudioEvent = 0;
		PFOnUserMuteVideo onUserMuteVideoEvent = 0;
		PFOnUserEnableVideo onUserEnableVideoEvent = 0;
		PFOnApiCallExecuted onApiCallExecutedEvent = 0;
		PFOnLocalVideoStats onLocalVideoStatsEvent = 0;
		PFOnRemoteVideoStats onRemoteVideoStatsEvent = 0;
		PFOnCameraReady onCameraReadyEvent = 0;
		PFOnVideoStopped onVideoStoppedEvent = 0;
		PFOnConnectionLost onConnectionLostEvent = 0;
		PFOnConnectionInterrupted onConnectionInterruptedEvent = 0;
		PFOnRefreshRecordingServiceStatus onRefreshRecordingServiceStatusEvent = 0;
		PFOnStreamMessage onStreamMessageEvent = 0;
		PFOnStreamMessageError onStreamMessageErrorEvent = 0;

		virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		virtual void onWarning(int warn, const char* msg);
		virtual void onError(int err, const char* msg);
		virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
		virtual void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
		virtual void onLeaveChannel(const agora::rtc::RtcStats& stats);
		virtual void onRtcStats(const agora::rtc::RtcStats& stats);
		virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		virtual void onLastmileQuality(int quality);
		virtual void onFirstLocalVideoFrame(int width, int height, int elapsed);
		virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
		virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
		virtual void onUserJoined(uid_t uid, int elapsed);
		virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
		virtual void onUserMuteAudio(uid_t uid, bool muted);
		virtual void onUserMuteVideo(uid_t uid, bool muted);
		virtual void onUserEnableVideo(uid_t uid, bool enabled);
		virtual void onApiCallExecuted(const char* api, int error);
		virtual void onLocalVideoStats(const agora::rtc::LocalVideoStats& stats);
		virtual void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats);
		virtual void onCameraReady();
		virtual void onVideoStopped();
		virtual void onConnectionLost();
		virtual void onConnectionInterrupted();
		virtual void onRefreshRecordingServiceStatus(int status);
		virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length);
		virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached);

	};

}