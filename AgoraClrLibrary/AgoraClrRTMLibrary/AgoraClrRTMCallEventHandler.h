#pragma once

#include "..\..\agorasdk\include\IAgoraRtmCallManager.h"
#include "AgoraClrRTMTypes.h"

using namespace agora::rtm;

namespace AgoraClrLibrary {
	namespace CallEventTypes {
		using OnLocalInvitationReceivedByPeerType = ET<ILocalCallInvitation*>;
		using OnLocalInvitationCanceledType = ET<ILocalCallInvitation*>;
		using OnLocalInvitationFailureType = ET<ILocalCallInvitation*, LOCAL_INVITATION_ERR_CODE>;
		using OnLocalInvitationAcceptedType = ET<ILocalCallInvitation*, const char*>;
		using OnLocalInvitationRefusedType = ET<ILocalCallInvitation*, const char*>;
		using OnRemoteInvitationRefusedType = ET<IRemoteCallInvitation*>;
		using OnRemoteInvitationAcceptedType = ET<IRemoteCallInvitation*>;
		using OnRemoteInvitationReceivedType = ET<IRemoteCallInvitation*>;
		using OnRemoteInvitationFailureType = ET<IRemoteCallInvitation*, REMOTE_INVITATION_ERR_CODE>;
		using OnRemoteInvitationCanceledType = ET<IRemoteCallInvitation*>;
	}

	using namespace CallEventTypes;

	public class AgoraClrRTMCallEventHandler : public IRtmCallEventHandler {
	private:
		template<typename F, typename ...Args>
	inline void call(F&& event, Args&&... args) { if (event) event(std::forward<Args>(args)...); }
	
	public:
		OnLocalInvitationReceivedByPeerType::Pointer onLocalInvitationRecievedByPeerEvent;
		OnLocalInvitationCanceledType::Pointer onLocalInvitationCanceledEvent;
		OnLocalInvitationFailureType::Pointer onLocalInvitationFailureEvent;
		OnLocalInvitationAcceptedType::Pointer onLocalInvitationAcceptedEvent;
		OnLocalInvitationRefusedType::Pointer onLocalInvitationRefusedEvent;
		OnRemoteInvitationRefusedType::Pointer onRemoteInvitationRefusedEvent;
		OnRemoteInvitationAcceptedType::Pointer onRemoteInvitationAcceptedEvent;
		OnRemoteInvitationReceivedType::Pointer onRemoteInvitationReceivedEvent;
		OnRemoteInvitationFailureType::Pointer onRemoteInvitationFailureEvent;
		OnRemoteInvitationCanceledType::Pointer onRemoteInvitationCanceledEvent;

		void onLocalInvitationReceivedByPeer(ILocalCallInvitation* lci) override { call(onLocalInvitationRecievedByPeerEvent, lci); }
		void onLocalInvitationAccepted(ILocalCallInvitation* lci, const char* response) override { call(onLocalInvitationAcceptedEvent, lci, response); }
		void onLocalInvitationCanceled(ILocalCallInvitation* lci) override { call(onLocalInvitationCanceledEvent, lci); }
		void onLocalInvitationFailure(ILocalCallInvitation* lci, LOCAL_INVITATION_ERR_CODE code) override { call(onLocalInvitationFailureEvent, lci, code); }
		void onLocalInvitationRefused(ILocalCallInvitation* lci, const char* response) override { call(onLocalInvitationRefusedEvent, lci, response); }

		void onRemoteInvitationRefused(IRemoteCallInvitation* rci) override { call(onRemoteInvitationRefusedEvent, rci); }
		void onRemoteInvitationAccepted(IRemoteCallInvitation* rci) override { call(onRemoteInvitationAcceptedEvent, rci); }
		void onRemoteInvitationReceived(IRemoteCallInvitation* rci) override { call(onRemoteInvitationReceivedEvent, rci); }
		void onRemoteInvitationFailure(IRemoteCallInvitation* rci, REMOTE_INVITATION_ERR_CODE code) override { call(onRemoteInvitationFailureEvent, rci, code); }
		void onRemoteInvitationCanceled(IRemoteCallInvitation* rci) override { call(onRemoteInvitationCanceledEvent, rci); }

	};
}
