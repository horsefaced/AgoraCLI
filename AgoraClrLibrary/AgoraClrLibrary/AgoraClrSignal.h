#pragma once
#include "include\agora_api_win.h"
#include "AgoraClrSignalCallback.h"

using namespace agora_sdk_win;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace AgoraClrLibrary {

	public delegate void onReconnecting(int nretry);
	public delegate void onReconnected(int fd);
	public delegate void onLoginSuccess(int uid, int fd);
	public delegate void onLogout(int ecode);
	public delegate void onLoginFailed(int ecode);
	public delegate void onChannelJoined(String^ channelId);
	public delegate void onChannelJoinFailed(String^ channelId, int ecode);
	public delegate void onChannelLeaved(String^ channelId, int ecode);
	public delegate void onChannelUserJoined(String^ account, int uid);
	public delegate void onChannelUserLeaved(String^ account, int uid);
	public delegate void onChannelUserList(List<String^>^ accounts, List<int>^ uids);
	public delegate void onChannelQueryUserNumResult(String^ channelId, int ecode, int num);
	public delegate void onChannelAttrUpdated(String^ channelId, String^ name, String^ value, String^ type);
	public delegate void onInviteReceived(String^ channelId, String^ account, int uid, String^ extra);
	public delegate void onInviteReceivedByPeer(String^ channelId, String^ account, int uid);
	public delegate void onInviteAcceptedByPeer(String^ channelId, String^ account, int uid, String^ extra);
	public delegate void onInviteRefusedByPeer(String^ channelId, String^ account, int uid, String^ extra);
	public delegate void onInviteFailed(String^ channelId, String^ account, int uid, int ecode, String^ extra);
	public delegate void onInviteEndByPeer(String^ channelId, String^ account, int uid, String^ extra);
	public delegate void onInviteEndByMyself(String^ channelId, String^ account, int uid);
	public delegate void onInviteMsg(String^ channelId, String^ account, int uid, String^ msgType, String^ msgData, String^ extra);
	public delegate void onMessageSendError(String^ msgId, int ecode);
	public delegate void onMessageSendSuccess(String^ msgId);
	public delegate void onMessageAppReceived(String^ msg);
	public delegate void onMessageInstantReceive(String^ account, int uid, String^ msg);
	public delegate void onMessageChannelReceive(String^ channelId, String^ account, int uid, String^ msg);
	public delegate void onLog(String^ txt);
	public delegate void onInvokeRet(String^ name, int ofu, String^ reason, String^ resp);
	public delegate void onMsg(String^ from, String^ t, String^ msg);
	public delegate void onUserAttrResult(String^ account, String^ name, String^ value);
	public delegate void onUserAttrAllResult(String^ account, String^ value);
	public delegate void onSignalError(String^ name, int ecode, String^ desc);
	public delegate void onQueryUserStatusResult(String^ name, String^ status);


	public ref class AgoraClrSignal
	{
	public:
		onReconnecting^ onReconnecting;
		onReconnected^ onReconnected;
		onLoginSuccess^ onLoginSuccess;
		onLogout^ onLogout;
		onLoginFailed^ onLoginFailed;
		onChannelJoined^ onChannelJoined;
		onChannelJoinFailed^ onChannelJoinFailed;
		onChannelLeaved^ onChannelLeaved;
		onChannelUserJoined^ onChannelUserJoined;
		onChannelUserLeaved^ onChannelUserLeaved;
		onChannelUserList^ onChannelUserList;
		onChannelQueryUserNumResult^ onChannelQueryUserNumResult;
		onChannelAttrUpdated^ onChannelAttrUpdated;
		onInviteReceived^ onInviteReceived;
		onInviteReceivedByPeer^ onInviteReceivedByPeer;
		onInviteAcceptedByPeer^ onInviteAcceptedByPeer;
		onInviteRefusedByPeer^ onInviteRefusedByPeer;
		onInviteFailed^ onInviteFailed;
		onInviteEndByPeer^ onInviteEndByPeer;
		onInviteEndByMyself^ onInviteEndByMyself;
		onInviteMsg^ onInviteMsg;
		onMessageSendError^ onMessageSendError;
		onMessageSendSuccess^ onMessageSendSuccess;
		onMessageAppReceived^ onMessageAppReceived;
		onMessageInstantReceive^ onMessageInstantReceive;
		onMessageChannelReceive^ onMessageChannelReceive;
		onLog^ onLog;
		onInvokeRet^ onInvokeRet;
		onMsg^ onMsg;
		onUserAttrResult^ onUserAttrResult;
		onUserAttrAllResult^ onUserAttrAllResult;
		onSignalError^ onError;
		onQueryUserStatusResult^ onQueryUserStatusResult;

		AgoraClrSignal(String^ venderId);
		~AgoraClrSignal();
		!AgoraClrSignal();

		void login(String^ appId, String^ account, String^ token, String^ device);
		void login2(String^ vendorId, String^ account, String^ token, Nullable<int> retry_time, Nullable<int> retry_count, String^ device);
		void logout();

		void channelJoin(String^ channelID);
		void channelLeave(String^ channelID);
		void channelQueryUserNum(String^ channelID);
		void channelSetAttr(String^ channelID, String^ name, String^ value);
		void channelDelAttr(String^ channelID, String^ name);
		void channelClearAttr(String^ channelID);

		void channelInviteUser(String^ channelID, String^ account);
		void channelInviteUser2(String^ channelID, String^ account, String^ extra);
		void channelInviteDTMF(String^ channelID, String^ phone, String^ dtmf);

		void channelInviteAccept(String^ channelID, String^ account);
		void channelInviteRefuse(String^ channelID, String^ account, String^ extra);
		void channelInviteEnd(String^ channelID, String^ account);

		void messageInstantSend(String^ account, String^ msg, String^ msgID);
		void messageChannelSend(String^ channel, String^ msg, String^ msgID);
		void messageChannelSendForce(String^ channelID, String^ message, String^ messageID);

		void queryUserStatus(String^ account);

		void setAttr(String^ name, String^ value);
		void getAttr(String^ name);
		void getAttrAll();
		void getUserAttr(String^ account, String^ name);
		void getUserAttrAll(String^ account);

		int getStatus();

		int getSDKVersion();
		
		[ObsoleteAttribute]
		bool isOnline();

		//过渡接口
		void messageAppSend(String^ message, String^ messageID);
		void messagePushSend(String^ account, String^ message, String^ messageID);
		void messageChatSend(String^ account, String^ message, String^ messageID);
		//void messageDTMFSend 这个接口用到了uid，但在大部分接口中 uid 已经被废弃， 所以这个接口暂时不实现
		//这两个接口不知道是做什么的，所以参数就随便叫了
		void setBackground(int Out);
		void setNetworkStatus(int Out);
		void ping();
		

	private:
		IAgoraAPI* signal = 0;
		List<GCHandle>^ gchs;

		void* regEvent(Object^ obj);
		void setCallback();

		void NativeOnReconnecting(uint32_t nretry);
		void NativeOnReconnected(int fd);

		void NativeOnLoginSuccess(uint32_t uid, int fd);
		void NativeOnLogout(int ecode);
		void NativeOnLoginFailed(int ecode);

		void NativeOnChannelJoined(char const * channelID, size_t channelID_size);
		void NativeOnChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode);

		void NativeOnChannelLeaved(char const * channelID, size_t channelID_size, int ecode);

		void NativeOnChannelUserJoined(char const * account, size_t account_size, uint32_t uid);
		void NativeOnChannelUserLeaved(char const * account, size_t account_size, uint32_t uid);
		void NativeOnChannelUserList(int n, char** accounts, uint32_t* uids);

		void NativeOnChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num);

		void NativeOnChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size);

		void NativeOnInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
		void NativeOnInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);

		void NativeOnInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
		void NativeOnInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
		void NativeOnInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode, char const * extra, size_t extra_size);
		void NativeOnInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
		void NativeOnInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		void NativeOnInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size);

		void NativeOnMessageSendError(char const * messageID, size_t messageID_size, int ecode);
		void NativeOnMessageSendSuccess(char const * messageID, size_t messageID_size);
		void NativeOnMessageAppReceived(char const * msg, size_t msg_size);
		void NativeOnMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
		void NativeOnMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
		void NativeOnLog(char const * txt, size_t txt_size);
		void NativeOnInvokeRet(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size);
		void NativeOnMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size);
		void NativeOnUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size);
		void NativeOnUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size);
		void NativeOnError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size);
		void NativeOnQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size);

	};

}