#include "AgoraClrChannel.h"
using namespace AgoraClrLibrary;

AgoraClrChannel::AgoraClrChannel(IChannel* channel) :
	channel(channel),
	gchs(gcnew List<GCHandle>),
	events(new AgoraClrChannelEventHandler()),
	metaObserver(new AgoraClrMetadataObserver()),
	packetObserver(new AgoraClrPacketObserver())
{
	bindEventHandler();
	bindMetaObserver();
	bindPacketObserver();

	channel->registerMediaMetadataObserver(metaObserver, agora::rtc::IMetadataObserver::METADATA_TYPE::VIDEO_METADATA);
}

AgoraClrChannel::~AgoraClrChannel()
{
	channel->release();
	for each (GCHandle handler in gchs) handler.Free();
	delete channel;
}

int AgoraClrChannel::joinChannel(String^ token, String^ info, uid_t uid, ClrChannelMediaOptions^ options)
{
	return channel->joinChannel(MarshalString(token).c_str(), MarshalString(info).c_str(), uid, options);
}

int AgoraClrChannel::joinChannelWithUserAccount(String^ token, String^ account, ClrChannelMediaOptions^ options)
{
	return channel->joinChannelWithUserAccount(MarshalString(token).c_str(), MarshalString(account).c_str(), options);
}

int AgoraClrChannel::leaveChannel()
{
	channel->registerPacketObserver(nullptr);
	return channel->leaveChannel();
}

int AgoraClrChannel::publish()
{
	return channel->publish();
}

int AgoraClrChannel::unpublish()
{
	return channel->unpublish();
}

String^ AgoraClrChannel::channelId()
{
	return gcnew String(channel->channelId());
}

int AgoraClrChannel::getCallId(String^% callid)
{
	agora::util::AString string;
	int result = channel->getCallId(string);
	callid = gcnew String(string->c_str());
	return result;	
}

int AgoraClrChannel::renewToken(String^ token)
{
	return channel->renewToken(MarshalString(token).c_str());
}

int AgoraClrChannel::setEncryptionSecret(String^ secret)
{
	channel->registerPacketObserver(packetObserver);
	return channel->setEncryptionSecret(MarshalString(secret).c_str());
}

int AgoraClrChannel::setEncryptionMode(String^ mode)
{
	return channel->setEncryptionMode(MarshalString(mode).c_str());
}

int AgoraClrChannel::setClientRole(EnumClientRoleType type)
{
	return channel->setClientRole(static_cast<CLIENT_ROLE_TYPE>(type));
}

int AgoraClrChannel::setRemoteVoicePosition(int uid, double pan, double gain)
{
	return channel->setRemoteVoicePosition(uid, pan, gain);
}

int AgoraClrChannel::setRemoteRenderMode(uid_t uid, EnumRenderModeType renderMode, EnumVideoMirrorModeType mirrorMode)
{
	return channel->setRemoteRenderMode(uid,
		static_cast<RENDER_MODE_TYPE>(renderMode),
		static_cast<VIDEO_MIRROR_MODE_TYPE>(mirrorMode));
}

int AgoraClrChannel::setDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return channel->setDefaultMuteAllRemoteAudioStreams(mute);
}

int AgoraClrChannel::setDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return channel->setDefaultMuteAllRemoteVideoStreams(mute);
}

int AgoraClrChannel::muteAllRemoteAudioStreams(bool mute)
{
	return channel->muteAllRemoteAudioStreams(mute);
}

int AgoraClrChannel::adjustUserPlaybackSignalVolume(uid_t uid, int volume)
{
	return channel->adjustUserPlaybackSignalVolume(uid, volume);
}

int AgoraClrChannel::muteRemoteAudioStream(uid_t uid, bool mute)
{
	return channel->muteRemoteAudioStream(uid, mute);
}

int AgoraClrChannel::muteAllRemoteVideoStreams(bool mute)
{
	return channel->muteAllRemoteVideoStreams(mute);
}

int AgoraClrChannel::muteRemoteVideoStream(uid_t uid, bool mute)
{
	return channel->muteRemoteVideoStream(uid, mute);
}

