#pragma once
#include "include\agora_api_win.h"

using namespace agora_sdk_win;

namespace AgoraClrLibrary {
	typedef void(__stdcall * PFOnReconnecting)(uint32_t nretry);
	typedef void(__stdcall * PFOnReconnected)(int fd);
	typedef void(__stdcall * PFOnLoginSuccess)(uint32_t uid, int fd);
	typedef void(__stdcall * PFOnLogout)(int ecode);
	typedef void(__stdcall * PFOnLoginFailed)(int ecode);
	typedef void(__stdcall * PFOnChannelJoined)(char const * channelID, size_t channelID_size);
	typedef void(__stdcall * PFOnChannelJoinFailed)(char const * channelID, size_t channelID_size, int ecode);
	typedef void(__stdcall * PFOnChannelLeaved)(char const * channelID, size_t channelID_size, int ecode);
	typedef void(__stdcall * PFOnChannelUserJoined)(char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnChannelUserLeaved)(char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnChannelUserList)(int n, char** accounts, uint32_t* uids);
	typedef void(__stdcall * PFOnChannelQueryUserNumResult)(char const * channelID, size_t channelID_size, int ecode, int num);
	typedef void(__stdcall * PFOnChannelAttrUpdated)(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size);
	typedef void(__stdcall * PFOnInviteReceived)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
	typedef void(__stdcall * PFOnInviteReceivedByPeer)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnInviteAcceptedByPeer)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnInviteRefusedByPeer)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnInviteFailed)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode);
	typedef void(__stdcall * PFOnInviteEndByPeer)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnInviteEndByMyself)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	typedef void(__stdcall * PFOnInviteMsg)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size);
	typedef void(__stdcall * PFOnMessageSendError)(char const * messageID, size_t messageID_size, int ecode);
	typedef void(__stdcall * PFOnMessageSendSuccess)(char const * messageID, size_t messageID_size);
	typedef void(__stdcall * PFOnMessageAppReceived)(char const * msg, size_t msg_size);
	typedef void(__stdcall * PFOnMessageInstantReceive)(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
	typedef void(__stdcall * PFOnMessageChannelReceive)(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
	typedef void(__stdcall * PFOnLog)(char const * txt, size_t txt_size);
	typedef void(__stdcall * PFOnInvokeRet)(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size);
	typedef void(__stdcall * PFOnMsg)(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size);
	typedef void(__stdcall * PFOnUserAttrResult)(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size);
	typedef void(__stdcall * PFOnUserAttrAllResult)(char const * account, size_t account_size, char const * value, size_t value_size);
	typedef void(__stdcall * PFOnSignalError)(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size);
	typedef void(__stdcall * PFOnQueryUserStatusResult)(char const * name, size_t name_size, char const * status, size_t status_size);

	delegate void NativeOnReconnectingDelegate(uint32_t nretry);
	delegate void NativeOnReconnectedDelegate(int fd);
	delegate void NativeOnLoginSuccessDelegate(uint32_t uid, int fd);
	delegate void NativeOnLogoutDelegate(int ecode);
	delegate void NativeOnLoginFailedDelegate(int ecode);
	delegate void NativeOnChannelJoinedDelegate(char const * channelID, size_t channelID_size);
	delegate void NativeOnChannelJoinFailedDelegate(char const * channelID, size_t channelID_size, int ecode);
	delegate void NativeOnChannelLeavedDelegate(char const * channelID, size_t channelID_size, int ecode);
	delegate void NativeOnChannelUserJoinedDelegate(char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnChannelUserLeavedDelegate(char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnChannelUserListDelegate(int n, char** accounts, uint32_t* uids);
	delegate void NativeOnChannelQueryUserNumResultDelegate(char const * channelID, size_t channelID_size, int ecode, int num);
	delegate void NativeOnChannelAttrUpdatedDelegate(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size);
	delegate void NativeOnInviteReceivedDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
	delegate void NativeOnInviteReceivedByPeerDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnInviteAcceptedByPeerDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnInviteRefusedByPeerDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnInviteFailedDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode);
	delegate void NativeOnInviteEndByPeerDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnInviteEndByMyselfDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
	delegate void NativeOnInviteMsgDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size);
	delegate void NativeOnMessageSendErrorDelegate(char const * messageID, size_t messageID_size, int ecode);
	delegate void NativeOnMessageSendSuccessDelegate(char const * messageID, size_t messageID_size);
	delegate void NativeOnMessageAppReceivedDelegate(char const * msg, size_t msg_size);
	delegate void NativeOnMessageInstantReceiveDelegate(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
	delegate void NativeOnMessageChannelReceiveDelegate(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
	delegate void NativeOnLogDelegate(char const * txt, size_t txt_size);
	delegate void NativeOnInvokeRetDelegate(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size);
	delegate void NativeOnMsgDelegate(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size);
	delegate void NativeOnUserAttrResultDelegate(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size);
	delegate void NativeOnUserAttrAllResultDelegate(char const * account, size_t account_size, char const * value, size_t value_size);
	delegate void NativeOnSignalErrorDelegate(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size);
	delegate void NativeOnQueryUserStatusResultDelegate(char const * name, size_t name_size, char const * status, size_t status_size);


	public class AgoraClrSignalCallback : public ICallBack
	{
	public:
		AgoraClrSignalCallback();

		PFOnReconnecting onReconnectingEvent = 0;
		PFOnReconnected onReconnectedEvent = 0;
		PFOnLoginSuccess onLoginSuccessEvent = 0;
		PFOnLogout onLogoutEvent = 0;
		PFOnLoginFailed onLoginFailedEvent = 0;
		PFOnChannelJoined onChannelJoinedEvent = 0;
		PFOnChannelJoinFailed onChannelJoinFailedEvent = 0;
		PFOnChannelLeaved onChannelLeavedEvent = 0;
		PFOnChannelUserJoined onChannelUserJoinedEvent = 0;
		PFOnChannelUserLeaved onChannelUserLeavedEvent = 0;
		PFOnChannelUserList onChannelUserListEvent = 0;
		PFOnChannelQueryUserNumResult onChannelQueryUserNumResultEvent = 0;
		PFOnChannelAttrUpdated onChannelAttrUpdatedEvent = 0;
		PFOnInviteReceived onInviteReceivedEvent = 0;
		PFOnInviteReceivedByPeer onInviteReceivedByPeerEvent = 0;
		PFOnInviteAcceptedByPeer onInviteAcceptedByPeerEvent = 0;
		PFOnInviteRefusedByPeer onInviteRefusedByPeerEvent = 0;
		PFOnInviteFailed onInviteFailedEvent = 0;
		PFOnInviteEndByPeer onInviteEndByPeerEvent = 0;
		PFOnInviteEndByMyself onInviteEndByMyselfEvent = 0;
		PFOnInviteMsg onInviteMsgEvent = 0;
		PFOnMessageSendError onMessageSendErrorEvent = 0;
		PFOnMessageSendSuccess onMessageSendSuccessEvent = 0;
		PFOnMessageAppReceived onMessageAppReceivedEvent = 0;
		PFOnMessageInstantReceive onMessageInstantReceiveEvent = 0;
		PFOnMessageChannelReceive onMessageChannelReceiveEvent = 0;
		PFOnLog onLogEvent = 0;
		PFOnInvokeRet onInvokeRetEvent = 0;
		PFOnMsg onMsgEvent = 0;
		PFOnUserAttrResult onUserAttrResultEvent = 0;
		PFOnUserAttrAllResult onUserAttrAllResultEvent = 0;
		PFOnSignalError onErrorEvent = 0;
		PFOnQueryUserStatusResult onQueryUserStatusResultEvent = 0;

		virtual void onReconnecting(uint32_t nretry);
		virtual void onReconnected(int fd);
		virtual void onLoginSuccess(uint32_t uid, int fd);
		virtual void onLogout(int ecode);
		virtual void onLoginFailed(int ecode);
		virtual void onChannelJoined(char const * channelID, size_t channelID_size);
		virtual void onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode);
		virtual void onChannelLeaved(char const * channelID, size_t channelID_size, int ecode);
		virtual void onChannelUserJoined(char const * account, size_t account_size, uint32_t uid);
		virtual void onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid);
		virtual void onChannelUserList(int n, char** accounts, uint32_t* uids);
		virtual void onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num);
		virtual void onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size);
		virtual void onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size);
		virtual void onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		virtual void onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		virtual void onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		virtual void onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode);
		virtual void onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		virtual void onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid);
		virtual void onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size);
		virtual void onMessageSendError(char const * messageID, size_t messageID_size, int ecode);
		virtual void onMessageSendSuccess(char const * messageID, size_t messageID_size);
		virtual void onMessageAppReceived(char const * msg, size_t msg_size);
		virtual void onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
		virtual void onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size);
		virtual void onLog(char const * txt, size_t txt_size);
		virtual void onInvokeRet(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size);
		virtual void onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size);
		virtual void onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size);
		virtual void onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size);
		virtual void onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size);
		virtual void onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size);
	};
}

