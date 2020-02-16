#pragma once

#include "..\..\agorasdk\include\IAgoraRtmCallManager.h"
#include "..\..\agorasdk\include\IAgoraRtmService.h"

#include "AgoraClrRTMCallEventHandler.h"
#include "AgoraClrRTMEnum.h"

using namespace agora::rtm;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace AgoraClrLibrary {
	public ref class AgoraClrRTMCallManager
	{
	public:
		AgoraClrRTMCallManager(IRtmService* service);
		~AgoraClrRTMCallManager();

		int sendLocalInvitation(ClrLocalCallInvation^ lci);
		int cancelLocalInvitation(ClrLocalCallInvation^ lci);

		int acceptRemoteInvitation(ClrRemoteCallInvitation^ rci);
		int refuseRemoteInvitation(ClrRemoteCallInvitation^ rci);

		using ATL = AT<ClrLocalCallInvation^>::Type^;
		ATL onLocalInvitationReceivedByPeer;
		ATL onLocalInvitationCanceled;
		AT<ClrLocalCallInvation^, String^>::Type^ onLocalInvitationAccepted;
		AT<ClrLocalCallInvation^, String^>::Type^ onLocalInvitationRefused;
		AT<ClrLocalCallInvation^, EnumLocalInvitationErrCode>::Type^ onLocalInvitationFailure;
	
		using ATR = AT<ClrRemoteCallInvitation^>::Type^;
		ATR onRemoteInvitationReceived;
		ATR onRemoteInvitationCanceled;
		ATR onRemoteInvitationAccepted;
		ATR onRemoteInvitationRefused;
		AT<ClrRemoteCallInvitation^, EnumRemoteInvitationErrCode>::Type^ onRemoteInvitationFailure;
	private:
		IRtmService* service;
		IRtmCallManager* manager;
		AgoraClrRTMCallEventHandler* events;
		List<GCHandle>^ gchs;

		void NativeOnLocalInvitationReceivedByPeer(ILocalCallInvitation* lci);
		void NativeOnLocalInvitationAccepted(ILocalCallInvitation* lci, const char* response);
		void NativeOnLocalInvitationCanceled(ILocalCallInvitation* lci);
		void NativeOnLocalInvitationFailure(ILocalCallInvitation* lci, LOCAL_INVITATION_ERR_CODE code);
		void NativeOnLocalInvitationRefused(ILocalCallInvitation* lci, const char* response);

		void NativeOnRemoteInvitationRefused(IRemoteCallInvitation* rci);
		void NativeOnRemoteInvitationAccepted(IRemoteCallInvitation* rci);
		void NativeOnRemoteInvitationReceived(IRemoteCallInvitation* rci);
		void NativeOnRemoteInvitationFailure(IRemoteCallInvitation* rci, REMOTE_INVITATION_ERR_CODE code);
		void NativeOnRemoteInvitationCanceled(IRemoteCallInvitation* rci);

	private:
		template<typename E, typename D>
		inline void regEvent(E& e, D^ d)
		{
			gchs->Add(GCHandle::Alloc(d));
			e = reinterpret_cast<E>(Marshal::GetFunctionPointerForDelegate(d).ToPointer());
		}

		void bindEvents();
	};

}

