
#include "pch.h"
#include "AgoraClrRTM.h"
#include "AgoraClrRTMEventHandler.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <tuple>

using namespace msclr::interop;
using namespace Collections::Generic;
using namespace AgoraClrLibrary;

AgoraClrRTM::AgoraClrRTM() :
	service(createRtmService()),
	rtmEvents(new AgoraClrRTMEventHandler()),
	manager(nullptr),
	gchs(gcnew List<GCHandle>)
{
	bindEventHandler();
}

AgoraClrRTM::~AgoraClrRTM()
{
	delete manager;
	service->removeEventHandler(rtmEvents);
	delete rtmEvents;
	for each (GCHandle handler in this->gchs)
	{
		handler.Free();
	}
	service->release();
	service = nullptr;
	appId = nullptr;
}

int AgoraClrRTM::initialize(String^ vendorkey)
{
	appId = vendorkey;
	return service->initialize(marshal_as<std::string>(vendorkey).c_str(), rtmEvents);
}

int AgoraClrRTM::login(String^ userId)
{
	const auto token = appId;
	return service->login(marshal_as<std::string>(token).c_str(), marshal_as<std::string>(userId).c_str());
}
int AgoraClrRTM::login(String^ token, String^ userId)
{
	return service->login(marshal_as<std::string>(token).c_str(), marshal_as<std::string>(userId).c_str());
}

int AgoraClrRTM::logout()
{
	return service->logout();
}

ClrMessage^ AgoraClrRTM::createMessage()
{
	return gcnew ClrMessage();
}

int AgoraClrRTM::sendMessageToPeer(String^ peerId, String^ msg)
{
	try
	{
		if (peerId == nullptr || peerId == "" ) {
			return 1;
		}
		const auto clrMsg = gcnew ClrMessage();
		clrMsg->Type = EnumMessageType::MESSAGE_TYPE_TEXT;
		clrMsg->Text = msg;
		const auto msgOption = gcnew ClrSendMessageOptions();
		msgOption->enableHistoricalMessaging = false;
		msgOption->enableOfflineMessaging = false;

		return this->sendMessageToPeer(peerId,clrMsg,msgOption);
	}
	catch (Exception^)
	{
		return FALSE;
	}
}

int AgoraClrRTM::sendMessageToPeer(String^ peerId, ClrMessage^ msg)
{
	const auto msgOption = gcnew ClrSendMessageOptions();
		msgOption->enableHistoricalMessaging = false;
		msgOption->enableOfflineMessaging = false;

	return this->sendMessageToPeer(peerId,msg,msgOption);
}

int AgoraClrRTM::sendMessageToPeer(String^ peerId, ClrMessage^ msg, ClrSendMessageOptions^ options)
{
	IMessage* raw = msg->toMessage(service);
	const auto result = service->sendMessageToPeer(marshal_as<std::string>(peerId).c_str(), raw, options);
	raw->release();
	return result;
}

int AgoraClrRTM::queryPeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long backId;
	const auto  result = service->queryPeersOnlineStatus(context.chars, context.count, backId);
	requestId = backId;
	return result;
}

