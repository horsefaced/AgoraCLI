#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrLibraryEnum.h"
#include "AgoraClrLibraryTypes.h"

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace agora::rtc;

namespace AgoraClrLibrary {

	//RtcEngineEventHandler Part
	public
		delegate void onJoinChannelSuccess(String^ channel, UINT uid, int elapsed);
	public
		delegate void onRejoinChannelSuccess(String^ channel, UINT uid, int elapsed);
	public
		delegate void onWarning(int warn, String^ msg);
	public
		delegate void onError(int err, String^ msg);
	public
		delegate void onAudioQuality(UINT uid, int quality, unsigned short delay, unsigned short lost);
	public
		delegate void onAudioVolumeIndication(List<ClrAudioVolumeInfo^>^ speakers, int totalVolume);
	public
		delegate void onLeaveChannel(ClrRtcStats^ stat);
	public
		delegate void onUserJoined(UINT uid, int elapsed);
	public
		delegate void onUserOffline(UINT uid, UserOfflineType reason);
	public
		delegate void onRtcStats(ClrRtcStats^ stat);
	public
		delegate void onLocalVideoStats(ClrLocalVideoStats^ stats);
	public
		delegate void onRemoteVideoStats(ClrRemoteVideoStats^ stats);
	public
		delegate void onFirstLocalVideoFrame(int width, int height, int elapsed);
	public
		delegate void onFirstRemoteVideoDecoded(UINT uid, int width, int height, int elapsed);
	public
		delegate void onFirstRemoteVideoFrame(UINT uid, int width, int height, int elapsed);

	public
		delegate void onAudioDeviceStateChanged(String^ deviceid, int deviceType, int deviceState);
	public
		delegate void onVideoDeviceStateChanged(String^ deviceid, int deviceType, int deviceState);

	public
		delegate void onLastmileQuality(int quality);
	public
		delegate void onNetworkQuality(UINT uid, int txQuality, int rxQuality);

	public
		delegate void onUserMuteAudio(UINT uid, bool muted);
	public
		delegate void onUserMuteVideo(UINT uid, bool muted);
	public
		delegate void onUserEnableVideo(UINT uid, bool enabled);
	public
		delegate void onCameraReady();
	public
		delegate void onVideoStopped();
	public
		delegate void onConnectionInterrupted();
	public
		delegate void onConnectionLost();
	public
		delegate void onConnectionBanned();

	public
		delegate void onRefreshRecordingServiceStatus(int status);
	public
		delegate void onApiCallExecuted(int err, String^ api, String^ result);
	public
		delegate void onStreamMessage(UINT uid, int streamId, String^ data);
	public
		delegate void onStreamMessageError(UINT uid, int streamId, int code, int missed, int cached);
	public
		delegate void onRequestChannelKey();
	public
		delegate void onRequestToken();
	public
		delegate void onAudioMixingFinished();

	public
		delegate void onActiveSpeaker(UINT uid);

	public
		delegate void onClientRoleChanged(ClientRoleType, ClientRoleType);
	public
		delegate void onAudioDeviceVolumeChanged(MediaDeviceType, int, bool);

	public
		delegate void onStreamUnpublished(String^ url);
	public
		delegate void onStreamPublished(String^ url, int error);
	public
		delegate void onTranscodingUpdated();

	public
		delegate void onConnectionStateChanged(EnumConnectionStateType state, EnumConnectionChangedReasonType reason);
	public
		delegate void onTokenPrivilegeWillExpire(String^ token);
	public
		delegate void onFirstLocalAudioFrame(int elapsed);
	public
		delegate void onFirstRemoteAudioFrame(UINT uid, int elapsed);
	public
		delegate void onUserEnableLocalVideo(UINT uid, bool enabled);
	public
		delegate void onVideoSizeChanged(UINT uid, int width, int height, int rotation);
	public
		delegate void onRemoteVideoStateChanged(UINT uid, EnumRemoteVideoState state, EnumRemoteVideoStateReason reason, int elapsed);
	public
		delegate void onLocalPublishFallbackToAudioOnly(bool);
	public
		delegate void onRemoteSubscribeFallbackToAudioOnly(UINT uid, bool isFallbackOrRecover);
	public
		delegate void onCameraFocusAreaChanged(int x, int y, int width, int height);
	public
		delegate void onRemoteAudioStats(ClrRemoteAudioStats^ stats);
	public
		delegate void onRemoteAudioTransportStats(UINT uid, short delay, short lost, short rxKBitRate);
	public
		delegate void onRemoteVideoTransportStats(UINT uid, short delay, short lost, short rxKBitRate);
	public
		delegate void onAudioMixingBegin();
	public
		delegate void onAudioMixingEnd();
	public
		delegate void onAudioEffectFinished(int soundId);
	public
		delegate void onStreamInjectedStatus(String^ url, UINT uid, int status);
	public
		delegate void onMediaEngineLoadSuccess();
	public
		delegate void onMediaEngineStartCallSuccess();

	//PacketObserver Part
	public
		delegate bool onSendAudioPacket(ClrPacket^ packet);
	public
		delegate bool onSendVideoPacket(ClrPacket^ packet);
	public
		delegate bool onReceiveAudioPacket(ClrPacket^ packet);
	public
		delegate bool onReceiveVideoPacket(ClrPacket^ packet);

	//Raw Data Part
	public
		delegate bool onRecordAudioFrame(ClrAudioFrame^ frame);
	public
		delegate bool onPlaybackAudioFrame(ClrAudioFrame^ frame);
	public
		delegate bool onPlaybackAudioFrameBeforeMixing(UINT uid, ClrAudioFrame^ frame);
	public
		delegate bool onMixedAudioFrame(ClrAudioFrame^ frame);

	public
		delegate bool onCaptureVideoFrame(ClrVideoFrame^ frame);
	public
		delegate bool onPreEncodeVideoFrame(ClrVideoFrame^ frame);
	public
		delegate bool onGetSmoothRenderingEnabled();
	public
		delegate bool onRenderVideoFrame(UINT uid, ClrVideoFrame^ frame);
	public delegate bool onRenderVideoFrameEx(String^channelId,UINT uid, ClrVideoFrame^ frame);

	public
		delegate void onNetworkTypeChanged(NetworkType type);

	public
		delegate void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error);

	public
		delegate void onLocalVideoStateChanged(LocalVideoStreamState state, LocalVideoStreamError error);

	public delegate void onRemoteAudioStateChanged(uid_t, EnumRemoteAudioState, EnumRemoteAudioStateReason, int);

	public delegate void onFirstRemoteAudioDecoded(uid_t, int);

	public delegate void onLocalAudioStats(ClrLocalAudioStats^ stats);

	public delegate void onAudioMixingStateChanged(AudioMixingStateType state, AudioMixingErrorType error);

	public delegate void onRtmpStreamingStateChanged(String^, EnumRtmpStreamPublishState, EnumRtmpStreamPublishError);

	public delegate void onChannelMediaRelayStateChanged(EnumChannelMediaRelayState, EnumChannelMediaRelayError);

}