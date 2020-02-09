// AgoraClrLibrary.h

#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrLibraryEnum.h"
#include "AgoraClrLibraryTypes.h"
#include "AgoraClrLibraryDelegates.h"

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
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
		int initialize(String^ vendorkey);
		void release();
		int setChannelProfile(ChannelProfile profile);
		int setClientRole(ClientRoleType role);
		int joinChannel(String^ token, String^ channelName, String^ channelInfo, int uid);
		int switchChannel(String^ token, String^ channelId);
		int leaveChannel();
		int renewToken(String^ token);
		int enableWebSdkInteroperability(bool enabled);
		ConnectionStateType getConnectionState();

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
		int adjustPlaybackSignalVolume(int volume);
		int enableLocalAudio(bool enabled);
		int muteLocalAudioStream(bool mute);
		int muteRemoteAudioStream(int uid, bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		int setDefaultMuteAllRemoteAudioStreams(bool mute);

		//视频管理方法
		int enableVideo();
		int disableVideo();
		int setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config);
		int setupLocalVideo(IntPtr view, int renderMode, int uid);
		int setupRemoteVideo(IntPtr view, int renderMode, int uid);
		int setLocalRenderMode(RenderMode mode);
		int setRemoteRenderMode(int uid, RenderMode mode);
		int startPreview();
		int stopPreview();
		int enableLocalVideo(bool enabled);
		int muteLocalVideoStream(bool mute);
		int muteRemoteVideoStream(int uid, bool mute);
		int muteAllRemoteVideoStreams(bool mute);
		int setDefaultMuteAllRemoteVideoStreams(bool mute);

		//本地媒体事件
		onLocalAudioStateChanged^ onLocalAudioStateChanged;
		onLocalVideoStateChanged^ onLocalVideoStateChanged;
		onFirstLocalVideoFrame^ onFirstLocalVideoFrame;
		onFirstLocalAudioFrame^ onFirstLocalAudioFrame;

		//远端媒体事件
		onRemoteAudioStateChanged^ onRemoteAudioStateChanged;
		onRemoteVideoStateChanged^ onRemoteVideoStateChanged;
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
		//setBeautyEffectOptions 在2.9.1上只适配iOS与Android,所以不添加

		//屏幕共享
		//startScreenCaptureByDisplayId 只在macos上有效,所以不添加
		int startScreenCaptureByScreenRect(ClrRectangle^ screenRect, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params);
		int startScreenCaptureByWindowId(IntPtr windowId, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params);
		int setScreenCaptureContentHint(ClrVideoContentHint hint);
		int updateScreenCaptureParameters(ClrScreenCaptureParameters^ params);
		int updateScreenCaptureRegion(ClrRectangle^ rect);
		int stopScreenCapture();

		//音乐文件播放及混音
		int startAudioMixing(String^ path, bool loop, bool replace, int cycle);
		int stopAudioMixing();
		int pauseAudioMixing();
		int resumeAudioMixing();
		int adjustAudioMixingVolume(int volume);
		int adjustAudioMixingPlayoutVolume(int volume);
		int adjustAudioMixingPublishVolume(int volume);
		int getAudioMixingPlayoutVolume();
		int getAudioMixingPublishVolume();
		int getAudioMixingDuration();
		int getAudioMixingCurrentPosition();
		int setAudioMixingPosition(int pos);

		//音乐文件播放及混音事件
		onAudioMixingStateChanged^ onAudioMixingStateChanged;
		Action^ onRemoteAudioMixingBegin;
		Action^ onRemoteAudioMixingEnd;

		//音效文件播放管理
		int getEffectsVolume();
		int setEffectsVolume(int volume);
		int setVolumeOfEffect(int soundId, int volume);
		int playEffect(int soundId, String^ file, int loopCount, double pitch, double pan, int gain, bool publish);
		int stopEffect(int soundId);
		int stopAllEffects();
		int preloadEffect(int soundId, String^ file);
		int unloadEffect(int soundId);
		int pauseEffect(int soundId);
		int pauseAllEffects();
		int resumeEffect(int soundId);
		int resumeAllEffects();

		//音效文件播放管理事件
		onAudioEffectFinished^ onAudioEffectFinished;

		//变声与混响
		int setLocalVoiceChanger(VoiceChangerPreset changer);
		int setLocalVoiceReverbPreset(AudioReverbPreset preset);
		int setLocalVoicePitch(double pitch);
		int setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain);
		int setLocalVoiceReverb(AudioReverbType type, int value);

		//听声辩位
		int enableSoundPositionIndication(bool enabled);
		int setRemoteVoicePosition(uid_t uid, double pan, double gain);


		//CDN推流
		int setLiveTranscoding(ClrLiveTranscoding^ transcoding);
		int addPublishStreamUrl(String^ url, bool transcodingEnabled);
		int removePublishStreamUrl(String^ url);

		//CDN推流事件
		Action<String^, RtmpStreamPublishState, RtmpStreamPublishError>^ onRtmpStreamingStateChanged;
		onTranscodingUpdated^ onTranscodingUpdated;

		//跨频道媒体流转发
		int startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int stopChannelMediaRelay();

		//跨频道媒体流转发事件
		Action<ChannelMediaRelayState, ChannelMediaRelayError>^ onChannelMediaRelayStateChanged;
		Action<ChannelMediaRelayEvent>^ onChannelMediaRelayEvent;

		//音量提示

		int setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate);


		int startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect, int bitrate);

		int setEncryptionSecret(String^ key);
		int setEncryptionMode(String^ mode);

		int getCallId(String^% callid);
		int rate(String^ callid, int rating, String^ desc);
		int complain(String^ callid, String^ desc);
		int startEchoTest();
		int stopEchoTest();
		int enableLastmileTest();
		int disableLastmileTest();

		int setVideoProfile(VideoProfile profile, bool swapWidthAndHeight);

		int enableDualStreamMode(bool enabled);
		int setRemoteVideoStreamType(int uid, RemoteVideoStreamType type);
		int setVideoQualityParameters(bool preferFrameRateOverImageQuality);
		int setVideoCompositingLayout(ClrVideoCompositingLayout^ sei);
		int clearVideoCompositingLayout();
		int configPublisher(ClrPublisherConfiguration^ config);

		int createDataStream(int% id);
		int sendStreamMessage(int id, String^ data);

		//Ô­Ê¼Êý¾ÝAPI
		//RtcEngineParameters Part
		int setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);

		int setPlaybackDeviceVolume(int volume);
		int enableAudioVolumeIndication(int interval, int smooth);
		int startAudioRecording(String^ path, AudioRecordingQualityType quality);
		int stopAudioRecording();

		int setLogFile(String^ path);
		int setLogFilter(unsigned int filter);

		int setInEarMonitoringVolume(int volume);

		int setExternalAudioSource(bool enabled, int sampleRate, int channels);

		int setLocalVideoMirrorMode(VideoMirrorModeType mode);
		String^ getVersion(int% build);
		int enableLoopbackRecording(bool enabled);

		int pushAudioFrame(ClrAudioFrameType type, ClrAudioFrame^ frame, bool wrap);

		int addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config);
		int removeInjectStreamUrl(String^ url);

		//2.3

		int setExternalAudioSink(bool enabled, int sampleRate, int channels);
		int setExternalVideoSource(bool enabled, bool useTexture);
		int pushVideoFrame(ClrExternalVideoFrame^ frame);
		int addVideoWatermark(ClrRtcImage^ image);
		int clearVideoWatermark();

		int setLocalPublishFallbackOption(StreamFallbackOptions option);
		int setRemoteSubscribeFallbackOption(StreamFallbackOptions option);
		int setRemoteDefaultVideoStreamType(RemoteVideoStreamType type);
		String^ getErrorDescription(int code);

		AgoraClrAudioDeviceManager^ getAudioDeviceManager();
		AgoraClrVideoDeviceManager^ getVideoDeviceManager();
		IRtcEngine* getEngine();

		//RtcEngineEventHandler Part

		onWarning^ onWarning;
		onError^ onError;
		onAudioQuality^ onAudioQuality;
		onAudioVolumeIndication^ onAudioVolumeIndication;


		onFirstRemoteVideoDecoded^ onFirstRemoteVideoDecoded;
		onAudioDeviceStateChanged^ onAudioDeviceStateChanged;
		onVideoDeviceStateChanged^ onVideoDeviceStateChanged;
		onLastmileQuality^ onLastmileQuality;
		onUserEnableVideo^ onUserEnableVideo;
		onCameraReady^ onCameraReady;
		onVideoStopped^ onVideoStopped;
		onConnectionInterrupted^ onConnectionInterrupted;
		onConnectionBanned^ onConnectionBanned;

		onApiCallExecuted^ onApiCallExecuted;
		onStreamMessage^ onStreamMessage;
		onStreamMessageError^ onStreamMessageError;
		onRequestChannelKey^ onRequestChannelKey;

		onAudioMixingFinished^ onAudioMixingFinished;

		onActiveSpeaker^ onActiveSpeaker;

		onAudioDeviceVolumeChanged^ onAudioDeviceVolumeChanged;

		onStreamUnpublished^ onStreamUnpublished;
		onStreamPublished^ onStreamPublished;

		onUserEnableLocalVideo^ onUserEnableLocalVideo;
		onVideoSizeChanged^ onVideoSizeChanged;
		onLocalPublishFallbackToAudioOnly^ onLocalPublishFallbackToAudioOnly;
		onRemoteSubscribeFallbackToAudioOnly^ onRemoteSubscribeFallbackToAudioOnly;
		onCameraFocusAreaChanged^ onCameraFocusAreaChanged;

		onRemoteAudioTransportStats^ onRemoteAudioTransportStats;
		onRemoteVideoTransportStats^ onRemoteVideoTransportStats;
		onAudioMixingBegin^ onAudioMixingBegin;
		onAudioMixingEnd^ onAudioMixingEnd;
		onStreamInjectedStatus^ onStreamInjectedStatus;
		onMediaEngineLoadSuccess^ onMediaEngineLoadSuccess;
		onMediaEngineStartCallSuccess^ onMediaEngineStartCallSuccess;

		//PacketObserver Part
		onSendAudioPacket^ onSendAudioPacket;
		onSendVideoPacket^ onSendVideoPacket;
		onReceiveAudioPacket^ onReceiveAudioPacket;
		onReceiveVideoPacket^ onReceiveVideoPacket;

		//Raw data Part
		onRecordAudioFrame^ onRecordAudioFrame;
		onPlaybackAudioFrame^ onPlaybackAudioFrame;
		onPlaybackAudioFrameBeforeMixing^ onPlaybackAudioFrameBeforeMixing;
		onMixedAudioFrame^ onMixedAudioFrame;

		onCaptureVideoFrame^ onCaptureVideoFrame;
		onRenderVideoFrame^ onRenderVideoFrame;

	private:
		agora::rtc::IRtcEngine* rtcEngine;

		AgoraClrEventHandler* agoraEventHandler;
		AgoraClrPacketObserver* agoraPacketObserver;
		AgoraClrRawFrameObserver* agoraRawObserver;
		agora::media::IMediaEngine* agoraMediaEngine;

		List<GCHandle>^ gchs;

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
		void NativeOnApiCallExecuted(const char* api, int error);
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
		void NativeOnCameraFocusAreaChanged(int x, int y, int width, int height);
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
		bool NativeOnRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& frame);

		void NativeOnNetworkTypeChanged(agora::rtc::NETWORK_TYPE type);
		void NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error);
		void NativeOnLocalVideoStateChanged(agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error);
		void NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed);
		void NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed);
		void NativeOnLocalAudioStats(const LocalAudioStats& stats);
		void NativeOnAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error);
		void NativeOnRemoteAudioMixingBegin();
		void NativeOnRemoteAudioMixingEnd();
		void NativeOnRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error);
		void NativeOnChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error);
		void NativeOnChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event);

		void initializeEventHandler();
		void initializePacketObserver();
		void initializeRawFrameObserver();
		void* regEvent(Object^ obj);
	};
} // namespace AgoraClrLibrary
