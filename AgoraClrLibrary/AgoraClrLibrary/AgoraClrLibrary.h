// AgoraClrLibrary.h

#pragma once
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrLibraryDelegates.h"
#include "AgoraClrLibraryEnum.h"
#include "AgoraClrLibraryTypes.h"
#include "AgoraClrMetadataObserver.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrChannel.h"
#include "AgoraClrClientRoleOptions.h"
#include "AgoraClrVideoSink.h"
#include "AgoraClrMediaRecorder.h"

#include <string>
#include "AgoraClrVideoSource.h"

using namespace System;
using namespace Runtime::InteropServices;
using namespace Collections::Generic;
using namespace agora::rtc;

namespace AgoraClrLibrary
{

	public
	ref class AgoraClr
	{
	public:
		AgoraClr();
		~AgoraClr();
		!AgoraClr();

		//频道管理
		int initialize(String^ vendorkey, [Optional] Nullable<int> areaCode);
		int initialize(ClrRtcEngineContext^ context);
		void release();
		int setChannelProfile(ChannelProfile profile);
		int setClientRole(ClientRoleType role);
		int setClientRole(ClientRoleType role, AgoraClrClientRoleOptions options);
		int joinChannel(String^ token, String^ channelName, String^ channelInfo, UINT uid);
		int joinChannel(String^ token, String^ channelName, String^ channelInfo, UINT uid, ClrChannelMediaOptions^ options);
		int switchChannel(String^ token, String^ channelId);
		int switchChannel(String^ token, String^ channelId, ClrChannelMediaOptions^ options);
		int leaveChannel();
		int setAVSyncSource(String^ channelId, UINT uid);
		int renewToken(String^ token);
		int enableWebSdkInteroperability(bool enabled);
		EnumConnectionStateType getConnectionState();

		//频道事件
		onConnectionStateChanged^ onConnectionStateChanged;
		onJoinChannelSuccess^ onJoinChannelSuccess;
		onRejoinChannelSuccess^ onRejoinChannelSuccess;
		onLeaveChannel^ onLeaveChannel;
		onClientRoleChanged^ onClientRoleChanged;
		onUserJoined^ onUserJoined;
		onUserOffline^ onUserOffline;
		onNetworkTypeChanged^ onNetworkTypeChanged;
		onConnectionLost^ onConnectionLost;
		onTokenPrivilegeWillExpire^ onTokenPrivilegeWillExpire;
		onRequestToken^ onRequestToken;

		//音频管理方法
		int enableAudio();
		int disableAudio();
		int setAudioProfile(AudioProfileType profile, AudioScenarioType scenario);
		int adjustRecordingSignalVolume(int volume);
		int adjustLoopbackRecordingSignalVolume(int volume);
		int adjustUserPlaybackSignalVolume(UINT uid, int volume);
		int adjustPlaybackSignalVolume(int volume);
		int enableLocalAudio(bool enabled);
		int muteLocalAudioStream(bool mute);
		int muteRemoteAudioStream(UINT uid, bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		[[deprecated]]
		int setDefaultMuteAllRemoteAudioStreams(bool mute);

		//视频管理方法
		int enableVideo();
		int disableVideo();
		int setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config);
		int setupLocalVideo(IntPtr view, int renderMode, UINT uid);
		int setupLocalVideo(IntPtr view, int renderMode, UINT uid, EnumVideoMirrorModeType mt);
		int setupRemoteVideo(IntPtr view, int renderMode, UINT uid);
		int setupRemoteVideo(IntPtr view, int renderMode, UINT uid, EnumVideoMirrorModeType mt);
		int setLocalRenderMode(EnumRenderModeType mode);
		int setLocalRenderMode(EnumRenderModeType mode, EnumVideoMirrorModeType mt);
		int setRemoteRenderMode(UINT uid, EnumRenderModeType mode);
		int setRemoteRenderMode(UINT uid, EnumRenderModeType mode, EnumVideoMirrorModeType mt);
		int startPreview();
		int stopPreview();
		int enableLocalVideo(bool enabled);
		int muteLocalVideoStream(bool mute);
		int muteRemoteVideoStream(UINT uid, bool mute);
		int muteAllRemoteVideoStreams(bool mute);
		int setDefaultMuteAllRemoteVideoStreams(bool mute);

		

		//本地媒体事件
		onLocalAudioStateChanged^ onLocalAudioStateChanged;
		onLocalVideoStateChanged^ onLocalVideoStateChanged;
		onFirstLocalVideoFrame^ onFirstLocalVideoFrame;
		[ObsoleteAttribute()]
		onFirstLocalAudioFrame^ onFirstLocalAudioFrame;
		onAudioPublishStateChanged^ onAudioPublishStateChanged;
		onVideoPublishStateChanged^ onVideoPublishStateChanged;
		onAudioSubscribeStateChanged^ onAudioSubscribeStateChanged;
		onVideoSubscribeStateChanged^ onVideoSubscribeStateChanged;
		onFirstLocalAudioFramePublished^ onFirstLocalAudioFramePublished;
		onFirstLocalVideoFramePublished^ onFirstLocalVideoFramePublished;

		//远端媒体事件
		onRemoteAudioStateChanged^ onRemoteAudioStateChanged;
		onRemoteVideoStateChanged^ onRemoteVideoStateChanged;

		//好像3.0上没有了
		onUserMuteAudio^ onUserMuteAudio;
		onUserMuteVideo^ onUserMuteVideo;
		onFirstRemoteAudioFrame^ onFirstRemoteAudioFrame;
		onFirstRemoteAudioDecoded^ onFirstRemoteAudioDecoded;
		onFirstRemoteVideoFrame^ onFirstRemoteVideoFrame;

		//数据统计事件
		onRtcStats^ onRtcStats;
		onNetworkQuality^ onNetworkQuality;
		onLocalAudioStats^ onLocalAudioStats;
		onLocalVideoStats^ onLocalVideoStats;
		onRemoteAudioStats^ onRemoteAudioStats;
		onRemoteVideoStats^ onRemoteVideoStats;

		//视频前处理及后处理
		int setBeautyEffectOptions(bool enabled, ClrBeautyOptions options); //在3.0上不适配macos, 在2.9.1上只适配iOS与Android,所以不添加

		//todo: 多频道管理
		AgoraClrChannel^ createChannel(String^ channelId);

		//屏幕共享
		ClrScreenCaptureSourceInfoList^ getScreenCaptureSources(ClrSize^ thumbSize, ClrSize^ iconSize, bool includeScreen);
		int startScreenCaptureByDisplayId(int displayId, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params);
		int startScreenCaptureByScreenRect(ClrRectangle^ screenRect, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params);
		int startScreenCaptureByWindowId(IntPtr windowId, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params);
		int setScreenCaptureContentHint(EnumVideoContentHint hint);
		int updateScreenCaptureParameters(ClrScreenCaptureParameters^ params);
		int updateScreenCaptureRegion(ClrRectangle^ rect);
		int stopScreenCapture();

		//音乐文件播放及混音
		int startAudioMixing(String^ path, bool loop, bool replace, int cycle, int startPos);
		int stopAudioMixing();
		int pauseAudioMixing();
		int resumeAudioMixing();
		int adjustAudioMixingVolume(int volume);
		int adjustAudioMixingPlayoutVolume(int volume);
		int adjustAudioMixingPublishVolume(int volume);
		int setAudioMixingPitch(int pitch);
		int getAudioMixingPlayoutVolume();
		int getAudioMixingPublishVolume();
		int getAudioMixingCurrentPosition();
		int setAudioMixingPosition(int pos);
		int getAudioTrackCount();
		int selectAudioTrack(int index);
		int setAudioMixingPlaybackSpeed(int speed);
		int setAudioMixingDualMonoMode(EnumAudioMixingDualMonoMode mode);
		[[DEPRECATED]]
		int getAudioMixingDuration();
		int getAudioFileInfo(String^ filePath);


		//音乐文件播放及混音事件
		onAudioMixingStateChanged^ onAudioMixingStateChanged;
		Action^ onRemoteAudioMixingBegin;
		Action^ onRemoteAudioMixingEnd;
		onRequestAudioFileInfo^ onRequestAudioFileInfo;

		//音效文件播放管理
		int getEffectsVolume();
		int setEffectsVolume(int volume);
		int setVolumeOfEffect(int soundId, int volume);
		int playEffect(int soundId, String^ file, int loopCount, double pitch, double pan, int gain, bool publish, int startPos);
		int stopEffect(int soundId);
		int stopAllEffects();
		int preloadEffect(int soundId, String^ file);
		int unloadEffect(int soundId);
		int pauseEffect(int soundId);
		int pauseAllEffects();
		int resumeEffect(int soundId);
		int resumeAllEffects();
		int getEffectDuration(String^ file);
		int setEffectPosition(int soundId, int pos);
		int getEffectCurrentPosition(int soundId);

		//音效文件播放管理事件
		onAudioEffectFinished^ onAudioEffectFinished;

		//变声与混响
		[[deprecated]]
		int setLocalVoiceChanger(VoiceChangerPreset changer);
		[[deprecated]]
		int setLocalVoiceReverbPreset(EnumAudioReverbPreset preset);
		int setLocalVoicePitch(double pitch);
		int setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain);
		int setLocalVoiceReverb(AudioReverbType type, int value);
		int setVoiceBeautifierPreset(EnumVoiceBeautifierPreset preset);
		int setVoiceBeautifierParameters(EnumVoiceBeautifierPreset preset, int param1, int param2);
		int setAudioEffectPreset(EnumAudioEffectPreset preset);
		int setAudioEffectParameters(EnumAudioEffectPreset preset, int param1, int param2);
		int setVoiceConversionPreset(EnumVoiceConversionPreset preset);

