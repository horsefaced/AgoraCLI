#include "pch.h"
#include "AgoraClrRTMChannel.h"
#include "AgoraClrRTMChannelEventHandler.h"

#include <msclr/marshal_cppstd.h>
#include <string>
using namespace Collections::Generic;
using namespace msclr::interop;
using namespace AgoraClrLibrary;

AgoraClrRTMChannel::AgoraClrRTMChannel(IRtmService* service, String^ id)
{
	this->events = new AgoraClrRTMChannelEventHandler();
	IChannel* channel = service->createChannel(marshal_as<std::string>(id).c_str(), this->events);
	if (channel == nullptr) {
		delete events;
		throw gcnew System::ArgumentNullException();
	}

	this->channel = channel;
	this->id = gcnew String(id);
	this->gchs = gcnew List<GCHandle>;
	this->service = service;
	
	bindEvents();
}

AgoraClrRTMChannel::~AgoraClrRTMChannel()
{
	this->service = nullptr;
	for each (GCHandle handler in this->gchs)
	{
		handler.Free();
	}
	delete events;
	this->channel->release();
}

int AgoraClrRTMChannel::Join()
{
	return channel->join();
}

int AgoraClrRTMChannel::Leave()
{
	return channel->leave();
}

void AgoraClrRTMChannel::Release()
{
	channel ->release();
}

int AgoraClrRTMChannel::SendMessage(ClrMessage^ msg)
{
	IMessage* raw = msg->toMessage(service);
	SendMessageOptions options;
	options.enableHistoricalMessaging=false;
	options.enableOfflineMessaging = false;
	const int result = channel->sendMessage(raw,options);
	raw->release();
	return result;
}

int AgoraClrRTMChannel::SendMessage(ClrMessage^ msg, ClrSendMessageOptions^ options)
{
	IMessage* raw = msg->toMessage(service);
	int result = channel->sendMessage(raw,options);
	raw->release();
	return result;
}

int AgoraClrRTMChannel::getMembers()
{
	return channel->getMembers();
}

void AgoraClrRTMChannel::NativeOnJoinSuccess()
{
	if (onJoinSuccess) onJoinSuccess();
}

void AgoraClrRTMChannel::NativeOnJoinFailure(JOIN_CHANNEL_ERR code)
{
	if (onJoinFailure) onJoinFailure(static_cast<EnumJoinChannelErrCode>(code));
}

void AgoraClrRTMChannel::NativeOnLeave(LEAVE_CHANNEL_ERR code)
{
	if (onLeave) onLeave(static_cast<EnumLeaveChannelErrCode>(code));
}

void AgoraClrRTMChannel::NativeOnMessageReceived(const char* userId, const IMessage* msg)
{
	if (onMessageReceived)
		onMessageReceived(gcnew String(userId), gcnew ClrMessage(const_cast<IMessage*>(msg)));
}

void AgoraClrRTMChannel::NativeOnSendMessageResult(long long id, CHANNEL_MESSAGE_ERR_CODE code)
{
	if (onSendMessageResult)
		onSendMessageResult(id, static_cast<EnumChannelMessageErrCode>(code));
}

void AgoraClrRTMChannel::NativeOnMemberJoined(IChannelMember* member)
{
	if (onMemberJoined) onMemberJoined(gcnew ClrChannelMember(member));
}

void AgoraClrRTMChannel::NativeOnMemberLeft(IChannelMember* member)
{
	if (onMemberLeft) onMemberLeft(gcnew ClrChannelMember(member));
}

void AgoraClrRTMChannel::NativeOnGetMembers(IChannelMember** members, int count, GET_MEMBERS_ERR code)
{
	if (onGetMembers) {
		List<ClrChannelMember^>^ list = gcnew List<ClrChannelMember^>;
		for (int i = 0; i < count; i++)
			list->Add(gcnew ClrChannelMember(members[i]));
		onGetMembers(list, static_cast<EnumGetMembersErrCode>(code));
	}
}

void AgoraClrRTMChannel::NativeOnAttributesUpdated(const IRtmChannelAttribute* attrs[], int count)
{
	if (onAttributesUpdated) {
		List<ClrRtmChannelAttribute^>^ list = gcnew List<ClrRtmChannelAttribute^>;
		for (int i = 0; i < count; i++)
			list->Add(gcnew ClrRtmChannelAttribute(attrs[i]));
		onAttributesUpdated(list);
	}
}

void AgoraClrRTMChannel::NativeOnMemberCountUpdated(int count)
{
	if (onMemberCountUpdated) onMemberCountUpdated(count);
}

void AgoraClrRTMChannel::NativeOnFileMessageReceived(const char* userId, const IFileMessage* message)
{
	if (onFileMessageReceived)
		onFileMessageReceived(gcnew String(userId), gcnew ClrFileMessage(const_cast<IFileMessage*>(message)));
}

void AgoraClrRTMChannel::NativeOnImageMessageReceived(const char* userId, const IImageMessage* message)
{
	if (onImageMessageReceived)
		onImageMessageReceived(gcnew String(userId), gcnew ClrImageMessage(const_cast<IImageMessage*>(message)));
}

void AgoraClrRTMChannel::bindEvents()
{
	regEvent(events->onJoinSuccessEvent, gcnew OnJoinSuccessType::Type(this, &AgoraClrRTMChannel::NativeOnJoinSuccess));
	regEvent(events->onJoinFailureEvent, gcnew OnJoinFailureType::Type(this, &AgoraClrRTMChannel::NativeOnJoinFailure));
	regEvent(events->onLeaveEvent, gcnew OnLeaveType::Type(this, &AgoraClrRTMChannel::NativeOnLeave));
	regEvent(events->onMessageReceivedEvent, gcnew OnMessageReceivedType::Type(this, &AgoraClrRTMChannel::NativeOnMessageReceived));
	regEvent(events->onSendMessageResultEvent, gcnew OnSendMessageResultType::Type(this, &AgoraClrRTMChannel::NativeOnSendMessageResult));
	regEvent(events->onMemberJoinedEvent, gcnew OnMemberJoinedType::Type(this, &AgoraClrRTMChannel::NativeOnMemberJoined));
	regEvent(events->onMemberLeftEvent, gcnew OnMemberLeftType::Type(this, &AgoraClrRTMChannel::NativeOnMemberLeft));
	regEvent(events->onGetMembersEvent, gcnew OnGetMembersType::Type(this, &AgoraClrRTMChannel::NativeOnGetMembers));
	regEvent(events->onAttributesUpdatedEvent, gcnew OnAttributesUpdatedType::Type(this, &AgoraClrRTMChannel::NativeOnAttributesUpdated));

	regEvent(events->onFileMessageReceivedEvent, gcnew OnFileMessageReceivedType::Type(this, &AgoraClrRTMChannel::NativeOnFileMessageReceived));
	regEvent(events->onImageMessageReceivedEvent, gcnew OnImageMessageReceivedType::Type(this, &AgoraClrRTMChannel::NativeOnImageMessageReceived));

}
