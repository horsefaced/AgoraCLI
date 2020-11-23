#include "stdafx.h"
#include "AgoraClrEventHandler.h"
using namespace AgoraClrLibrary;

AgoraClrEventHandler::AgoraClrEventHandler()
{
}

AgoraClrEventHandler::~AgoraClrEventHandler()
{
}

void AgoraClrEventHandler::onJoinChannelSuccess(const char * channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccessEvent) onJoinChannelSuccessEvent(channel, uid, elapsed);
}

void AgoraClrEventHandler::onRejoinChannelSuccess(const char * channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccessEvent) onRejoinChannelSuccessEvent(channel, uid, elapsed);
}

void AgoraClrEventHandler::onWarning(int warn, const char * msg)
{
	if (onWarningEvent) onWarningEvent(warn, msg);
}

void AgoraClrEventHandler::onError(int err, const char* msg) {
	if (onErrorEvent) onErrorEvent(err, msg);
}
void AgoraClrEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {
	if (onAudioQualityEvent) onAudioQualityEvent(uid, quality, delay, lost);
}
void AgoraClrEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
	if (onAudioVolumeIndicationEvent) onAudioVolumeIndicationEvent(speakers, speakerNumber, totalVolume);
}
void AgoraClrEventHandler::onLeaveChannel(const RtcStats& stats) {
	if (onLeaveChannelEvent) onLeaveChannelEvent(stats);
}
void AgoraClrEventHandler::onRtcStats(const RtcStats& stats) {
	if (onRtcStatsEvent) onRtcStatsEvent(stats);
}
void AgoraClrEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
	if (onAudioDeviceStateChangedEvent) onAudioDeviceStateChangedEvent(deviceId, deviceType, deviceState);
}
void AgoraClrEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
	if (onVideoDeviceStateChangedEvent) onVideoDeviceStateChangedEvent(deviceId, deviceType, deviceState);
}
void AgoraClrEventHandler::onLastmileQuality(int quality) {
	if (onLastmileQualityEvent) onLastmileQualityEvent(quality);
}
void AgoraClrEventHandler::onNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQualityEvent) onNetworkQualityEvent(uid, txQuality, rxQuality);
}
void AgoraClrEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed) {
	if (onFirstLocalVideoFrameEvent) onFirstLocalVideoFrameEvent(width, height, elapsed);
}
void AgoraClrEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) {
	if (onFirstRemoteVideoDecodedEvent) onFirstRemoteVideoDecodedEvent(uid, width, height, elapsed);
}
void AgoraClrEventHandler::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {
	if (onFirstRemoteVideoFrameEvent) onFirstRemoteVideoFrameEvent(uid, width, height, elapsed);
}
void AgoraClrEventHandler::onUserJoined(uid_t uid, int elapsed) {
	if (onUserJoinedEvent) onUserJoinedEvent(uid, elapsed);
}
void AgoraClrEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
	if (onUserOfflineEvent) onUserOfflineEvent(uid, reason);
}
void AgoraClrEventHandler::onUserMuteAudio(uid_t uid, bool muted) {
	if (onUserMuteAudioEvent) onUserMuteAudioEvent(uid, muted);
}
void AgoraClrEventHandler::onUserMuteVideo(uid_t uid, bool muted) {
	if (onUserMuteVideoEvent) onUserMuteVideoEvent(uid, muted);
}
void AgoraClrEventHandler::onUserEnableVideo(uid_t uid, bool enabled) {
	if (onUserEnableVideoEvent) onUserEnableVideoEvent(uid, enabled);
}
void AgoraClrEventHandler::onApiCallExecuted(int err, const char* api, const char* result) {
	if (onApiCallExecutedEvent) onApiCallExecutedEvent(err, api, result);
}
void AgoraClrEventHandler::onLocalVideoStats(const LocalVideoStats& stats) {
	if (onLocalVideoStatsEvent) onLocalVideoStatsEvent(stats);
}
void AgoraClrEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats) {
	if (onRemoteVideoStatsEvent) onRemoteVideoStatsEvent(stats);
}
void AgoraClrEventHandler::onCameraReady() {
	if (onCameraReadyEvent) onCameraReadyEvent();
}
void AgoraClrEventHandler::onVideoStopped() {
	if (onVideoStoppedEvent) onVideoStoppedEvent();
}
void AgoraClrEventHandler::onConnectionLost() {
	if (onConnectionLostEvent) onConnectionLostEvent();
}
void AgoraClrEventHandler::onConnectionInterrupted() {
	if (onConnectionInterruptedEvent) onConnectionLostEvent();
}
void AgoraClrEventHandler::onConnectionBanned()
{
	if (onConnectionBannedEvent) onConnectionBannedEvent();
}
void AgoraClrEventHandler::onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) {
	if (onStreamMessageEvent) onStreamMessageEvent(uid, streamId, data, length);
}
void AgoraClrEventHandler::onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) {
	if (onStreamMessageErrorEvent) onStreamMessageErrorEvent(uid, streamId, code, missed, cached);
}

