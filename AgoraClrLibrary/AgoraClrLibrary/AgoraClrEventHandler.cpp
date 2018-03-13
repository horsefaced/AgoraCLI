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
void AgoraClrLibrary::AgoraClrEventHandler::onRefreshRecordingServiceStatus(int status) {
	if (onRefreshRecordingServiceStatusEvent) onRefreshRecordingServiceStatusEvent(status);
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