int AgoraClrRTM::subscribePeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	const auto  result = service->subscribePeersOnlineStatus(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::unsubscribePeersOnlineStatus(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	const auto  result = service->unsubscribePeersOnlineStatus(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::queryPeersBySubscriptionOption(EnumPeerSubscriptionOption option, long long% requestId)
{
	long long tmpId = requestId;
	const auto  result = service->queryPeersBySubscriptionOption(static_cast<PEER_SUBSCRIPTION_OPTION>(option), tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::addOrUpdateLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId)
{

	const int count = attributes->Count;
	const RtmAttribute* attrs = ClrRtmAttribute::createAttrs(attributes);
	long long tmpId;
	const int result = service->addOrUpdateLocalUserAttributes(attrs, count, tmpId);
	requestId = tmpId;
	ClrRtmAttribute::releaseAttrs(attrs, count);
	return result;
}

int AgoraClrRTM::deleteLocalUserAttributesByKeys(List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);
	long long tmpId;
	const auto  result = service->deleteLocalUserAttributesByKeys(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::clearLocalUserAttributes(long long% requestId)
{
	long long tmpId;
	const auto  result = service->clearLocalUserAttributes(tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::getUserAttributes(String^ userId, long long% requestId)
{
	long long tmpId;
	const auto  result = service->getUserAttributes(marshal_as<std::string>(userId).c_str(), tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::getUserAttributesByKeys(String^ userId, List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);

	long long tmpId;
	const auto  result = service->getUserAttributesByKeys(context.marshal_as(userId), context.chars, context.count, tmpId);
	requestId = tmpId;

	return result;
}

int AgoraClrRTM::setLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId)
{
	long long tmpId;
	const RtmAttribute* attrs = ClrRtmAttribute::createAttrs(attributes);
	int result = service->setLocalUserAttributes(attrs, attributes->Count, tmpId);
	requestId = tmpId;
	ClrRtmAttribute::releaseAttrs(attrs, attributes->Count);
	return result;
}

ClrRtmChannelAttribute^ AgoraClrRTM::createChannelAttribute()
{
	return gcnew ClrRtmChannelAttribute();
}

int AgoraClrRTM::addOrUpdateChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId)
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

int AgoraClrRTM::deleteChannelAttributesByKeys(String^ channelId, List<String^>^ keys, ClrChannelAttributeOptions^ options, long long% requestId)
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

int AgoraClrRTM::clearChannelAttributes(String^ channelId, ClrChannelAttributeOptions^ options, long long% requestId)
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

int AgoraClrRTM::getChannelAttributes(String^ channelId, long long% requestId)
{
	long long tmpId;
	int result = service->getChannelAttributes(
		marshal_as<std::string>(channelId).c_str(),
		tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::getChannelAttributesByKeys(String^ channelId, List<String^>^ keys, long long% requestId)
{
	AutoChars context(keys);
	long long tmpId;
	int result = service->getChannelAttributesByKeys(
		context.marshal_as(channelId),
		context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

int AgoraClrRTM::setChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId)
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

int AgoraClrRTM::getChannelMemberCount(List<String^>^ ids, long long% requestId)
{
	AutoChars context(ids);
	long long tmpId;
	int result = service->getChannelMemberCount(context.chars, context.count, tmpId);
	requestId = tmpId;
	return result;
}

AgoraClrRTMChannel^ AgoraClrRTM::createChannel(String^ id)
{
	return gcnew AgoraClrRTMChannel(service, id);
}

AgoraClrRTMCallManager^ AgoraClrRTM::getRtmCallManager()
{
	if (manager == nullptr) manager = gcnew AgoraClrRTMCallManager(service);
	return manager;
}

int AgoraClrRTM::renewToken(String^ token)
{
	marshal_context context;
	return service->renewToken(context.marshal_as<const char*>(token));
}

int AgoraClrRTM::setLogFile(String^ file)
{
	return service->setLogFile(marshal_as<std::string>(file).c_str());
}

int AgoraClrRTM::setLogFilter(EnumLogFilterType filter)
{
	return service->setLogFilter(static_cast<LOG_FILTER_TYPE>(filter));
}

int AgoraClrRTM::setLogFileSize(int size)
{
	return service->setLogFileSize(size);
}

String^ AgoraClrRTM::getRTMSdkVersion()
{
	return gcnew String(getRtmSdkVersion());
}

int AgoraClrRTM::createFileMessageByUploading(String^ filePath, long long% requestId)
{
	long long backId;
	const int result =  service->createFileMessageByUploading(marshal_as<std::string>(filePath).data(),backId);
	requestId = backId;
	return result;
}

int AgoraClrRTM::createImageMessageByUploading(String^ filePath, long long% requestId)
{
	long long backId;
	const int result =  service->createImageMessageByUploading(marshal_as<std::string>(filePath).data(),backId);
	requestId = backId;
	return result;
}

int AgoraClrRTM::cancelMediaUpload(long requestId)
{
	return service->cancelMediaDownload(requestId);
}

int AgoraClrRTM::cancelMediaDownload(long requestId)
{
	return service->cancelMediaDownload(requestId);
}

ClrFileMessage^ AgoraClrRTM::createFileMessageByMediaId(String^ mediaId)
{
	const auto raw = service->createFileMessageByMediaId(marshal_as<std::string>(mediaId).data());
	if(nullptr == raw)
		return nullptr;
	return gcnew ClrFileMessage(raw );
}

ClrImageMessage^ AgoraClrRTM::createImageMessageByMediaId(String^ mediaId)
{
	const auto raw = service->createImageMessageByMediaId(marshal_as<std::string>(mediaId).data());
	if(nullptr == raw)
		return nullptr;
	return gcnew ClrImageMessage(raw );
}

int AgoraClrRTM::downloadMediaToMemory(String^ mediaId, long long% requestId)
{
	long long backId;
	const int result =  service->downloadMediaToMemory(marshal_as<std::string>(mediaId).data(),backId);
	requestId = backId;
	return result;
}

int AgoraClrRTM::downloadMediaToFile(String^ mediaId, String^ filePath, long long% requestId)
{
	long long backId;
	const int result =  service->downloadMediaToFile(marshal_as<std::string>(mediaId).data(),
		marshal_as<std::string>(filePath).data(),backId);
	requestId = backId;
	return result;
}
void AgoraClrRTM::NativeOnLoginSuccess()
{
	if (onLoginSuccess) onLoginSuccess();
}

void AgoraClrRTM::NativeOnLoginFailure(LOGIN_ERR_CODE code)
{
	if (onLoginFailure) onLoginFailure(static_cast<EnumLoginErrCode>(code));
}

void AgoraClrRTM::NativeOnLogout(LOGOUT_ERR_CODE code)
{
	if (onLogout) onLogout(static_cast<EnumLogoutErrCode>(code));
}

void AgoraClrRTM::NativeOnConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason)
{
	if (onConnectionStateChanged) onConnectionStateChanged(static_cast<EnumConnectionState>(state), static_cast<EnumConnectionChangeReason>(reason));
}

void AgoraClrRTM::NativeOnSendMessageResult(long long id, PEER_MESSAGE_ERR_CODE code)
{
	if (onSendMessageResult) onSendMessageResult(id, static_cast<EnumPeerMessageErrCode>(code));
}

void AgoraClrRTM::NativeOnMessageReceivedFromPeer(const char* peerId, const IMessage* message)
{
	if (onMessageReceivedFromPeer) onMessageReceivedFromPeer(gcnew String(peerId), gcnew ClrMessage(const_cast<IMessage*>(message)));
}

void AgoraClrRTM::NativeOnQueryPeersOnlineStatusResult(long long requestId, const PeerOnlineStatus* peersStatus, int peerCount, QUERY_PEERS_ONLINE_STATUS_ERR code)
{
	if (onQueryPeersOnlineStatusResult) {
		List<ClrPeerOnlineStatus^>^ list = gcnew List<ClrPeerOnlineStatus^>();
		for (int i = 0; i < peerCount; i++) 
			list->Add(gcnew ClrPeerOnlineStatus(peersStatus[i]));
		
		onQueryPeersOnlineStatusResult(requestId, list, static_cast<EnumQueryPeersOnlineStatusErrCode>(code));
	}
}

void AgoraClrRTM::NativeOnSubscriptionRequestResult(long long requestId, PEER_SUBSCRIPTION_STATUS_ERR code)
{
	if (onSubscriptionRequestResult) onSubscriptionRequestResult(requestId, static_cast<EnumPeerSubscriptionStatusErrCode>(code));
}

void AgoraClrRTM::NativeOnPeersOnlineStatusChanged(const PeerOnlineStatus status[], int count)
{
	if (onPeersOnlineStatusChanged) {
		List<ClrPeerOnlineStatus^>^ list = gcnew List<ClrPeerOnlineStatus^>();

		for (int i = 0; i < count; i++) {
			list->Add(gcnew ClrPeerOnlineStatus(status[i]));
		}

		onPeersOnlineStatusChanged(list);
	}
}

void AgoraClrRTM::NativeOnQueryPeersBySubscriptionOptionResult(long long requestId, const char* peerIds[], int peerCount, QUERY_PEERS_BY_SUBSCRIPTION_OPTION_ERR errorCode)
{
	if (onQueryPeersBySubscriptionOptionResult) {
		List<String^>^ list = gcnew List<String^>();
		for (int i = 0; i < peerCount; i++) {
			list->Add(gcnew String(peerIds[i]));
		}
		onQueryPeersBySubscriptionOptionResult(requestId, list, static_cast<EnumQueryPeersBySubscriptionOptionErrCode>(errorCode));
	}
}

void AgoraClrRTM::NativeOnSetLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onSetLocalUserAttributesResult) {
		onSetLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrRTM::NativeOnAddOrUpdateLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onAddOrUpdateLocalUserAttributesResult) onAddOrUpdateLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnDeleteLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onDeleteLocalUserAttributesResult) onDeleteLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnClearLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onClearLocalUserAttributesResult) onClearLocalUserAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnGetUserAttributesResult(long long id, const char* userId, const RtmAttribute* attributes, int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code)
{
	if (onGetUserAttributesResult) {
		List<ClrRtmAttribute^>^ list = gcnew List <ClrRtmAttribute^>;
		for (int i = 0; i < numberOfAttributes; i++) {
			list->Add(gcnew ClrRtmAttribute(attributes[i]));
		}

		onGetUserAttributesResult(id, gcnew String(userId), list, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrRTM::NativeOnSetChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onSetChannelAttributesResult) onSetChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnAddOrUpdateChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onAddOrUpdateChannelAttributesResult)
		onAddOrUpdateChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnDeleteChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onDeleteChannelAttributesResult)
		onDeleteChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnCleanChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code)
{
	if (onClearChannelAttributesResult)
		onClearChannelAttributesResult(id, static_cast<EnumAttributeOperationErrCode>(code));
}

void AgoraClrRTM::NativeOnGetChannelAttributesResult(long long id, const IRtmChannelAttribute* attributes[], int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code)
{
	if (onGetChannelAttributesResult) {
		List<ClrRtmChannelAttribute^>^ list = gcnew List<ClrRtmChannelAttribute^>;
		for (int i = 0; i < numberOfAttributes; i++) {
			list->Add(gcnew ClrRtmChannelAttribute(attributes[i]));
		}
		onGetChannelAttributesResult(id, list, static_cast<EnumAttributeOperationErrCode>(code));
	}
}

void AgoraClrRTM::NativeOnGetChannelMemberCountResult(long long id, const ChannelMemberCount* members, int count, GET_CHANNEL_MEMBER_COUNT_ERR_CODE code)
{
	if (onGetChannelMemberCountResult) {
		List<ClrChannelMemberCount^>^ list = gcnew List<ClrChannelMemberCount^>;
		for (int i = 0; i < count; i++)
			list->Add(gcnew ClrChannelMemberCount(members[i]));
		onGetChannelMemberCountResult(
			id, list, static_cast<EnumGetChannelMemberCountErrCode>(code));
	}
}

void AgoraClrRTM::NativeOnTokenExpired()
{
	if (onTokenExpired) onTokenExpired();
}

void AgoraClrRTM::NativeOnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE code)
{
	if (onRenewTokenResult)
		onRenewTokenResult(gcnew String(token), static_cast<EnumRenewTokenErrCode>(code));
}

void AgoraClrRTM::NativeOnMediaUploadingProgress(long long requestId,
	const MediaOperationProgress& progress)
{
	if (onMediaUploadingProgress)
		onMediaUploadingProgress(requestId, gcnew ClrMediaOperationProgress(progress));
}

void AgoraClrRTM::NativeOnMediaDownloadingProgress(long long requestId,
	const MediaOperationProgress& progress)
{
	if (onMediaDownloadingProgress)
		onMediaDownloadingProgress(requestId, gcnew ClrMediaOperationProgress(progress));
}

void AgoraClrRTM::NativeOnMediaCancelResult(long long requestId, CANCEL_MEDIA_ERR_CODE code)
{
	if (onMediaCancelResult)
		onMediaCancelResult(requestId, static_cast<EnumCancelMediaErrCode>(code));
}

void AgoraClrRTM::NativeOnFileMediaUploadResult(long long requestId,  IFileMessage* fileMessage,
	UPLOAD_MEDIA_ERR_CODE code)
{
	if (onFileMediaUploadResult)
		onFileMediaUploadResult(requestId, gcnew ClrFileMessage(fileMessage), static_cast<EnumUploadMediaErrCode>(code));
}

void AgoraClrRTM::NativeOnImageMediaUploadResult(long long requestId,  IImageMessage* fileMessage,
	UPLOAD_MEDIA_ERR_CODE code)
{
	if (onImageMediaUploadResult)
		onImageMediaUploadResult(requestId, gcnew ClrImageMessage(fileMessage), static_cast<EnumUploadMediaErrCode>(code));
}

void AgoraClrRTM::NativeOnFileMessageReceivedFromPeer(const char* peerId, const IFileMessage* message)
{
	if (onFileMessageReceivedFromPeer)
		onFileMessageReceivedFromPeer(gcnew String(peerId), gcnew ClrFileMessage(const_cast<IFileMessage*>(message)));
}

void AgoraClrRTM::NativeOnImageMessageReceivedFromPeer(const char* peerId, const IImageMessage* message)
{
	if (onImageMessageReceivedFromPeer)
		onImageMessageReceivedFromPeer(gcnew String(peerId), gcnew ClrImageMessage(const_cast<IImageMessage*>(message)));
}


void AgoraClrRTM::NativeOnMediaDownloadToMemoryResult(long long requestId, const char* memory,
		long long length, DOWNLOAD_MEDIA_ERR_CODE code)
{
	if (onMediaDownloadToMemoryResult)
	{
		const auto result = gcnew array<Byte>(length);
		if (length > 0) 
			Marshal::Copy(IntPtr(reinterpret_cast<void*>(const_cast<char*>(memory))), result, 0, length);
		onMediaDownloadToMemoryResult(requestId, result,static_cast<EnumDownloadMediaErrCode>(code));
	}
}
void AgoraClrRTM::NativeOnMediaDownloadToFileResult(long long requestId,
	DOWNLOAD_MEDIA_ERR_CODE code)
{
	if (onMediaDownloadToFileResult)
		onMediaDownloadToFileResult(requestId, static_cast<EnumDownloadMediaErrCode>(code));
}
void AgoraClrRTM::bindEventHandler()
{
	regEvent(rtmEvents->onLoginSuccessEvent, gcnew OnLoginSuccessType::Type(this, &AgoraClrRTM::NativeOnLoginSuccess));
	regEvent(rtmEvents->onLoginFailureEvent, gcnew OnLoginFailureType::Type(this, &AgoraClrRTM::NativeOnLoginFailure));
	regEvent(rtmEvents->onLogoutEvent, gcnew OnLogoutType::Type(this, &AgoraClrRTM::NativeOnLogout));
	regEvent(rtmEvents->onConnectionStateChangedEvent,gcnew OnConnectionStateChangedType::Type(this,&AgoraClrRTM::NativeOnConnectionStateChanged));
	regEvent(rtmEvents->onSendMessageResultEvent, gcnew RTMEventType::OnSendMessageResultType::Type(this, &AgoraClrRTM::NativeOnSendMessageResult));
	regEvent(rtmEvents->onMessageReceivedFromPeerEvent, gcnew OnMessageReceivedFromPeerType::Type(this, &AgoraClrRTM::NativeOnMessageReceivedFromPeer));
	regEvent(rtmEvents->onQueryPeersOnlineStatusResultEvent, gcnew OnQueryPeersOnlineStatusResultType::Type(this, &AgoraClrRTM::NativeOnQueryPeersOnlineStatusResult));
	regEvent(rtmEvents->onSubscriptionRequestResultEvent, gcnew OnSubscriptionRequestResultType::Type(this, &AgoraClrRTM::NativeOnSubscriptionRequestResult));
	regEvent(rtmEvents->onPeersOnlineStatusChangedEvent, gcnew OnPeersOnlineStatusChangedType::Type(this, &AgoraClrRTM::NativeOnPeersOnlineStatusChanged));
	regEvent(rtmEvents->onQueryPeersBySubscriptionOptionResultEvent, gcnew OnQueryPeersBySubscriptionOptionResultType::Type(this, &AgoraClrRTM::NativeOnQueryPeersBySubscriptionOptionResult));
	regEvent(rtmEvents->onSetLocalUserAttributesResultEvent, gcnew OnSetLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnSetLocalUserAttributesResult));
	regEvent(rtmEvents->onAddOrUpdateLocalUserAttributesResultEvent, gcnew OnAddOrUpdateLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnAddOrUpdateLocalUserAttributesResult));
	regEvent(rtmEvents->onDeleteLocalUserAttributesResultEvent, gcnew OnDeleteLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnDeleteLocalUserAttributesResult));
	regEvent(rtmEvents->onClearLocalUserAttributesResultEvent, gcnew OnClearLocalUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnClearLocalUserAttributesResult));
	regEvent(rtmEvents->onGetUserAttributesResultEvent, gcnew OnGetUserAttributesResultType::Type(this, &AgoraClrRTM::NativeOnGetUserAttributesResult));
	regEvent(rtmEvents->OnSetChannelAttributesResultEvent, gcnew OnSetChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnSetChannelAttributesResult));
	regEvent(rtmEvents->onAddOrUpdateChannelAttributesResultEvent, gcnew OnAddOrUpdateChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnAddOrUpdateChannelAttributesResult));
	regEvent(rtmEvents->onDeleteChannelAttributesResultEvent, gcnew OnDeleteChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnDeleteChannelAttributesResult));
	regEvent(rtmEvents->onClearChannelAttributesResultEvent, gcnew OnClearChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnCleanChannelAttributesResult));
	regEvent(rtmEvents->onGetChannelAttributesResultEvent, gcnew OnGetChannelAttributesResultType::Type(this, &AgoraClrRTM::NativeOnGetChannelAttributesResult));
	regEvent(rtmEvents->onGetChannelMemberCountResultEvent, gcnew OnGetChannelMemberCountResultType::Type(this, &AgoraClrRTM::NativeOnGetChannelMemberCountResult));
	regEvent(rtmEvents->onTokenExpiredEvent, gcnew OnTokenExpiredType::Type(this, &AgoraClrRTM::NativeOnTokenExpired));
	regEvent(rtmEvents->onRenewTokenResultEvent, gcnew OnRenewTokenResultType::Type(this, &AgoraClrRTM::NativeOnRenewTokenResult));

	regEvent(rtmEvents->onMediaUploadingProgressEvent, gcnew OnMediaUploadingProgressType::Type(this, &AgoraClrRTM::NativeOnMediaUploadingProgress));
	regEvent(rtmEvents->onMediaDownloadingProgressEvent, gcnew OnMediaDownloadingProgressType::Type(this, &AgoraClrRTM::NativeOnMediaDownloadingProgress));
	regEvent(rtmEvents->onMediaCancelResultEvent, gcnew OnMediaCancelResultType::Type(this, &AgoraClrRTM::NativeOnMediaCancelResult));
	regEvent(rtmEvents->onFileMediaUploadResultEvent, gcnew OnFileMediaUploadResultType::Type(this, &AgoraClrRTM::NativeOnFileMediaUploadResult));
	regEvent(rtmEvents->onImageMediaUploadResultEvent, gcnew OnImageMediaUploadResultType::Type(this, &AgoraClrRTM::NativeOnImageMediaUploadResult));
	regEvent(rtmEvents->onFileMessageReceivedFromPeerEvent, gcnew OnFileMessageReceivedFromPeerType::Type(this, &AgoraClrRTM::NativeOnFileMessageReceivedFromPeer));
	regEvent(rtmEvents->onImageMessageReceivedFromPeerEvent, gcnew OnImageMessageReceivedFromPeerType::Type(this, &AgoraClrRTM::NativeOnImageMessageReceivedFromPeer));
	regEvent(rtmEvents->onMediaDownloadToMemoryResultEvent, gcnew OnMediaDownloadToMemoryResultType::Type(this, &AgoraClrRTM::NativeOnMediaDownloadToMemoryResult));
	regEvent(rtmEvents->onMediaDownloadToFileResultEvent, gcnew OnMediaDownloadToFileResultType::Type(this, &AgoraClrRTM::NativeOnMediaDownloadToFileResult));
}