void AgoraClrEventHandler::onRequestToken()
{
	if (onRequestTokenEvent) onRequestTokenEvent();
}

void AgoraClrEventHandler::onAudioMixingFinished()
{
	if (onAudioMixingFinishedEvent) onAudioMixingFinishedEvent();
}

void AgoraClrEventHandler::onActiveSpeaker(uid_t uid)
{
	if (onActiveSpeakerEvent) onActiveSpeakerEvent(uid);
}

void AgoraClrEventHandler::onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	if (onClientRoleChangedEvent) onClientRoleChangedEvent(oldRole, newRole);
}

void AgoraClrEventHandler::onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChangedEvent) onAudioDeviceVolumeChangedEvent(deviceType, volume, muted);
}

void AgoraClrEventHandler::onStreamUnpublished(const char * url)
{
	if (onStreamUnpublishedEvent) onStreamUnpublishedEvent(url);
}

void AgoraClrEventHandler::onStreamPublished(const char * url, int error)
{
	if (onStreamPublishedEvent) onStreamPublishedEvent(url, error);
}

void AgoraClrEventHandler::onTranscodingUpdated()
{
	if (onTranscodingUpdatedEvent) onTranscodingUpdatedEvent();
}

void AgoraClrEventHandler::onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (onConnectionStateChangedEvent) onConnectionStateChangedEvent(state, reason);
}

void AgoraClrEventHandler::onTokenPrivilegeWillExpire(const char * token)
{
	if (onTokenPrivilegeWillExpireEvent) onTokenPrivilegeWillExpireEvent(token);
}

void AgoraClrEventHandler::onFirstLocalAudioFrame(int elapsed)
{
	if (onFirstLocalAudioFrameEvent) onFirstLocalAudioFrameEvent(elapsed);
}

void AgoraClrEventHandler::onFirstRemoteAudioFrame(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioFrameEvent) onFirstRemoteAudioFrameEvent(uid, elapsed);
}

void AgoraClrEventHandler::onUserEnableLocalVideo(uid_t uid, bool enabled)
{
	if (onUserEnableLocalVideoEvent) onUserEnableLocalVideoEvent(uid, enabled);
}

void AgoraClrEventHandler::onVideoSizeChanged(uid_t uid, int width, int height, int rotation)
{
	if (onVideoSizeChangedEvent) onVideoSizeChangedEvent(uid, width, height, rotation);
}

void AgoraClrEventHandler::onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	if (onRemoteVideoStateChangedEvent) onRemoteVideoStateChangedEvent(uid, state, reason, elapsed);
}

void AgoraClrEventHandler::onLocalPublishFallbackToAudioOnly(bool fallbackOrRecover)
{
	if (onLocalPublishFallbackToAudioOnlyEvent) onLocalPublishFallbackToAudioOnlyEvent(fallbackOrRecover);
}

void AgoraClrEventHandler::onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover)
{
	if (onRemoteSubscribeFallbackToAudioOnlyEvent) onRemoteSubscribeFallbackToAudioOnlyEvent(uid, isFallbackOrRecover);
}

void AgoraClrEventHandler::onRemoteAudioStats(const RemoteAudioStats & stats)
{
	if (onRemoteAudioStatsEvent) onRemoteAudioStatsEvent(stats);
}

void AgoraClrEventHandler::onRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteAudioTransportStatsEvent) onRemoteAudioTransportStatsEvent(uid, delay, lost, rxKBitRate);
}

