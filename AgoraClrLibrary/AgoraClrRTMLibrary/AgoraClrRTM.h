#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"
#include "AgoraClrRTMEnum.h"
#include "AgoraClrRTMTypes.h"
#include "AgoraClrRTMEventHandler.h"
#include "AgoraClrRTMChannel.h"
#include "AgoraClrRTMCallManager.h"

#include <memory>

using namespace agora::rtm;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace AgoraClrLibrary {

	public ref class AgoraClrRTM
	{
	public:
		AgoraClrRTM();
		~AgoraClrRTM();

		int initialize(String^ vendorkey);

		//登入登出相关
		int login(String^ userId);
		int login(String^ token, String^ userId);
		int logout();
		AT<>::Type^ onLoginSuccess;
		AT<EnumLoginErrCode>::Type^ onLoginFailure;
		AT<EnumLogoutErrCode>::Type^ onLogout;
		AT<EnumConnectionState, EnumConnectionChangeReason>::Type^ onConnectionStateChanged;

		//点对点消息
		ClrMessage^ createMessage();
		int sendMessageToPeer(String^ peerId, String^ msg);
		int sendMessageToPeer(String^ peerId, ClrMessage^ msg);
		int sendMessageToPeer(String^ peerId, ClrMessage^ msg, ClrSendMessageOptions^ options);
		AT<long long, EnumPeerMessageErrCode>::Type^ onSendMessageResult;
		AT<String^, ClrMessage^>::Type^ onMessageReceivedFromPeer;

		//查询单个或多个用户的在线状态
		int queryPeersOnlineStatus(List<String^>^ ids, long long% requestId);
		AT<long long, List<ClrPeerOnlineStatus^>^, EnumQueryPeersOnlineStatusErrCode>::Type^ onQueryPeersOnlineStatusResult;
		
		//订阅或退订单个或多个指定用户的在线状态
		int subscribePeersOnlineStatus(List<String^>^ ids, long long% requestId);
		int unsubscribePeersOnlineStatus(List<String^>^ ids, long long% requestId);
		int queryPeersBySubscriptionOption(EnumPeerSubscriptionOption option, long long% requestId);
		AT<long long, EnumPeerSubscriptionStatusErrCode>::Type^ onSubscriptionRequestResult;
		AT<List<ClrPeerOnlineStatus^>^>::Type^ onPeersOnlineStatusChanged;
		AT<long long, List<String^>^, EnumQueryPeersBySubscriptionOptionErrCode>::Type^ onQueryPeersBySubscriptionOptionResult;

		//用户属性增删改查
		int setLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId);
		int addOrUpdateLocalUserAttributes(List<ClrRtmAttribute^>^ attributes, long long% requestId);
		int deleteLocalUserAttributesByKeys(List<String^>^ keys, long long% requestId);
		int clearLocalUserAttributes(long long% requestId);
		int getUserAttributes(String^ userId, long long% requestId);
		int getUserAttributesByKeys(String^ userId, List<String^>^ keys, long long% requestId);
		AT<long long, EnumAttributeOperationErrCode>::Type^ onSetLocalUserAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onAddOrUpdateLocalUserAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onDeleteLocalUserAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onClearLocalUserAttributesResult;
		AT<long long, String^, List<ClrRtmAttribute^>^, EnumAttributeOperationErrCode>::Type^ onGetUserAttributesResult;

		//频道属性增删改查
		AgoraClrLibrary::ClrRtmChannelAttribute^ createChannelAttribute();
		int setChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId);
		int addOrUpdateChannelAttributes(String^ channelId, List<ClrRtmChannelAttribute^>^ attributes, ClrChannelAttributeOptions^ options, long long% requestId);
		int deleteChannelAttributesByKeys(String^ channelId, List<String^>^ keys, ClrChannelAttributeOptions^ options, long long% requestId);
		int clearChannelAttributes(String^ channelId, ClrChannelAttributeOptions^ options, long long% requestId);
		int getChannelAttributes(String^ channelId, long long% requestId);
		int getChannelAttributesByKeys(String^ channelId, List<String^>^ keys, long long% requestId);
		AT<long long, EnumAttributeOperationErrCode>::Type^ onSetChannelAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onAddOrUpdateChannelAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onDeleteChannelAttributesResult;
		AT<long long, EnumAttributeOperationErrCode>::Type^ onClearChannelAttributesResult;
		AT<long long, List<ClrRtmChannelAttribute^>^, EnumAttributeOperationErrCode>::Type^ onGetChannelAttributesResult;

		//查询单个或多个频道的成员人数
		int getChannelMemberCount(List<String^>^ ids, long long% requestId);
		AT<long long, List<ClrChannelMemberCount^>^, EnumGetChannelMemberCountErrCode>::Type^ onGetChannelMemberCountResult;

		//加入离开频道相关
		AgoraClrRTMChannel^ createChannel(String^ id);

		//呼叫邀请管理
		AgoraClrRTMCallManager^ getRtmCallManager();

		//更新token
		int renewToken(String^ token);
		AT<>::Type^ onTokenExpired;
		AT<String^, EnumRenewTokenErrCode>::Type^ onRenewTokenResult;

		//日志设置与版本查询
		int setLogFile(String^ file);
		int setLogFilter(EnumLogFilterType filter);
		int setLogFileSize(int size);
		static String^ getRTMSdkVersion();

		//1.3版本新增 文件+图片消息 （最大30M，服务器最多放七天）
		int createFileMessageByUploading(String^ filePath,long long% requestId);
		int createImageMessageByUploading(String^ filePath,long long% requestId);
		int cancelMediaUpload(long requestId);
		int cancelMediaDownload(long requestId);
		ClrFileMessage^ createFileMessageByMediaId(String^ mediaId);
		ClrImageMessage^ createImageMessageByMediaId(String^ mediaId);
		int downloadMediaToMemory(String^ mediaId,long long% requestId);
		int downloadMediaToFile(String^ mediaId,String^ filePath,long long% requestId);

		AT<long long,ClrMediaOperationProgress^>::Type^ onMediaUploadingProgress;
		AT<long long,ClrMediaOperationProgress^>::Type^ onMediaDownloadingProgress;
		AT<long long,EnumCancelMediaErrCode>::Type^ onMediaCancelResult;
		AT<long long,ClrFileMessage^,EnumUploadMediaErrCode>::Type^ onFileMediaUploadResult;
		AT<long long,ClrImageMessage^,EnumUploadMediaErrCode>::Type^ onImageMediaUploadResult;
		AT<String^,ClrFileMessage^>::Type^ onFileMessageReceivedFromPeer;
		AT<String^,ClrImageMessage^>::Type^ onImageMessageReceivedFromPeer;
		AT<long long,array<Byte>^,EnumDownloadMediaErrCode>::Type^ onMediaDownloadToMemoryResult;
		AT<long long,EnumDownloadMediaErrCode>::Type^ onMediaDownloadToFileResult;
		
	private:
		IRtmService* service;
		AgoraClrRTMEventHandler* rtmEvents;
		AgoraClrRTMCallManager^ manager;

		List<GCHandle>^ gchs;
	    String^ appId;

	private:
		void NativeOnLoginSuccess();
		void NativeOnLoginFailure(LOGIN_ERR_CODE code);
		void NativeOnLogout(LOGOUT_ERR_CODE code);
		void NativeOnConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason);
		void NativeOnSendMessageResult(long long id, PEER_MESSAGE_ERR_CODE code);
		void NativeOnMessageReceivedFromPeer(const char* peerId, const IMessage* message);
		void NativeOnQueryPeersOnlineStatusResult(long long requestId, const PeerOnlineStatus* peersStatus, int peerCount, QUERY_PEERS_ONLINE_STATUS_ERR code);
		void NativeOnSubscriptionRequestResult(long long requestId, PEER_SUBSCRIPTION_STATUS_ERR code);
		void NativeOnPeersOnlineStatusChanged(const PeerOnlineStatus status[], int count);
		void NativeOnQueryPeersBySubscriptionOptionResult(long long requestId, const char* peerIds[], int peerCount, QUERY_PEERS_BY_SUBSCRIPTION_OPTION_ERR errorCode);
		void NativeOnSetLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnAddOrUpdateLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnDeleteLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnClearLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnGetUserAttributesResult(long long id, const char* userId, const RtmAttribute* attributes, int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnSetChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnAddOrUpdateChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnDeleteChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnCleanChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnGetChannelAttributesResult(long long id, const IRtmChannelAttribute* attributes[], int numberOfAttributes, ATTRIBUTE_OPERATION_ERR code);
		void NativeOnGetChannelMemberCountResult(long long id, const ChannelMemberCount* members, int count, GET_CHANNEL_MEMBER_COUNT_ERR_CODE code);
		void NativeOnTokenExpired();
		void NativeOnRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE code);

		//1.3版本新增 文件+图片消息 （最大30M，服务器最多放七天）
		void NativeOnMediaUploadingProgress(long long requestId,const MediaOperationProgress & progress);
		void NativeOnMediaDownloadingProgress(long long requestId,const MediaOperationProgress & progress);
		void NativeOnMediaCancelResult(long long requestId,	CANCEL_MEDIA_ERR_CODE code);
		void NativeOnFileMediaUploadResult(long long requestId, IFileMessage*  fileMessage,UPLOAD_MEDIA_ERR_CODE code);
		void NativeOnImageMediaUploadResult(long long requestId, IImageMessage*  fileMessage,UPLOAD_MEDIA_ERR_CODE code);
		void NativeOnFileMessageReceivedFromPeer(const char * peerId, const IFileMessage*  message);
		void NativeOnImageMessageReceivedFromPeer(const char * peerId, const IImageMessage*  message);
		void NativeOnMediaDownloadToMemoryResult(long long requestId,const char * memory,long long length,DOWNLOAD_MEDIA_ERR_CODE code);
		void NativeOnMediaDownloadToFileResult(long long requestId,DOWNLOAD_MEDIA_ERR_CODE code);
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