int AgoraClrChannel::setRemoteVideoStreamType(uid_t uid, EnumRemoteVideoStreamType type)
{
	return channel->setRemoteVideoStreamType(uid,
		static_cast<REMOTE_VIDEO_STREAM_TYPE>(type));
}

int AgoraClrChannel::setRemoteDefaultVideoStreamType(EnumRemoteVideoStreamType type)
{
	return channel->setRemoteDefaultVideoStreamType(
		static_cast<REMOTE_VIDEO_STREAM_TYPE>(type)
		);
}

int AgoraClrChannel::createDataStream(int% streamId, bool reliable, bool ordered)
{
	int id;
	int result = channel->createDataStream(&id, reliable, ordered);
	streamId = id;
	return result;
}

int AgoraClrChannel::sendStreamMessage(int streamId, String^ msg)
{
	std::string data = MarshalString(msg);
	return channel->sendStreamMessage(streamId, data.c_str(), data.size());
}

int AgoraClrChannel::addPublishStreamUrl(String^ url, bool transcodingEnabled)
{
	return channel->addPublishStreamUrl(MarshalString(url).c_str(), transcodingEnabled);
}

int AgoraClrChannel::removePublishStreamUrl(String^ url)
{
	return channel->removePublishStreamUrl(MarshalString(url).c_str());
}

int AgoraClrChannel::setLiveTranscoding(ClrLiveTranscoding^ transcoding)
{
	return channel->setLiveTranscoding(transcoding);
}

int AgoraClrChannel::addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config)
{
	return channel->addInjectStreamUrl(MarshalString(url).c_str(), config);
}

int AgoraClrChannel::removeInjectStreamUrl(String^ url)
{
	return channel->removeInjectStreamUrl(MarshalString(url).c_str());
}

int AgoraClrChannel::startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return channel->startChannelMediaRelay(config);
}

int AgoraClrChannel::updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return channel->updateChannelMediaRelay(config);
}

int AgoraClrChannel::stopChannelMediaRelay()
{
	return channel->stopChannelMediaRelay();
}

