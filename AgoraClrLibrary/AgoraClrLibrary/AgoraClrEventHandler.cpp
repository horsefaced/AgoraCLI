#include "stdafx.h"
#include "AgoraClrEventHandler.h"

AgoraClrLibrary::AgoraClrEventHandler::AgoraClrEventHandler()
{
}

AgoraClrLibrary::AgoraClrEventHandler::~AgoraClrEventHandler()
{
}

void AgoraClrLibrary::AgoraClrEventHandler::onJoinChannelSuccess(const char * channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccessEvent) onJoinChannelSuccessEvent(channel, uid, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRejoinChannelSuccess(const char * channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccessEvent) onRejoinChannelSuccessEvent(channel, uid, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onWarning(int warn, const char * msg)
{
	if (onWarningEvent) onWarningEvent(warn, msg);
}

void AgoraClrLibrary::AgoraClrEventHandler::onError(int err, const char* msg) {
	if (onErrorEvent) onErrorEvent(err, msg);
}
void AgoraClrLibrary::AgoraClrEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {
	if (onAudioQualityEvent) onAudioQualityEvent(uid, quality, delay, lost);
}
void AgoraClrLibrary::AgoraClrEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
	if (onAudioVolumeIndicationEvent) onAudioVolumeIndicationEvent(speakers, speakerNumber, totalVolume);
}
void AgoraClrLibrary::AgoraClrEventHandler::onLeaveChannel(const RtcStats& stats) {
	if (onLeaveChannelEvent) onLeaveChannelEvent(stats);
}
void AgoraClrLibrary::AgoraClrEventHandler::onRtcStats(const RtcStats& stats) {
	if (onRtcStatsEvent) onRtcStatsEvent(stats);
}
void AgoraClrLibrary::AgoraClrEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
	if (onAudioDeviceStateChangedEvent) onAudioDeviceStateChangedEvent(deviceId, deviceType, deviceState);
}
void AgoraClrLibrary::AgoraClrEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
	if (onVideoDeviceStateChangedEvent) onVideoDeviceStateChangedEvent(deviceId, deviceType, deviceState);
}
void AgoraClrLibrary::AgoraClrEventHandler::onLastmileQuality(int quality) {
	if (onLastmileQualityEvent) onLastmileQualityEvent(quality);
}
void AgoraClrLibrary::AgoraClrEventHandler::onNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQualityEvent) onNetworkQualityEvent(uid, txQuality, rxQuality);
}
void AgoraClrLibrary::AgoraClrEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed) {
	if (onFirstLocalVideoFrameEvent) onFirstLocalVideoFrameEvent(width, height, elapsed);
}
void AgoraClrLibrary::AgoraClrEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) {
	if (onFirstRemoteVideoDecodedEvent) onFirstRemoteVideoDecodedEvent(uid, width, height, elapsed);
}
void AgoraClrLibrary::AgoraClrEventHandler::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {
	if (onFirstRemoteVideoFrameEvent) onFirstRemoteVideoFrameEvent(uid, width, height, elapsed);
}
void AgoraClrLibrary::AgoraClrEventHandler::onUserJoined(uid_t uid, int elapsed) {
	if (onUserJoinedEvent) onUserJoinedEvent(uid, elapsed);
}
void AgoraClrLibrary::AgoraClrEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
	if (onUserOfflineEvent) onUserOfflineEvent(uid, reason);
}
void AgoraClrLibrary::AgoraClrEventHandler::onUserMuteAudio(uid_t uid, bool muted) {
	if (onUserMuteAudioEvent) onUserMuteAudioEvent(uid, muted);
}
void AgoraClrLibrary::AgoraClrEventHandler::onUserMuteVideo(uid_t uid, bool muted) {
	if (onUserMuteVideoEvent) onUserMuteVideoEvent(uid, muted);
}
void AgoraClrLibrary::AgoraClrEventHandler::onUserEnableVideo(uid_t uid, bool enabled) {
	if (onUserEnableVideoEvent) onUserEnableVideoEvent(uid, enabled);
}
void AgoraClrLibrary::AgoraClrEventHandler::onApiCallExecuted(const char* api, int error) {
	if (onApiCallExecutedEvent) onApiCallExecutedEvent(api, error);
}
void AgoraClrLibrary::AgoraClrEventHandler::onLocalVideoStats(const LocalVideoStats& stats) {
	if (onLocalVideoStatsEvent) onLocalVideoStatsEvent(stats);
}
void AgoraClrLibrary::AgoraClrEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats) {
	if (onRemoteVideoStatsEvent) onRemoteVideoStatsEvent(stats);
}
void AgoraClrLibrary::AgoraClrEventHandler::onCameraReady() {
	if (onCameraReadyEvent) onCameraReadyEvent();
}
void AgoraClrLibrary::AgoraClrEventHandler::onVideoStopped() {
	if (onVideoStoppedEvent) onVideoStoppedEvent();
}
void AgoraClrLibrary::AgoraClrEventHandler::onConnectionLost() {
	if (onConnectionLostEvent) onConnectionLostEvent();
}
void AgoraClrLibrary::AgoraClrEventHandler::onConnectionInterrupted() {
	if (onConnectionInterruptedEvent) onConnectionLostEvent();
}
void AgoraClrLibrary::AgoraClrEventHandler::onConnectionBanned()
{
	if (onConnectionBannedEvent) onConnectionBannedEvent();
}
void AgoraClrLibrary::AgoraClrEventHandler::onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) {
	if (onStreamMessageEvent) onStreamMessageEvent(uid, streamId, data, length);
}
void AgoraClrLibrary::AgoraClrEventHandler::onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) {
	if (onStreamMessageErrorEvent) onStreamMessageErrorEvent(uid, streamId, code, missed, cached);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRequestChannelKey()
{
	if (onRequestChannelKeyEvent) onRequestChannelKeyEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onRequestToken()
{
	if (onRequestTokenEvent) onRequestTokenEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioMixingFinished()
{
	if (onAudioMixingFinishedEvent) onAudioMixingFinishedEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onActiveSpeaker(uid_t uid)
{
	if (onActiveSpeakerEvent) onActiveSpeakerEvent(uid);
}

void AgoraClrLibrary::AgoraClrEventHandler::onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	if (onClientRoleChangedEvent) onClientRoleChangedEvent(oldRole, newRole);
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChangedEvent) onAudioDeviceVolumeChangedEvent(deviceType, volume, muted);
}

void AgoraClrLibrary::AgoraClrEventHandler::onStreamUnpublished(const char * url)
{
	if (onStreamUnpublishedEvent) onStreamUnpublishedEvent(url);
}

void AgoraClrLibrary::AgoraClrEventHandler::onStreamPublished(const char * url, int error)
{
	if (onStreamPublishedEvent) onStreamPublishedEvent(url, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onTranscodingUpdated()
{
	if (onTranscodingUpdatedEvent) onTranscodingUpdatedEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (onConnectionStateChangedEvent) onConnectionStateChangedEvent(state, reason);
}

void AgoraClrLibrary::AgoraClrEventHandler::onTokenPrivilegeWillExpire(const char * token)
{
	if (onTokenPrivilegeWillExpireEvent) onTokenPrivilegeWillExpireEvent(token);
}

void AgoraClrLibrary::AgoraClrEventHandler::onFirstLocalAudioFrame(int elapsed)
{
	if (onFirstLocalAudioFrameEvent) onFirstLocalAudioFrameEvent(elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onFirstRemoteAudioFrame(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioFrameEvent) onFirstRemoteAudioFrameEvent(uid, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onUserEnableLocalVideo(uid_t uid, bool enabled)
{
	if (onUserEnableLocalVideoEvent) onUserEnableLocalVideoEvent(uid, enabled);
}

void AgoraClrLibrary::AgoraClrEventHandler::onVideoSizeChanged(uid_t uid, int width, int height, int rotation)
{
	if (onVideoSizeChangedEvent) onVideoSizeChangedEvent(uid, width, height, rotation);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	if (onRemoteVideoStateChangedEvent) onRemoteVideoStateChangedEvent(uid, state, reason, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onLocalPublishFallbackToAudioOnly(bool fallbackOrRecover)
{
	if (onLocalPublishFallbackToAudioOnlyEvent) onLocalPublishFallbackToAudioOnlyEvent(fallbackOrRecover);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover)
{
	if (onRemoteSubscribeFallbackToAudioOnlyEvent) onRemoteSubscribeFallbackToAudioOnlyEvent(uid, isFallbackOrRecover);
}

void AgoraClrLibrary::AgoraClrEventHandler::onCameraFocusAreaChanged(int x, int y, int width, int height)
{
	if (onCameraFocusAreaChangedEvent) onCameraFocusAreaChangedEvent(x, y, width, height);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteAudioStats(const RemoteAudioStats & stats)
{
	if (onRemoteAudioStatsEvent) onRemoteAudioStatsEvent(stats);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteAudioTransportStatsEvent) onRemoteAudioTransportStatsEvent(uid, delay, lost, rxKBitRate);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteVideoTransportStatsEvent) onRemoteVideoTransportStatsEvent(uid, delay, lost, rxKBitRate);
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioMixingBegin()
{
	if (onAudioMixingBeginEvent) onAudioMixingBeginEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioMixingEnd()
{
	if (onAudioMixingEndEvent) onAudioMixingEndEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioEffectFinished(int soundId)
{
	if (onAudioEffectFinishedEvent) onAudioEffectFinishedEvent(soundId);
}

void AgoraClrLibrary::AgoraClrEventHandler::onStreamInjectedStatus(const char * url, uid_t uid, int status)
{
	if (onStreamInjectedStatusEvent) onStreamInjectedStatusEvent(url, uid, status);
}

void AgoraClrLibrary::AgoraClrEventHandler::onMediaEngineLoadSuccess()
{
	if (onMediaEngineLoadSuccessEvent) onMediaEngineLoadSuccessEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onMediaEngineStartCallSuccess()
{
	if (onMediaEngineStartCallSuccessEvent) onMediaEngineStartCallSuccessEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onNetworkTypeChanged(NETWORK_TYPE type)
{
	if (onNetworkTypeChangedEvent) onNetworkTypeChangedEvent(type);
}

void AgoraClrLibrary::AgoraClrEventHandler::onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error)
{
	if (onLocalAudioStateChangedEvent) onLocalAudioStateChangedEvent(state, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
{
	if (onLocalVideoStateChangedEvent) onLocalVideoStateChangedEvent(state, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChangedEvent) onRemoteAudioStateChangedEvent(uid, state, reason, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onFirstRemoteAudioDecoded(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioDecodedEvent) onFirstRemoteAudioDecodedEvent(uid, elapsed);
}

void AgoraClrLibrary::AgoraClrEventHandler::onLocalAudioStats(const LocalAudioStats& stats)
{
	if (onLocalAudioStatsEvent) onLocalAudioStatsEvent(stats);
}

void AgoraClrLibrary::AgoraClrEventHandler::onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error)
{
	if (onAudioMixingStateChangedEvent) onAudioMixingStateChangedEvent(state, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteAudioMixingBegin()
{
	if (onRemoteAudioMixingBeginEvent) onRemoteAudioMixingBeginEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onRemoteAudioMixingEnd()
{
	if (onRemoteAudioMixingEndEvent) onRemoteAudioMixingEndEvent();
}

void AgoraClrLibrary::AgoraClrEventHandler::onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error)
{
	if (onRtmpStreamingStateChangedEvent) onRtmpStreamingStateChangedEvent(url, state, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error)
{
	if (onChannelMediaRelayStateChangedEvent) onChannelMediaRelayStateChangedEvent(state, error);
}

void AgoraClrLibrary::AgoraClrEventHandler::onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event)
{
	if (onChannelMediaRelayEventEvnet) onChannelMediaRelayEventEvnet(event);
}

void AgoraClrLibrary::AgoraClrEventHandler::onLastmileProbeResult(const LastmileProbeResult& result)
{
	if (onLastmileProbeResultEvent) onLastmileProbeResultEvent(result);
}
