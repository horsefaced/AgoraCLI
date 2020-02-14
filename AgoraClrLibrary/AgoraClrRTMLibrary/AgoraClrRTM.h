#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"
#include "AgoraClrRTMEnum.h"
#include "AgoraClrRTMTypes.h"
#include "AgoraClrRTMEventHandler.h"
#include <memory>

using namespace agora::rtm;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace AgoraClrLibrary {

	template<typename ...T>
	ref struct AT {
		delegate void Type(T...);
	};

	template<>
	ref struct AT<> {
		delegate void Type();
	};

	template<typename R, typename ...T>
	ref struct FT {
		delegate R Type(T...);
	};

	template<typename R>
	ref struct FT<R> {
		delegate R Type();
	};
	
	public ref class AgoraClrRTM
	{
	public:
		AgoraClrRTM(String^ vendorkey);
		~AgoraClrRTM();

		//登入登出相关
		int login(String^ token, String^ userId);
		int logout();
		AT<>::Type^ onLoginSuccess;
		AT<EnumLoginErrCode>::Type^ onLoginFailure;
		AT<EnumLogoutErrCode>::Type^ onLogout;
		AT<EnumConnectionState, EnumConnectionChangeReason>::Type^ onConnectionStateChanged;

		//点对点消息
		ClrMessage^ createMessage();
		int sendMessageToPeer(String^ peerId, ClrMessage^ msg, ClrSendMessageOptions^ options);
		AT<long long, EnumPeerMessageErrCode>::Type^ onSendMessageResult;
		AT<String^, ClrMessage^>::Type^ onMessageReceivedFromPeer;

		//todo: 查询单个或多个用户的在线状态
		
	private:
		IRtmService* service;
		AgoraClrRTMEventHandler* rtmEvents;
		List<GCHandle>^ gchs;

	private:
		void NativeOnLoginSuccess();
		void NativeOnLoginFailure(LOGIN_ERR_CODE code);
		void NativeOnLogout(LOGOUT_ERR_CODE code);
		void NativeOnConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason);
		void NativeOnSendMessageResult(long long id, PEER_MESSAGE_ERR_CODE code);
		void NativeOnMessageReceivedFromPeer(const char* peerId, const IMessage* message);

	private:
		template<typename E, typename D>
		inline void regEvent(E &e, D^ d)
		{
			gchs->Add(GCHandle::Alloc(d));
			e = reinterpret_cast<E>(Marshal::GetFunctionPointerForDelegate(d).ToPointer());
		}

		void bindEventHandler();
	};

}