void AgoraClrChannel::bindEventHandler()
{
	regEvent(events->onChannelWarningEvent, gcnew OnChannelWarningType::Type(this, &AgoraClrChannel::NativeOnChannelWarning));
	regEvent(events->onChannelErrorEvent, gcnew OnChannelErrorType::Type(this, &AgoraClrChannel::NativeOnChannelError));
	regEvent(events->onJoinChannelSuccessEvent, gcnew OnJoinChannelSuccessType::Type(this, &AgoraClrChannel::NativeOnJoinChannelSuccess));
	regEvent(events->onRejoinChannelSuccessEvent, gcnew OnRejoinChanelSuccessType::Type(this, &AgoraClrChannel::NativeOnRejoinChanelSuccess));
	regEvent(events->onLeaveChannelEvent, gcnew OnLeaveChannelType::Type(this, &AgoraClrChannel::NativeOnLeaveChannel));
	regEvent(events->onClientRoleChangedEvent, gcnew OnClientRoleChangedType::Type(this, &AgoraClrChannel::NativeOnClientRoleChanged));
	regEvent(events->onUserJoinEvent, gcnew OnUserJoinedType::Type(this, &AgoraClrChannel::NativeOnUserJoined));
	regEvent(events->onUserOfflineEvent, gcnew OnUserOfflineType::Type(this, &AgoraClrChannel::NativeOnUserOffline));
	regEvent(events->onConnectionLostEvent, gcnew OnConnectionLostType::Type(this, &AgoraClrChannel::NativeOnConnectionLost));
	regEvent(events->onRequestTokenEvent, gcnew OnRequestTokenType::Type(this, &AgoraClrChannel::NativeOnRequestToken));
	regEvent(events->onTokePrivilegeWillExpireEvent, gcnew OnTokenPrivilegeWillExpireType::Type(this, &AgoraClrChannel::NativeOnTokenPrivilegeWillExpire));
	regEvent(events->onRtcStatsEvent, gcnew OnRtcStatsType ::Type(this, &AgoraClrChannel::NativeOnRtcStats));
	regEvent(events->onNetworkQualityEvent, gcnew OnNetworkQualityType::Type(this, &AgoraClrChannel::NativeOnNetworkQuality));
	regEvent(events->onRemoteVideoStatsEvent, gcnew OnRemoteVideoStatsType::Type(this, &AgoraClrChannel::NativeOnRemoteVideoStats));
	regEvent(events->onRemoteAudioStatsEvent, gcnew OnRemoteAudioStatsType::Type(this, &AgoraClrChannel::NativeOnRemoteAudioStats));
	regEvent(events->onRemoteAudioStateChangedEvent, gcnew OnRemoteAudioStateChangedType::Type(this, &AgoraClrChannel::NativeOnRemoteAudioStateChanged));
	regEvent(events->onActiveSpeakerEvent, gcnew OnActiveSpeakerType::Type(this, &AgoraClrChannel::NativeOnActiveSpeaker));
	regEvent(events->onVideoSizeChangedEvent, gcnew OnVideoSizeChangedType::Type(this, &AgoraClrChannel::NativeOnVideoSizeChanged));
	regEvent(events->onRemoteVideoStateChangedEvent, gcnew OnRemoteVideoStateChangedType::Type(this, &AgoraClrChannel::NativeOnRemoteVideoStateChanged));
	regEvent(events->onStreamMessageEvent, gcnew OnStreamMessageType::Type(this, &AgoraClrChannel::NativeOnStreamMessage));
	regEvent(events->onStreamMessageErrorEvent, gcnew OnStreamMessageErrorType::Type(this, &AgoraClrChannel::NativeOnStreamMessageError));
	regEvent(events->onChannelMediaRelayStateChangedEvent, gcnew OnChannelMediaRelayStateChangedType::Type(this, &AgoraClrChannel::NativeOnChannelMediaRelayStateChanged));
	regEvent(events->onChannelMediaRelayEventEvent, gcnew OnChannelMediaRelayEventType::Type(this, &AgoraClrChannel::NativeOnChannelMediaRelayEvent));
	regEvent(events->onRtmpStreamingStateChangedEvent, gcnew OnRtmpStreamingStateChangedType::Type(this, &AgoraClrChannel::NativeOnRtmpStreamingStateChanged));
	regEvent(events->onTranscodingUpdatedEvent, gcnew OnTranscodingUpdatedType::Type(this, &AgoraClrChannel::NativeOnTranscodingUpdated));
	regEvent(events->onStreamInjectedStatusEvent, gcnew OnStreamInjectedStatusType::Type(this, &AgoraClrChannel::NativeOnStreamInjectedStatus));
	regEvent(events->onRemoteSubscribeFallbackToAudioOnlyEvent, gcnew OnRemoteSubscribeFallbackToAudioOnlyType::Type(this, &AgoraClrChannel::NativeOnRemoteSubscribeFallbackToAudioOnly));
	regEvent(events->onConnectionStateChangedEvent, gcnew OnConnectionStateChangedType::Type(this, &AgoraClrChannel::NativeOnConnectionStateChanged));
}

void AgoraClrChannel::bindMetaObserver()
{
	regEvent(metaObserver->onGetMaxMetadataSizeEvent, gcnew NativeOnGetMaxMetadataSizeDelegate(this, &AgoraClrChannel::NativeGetMaxMetadataSize));
	regEvent(metaObserver->onReadyToSendMetadataEvent, gcnew NativeOnReadyToSendMetadataDelegate(this, &AgoraClrChannel::NativeOnReadyToSendMetadata));
	regEvent(metaObserver->onMetadataReceivedEvent, gcnew NativeOnMetadataReceivedDelegate(this, &AgoraClrChannel::NativeOnMetadataReceived));
}

