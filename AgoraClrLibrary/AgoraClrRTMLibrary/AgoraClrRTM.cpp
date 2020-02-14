
#include "pch.h"
#include "AgoraClrRTM.h"
#include "AgoraClrRTMEventHandler.h"

#include <msclr/marshal_cppstd.h>
#include <string>

using namespace msclr::interop;

AgoraClrLibrary::AgoraClrRTM::AgoraClrRTM(String^ vendorkey): service(createRtmService()), rtmEvents(new AgoraClrRTMEventHandler())
{
	bindEventHandler();
	int result = service->initialize(marshal_as<std::string>(vendorkey).c_str(), rtmEvents);
	if (result < 0) throw gcnew System::ArgumentException(result.ToString(), "vendorkey");

	
}

AgoraClrLibrary::AgoraClrRTM::~AgoraClrRTM()
{
	service->removeEventHandler(rtmEvents);
	delete rtmEvents;
	service->release();
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
	IMessage* raw;
	if (msg->Data == nullptr || msg->Data->Length == 0) 
		raw = service->createMessage();
	else {
		auto [rawData, length] = msg->rawData();
		raw = service->createMessage(static_cast<const uint8_t*>(rawData), length);
	}

	if (msg->Text != nullptr)
		raw->setText(marshal_as<std::string>(msg->Text).c_str());
	
	int result = service->sendMessageToPeer(marshal_as<std::string>(peerId).c_str(), raw, options);
	msg->ID = raw->getMessageId();
	raw->release();
	return result;
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

void AgoraClrLibrary::AgoraClrRTM::bindEventHandler()
{
	regEvent(rtmEvents->onLoginSuccessEvent, gcnew OnLoginSuccessType::Type(this, &AgoraClrRTM::NativeOnLoginSuccess));
	regEvent(rtmEvents->onLoginFailureEvent, gcnew OnLoginFailureType::Type(this, &AgoraClrRTM::NativeOnLoginFailure));
	regEvent(rtmEvents->onLogoutEvent, gcnew OnLogoutType::Type(this, &AgoraClrRTM::NativeOnLogout));
	regEvent(rtmEvents->onSendMessageResultEvent, gcnew OnSendMessageResultType::Type(this, &AgoraClrRTM::NativeOnSendMessageResult));
	regEvent(rtmEvents->onMessageReceivedFromPeerEvent, gcnew OnMessageReceivedFromPeerType::Type(this, &AgoraClrRTM::NativeOnMessageReceivedFromPeer));

}