		//听声辩位
		int enableSoundPositionIndication(bool enabled);
		int setRemoteVoicePosition(uid_t uid, double pan, double gain);

		//CDN推流
		int startRtmpStreamWithoutTranscoding(String^ url);
		int startRtmpStreamWithTranscoding(String^ url, ClrLiveTranscoding^ transcoding);
		int updateRtmpTranscoding(ClrLiveTranscoding^ transcoding);
		int stopRtmpStream(String^ url);
		int setLiveTranscoding(ClrLiveTranscoding^ transcoding);
		int addPublishStreamUrl(String^ url, bool transcodingEnabled);
		int removePublishStreamUrl(String^ url);

		//CDN推流事件
		onRtmpStreamingStateChanged^ onRtmpStreamingStateChanged;
		onTranscodingUpdated^ onTranscodingUpdated;
		onRtmpStreamingEvent^ onRtmpStreamingEvent;

		//跨频道媒体流转发
		int startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int pauseAllChannelMediaRelay();
		int resumeAllChannelMediaRelay();
		int stopChannelMediaRelay();

		//跨频道媒体流转发事件
		onChannelMediaRelayStateChanged^ onChannelMediaRelayStateChanged;
		Action<EnumChannelMediaRelayEvent>^ onChannelMediaRelayEvent;

