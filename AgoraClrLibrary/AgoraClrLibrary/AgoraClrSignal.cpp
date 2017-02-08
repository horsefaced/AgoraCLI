#include "stdafx.h"
#include "AgoraClrSignal.h"
#include "AgoraClrLibrary.h"

using namespace agora_sdk_win;

AgoraClrLibrary::AgoraClrSignal::AgoraClrSignal(String^ venderId)
{
	std::string vender = AgoraClrLibrary::MarshalString(venderId);
	signal = getAgoraSDKInstanceWin(vender.c_str(), vender.length());
	gchs = gcnew List<GCHandle>();
	setCallback();
}

AgoraClrLibrary::AgoraClrSignal::~AgoraClrSignal()
{
	signal->stop();
	for each (GCHandle handle in gchs)
	{
		handle.Free();
	}
	this->!AgoraClrSignal();
}

AgoraClrLibrary::AgoraClrSignal::!AgoraClrSignal()
{
}

void AgoraClrLibrary::AgoraClrSignal::login(String ^ vendorId, String ^ account, String ^ token, Nullable<int> retry_time, Nullable<int> retry_count, String ^ device)
{
	std::string vendorStr = MarshalString(vendorId), accountStr = MarshalString(account), tokenStr = MarshalString(token);
	int time = retry_time.HasValue ? retry_time.Value : 30, count = retry_count.HasValue ? retry_count.Value : 3;
	signal->login2(vendorStr.c_str(), vendorStr.length(), accountStr.c_str(), accountStr.length(), tokenStr.c_str(), tokenStr.length(), 0, NULL, 0, time, count);
}

void AgoraClrLibrary::AgoraClrSignal::logout()
{
	signal->logout();
}

