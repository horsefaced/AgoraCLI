#include "stdafx.h"
#include "AgoraClrSignalCallback.h"


AgoraClrLibrary::AgoraClrSignalCallback::AgoraClrSignalCallback()
{
}

void AgoraClrLibrary::AgoraClrSignalCallback::onReconnecting(uint32_t nretry)
{
	if (onReconnectingEvent) onReconnectingEvent(nretry);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onReconnected(int fd)
{
	if (onReconnectedEvent) onReconnectedEvent(fd);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onLoginSuccess(uint32_t uid, int fd)
{
	if (onLoginSuccessEvent) onLoginSuccessEvent(uid, fd);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onLogout(int ecode)
{
	if (onLogoutEvent) onLogoutEvent(ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onLoginFailed(int ecode)
{
	if (onLoginFailedEvent) onLoginFailedEvent(ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelJoined(char const * channelID, size_t channelID_size)
{
	if (onChannelJoinedEvent) onChannelJoinedEvent(channelID, channelID_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode)
{
	if (onChannelJoinFailedEvent) onChannelJoinFailedEvent(channelID, channelID_size, ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelLeaved(char const * channelID, size_t channelID_size, int ecode)
{
	if (onChannelLeavedEvent) onChannelLeavedEvent(channelID, channelID_size, ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelUserJoined(char const * account, size_t account_size, uint32_t uid)
{
	if (onChannelUserJoinedEvent) onChannelUserJoinedEvent(account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid)
{
	if (onChannelUserLeavedEvent) onChannelUserLeavedEvent(account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelUserList(int n, char ** accounts, uint32_t * uids)
{
	if (onChannelUserListEvent) onChannelUserListEvent(n, accounts, uids);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num)
{
	if (onChannelQueryUserNumResultEvent) onChannelQueryUserNumResultEvent(channelID, channelID_size, ecode, num);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)
{
	if (onChannelAttrUpdatedEvent) onChannelAttrUpdatedEvent(channelID, channelID_size, name, name_size, value, value_size, type, type_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	if (onInviteReceivedEvent) onInviteReceivedEvent(channelID, channelID_size, account, account_size, uid, extra, extra_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteReceivedByPeerEvent) onInviteReceivedByPeerEvent(channelID, channelID_size, account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteAcceptedByPeerEvent) onInviteAcceptedByPeer(channelID, channelID_size, account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteRefusedByPeerEvent) onInviteRefusedByPeerEvent(channelID, channelID_size, account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode)
{
	if (onInviteFailedEvent) onInviteFailedEvent(channelID, channelID_size, account, account_size, uid, ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteEndByPeerEvent) onInviteEndByPeerEvent(channelID, channelID_size, account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteEndByMyselfEvent) onInviteEndByMyselfEvent(channelID, channelID_size, account, account_size, uid);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)
{
	if (onInviteMsgEvent) onInviteMsgEvent(channelID, channelID_size, account, account_size, uid, msgType, msgType_size, msgData, msgData_size, extra, extra_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMessageSendError(char const * messageID, size_t messageID_size, int ecode)
{
	if (onMessageSendErrorEvent) onMessageSendErrorEvent(messageID, messageID_size, ecode);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMessageSendSuccess(char const * messageID, size_t messageID_size)
{
	if (onMessageSendSuccessEvent) onMessageSendSuccessEvent(messageID, messageID_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMessageAppReceived(char const * msg, size_t msg_size)
{
	if (onMessageAppReceivedEvent) onMessageAppReceivedEvent(msg, msg_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	if (onMessageInstantReceiveEvent) onMessageInstantReceiveEvent(account, account_size, uid, msg, msg_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	if (onMessageChannelReceiveEvent) onMessageChannelReceiveEvent(channelID, channelID_size, account, account_size, uid, msg, msg_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onLog(char const * txt, size_t txt_size)
{
	if (onLogEvent) onLogEvent(txt, txt_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onInvokeRet(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size)
{
	if (onInvokeRetEvent) onInvokeRetEvent(name, name_size, ofu, reason, reason_size, resp, resp_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size)
{
	if (onMsgEvent) onMsgEvent(from, from_size, t, t_size, msg, msg_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size)
{
	if (onUserAttrResultEvent) onUserAttrResultEvent(account, account_size, name, name_size, value, value_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size)
{
	if (onUserAttrAllResultEvent) onUserAttrAllResultEvent(account, account_size, value, value_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size)
{
	if (onErrorEvent) onErrorEvent(name, name_size, ecode, desc, desc_size);
}

void AgoraClrLibrary::AgoraClrSignalCallback::onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size)
{
	if (onQueryUserStatusResultEvent) onQueryUserStatusResultEvent(name, name_size, status, status_size);
}