void AgoraClrEventHandler::onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteVideoTransportStatsEvent) onRemoteVideoTransportStatsEvent(uid, delay, lost, rxKBitRate);
}

void AgoraClrEventHandler::onAudioEffectFinished(int soundId)
{
	if (onAudioEffectFinishedEvent) onAudioEffectFinishedEvent(soundId);
}

void AgoraClrEventHandler::onStreamInjectedStatus(const char * url, uid_t uid, int status)
{
	if (onStreamInjectedStatusEvent) onStreamInjectedStatusEvent(url, uid, status);
}

void AgoraClrEventHandler::onMediaEngineLoadSuccess()
{
	if (onMediaEngineLoadSuccessEvent) onMediaEngineLoadSuccessEvent();
}

void AgoraClrEventHandler::onMediaEngineStartCallSuccess()
{
	if (onMediaEngineStartCallSuccessEvent) onMediaEngineStartCallSuccessEvent();
}

void AgoraClrEventHandler::onNetworkTypeChanged(NETWORK_TYPE type)
{
	if (onNetworkTypeChangedEvent) onNetworkTypeChangedEvent(type);
}

void AgoraClrEventHandler::onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error)
{
	if (onLocalAudioStateChangedEvent) onLocalAudioStateChangedEvent(state, error);
}

void AgoraClrEventHandler::onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
{
	if (onLocalVideoStateChangedEvent) onLocalVideoStateChangedEvent(state, error);
}

void AgoraClrEventHandler::onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChangedEvent) onRemoteAudioStateChangedEvent(uid, state, reason, elapsed);
}

void AgoraClrEventHandler::onFirstRemoteAudioDecoded(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioDecodedEvent) onFirstRemoteAudioDecodedEvent(uid, elapsed);
}

void AgoraClrEventHandler::onLocalAudioStats(const LocalAudioStats& stats)
{
	if (onLocalAudioStatsEvent) onLocalAudioStatsEvent(stats);
}

void AgoraClrEventHandler::onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error)
{
	if (onAudioMixingStateChangedEvent) onAudioMixingStateChangedEvent(state, error);
}

void AgoraClrEventHandler::onRemoteAudioMixingBegin()
{
	if (onRemoteAudioMixingBeginEvent) onRemoteAudioMixingBeginEvent();
}

void AgoraClrEventHandler::onRemoteAudioMixingEnd()
{
	if (onRemoteAudioMixingEndEvent) onRemoteAudioMixingEndEvent();
}

void AgoraClrEventHandler::onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error)
{
	if (onRtmpStreamingStateChangedEvent) onRtmpStreamingStateChangedEvent(url, state, error);
}

void AgoraClrEventHandler::onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error)
{
	if (onChannelMediaRelayStateChangedEvent) onChannelMediaRelayStateChangedEvent(state, error);
}

void AgoraClrEventHandler::onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event)
{
	if (onChannelMediaRelayEventEvnet) onChannelMediaRelayEventEvnet(event);
}

void AgoraClrEventHandler::onLastmileProbeResult(const LastmileProbeResult& result)
{
	if (onLastmileProbeResultEvent) onLastmileProbeResultEvent(result);
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	if (onAudioPublishStateChangedEvent) onAudioPublishStateChangedEvent(channel, oldState, newState, elapseSinceLastState);
}

void AgoraClrLibrary::AgoraClrEventHandler::onVideoPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	if (onVideoPublishStateChangedEvent) onVideoPublishStateChangedEvent(channel, oldState, newState, elapseSinceLastState);
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	if (onAudioSubscribeStateChangedEvent) onAudioSubscribeStateChangedEvent(channel, uid, oldState, newState, elapseSinceLastState);
}

void AgoraClrLibrary::AgoraClrEventHandler::onVideoSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	if (onVideoSubscribeStateChangedEvent) onVideoSubscribeStateChangedEvent(channel, uid, oldState, newState, elapseSinceLastState);
}

void AgoraClrLibrary::AgoraClrEventHandler::onFirstLocalAudioFramePublished(int elapsed)
{
	if (onFirstLocalAudioFrameEvent) onFirstLocalAudioFrameEvent(elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onFirstLocalVideoFramePublished(int elapsed)
{
	if (onFirstLocalVideoFramePublishedEvent) onFirstLocalVideoFramePublishedEvent(elapsed);
}