		//音量提示
		int enableAudioVolumeIndication(int interval, int smooth, bool report_vad);

		//音量提示事件
		onAudioVolumeIndication^ onAudioVolumeIndication;
		onActiveSpeaker^ onActiveSpeaker;

		//音频播放路由及其事件
		//这个部分2.9.1只用在Android与iOS上, 所以没有添加

		//耳返控制, 这个函数现在在2.9.1上只在Android与iOS上提供, 请不要调用
		//int setInEarMonitoringVolume(int volume);

		//视频双流模式
		int enableDualStreamMode(bool enabled);
		int setRemoteVideoStreamType(UINT uid, EnumRemoteVideoStreamType type);
		int setRemoteDefaultVideoStreamType(EnumRemoteVideoStreamType type);

		//直播音视频回退
		int setLocalPublishFallbackOption(StreamFallbackOptions option);
		int setRemoteSubscribeFallbackOption(StreamFallbackOptions option);
		int setRemoteUserPriority(uid_t uid, PriorityType priority);

		//直播音视频回退事件
		onLocalPublishFallbackToAudioOnly^ onLocalPublishFallbackToAudioOnly;
		onRemoteSubscribeFallbackToAudioOnly^ onRemoteSubscribeFallbackToAudioOnly;

		//通话前网络测试
		int startEchoTest(int intervalInSeconds);
		int startEchoTest(ClrEchoTestConfiguration^ config);
		int stopEchoTest();
		int enableLastmileTest();
		int disableLastmileTest();
		int startLastmileProbeTest(ClrLastmileProbeConfig^ config);
		int stopLastmileProbeTest();

		//通话前网络测试事件
		onLastmileQuality^ onLastmileQuality;
		Action<ClrLastmileProbeResult^>^ onLastmileProbeResult;