void AgoraClrLibrary::AgoraClrSignal::channelJoin(String ^ channelID)
{
	std::string channel = MarshalString(channelID);
	signal->channelJoin(channel.c_str(), channel.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelLeave(String ^ channelID)
{
	std::string channel = MarshalString(channelID);
	signal->channelLeave(channel.c_str(), channel.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelQueryUserNum(String ^ channelID)
{
	std::string channel = MarshalString(channelID);
	signal->channelQueryUserNum(channel.c_str(), channel.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelSetAttr(String ^ channelID, String ^ name, String ^ value)
{
	std::string channel = MarshalString(channelID), nameStr = MarshalString(name), valueStr = MarshalString(value);
	signal->channelSetAttr(channel.c_str(), channel.length(), nameStr.c_str(), nameStr.length(), valueStr.c_str(), valueStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelDelAttr(String ^ channelID, String ^ name)
{
	std::string channel = MarshalString(channelID), nameStr = MarshalString(name);
	signal->channelDelAttr(channel.c_str(), channel.length(), nameStr.c_str(), nameStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelClearAttr(String ^ channelID)
{
	std::string channel = MarshalString(channelID);
	signal->channelClearAttr(channel.c_str(), channel.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelInviteUser(String ^ channelID, String ^ account, String ^ extra)
{
	std::string channel = MarshalString(channelID), accountStr = MarshalString(account), extraStr = MarshalString(extra);
	signal->channelInviteUser2(channel.c_str(), channel.length(), accountStr.c_str(), accountStr.length(), extraStr.c_str(), extraStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelInviteDTMF(String ^ channelID, String ^ phone, String ^ dtmf)
{
	std::string channel = MarshalString(channelID), phoneStr = MarshalString(phone), dtmfStr = MarshalString(dtmf);
	signal->channelInviteDTMF(channel.c_str(), channel.length(), phoneStr.c_str(), phoneStr.length(), dtmfStr.c_str(), dtmfStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::channelInviteAccept(String ^ channelID, String ^ account)
{
	std::string channel = MarshalString(channelID), accountStr = MarshalString(account);
	signal->channelInviteAccept(channel.c_str(), channel.length(), accountStr.c_str(), accountStr.length(), 0);
}

void AgoraClrLibrary::AgoraClrSignal::channelInviteRefuse(String ^ channelID, String ^ account)
{
	std::string channel = MarshalString(channelID), accountStr = MarshalString(account);
	signal->channelInviteRefuse(channel.c_str(), channel.length(), accountStr.c_str(), accountStr.length(), 0);
}

void AgoraClrLibrary::AgoraClrSignal::channelInviteEnd(String ^ channelID, String ^ account)
{
	std::string channel = MarshalString(channelID), accountStr = MarshalString(account);
	signal->channelInviteEnd(channel.c_str(), channel.length(), accountStr.c_str(), accountStr.length(), 0);
}

void AgoraClrLibrary::AgoraClrSignal::messageInstantSend(String ^ account, String ^ msg, String ^ msgID)
{
	std::string accountStr = MarshalString(account), msgStr = MarshalString(msg), msgidStr = MarshalString(msgID);
	signal->messageInstantSend(accountStr.c_str(), accountStr.length(), 0, msgStr.c_str(), msgStr.length(), msgidStr.c_str(), msgidStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::messageChannelSend(String^ channel, String ^ msg, String ^ msgID)
{
	std::string channelStr = MarshalString(channel), msgidStr = MarshalString(msgID), msgStr = MarshalString(msg);
	signal->messageChannelSend(channelStr.c_str(), channelStr.length(), msgStr.c_str(), msgStr.length(), msgidStr.c_str(), msgidStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::setAttr(String ^ name, String ^ value)
{
	std::string nameStr = MarshalString(name), valueStr = MarshalString(value);
	signal->setAttr(nameStr.c_str(), nameStr.length(), valueStr.c_str(), valueStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::getAttr(String ^ name)
{
	std::string nameStr = MarshalString(name);
	signal->getAttr(nameStr.c_str(), nameStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::getAttrAll()
{
	signal->getAttrAll();
}

void AgoraClrLibrary::AgoraClrSignal::getUserAttr(String ^ account, String ^ name)
{
	std::string accountStr = MarshalString(account), nameStr = MarshalString(name);
	signal->getUserAttr(accountStr.c_str(), accountStr.length(), nameStr.c_str(), nameStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::getUserAttrAll(String ^ account)
{
	std::string accountStr = MarshalString(account);
	signal->getUserAttrAll(accountStr.c_str(), accountStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::queryUserStatus(String ^ account)
{
	std::string accountStr = MarshalString(account);
	signal->queryUserStatus(accountStr.c_str(), accountStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::invoke(String ^ name, String ^ req)
{
	std::string nameStr = MarshalString(name), reqStr = MarshalString(req);
	signal->invoke(nameStr.c_str(), nameStr.length(), reqStr.c_str(), reqStr.length());
}

void AgoraClrLibrary::AgoraClrSignal::start()
{
	signal->start();
}

void AgoraClrLibrary::AgoraClrSignal::stop()
{
	signal->stop();
}

bool AgoraClrLibrary::AgoraClrSignal::isOnline()
{
	return signal->isOnline();
}

int AgoraClrLibrary::AgoraClrSignal::getStatus()
{
	return signal->getStatus();
}

void AgoraClrLibrary::AgoraClrSignal::dbg(String ^ a, String ^ b)
{
	std::string aStr = MarshalString(a), bStr = MarshalString(b);
	signal->dbg(aStr.c_str(), aStr.length(), bStr.c_str(), bStr.length());
}

void * AgoraClrLibrary::AgoraClrSignal::regEvent(Object ^ obj)
{
	gchs->Add(GCHandle::Alloc(obj));
	return Marshal::GetFunctionPointerForDelegate(obj).ToPointer();
}

void AgoraClrLibrary::AgoraClrSignal::setCallback()
{
	AgoraClrSignalCallback* callback = new AgoraClrSignalCallback();
	callback->onReconnectingEvent = PFOnReconnecting(regEvent(gcnew NativeOnReconnectingDelegate(this, &AgoraClrSignal::NativeOnReconnecting)));
	callback->onReconnectedEvent = PFOnReconnected(regEvent(gcnew NativeOnReconnectedDelegate(this, &AgoraClrSignal::NativeOnReconnected)));
	callback->onLoginSuccessEvent = PFOnLoginSuccess(regEvent(gcnew NativeOnLoginSuccessDelegate(this, &AgoraClrSignal::NativeOnLoginSuccess)));
	callback->onLogoutEvent = PFOnLogout(regEvent(gcnew NativeOnLogoutDelegate(this, &AgoraClrSignal::NativeOnLogout)));
	callback->onLoginFailedEvent = PFOnLoginFailed(regEvent(gcnew NativeOnLoginFailedDelegate(this, &AgoraClrSignal::NativeOnLoginFailed)));
	callback->onChannelJoinedEvent = PFOnChannelJoined(regEvent(gcnew NativeOnChannelJoinedDelegate(this, &AgoraClrSignal::NativeOnChannelJoined)));
	callback->onChannelJoinFailedEvent = PFOnChannelJoinFailed(regEvent(gcnew NativeOnChannelJoinFailedDelegate(this, &AgoraClrSignal::NativeOnChannelJoinFailed)));
	callback->onChannelLeavedEvent = PFOnChannelLeaved(regEvent(gcnew NativeOnChannelLeavedDelegate(this, &AgoraClrSignal::NativeOnChannelLeaved)));
	callback->onChannelUserJoinedEvent = PFOnChannelUserJoined(regEvent(gcnew NativeOnChannelUserJoinedDelegate(this, &AgoraClrSignal::NativeOnChannelUserJoined)));
	callback->onChannelUserLeavedEvent = PFOnChannelUserLeaved(regEvent(gcnew NativeOnChannelUserLeavedDelegate(this, &AgoraClrSignal::NativeOnChannelUserLeaved)));
	callback->onChannelUserListEvent = PFOnChannelUserList(regEvent(gcnew NativeOnChannelUserListDelegate(this, &AgoraClrSignal::NativeOnChannelUserList)));
	callback->onChannelQueryUserNumResultEvent = PFOnChannelQueryUserNumResult(regEvent(gcnew NativeOnChannelQueryUserNumResultDelegate(this, &AgoraClrSignal::NativeOnChannelQueryUserNumResult)));
	callback->onChannelAttrUpdatedEvent = PFOnChannelAttrUpdated(regEvent(gcnew NativeOnChannelAttrUpdatedDelegate(this, &AgoraClrSignal::NativeOnChannelAttrUpdated)));
	callback->onInviteReceivedEvent = PFOnInviteReceived(regEvent(gcnew NativeOnInviteReceivedDelegate(this, &AgoraClrSignal::NativeOnInviteReceived)));
	callback->onInviteReceivedByPeerEvent = PFOnInviteReceivedByPeer(regEvent(gcnew NativeOnInviteReceivedByPeerDelegate(this, &AgoraClrSignal::NativeOnInviteReceivedByPeer)));
	callback->onInviteAcceptedByPeerEvent = PFOnInviteAcceptedByPeer(regEvent(gcnew NativeOnInviteAcceptedByPeerDelegate(this, &AgoraClrSignal::NativeOnInviteAcceptedByPeer)));
	callback->onInviteRefusedByPeerEvent = PFOnInviteRefusedByPeer(regEvent(gcnew NativeOnInviteRefusedByPeerDelegate(this, &AgoraClrSignal::NativeOnInviteRefusedByPeer)));
	callback->onInviteFailedEvent = PFOnInviteFailed(regEvent(gcnew NativeOnInviteFailedDelegate(this, &AgoraClrSignal::NativeOnInviteFailed)));
	callback->onInviteEndByPeerEvent = PFOnInviteEndByPeer(regEvent(gcnew NativeOnInviteEndByPeerDelegate(this, &AgoraClrSignal::NativeOnInviteEndByPeer)));
	callback->onInviteEndByMyselfEvent = PFOnInviteEndByMyself(regEvent(gcnew NativeOnInviteEndByMyselfDelegate(this, &AgoraClrSignal::NativeOnInviteEndByMyself)));
	callback->onInviteMsgEvent = PFOnInviteMsg(regEvent(gcnew NativeOnInviteMsgDelegate(this, &AgoraClrSignal::NativeOnInviteMsg)));
	callback->onMessageSendErrorEvent = PFOnMessageSendError(regEvent(gcnew NativeOnMessageSendErrorDelegate(this, &AgoraClrSignal::NativeOnMessageSendError)));
	callback->onMessageSendSuccessEvent = PFOnMessageSendSuccess(regEvent(gcnew NativeOnMessageSendSuccessDelegate(this, &AgoraClrSignal::NativeOnMessageSendSuccess)));
	callback->onMessageAppReceivedEvent = PFOnMessageAppReceived(regEvent(gcnew NativeOnMessageAppReceivedDelegate(this, &AgoraClrSignal::NativeOnMessageAppReceived)));
	callback->onMessageInstantReceiveEvent = PFOnMessageInstantReceive(regEvent(gcnew NativeOnMessageInstantReceiveDelegate(this, &AgoraClrSignal::NativeOnMessageInstantReceive)));
	callback->onMessageChannelReceiveEvent = PFOnMessageChannelReceive(regEvent(gcnew NativeOnMessageChannelReceiveDelegate(this, &AgoraClrSignal::NativeOnMessageChannelReceive)));
	callback->onLogEvent = PFOnLog(regEvent(gcnew NativeOnLogDelegate(this, &AgoraClrSignal::NativeOnLog)));
	callback->onInvokeRetEvent = PFOnInvokeRet(regEvent(gcnew NativeOnInvokeRetDelegate(this, &AgoraClrSignal::NativeOnInvokeRet)));
	callback->onMsgEvent = PFOnMsg(regEvent(gcnew NativeOnMsgDelegate(this, &AgoraClrSignal::NativeOnMsg)));
	callback->onUserAttrResultEvent = PFOnUserAttrResult(regEvent(gcnew NativeOnUserAttrResultDelegate(this, &AgoraClrSignal::NativeOnUserAttrResult)));
	callback->onUserAttrAllResultEvent = PFOnUserAttrAllResult(regEvent(gcnew NativeOnUserAttrAllResultDelegate(this, &AgoraClrSignal::NativeOnUserAttrAllResult)));
	callback->onErrorEvent = PFOnSignalError(regEvent(gcnew NativeOnSignalErrorDelegate(this, &AgoraClrSignal::NativeOnError)));
	callback->onQueryUserStatusResultEvent = PFOnQueryUserStatusResult(regEvent(gcnew NativeOnQueryUserStatusResultDelegate(this, &AgoraClrSignal::NativeOnQueryUserStatusResult)));

	signal->callbackSet(callback);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnReconnecting(uint32_t nretry)
{
	if (onReconnecting) PFOnReconnecting(nretry);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnReconnected(int fd)
{
	if (onReconnected) onReconnected(fd);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnLoginSuccess(uint32_t uid, int fd)
{
	if (onLoginSuccess) onLoginSuccess(uid, fd);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnLogout(int ecode)
{
	if (onLogout) onLogout(ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnLoginFailed(int ecode)
{
	if (onLoginFailed) onLoginFailed(ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelJoined(char const * channelID, size_t channelID_size)
{
	if (onChannelJoined) onChannelJoined(gcnew String(channelID));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode)
{
	if (onChannelJoinFailed) onChannelJoinFailed(gcnew String(channelID), ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelLeaved(char const * channelID, size_t channelID_size, int ecode)
{
	if (onChannelLeaved) onChannelLeaved(gcnew String(channelID), ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelUserJoined(char const * account, size_t account_size, uint32_t uid)
{
	if (onChannelUserJoined) onChannelUserJoined(gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelUserLeaved(char const * account, size_t account_size, uint32_t uid)
{
	if (onChannelUserLeaved) onChannelUserLeaved(gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelUserList(int n, char ** accounts, uint32_t * uids)
{
	if (onChannelUserList) {
		List<String^>^ accountList = gcnew List<String^>();
		List<int>^ uidList = gcnew List<int>();
		for (int i = 0; i < n; i++) {
			accountList->Add(gcnew String(accounts[i]));
			uidList->Add(uids[i]);
		}
		onChannelUserList(accountList, uidList);
	}
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num)
{
	if (onChannelQueryUserNumResult) onChannelQueryUserNumResult(gcnew String(channelID), ecode, num);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)
{
	if (onChannelAttrUpdated) onChannelAttrUpdated(gcnew String(channelID), gcnew String(name), gcnew String(value), gcnew String(type));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	if (onInviteReceived) onInviteReceived(gcnew String(channelID), gcnew String(account), uid, gcnew String(extra));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteReceivedByPeer) onInviteReceivedByPeer(gcnew String(channelID), gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteAcceptedByPeer) onInviteAcceptedByPeer(gcnew String(channelID), gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteRefusedByPeer) onInviteRefusedByPeer(gcnew String(channelID), gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode)
{
	if (onInviteFailed) onInviteFailed(gcnew String(channelID), gcnew String(account), uid, ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteEndByPeer) onInviteEndByPeer(gcnew String(channelID), gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	if (onInviteEndByMyself) onInviteEndByMyself(gcnew String(channelID), gcnew String(account), uid);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)
{
	if (onInviteMsg) onInviteMsg(gcnew String(channelID), gcnew String(account), uid, gcnew String(msgType), gcnew String(msgData), gcnew String(extra));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMessageSendError(char const * messageID, size_t messageID_size, int ecode)
{
	if (onMessageSendError) onMessageSendError(gcnew String(messageID), ecode);
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMessageSendSuccess(char const * messageID, size_t messageID_size)
{
	if (onMessageSendSuccess) onMessageSendSuccess(gcnew String(messageID));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMessageAppReceived(char const * msg, size_t msg_size)
{
	if (onMessageAppReceived) onMessageAppReceived(gcnew String(msg));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	if (onMessageInstantReceive) onMessageInstantReceive(gcnew String(account), uid, gcnew String(msg));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	if (onMessageChannelReceive) onMessageChannelReceive(gcnew String(channelID), gcnew String(account), uid, gcnew String(msg));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnLog(char const * txt, size_t txt_size)
{
	if (onLog) onLog(gcnew String(txt));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnInvokeRet(char const * name, size_t name_size, int ofu, char const * reason, size_t reason_size, char const * resp, size_t resp_size)
{
	if (onInvokeRet) onInvokeRet(gcnew String(name), ofu, gcnew String(reason), gcnew String(resp));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size)
{
	if (onMsg) onMsg(gcnew String(from), gcnew String(t), gcnew String(msg));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size)
{
	if (onUserAttrResult) onUserAttrResult(gcnew String(account), gcnew String(name), gcnew String(value));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size)
{
	if (onUserAttrAllResult) onUserAttrAllResult(gcnew String(account), gcnew String(value));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size)
{
	if (onError) onError(gcnew String(name), ecode, gcnew String(desc));
}

void AgoraClrLibrary::AgoraClrSignal::NativeOnQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size)
{
	if (onQueryUserStatusResult) onQueryUserStatusResult(gcnew String(name), gcnew String(status));
}


