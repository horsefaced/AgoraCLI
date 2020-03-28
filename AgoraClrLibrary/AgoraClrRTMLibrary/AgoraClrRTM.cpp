
#include "pch.h"
#include "AgoraClrRTM.h"
#include "AgoraClrRTMEventHandler.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <tuple>

using namespace msclr::interop;
using namespace System::Collections::Generic;

AgoraClrLibrary::AgoraClrRTM::AgoraClrRTM() :
	service(createRtmService()),
	rtmEvents(new AgoraClrRTMEventHandler()),
	manager(nullptr),
	gchs(gcnew List<GCHandle>)
{
	bindEventHandler();
}

AgoraClrLibrary::AgoraClrRTM::~AgoraClrRTM()
{
	delete manager;
	service->removeEventHandler(rtmEvents);
	delete rtmEvents;
	for each (GCHandle handler in this->gchs)
	{
		handler.Free();
	}
	service->release();
}

int AgoraClrLibrary::AgoraClrRTM::initialize(String^ vendorkey)
{
	return service->initialize(marshal_as<std::string>(vendorkey).c_str(), rtmEvents);
}

int AgoraClrLibrary::AgoraClrRTM::login(String^ token, String^ userId)
{
	return service->login(marshal_as<std::string>(token).c_str(), marshal_as<std::string>(userId).c_str());
}

int AgoraClrLibrary::AgoraClrRTM::logout()
{
	return service->logout();
}

AgoraClrLibrary::ClrMessage^ AgoraClrLibrary::AgoraClrRTM::createMessage()
{
	return gcnew ClrMessage();
}