void AgoraClrChannel::bindPacketObserver()
{
	regEvent(packetObserver->onSendAudioPacketEvent, gcnew NativeOnSendAudioPacketDelegate(this, &AgoraClrChannel::NativeOnSendAudioPacket));
	regEvent(packetObserver->onSendVideoPacketEvent, gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClrChannel::NativeOnSendVideoPacket));
	regEvent(packetObserver->onReceiveVideoPacketEvent, gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClrChannel::NativeOnReceiveVideoPacket));
	regEvent(packetObserver->onReceiveAudioPacketEvent, gcnew NativeOnReceiveAudioPacketDelegate(this, &AgoraClrChannel::NativeOnReceiveAudioPacket));
}

void AgoraClrChannel::NativeOnChannelWarning(IChannel* channel, int warn, const char* msg)
{
	if (onChannelWarning) onChannelWarning(this, warn, gcnew String(msg));
}

void AgoraClrChannel::NativeOnChannelError(IChannel* channel, int err, const char* msg)
{
	if (onChannelError) onChannelError(this, err, gcnew String(msg));
}

void AgoraClrChannel::NativeOnJoinChannelSuccess(IChannel* channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccess) onJoinChannelSuccess(this, uid, elapsed);
}

void AgoraClrChannel::NativeOnRejoinChanelSuccess(IChannel* channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccess) onRejoinChannelSuccess(this, uid, elapsed);
}

void AgoraClrChannel::NativeOnLeaveChannel(IChannel* channel, const RtcStats& stats)
{
	if (onLeaveChannel) onLeaveChannel(this, gcnew ClrRtcStats(stats));
}

void AgoraClrChannel::NativeOnClientRoleChanged(IChannel* channel, CLIENT_ROLE_TYPE old, CLIENT_ROLE_TYPE newer)
{
	if (onClientRoleChanged) onClientRoleChanged(this, static_cast<EnumClientRoleType>(old), static_cast<EnumClientRoleType>(newer));
}

void AgoraClrChannel::NativeOnUserJoined(IChannel* channel, uid_t uid, int elapsed)
{
	if (onUserJoined) onUserJoined(this, uid, elapsed);
}

void AgoraClrChannel::NativeOnUserOffline(IChannel* channel, uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	if (onUserOffline) onUserOffline(this, uid, static_cast<EnumUserOfflineReasonType>(reason));
}

void AgoraClrChannel::NativeOnConnectionLost(IChannel* channel)
{
	if (onConnectionLost) onConnectionLost(this);
}

void AgoraClrChannel::NativeOnRequestToken(IChannel* channel)
{
	if (onRequestToken) onRequestToken(this);
}

void AgoraClrChannel::NativeOnTokenPrivilegeWillExpire(IChannel* channel, const char* token)
{
	if (onTokenPrivilegeWilExpire) onTokenPrivilegeWilExpire(this, gcnew String(token));
}

void AgoraClrChannel::NativeOnRtcStats(IChannel* channel, const RtcStats& stats)
{
	if (onRtcStats) onRtcStats(this, gcnew ClrRtcStats(stats));
}

void AgoraClrChannel::NativeOnNetworkQuality(IChannel* channel, uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQuality) onNetworkQuality(this, uid, txQuality, rxQuality);
}

void AgoraClrChannel::NativeOnRemoteVideoStats(IChannel* channel, const RemoteVideoStats& stats)
{
	if (onRemoteVideoStats) onRemoteVideoStats(this, gcnew ClrRemoteVideoStats(stats));
}

void AgoraClrChannel::NativeOnRemoteAudioStats(IChannel* channel, const RemoteAudioStats& stats)
{
	if (onRemoteAudioStats) onRemoteAudioStats(this, gcnew ClrRemoteAudioStats(stats));
}

void AgoraClrChannel::NativeOnRemoteAudioStateChanged(IChannel* channel, uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChanged) onRemoteAudioStateChanged(this, uid, static_cast<EnumRemoteAudioState>(state), static_cast<EnumRemoteAudioStateReason>(reason), elapsed);
}

void AgoraClrChannel::NativeOnActiveSpeaker(IChannel* channel, uid_t uid)
{
	if (onActiveSpeaker) onActiveSpeaker(this, uid);
}

