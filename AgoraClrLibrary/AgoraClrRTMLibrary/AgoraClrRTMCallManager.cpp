#include "pch.h"
#include "AgoraClrRTMCallManager.h"
using namespace AgoraClrLibrary;

AgoraClrRTMCallManager::AgoraClrRTMCallManager(IRtmService* service)
{
	this->service = service;
	this->events = new AgoraClrRTMCallEventHandler();
	this->gchs = gcnew List<GCHandle>;
	this->manager = service->getRtmCallManager(this->events);
}

AgoraClrRTMCallManager::~AgoraClrRTMCallManager()
{
	this->manager->release();
	delete this->events;
	for each (GCHandle handle in gchs) handle.Free();
	gchs->Clear();
}

int AgoraClrRTMCallManager::acceptRemoteInvitation(ClrRemoteCallInvitation^ rci)
{
	return manager->acceptRemoteInvitation(rci);
}

int AgoraClrRTMCallManager::refuseRemoteInvitation(ClrRemoteCallInvitation^ rci)
{
	return manager->refuseRemoteInvitation(rci);
}

int AgoraClrRTMCallManager::sendLocalInvitation(ClrLocalCallInvation^ lci)
{
	auto ilci = lci->toILCI(manager);
	int result = manager->sendLocalInvitation(ilci);
	ilci->release();
	return result;
}

int AgoraClrRTMCallManager::cancelLocalInvitation(ClrLocalCallInvation^ lci)
{
	auto ilci = lci->toILCI(manager);
	int result = manager->cancelLocalInvitation(ilci);
	ilci->release();
	return result;
}

void AgoraClrRTMCallManager::NativeOnLocalInvitationReceivedByPeer(ILocalCallInvitation* lci)
{
	if (onLocalInvitationReceivedByPeer) onLocalInvitationReceivedByPeer(gcnew ClrLocalCallInvation(lci));
}

void AgoraClrRTMCallManager::NativeOnLocalInvitationAccepted(ILocalCallInvitation* lci, const char* response)
{
	if (onLocalInvitationAccepted) onLocalInvitationAccepted(gcnew ClrLocalCallInvation(lci), gcnew String(response));
}

void AgoraClrRTMCallManager::NativeOnLocalInvitationCanceled(ILocalCallInvitation* lci)
{
	if (onLocalInvitationCanceled)
		onLocalInvitationCanceled(gcnew ClrLocalCallInvation(lci));
}

void AgoraClrRTMCallManager::NativeOnLocalInvitationFailure(ILocalCallInvitation* lci, LOCAL_INVITATION_ERR_CODE code)
{
	if (onLocalInvitationFailure)
		onLocalInvitationFailure(gcnew ClrLocalCallInvation(lci), static_cast<EnumLocalInvitationErrCode>(code));
}

void AgoraClrRTMCallManager::NativeOnLocalInvitationRefused(ILocalCallInvitation* lci, const char* response)
{
	if (onLocalInvitationRefused)
		onLocalInvitationRefused(gcnew ClrLocalCallInvation(lci), gcnew String(response));
}

void AgoraClrRTMCallManager::NativeOnRemoteInvitationRefused(IRemoteCallInvitation* rci)
{
	if (onRemoteInvitationRefused)
		onRemoteInvitationRefused(gcnew ClrRemoteCallInvitation(rci));
}

void AgoraClrRTMCallManager::NativeOnRemoteInvitationAccepted(IRemoteCallInvitation* rci)
{
	if (onRemoteInvitationAccepted)
		onRemoteInvitationAccepted(gcnew ClrRemoteCallInvitation(rci));
}

void AgoraClrRTMCallManager::NativeOnRemoteInvitationReceived(IRemoteCallInvitation* rci)
{
	if (onRemoteInvitationReceived)
		onRemoteInvitationReceived(gcnew ClrRemoteCallInvitation(rci));
}

void AgoraClrRTMCallManager::NativeOnRemoteInvitationFailure(IRemoteCallInvitation* rci, REMOTE_INVITATION_ERR_CODE code)
{
	if (onRemoteInvitationFailure)
		onRemoteInvitationFailure(gcnew ClrRemoteCallInvitation(rci), static_cast<EnumRemoteInvitationErrCode>(code));
}

void AgoraClrRTMCallManager::NativeOnRemoteInvitationCanceled(IRemoteCallInvitation* rci)
{
	if (onRemoteInvitationCanceled)
		onRemoteInvitationCanceled(gcnew ClrRemoteCallInvitation(rci));
}

void AgoraClrRTMCallManager::bindEvents()
{
	regEvent(events->onLocalInvitationReceivedByPeerEvent, gcnew OnLocalInvitationReceivedByPeerType::Type(this, &AgoraClrRTMCallManager::NativeOnLocalInvitationReceivedByPeer));
	regEvent(events->onLocalInvitationAcceptedEvent, gcnew OnLocalInvitationAcceptedType::Type(this, &AgoraClrRTMCallManager::NativeOnLocalInvitationAccepted));
	regEvent(events->onLocalInvitationCanceledEvent, gcnew OnLocalInvitationCanceledType::Type(this, &AgoraClrRTMCallManager::NativeOnLocalInvitationCanceled));
	regEvent(events->onLocalInvitationFailureEvent, gcnew OnLocalInvitationFailureType::Type(this, &AgoraClrRTMCallManager::NativeOnLocalInvitationFailure));
	regEvent(events->onLocalInvitationRefusedEvent, gcnew OnLocalInvitationRefusedType::Type(this, &AgoraClrRTMCallManager::NativeOnLocalInvitationRefused));

	regEvent(events->onRemoteInvitationRefusedEvent, gcnew OnRemoteInvitationRefusedType::Type(this, &AgoraClrRTMCallManager::NativeOnRemoteInvitationRefused));
	regEvent(events->onRemoteInvitationAcceptedEvent, gcnew OnRemoteInvitationAcceptedType::Type(this, &AgoraClrRTMCallManager::NativeOnRemoteInvitationAccepted));
	regEvent(events->onRemoteInvitationReceivedEvent, gcnew OnRemoteInvitationReceivedType::Type(this, &AgoraClrRTMCallManager::NativeOnRemoteInvitationReceived));
	regEvent(events->onRemoteInvitationFailureEvent, gcnew OnRemoteInvitationFailureType::Type(this, &AgoraClrRTMCallManager::NativeOnRemoteInvitationFailure));
	regEvent(events->onRemoteInvitationCanceledEvent, gcnew OnRemoteInvitationCanceledType::Type(this, &AgoraClrRTMCallManager::NativeOnRemoteInvitationCanceled));
}