		//自定义视频模块
		bool setVideoSource(ClrVideoSource^ source);

		//音视频自采集
		int setExternalVideoSource(bool enabled, bool useTexture);
		int pushVideoFrame(ClrExternalVideoFrame^ frame);
		int setExternalAudioSource(bool enabled, int sampleRate, int channels);
		int setExternalAudioSourceVolume(int sourcePos, int volume);
		int pushAudioFrame(int sourcePos, ClrAudioFrame^ frame);

		//音视频自渲染
		int setExternalAudioSink(bool enabled, int sampleRate, int channels);
		int pullAudioFrame([Out] ClrAudioFrame^% frame);

		int setLocalVideoRenderer(ClrVideoSink^ sink);
		int setRemoteVideoRenderer(uid_t uid, ClrVideoSink^ sink);

		//原始音频数据
		int setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);

		//原始音频数据事件
		onRecordAudioFrame^ onRecordAudioFrame;
		onPlaybackAudioFrame^ onPlaybackAudioFrame;
		onPlaybackAudioFrameBeforeMixing^ onPlaybackAudioFrameBeforeMixing;
		onMixedAudioFrame^ onMixedAudioFrame;

		//原始视频数据
		onCaptureVideoFrame^ onCaptureVideoFrame;
		onPreEncodeVideoFrame^ onPreEncodeVideoFrame;
		onRenderVideoFrame^ onRenderVideoFrame;
		onRenderVideoFrameEx^ onRenderVideoFrameEx;
		property bool IsSmoothRenderingEnabled;
		property VideoFrameType VideoFormatPreference;
		property bool IsVideoRotationApplied;
		property bool IsVideoMirrorApplied;
		property bool IsMultipleChannelVideoFrameWanted;
		property bool IsMultipleChannelAudioFrameWanted;
		property UINT ObservedVideoFramePosition;

		//媒体附属信息
		property int MaxMetadataSize;
		Func<ClrMetadata^, bool>^ onReadyToSendMetadata;
		Action<ClrMetadata^>^ onMetadataReceived;

		//直播水印
		int addVideoWatermark(String^ url, ClrWatermarkOptions^ options);
		int clearVideoWatermarks();

		//视频截图
		int takeSnapshot(String^ channel, UINT uid, String^ path);
		AT<String^, UINT, String^, int, int, int>::Type^ onSnapshotTaken;

		//加密
		int enableEncryption(bool enabled, ClrEncryptionConfig^ config);


		//音频录制
		[[DEPRECATED]]
		int startAudioRecording(String^ path, int sampleRate, AudioRecordingQualityType quality);
		int startAudioRecording(ClrAudioRecordingConfiguration config);
		int stopAudioRecording();

		//音视频录制
		AgoraClrMediaRecorder^ getMediaRecorder();

		//直播导入在线媒体流
		int addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config);
		int removeInjectStreamUrl(String^ url);
		onStreamInjectedStatus^ onStreamInjectedStatus;

		//摄像头控制, 只适用于Android与iOS,所以没有实现
		//onCameraFocusAreaChanged^ onCameraFocusAreaChanged;

		//设备管理, 设备管理的一部分接口是在这两个类里面的
		AgoraClrAudioDeviceManager^ getAudioDeviceManager();
		AgoraClrVideoDeviceManager^ getVideoDeviceManager();
		onAudioDeviceStateChanged^ onAudioDeviceStateChanged;
		onVideoDeviceStateChanged^ onVideoDeviceStateChanged;
		onAudioDeviceVolumeChanged^ onAudioDeviceVolumeChanged;

		//流消息
		[[deprecated]]
		int createDataStream(int% id, bool reliable, bool ordered);
		int createDataStream(int% id, ClrDataStreamConfig config);
		int sendStreamMessage(int id, String^ data);
		onStreamMessage^ onStreamMessage;
		onStreamMessageError^ onStreamMessageError;

		//其他音频控制
		int enableLoopbackRecording(bool enabled, String^ name);
		//只在iOS上有
		//int setAudioSessionOperationRestriction(EnumAudioSessionOperationRestriction restriction);

		//其他视频控制
		int setLocalVideoMirrorMode(EnumVideoMirrorModeType mode); //这个在3.0上好像没有
		int setCameraCapturerConfiguration(ClrCameraCaptureConfiguration^ config);

		//其他方法
		int setCloudProxy(EnumCloudProxyType type);
		int enableDeepLearningDenoise(bool enable);
		int sendCustomReportMessage(String^ id, String^ category, String^ event, String^ label, int value);
		int getCallId(String^% callid);
		int rate(String^ callid, int rating, String^ desc);
		int complain(String^ callid, String^ desc);
		String^ getVersion(int% build);
		[[deprecated]]
		int setLogFile(String^ path);
		[[deprecated]]
		int setLogFilter(unsigned int filter);
		[[deprecated]]
		int setLogFileSize(unsigned int size);
		String^ getErrorDescription(int code);

		//其他事件
		onWarning^ onWarning;
		onError^ onError;
		onApiCallExecuted^ onApiCallExecuted;

		//定制方法
		//setParameters方法不实现

		//PacketObserver Part
		onSendAudioPacket^ onSendAudioPacket;
		onSendVideoPacket^ onSendVideoPacket;
		onReceiveAudioPacket^ onReceiveAudioPacket;
		onReceiveVideoPacket^ onReceiveVideoPacket;

		//以下是暂时没有地方认领的方法与事件, 可能以后就不存在了, 谨慎调用
		int setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate);
		int startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect, int bitrate);
		int setVideoProfile(VideoProfile profile, bool swapWidthAndHeight);
		int setVideoQualityParameters(bool preferFrameRateOverImageQuality);
		[ObsoleteAttribute()]
		int setEncryptionSecret(String^ key);
		[ObsoleteAttribute()]
		int setEncryptionMode(String^ mode);
		//int setPlaybackDeviceVolume(int volume);

		onAudioQuality^ onAudioQuality;
		onFirstRemoteVideoDecoded^ onFirstRemoteVideoDecoded;
		onUserEnableVideo^ onUserEnableVideo;
		onCameraReady^ onCameraReady;
		onVideoStopped^ onVideoStopped;
		onConnectionInterrupted^ onConnectionInterrupted;
		onConnectionBanned^ onConnectionBanned;
		onRequestChannelKey^ onRequestChannelKey;
		onAudioMixingFinished^ onAudioMixingFinished;
		onStreamUnpublished^ onStreamUnpublished;
		onStreamPublished^ onStreamPublished;
		onUserEnableLocalVideo^ onUserEnableLocalVideo;
		onVideoSizeChanged^ onVideoSizeChanged;
		onRemoteAudioTransportStats^ onRemoteAudioTransportStats;
		onRemoteVideoTransportStats^ onRemoteVideoTransportStats;
		onAudioMixingBegin^ onAudioMixingBegin;
		onAudioMixingEnd^ onAudioMixingEnd;
		onMediaEngineLoadSuccess^ onMediaEngineLoadSuccess;
		onMediaEngineStartCallSuccess^ onMediaEngineStartCallSuccess;

	private:
		agora::rtc::IRtcEngine* rtcEngine;

		AgoraClrEventHandler* agoraEventHandler;
		AgoraClrPacketObserver* agoraPacketObserver;
		AgoraClrAudioFrameObserver* agoraAudioObserver;
		AgoraClrVideoFrameObserver* agoraVideoObserver;
		AgoraClrMetadataObserver* agoraMetadataObserver;

		agora::media::IMediaEngine* agoraMediaEngine;

		List<GCHandle>^ gchs;

		InnerVideoSource^ innerVideoSoruce;
		InnerVideoSink^ innerLocalVideoSink;
		InnerVideoSink^ innerRemoteVideoSink;

		//Native Agora Event Handler
		void NativeOnJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		void NativeOnRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		void NativeOnWarning(int warn, const char* msg);
		void NativeOnError(int err, const char* msg);
		void NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
		void NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
		void NativeOnLeaveChannel(const agora::rtc::RtcStats& stats);
		void NativeOnRtcStats(const agora::rtc::RtcStats& stats);
		void NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnLastmileQuality(int quality);
		void NativeOnNetworkQuality(uid_t uid, int txQuality, int rxQuality);
		void NativeOnFirstLocalVideoFrame(int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
		void NativeOnUserJoined(uid_t uid, int elapsed);
		void NativeOnUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
		void NativeOnUserMuteAudio(uid_t uid, bool muted);
		void NativeOnUserMuteVideo(uid_t uid, bool muted);
		void NativeOnUserEnableVideo(uid_t uid, bool enabled);
		void NativeOnApiCallExecuted(int err, const char* api, const char* result);
		void NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats);
		void NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats);
		void NativeOnCameraReady();
		void NativeOnVideoStopped();
		void NativeOnConnectionLost();
		void NativeOnConnectionBanned();

		void NativeOnConnectionInterrupted();
		void NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length);
		void NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached);
		void NativeOnRequestChannelKey();
		void NativeOnRequestToken();

		void NativeOnAudioMixingFinished();

		void NativeOnActiveSpeaker(uid_t uid);

		void NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
		void NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);

		void NativeOnStreamUnpublished(const char* url);
		void NativeOnStreamPublished(const char* url, int error);
		void NativeOnTranscodingUpdated();

		void NativeOnConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
		void NativeOnTokenPrivilegeWillExpire(const char* token);
		void NativeOnFirstLocalAudioFrame(int elapsed);
		void NativeOnFirstRemoteAudioFrame(uid_t uid, int elapsed);
		void NativeOnUserEnableLocalVideo(uid_t uid, bool enabled);
		void NativeOnVideoSizeChanged(uid_t uid, int width, int height, int rotation);
		void NativeOnRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed);
		void NativeOnLocalPublishFallbackToAudioOnly(bool);
		void NativeOnRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover);
		void NativeOnRemoteAudioStats(const RemoteAudioStats& stats);
		void NativeOnRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		void NativeOnRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		void NativeOnAudioMixingBegin();
		void NativeOnAudioMixingEnd();
		void NativeOnAudioEffectFinished(int soundId);
		void NativeOnStreamInjectedStatus(const char* url, uid_t uid, int status);
		void NativeOnMediaEngineLoadSuccess();
		void NativeOnMediaEngineStartCallSuccess();

		bool NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet);

		bool NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);

		bool NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnPreEncodeVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnGetSmoothRenderingEnabled();
		bool NativeOnRenderVideoFrame(uid_t uid, agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnRenderVideoFrameEx(const char* channelId,uid_t uid, agora::media::IVideoFrameObserver::VideoFrame& frame);
		IVideoFrameObserver::VIDEO_FRAME_TYPE NativeOnGetVideoFormatPreference();
		bool NativeOnGetRotationApplied();
		bool NativeOnGetMirrorApplied();
		bool NativeIsMultipleChannelVideoFrameWanted();
		bool NativeIsMultipleChannelAudioFrameWanted();
		UINT NativeObservedVideoFramePosition();
		

		void NativeOnNetworkTypeChanged(agora::rtc::NETWORK_TYPE type);
		void NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error);
		void NativeOnLocalVideoStateChanged(agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error);
		void NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed);
		void NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed);
		void NativeOnLocalAudioStats(const LocalAudioStats& stats);
		void NativeOnAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_REASON_TYPE reason);
		void NativeOnRemoteAudioMixingBegin();
		void NativeOnRemoteAudioMixingEnd();
		void NativeOnRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE error);
		void NativeOnChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error);
		void NativeOnChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event);
		void NativeOnLastmileProbeResult(const LastmileProbeResult& result);

		int NativeGetMaxMetadataSize();
		bool NativeOnReadyToSendMetadata(IMetadataObserver::Metadata& metadata);
		void NativeOnMetadataReceived(const IMetadataObserver::Metadata& metadata);

		void NativeOnAudioPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState);
		void NativeOnVideoPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState);
		void NativeOnAudioSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState);
		void NativeOnVideoSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState);
		void NativeOnFirstLocalAudioFramePublished(int elapse);
		void NativeOnFirstLocalVideoFramePublished(int elapse);

		void NativeOnRtmpStreamingEvent(const char* url, RTMP_STREAMING_EVENT code);
		void NativeOnRequestAudioFileInfo(const AudioFileInfo& info, AUDIO_FILE_INFO_ERROR error);

		void NativeOnSnapshotTaken(const char* channel, uid_t uid, const char* filePath, int width, int height, int errCode);

		void initializeEventHandler();
		void initializePacketObserver();
		void initializeRawFrameObserver();
		void initializeMetaObserver();
		void* regEvent(Object^ obj);
	};
} // namespace AgoraClrLibrary