int AgoraClrLibrary::AgoraClrRTM::sendMessageToPeer(String^ peerId, ClrMessage^ msg, ClrSendMessageOptions^ options)
{
	IMessage* raw = msg->toMessage(service);
	int result = service->sendMessageToPeer(marshal_as<std::string>(peerId).c_str(), raw, options);
	raw->release();
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::queryPeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long backId;
	int result = service->queryPeersOnlineStatus(context.chars, context.count, backId);
	requestId = backId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::subscribePeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	int result = service->subscribePeersOnlineStatus(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::unsubscribePeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	int result = service->unsubscribePeersOnlineStatus(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::queryPeersBySubscriptionOption(EnumPeerSubscriptionOption option, long long% requestId)
{
	long long tmpId = requestId;
	int result = service->queryPeersBySubscriptionOption(static_cast<PEER_SUBSCRIPTION_OPTION>(option), tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::addOrUpdateLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId)
{
	int count = attributes->Count;
	const RtmAttribute** attrs = ClrRtmAttribute::createAttrs(attributes);
	long long tmpId;
	int result = service->addOrUpdateLocalUserAttributes(attrs[0], count, tmpId);
	requestId = tmpId;
	ClrRtmAttribute::releaseAttrs(attrs, count);
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::deleteLocalUserAttributesByKeys(List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);
	long long tmpId;
	int result = service->deleteLocalUserAttributesByKeys(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::clearLocalUserAttributes(long long% requestId)
{
	long long tmpId;
	int result = service->clearLocalUserAttributes(tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::getUserAttributes(String^ userId, long long% requestId)
{
	long long tmpId;
	int result = service->getUserAttributes(marshal_as<std::string>(userId).c_str(), tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::getUserAttributesByKeys(String^ userId, List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);

	long long tmpId;
	int result = service->getUserAttributesByKeys(context.marshal_as(userId), context.chars, context.count, tmpId);
	requestId = tmpId;

	return result;
}

int AgoraClrLibrary::AgoraClrRTM::setLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId)
{
	long long tmpId;
	const RtmAttribute** attrs = ClrRtmAttribute::createAttrs(attributes);
	int result = service->setLocalUserAttributes(attrs[0], attributes->Count, tmpId);
	requestId = tmpId;
	ClrRtmAttribute::releaseAttrs(attrs, attributes->Count);
	return result;
}

AgoraClrLibrary::ClrRtmChannelAttribute^ AgoraClrLibrary::AgoraClrRTM::createChannelAttribute()
{
	return gcnew ClrRtmChannelAttribute();
}

int AgoraClrLibrary::AgoraClrRTM::addOrUpdateChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId)
{
	long long tmpId;
	auto [tmpAttrs, count] = ClrRtmChannelAttribute::toArray(service, attributes);
	ChannelAttributeOptions tmpOptions;
	tmpOptions.enableNotificationToChannelMembers = options->enableNotificationToChannelMembers;
	int result = service->addOrUpdateChannelAttributes(
		marshal_as<std::string>(channelId).c_str(),
		const_cast<const IRtmChannelAttribute**>(tmpAttrs),
		count, tmpOptions, tmpId);

	for (int i = 0; i < count; i++) tmpAttrs[i]->release();
	delete[] tmpAttrs;
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::deleteChannelAttributesByKeys(String^ channelId, List<String^>^ keys, ClrChannelAttributeOptions^ options, long long% requestId)
{
	long long tmpId;
	AutoChars context(keys);
	ChannelAttributeOptions tmpOptons;
	tmpOptons.enableNotificationToChannelMembers = options->enableNotificationToChannelMembers;
	int result = service->deleteChannelAttributesByKeys(
		context.marshal_as(channelId),
		context.chars, context.count, tmpOptons, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::clearChannelAttributes(String^ channelId, ClrChannelAttributeOptions^ options, long long% requestId)
{
	long long tmpId;
	ChannelAttributeOptions tmpOptions;
	tmpOptions.enableNotificationToChannelMembers = options->enableNotificationToChannelMembers;

	int result = service->clearChannelAttributes(
		marshal_as<std::string>(channelId).c_str(),
		tmpOptions, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::getChannelAttributes(String^ channelId, long long% requestId)
{
	long long tmpId;
	int result = service->getChannelAttributes(
		marshal_as<std::string>(channelId).c_str(),
		tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::getChannelAttributesByKeys(String^ channelId, List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);
	long long tmpId;
	int result = service->getChannelAttributesByKeys(
		context.marshal_as(channelId),
		context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::setChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId)
{
	long long tmpId;
	auto [tmpAttrs, count] = ClrRtmChannelAttribute::toArray(service, attributes);

	ChannelAttributeOptions tmpOptions;
	tmpOptions.enableNotificationToChannelMembers = options->enableNotificationToChannelMembers;
	int result = service->setChannelAttributes(
		marshal_as<std::string>(channelId).c_str(),
		const_cast<const IRtmChannelAttribute**>(tmpAttrs), 
		count, tmpOptions, tmpId);

	for (int i = 0; i < count; i++) tmpAttrs[i]->release();

	delete[] tmpAttrs;
	requestId = tmpId;
	return result;
}

int AgoraClrLibrary::AgoraClrRTM::getChannelMemberCount(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	int result = service->getChannelMemberCount(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

AgoraClrLibrary::AgoraClrRTMChannel^ AgoraClrLibrary::AgoraClrRTM::createChannel(String^ id)
{
	return gcnew AgoraClrRTMChannel(service, id);
}

AgoraClrLibrary::AgoraClrRTMCallManager^ AgoraClrLibrary::AgoraClrRTM::getRtmCallManager()
{
	if (manager == nullptr) manager = gcnew AgoraClrRTMCallManager(service);
	return manager;
}

int AgoraClrLibrary::AgoraClrRTM::renewToken(String^ token)
{
	marshal_context context;
	return service->renewToken(context.marshal_as<const char*>(token));
}

int AgoraClrLibrary::AgoraClrRTM::setLogFile(String^ file)
{
	return service->setLogFile(marshal_as<std::string>(file).c_str());
}

int AgoraClrLibrary::AgoraClrRTM::setLogFilter(EnumLogFilterType filter)
{
	return service->setLogFilter(static_cast<LOG_FILTER_TYPE>(filter));
}

int AgoraClrLibrary::AgoraClrRTM::setLogFileSize(int size)
{
	return service->setLogFileSize(size);
}

String^ AgoraClrLibrary::AgoraClrRTM::getRTMSdkVersion()
{
	return gcnew String(getRtmSdkVersion());
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnLoginSuccess()
{
	if (onLoginSuccess) onLoginSuccess();
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnLoginFailure(LOGIN_ERR_CODE code)
{
	if (onLoginFailure) onLoginFailure(static_cast<EnumLoginErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnLogout(LOGOUT_ERR_CODE code)
{
	if (onLogout) onLogout(static_cast<EnumLogoutErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason)
{
	if (onConnectionStateChanged) onConnectionStateChanged(static_cast<EnumConnectionState>(state), static_cast<EnumConnectionChangeReason>(reason));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnSendMessageResult(long long id, PEER_MESSAGE_ERR_CODE code)
{
	if (onSendMessageResult) onSendMessageResult(id, static_cast<EnumPeerMessageErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnMessageReceivedFromPeer(const char* peerId, const IMessage* message)
{
	if (onMessageReceivedFromPeer) onMessageReceivedFromPeer(gcnew String(peerId), gcnew ClrMessage(const_cast<IMessage*>(message)));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnQueryPeersOnlineStatusResult(long long requestId, const PeerOnlineStatus* peersStatus, int peerCount, QUERY_PEERS_ONLINE_STATUS_ERR code)
{
	if (onQueryPeersOnlineStatusResult) {
		List<ClrPeerOnlineStatus^>^ list = gcnew List<ClrPeerOnlineStatus^>();
		for (int i = 0; i < peerCount; i++) 
			list->Add(gcnew ClrPeerOnlineStatus(peersStatus[i]));
		
		onQueryPeersOnlineStatusResult(requestId, list, static_cast<EnumQueryPeersOnlineStatusErrCode>(code));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnSubscriptionRequrestResult(long long requestId, PEER_SUBSCRIPTION_STATUS_ERR code)
{
	if (onSubscriptionRequestResult) onSubscriptionRequestResult(requestId, static_cast<EnumPeerSubscriptionStatusErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnPeersOnlineStatusChanged(const PeerOnlineStatus status[], int count)
{
	if (onPeersOnlineStatusChanged) {
		List<ClrPeerOnlineStatus^>^ list = gcnew List<ClrPeerOnlineStatus^>();

		for (int i = 0; i < count; i++) {
			list->Add(gcnew ClrPeerOnlineStatus(status[i]));
		}

		onPeersOnlineStatusChanged(list);
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnQueryPeersBySubscriptionOptionResult(long long requestId, const char* peerIds[], int peerCount, QUERY_PEERS_BY_SUBSCRIPTION_OPTION_ERR errorCode)
{
	if (onQueryPeersBySubscriptionOptionResult) {
		List<String^>^ list = gcnew List<String^>();
		for (int i = 0; i < peerCount; i++) {
			list->Add(gcnew String(peerIds[i]));
		}
		onQueryPeersBySubscriptionOptionResult(requestId, list, static_cast<EnumQueryPeersBySubscriptionOptionErrCode>(errorCode));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnSetLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onSetLocalUserAttributesResult) {
		onSetLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnAddOrUpdateLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onAddOrUpdateLocalUserAttributesResult) onAddOrUpdateLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnDeleteLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onDeleteLocalUserAttributesResult) onDeleteLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnClearLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onClearLocalUserAttributesResult) onClearLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnGetUserAttributesResult(long long id, const char* userId, const RtmAttribute* attributes, int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code)
{
	if (onGetUserAttributesResult) {
		List<ClrRtmAttribute^>^ list = gcnew List <ClrRtmAttribute^>;
		for (int i = 0; i < numberOfAttributes; i++) {
			list->Add(gcnew ClrRtmAttribute(attributes[i]));
		}

		onGetUserAttributesResult(id, gcnew String(userId), list, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnSetChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onSetChannelAttributesResult) onSetChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnAddOrUpdateChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onAddOrUpdateChannelAttributesResult)
		onAddOrUpdateChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnDeleteChannelAttriutesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onDeleteChannelAttributesResult)
		onDeleteChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnCleanChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onClearChannelAttributesResult)
		onClearChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnGetChannelAttributesResult(long long id, const IRtmChannelAttribute* attributes[], int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code)
{
	if (onGetChannelAttributesResult) {
		List<ClrRtmChannelAttribute^>^ list = gcnew List<ClrRtmChannelAttribute^>;
		for (int i = 0; i < numberOfAttributes; i++) {
			list->Add(gcnew ClrRtmChannelAttribute(attributes[i]));
		}
		onGetChannelAttributesResult(id, list, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnGetChannelMemberCountResult(long long id, const ChannelMemberCount* members, int count, GET_CHANNEL_MEMBER_COUNT_ERR_CODE code)
{
	if (onGetChannelMemberCountResult) {
		List<ClrChannelMemberCount^>^ list = gcnew List<ClrChannelMemberCount^>;
		for (int i = 0; i < count; i++)
			list->Add(gcnew ClrChannelMemberCount(members[i]));
		onGetChannelMemberCountResult(
			id, list, static_cast<EnumGetChannelMemberCountErrCode>(code));
	}
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnTokenExpired()
{
	if (onTokenExpired) onTokenExpired();
}

void AgoraClrLibrary::AgoraClrRTM::NativeOnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE code)
{
	if (onRenewTokenResult)
		onRenewTokenResult(gcnew String(token), static_cast<EnumRenewTokenErrCode>(code));
}

void AgoraClrLibrary::AgoraClrRTM::bindEventHandler()
{
	regEvent(rtmEvents->onLoginSuccessEvent, gcnew OnLoginSuccessType::Type(this, &AgoraClrRTM::NativeOnLoginSuccess));
	regEvent(rtmEvents->onLoginFailureEvent, gcnew OnLoginFailureType::Type(this, &AgoraClrRTM::NativeOnLoginFailure));
	regEvent(rtmEvents->onLogoutEvent, gcnew OnLogoutType::Type(this, &AgoraClrRTM::NativeOnLogout));
	regEvent(rtmEvents->onSendMessageResultEvent, gcnew AgoraClrLibrary::RTMEventType::OnSendMessageResultType::Type(this, &AgoraClrRTM::NativeOnSendMessageResult));
	regEvent(rtmEvents->onMessageReceivedFromPeerEvent, gcnew OnMessageReceivedFromPeerType::Type(this, &AgoraClrRTM::NativeOnMessageReceivedFromPeer));
	regEvent(rtmEvents->onQueryPeersOnlineStatusResultEvent, gcnew OnQueryPeersOnlineStatusResultType::Type(this, &AgoraClrRTM::NativeOnQueryPeersOnlineStatusResult));
	regEvent(rtmEvents->onSubscriptionRequestResultEvent, gcnew OnSubscriptionRequestResultType::Type(this, &AgoraClrRTM::NativeOnSubscriptionRequrestResult));
	regEvent(rtmEvents->onPeersOnlineStatusChangedEvent, gcnew OnPeersOnlineStatusChangedType::Type(this, &AgoraClrRTM::NativeOnPeersOnlineStatusChanged));
	regEvent(rtmEvents->onQueryPeersBySubscriptionOptionResultEvent, gcnew OnQueryPeersBySubscriptionOptionResultType::Type(this, &AgoraClrRTM::NativeOnQueryPeersBySubscriptionOptionResult));
	regEvent(rtmEvents->onSetLocalUserAttributesResultEvent, gcnew OnSetLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnSetLocalUserAttributesResult));
	regEvent(rtmEvents->onAddOrUpdateLocalUserAttributesResultEvent, gcnew OnAddOrUpdateLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnAddOrUpdateLocalUserAttributesResult));
	regEvent(rtmEvents->onDeleteLocalUserAttributesResultEvent, gcnew OnDeleteLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnDeleteLocalUserAttributesResult));
	regEvent(rtmEvents->onClearLocalUserAttributesResultEvent, gcnew OnClearLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnClearLocalUserAttributesResult));
	regEvent(rtmEvents->onGetUserAttributesResultEvent, gcnew OnGetUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnGetUserAttributesResult));
	regEvent(rtmEvents->OnSetChannelAttributesResultEvent, gcnew OnSetChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnSetChannelAttributesResult));
	regEvent(rtmEvents->onAddOrUpdateChannelAttributesResultEvent, gcnew OnAddOrUpdateChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnAddOrUpdateChannelAttributesResult));
	regEvent(rtmEvents->onDeleteChannelAttributesResultEvent, gcnew OnDeleteChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnDeleteChannelAttriutesResult));
	regEvent(rtmEvents->onClearChannelAttributesResultEvent, gcnew OnClearChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnCleanChannelAttributesResult));
	regEvent(rtmEvents->onGetChannelAttributesResultEvent, gcnew OnGetChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnGetChannelAttributesResult));
	regEvent(rtmEvents->onGetChannelMemberCountResultEvent, gcnew OnGetChannelMemberCountResultType::Type(this, &AgoraClrRTM::NativeOnGetChannelMemberCountResult));
	regEvent(rtmEvents->onTokenExpiredEvent, gcnew OnTokenExpiredType::Type(this, &AgoraClrRTM::NativeOnTokenExpired));
	regEvent(rtmEvents->onRenewTokenResultEvent, gcnew OnRenewTokenResultType::Type(this, &AgoraClrRTM::NativeOnRenewTokenResult));

}