void AgoraClrChannel::NativeOnVideoSizeChanged(IChannel* channel, uid_t uid, int width, int height, int rotation)
{
	if (onVideoSizeChanged) onVideoSizeChanged(this, uid, width, height, rotation);
}

void AgoraClrChannel::NativeOnRemoteVideoStateChanged(IChannel* channel, uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	if (onRemoteVideoStateChanged) onRemoteVideoStateChanged(this, uid, static_cast<EnumRemoteVideoState>(state), static_cast<EnumRemoteVideoStateReason>(reason), elapsed);
}

void AgoraClrChannel::NativeOnStreamMessage(IChannel* channel, uid_t uid, int streamId, const char* data, size_t length)
{
	auto bytes = gcnew array<Byte>(length);
	if (length > 0) Marshal::Copy(IntPtr(reinterpret_cast<void*>(const_cast<char*>(data))), bytes, 0, length);
	if (onStreamMessage) onStreamMessage(this, uid, streamId, bytes);
}

void AgoraClrChannel::NativeOnStreamMessageError(IChannel* channel, uid_t uid, int streamId, int code, int missed, int cached)
{
	if (onStreamMessageError) onStreamMessageError(this, uid, streamId, code, missed, cached);
}

void AgoraClrChannel::NativeOnChannelMediaRelayStateChanged(IChannel* channel, CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR code)
{
	if (onChannelMediaRelayStateChanged)
		onChannelMediaRelayStateChanged(this,
			static_cast<EnumChannelMediaRelayState>(state),
			static_cast<EnumChannelMediaRelayError>(code));
}

void AgoraClrChannel::NativeOnChannelMediaRelayEvent(IChannel* channel, CHANNEL_MEDIA_RELAY_EVENT code)
{
	if (onChannelMediaRelayEvent)
		onChannelMediaRelayEvent(this,
			static_cast<EnumChannelMediaRelayEvent>(code));
}

void AgoraClrChannel::NativeOnRtmpStreamingStateChanged(IChannel* channel, const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR code)
{
	if (onRtmpStreamingStateChanged)
		onRtmpStreamingStateChanged(this, gcnew String(url),
			static_cast<EnumRtmpStreamPublishState>(state),
			static_cast<EnumRtmpStreamPublishError>(code));
}

void AgoraClrChannel::NativeOnTranscodingUpdated(IChannel* channel)
{
	if (onTranscodingUpdated) onTranscodingUpdated(this);
}

void AgoraClrChannel::NativeOnStreamInjectedStatus(IChannel* channel, const char* url, uid_t uid, int status)
{
	if (onStreamInjectedStatus)
		onStreamInjectedStatus(this, gcnew String(url), uid, status);
}

void AgoraClrChannel::NativeOnRemoteSubscribeFallbackToAudioOnly(IChannel* channel, uid_t uid, bool isFallbackOrRecover)
{
	if (onRemoteSubscribeFallbackToAudioOnly)
		onRemoteSubscribeFallbackToAudioOnly(this, uid, isFallbackOrRecover);
}

void AgoraClrChannel::NativeOnConnectionStateChanged(IChannel* channel, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (onConnectionStateChanged)
		onConnectionStateChanged(this,
			static_cast<EnumConnectionStateType>(state),
			static_cast<EnumConnectionChangedReasonType>(reason));
}

int AgoraClrChannel::NativeGetMaxMetadataSize()
{
	return 1024;
}

bool AgoraClrChannel::NativeOnReadyToSendMetadata(IMetadataObserver::Metadata& metadata)
{
	return onReadyToSendMetadata ? onReadyToSendMetadata(gcnew ClrMetadata(metadata)) : false;
}

void AgoraClrChannel::NativeOnMetadataReceived(const IMetadataObserver::Metadata& metadata)
{
	if (onMetadataReceived)
		onMetadataReceived(gcnew ClrMetadata(metadata));
}

bool AgoraClrChannel::NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendAudioPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onSendAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrChannel::NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onSendVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrChannel::NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrChannel::NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}
