#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"
#include "AgoraClrRTMTypes.h"

#include <type_traits>
#include <utility>

using namespace agora::rtm;

namespace AgoraClrLibrary {
	namespace RTMEventType {
		using OnLoginSuccessType = ET<void>;
		using OnLoginFailureType = ET<LOGIN_ERR_CODE>;
		using OnRenewTokenResultType = ET<const char*, RENEW_TOKEN_ERR_CODE>;
		using OnTokenExpiredType = ET<void>;
		using OnLogoutType = ET<LOGOUT_ERR_CODE>;
		using OnConnectionStateChangedType = ET<CONNECTION_STATE, CONNECTION_CHANGE_REASON>;
		using OnSendMessageResultType = ET<long long, PEER_MESSAGE_ERR_CODE>;
		using OnMessageReceivedFromPeerType = ET<const char*, const IMessage*>;
		using OnQueryPeersOnlineStatusResultType = ET<long long, const PeerOnlineStatus*, int, QUERY_PEERS_ONLINE_STATUS_ERR>;
		using OnSubscriptionRequestResultType = ET<long long, PEER_SUBSCRIPTION_STATUS_ERR>;
		using OnQueryPeersBySubscriptionOptionResultType = ET<long long, const char* [], int, QUERY_PEERS_BY_SUBSCRIPTION_OPTION_ERR>;
		using OnPeersOnlineStatusChangedType = ET<const PeerOnlineStatus[], int>;
		using OnSetLocalUserAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnAddOrUpdateLocalUserAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnDeleteLocalUserAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnClearLocalUserAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnGetUserAttributesResultType = ET<long long, const char*, const RtmAttribute*, int, ATTRIBUTE_OPERATION_ERR>;
		using OnSetChannelAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnAddOrUpdateChannelAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnDeleteChannelAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnClearChannelAttributesResultType = ET<long long, ATTRIBUTE_OPERATION_ERR>;
		using OnGetChannelAttributesResultType = ET<long long, const IRtmChannelAttribute * [], int, ATTRIBUTE_OPERATION_ERR>;
		using OnGetChannelMemberCountResultType = ET<long long, const ChannelMemberCount*, int, GET_CHANNEL_MEMBER_COUNT_ERR_CODE>;

		//1.3版本新增 文件+图片消息 （最大30M，服务器最多放七天）
		using OnMediaUploadingProgressType = ET<long long,const MediaOperationProgress&>;
		using OnMediaDownloadingProgressType = ET<long long, const MediaOperationProgress&>;
		using OnMediaCancelResultType = ET<long long, CANCEL_MEDIA_ERR_CODE>;
		using OnFileMediaUploadResultType = ET<long long,  IFileMessage*, UPLOAD_MEDIA_ERR_CODE>;
		using OnImageMediaUploadResultType = ET<long long, IImageMessage*, UPLOAD_MEDIA_ERR_CODE>;
		using OnFileMessageReceivedFromPeerType = ET<const char*, const IFileMessage*>;
		using OnImageMessageReceivedFromPeerType = ET<const char*, const IImageMessage*>;
		using OnMediaDownloadToMemoryResultType = ET<long long, const char*,long long, DOWNLOAD_MEDIA_ERR_CODE>;
		using OnMediaDownloadToFileResultType = ET<long long, DOWNLOAD_MEDIA_ERR_CODE>;

	}

	using namespace RTMEventType;

	public class AgoraClrRTMEventHandler : public IRtmServiceEventHandler
	{
	private:
		template<typename F, typename ...Args>
		inline void call(F&& event, Args&&... args) { if (event) event(std::forward<Args>(args)...); }

	public:
		OnLoginSuccessType::Pointer onLoginSuccessEvent = 0;
		OnLoginFailureType::Pointer onLoginFailureEvent = 0;
		OnRenewTokenResultType::Pointer onRenewTokenResultEvent = 0;
		OnTokenExpiredType::Pointer onTokenExpiredEvent = 0;
		OnLogoutType::Pointer onLogoutEvent = 0;
		OnConnectionStateChangedType::Pointer onConnectionStateChangedEvent = 0;
		RTMEventType::OnSendMessageResultType::Pointer onSendMessageResultEvent = 0;
		OnMessageReceivedFromPeerType::Pointer onMessageReceivedFromPeerEvent = 0;
		OnQueryPeersOnlineStatusResultType::Pointer onQueryPeersOnlineStatusResultEvent = 0;
		OnSubscriptionRequestResultType::Pointer onSubscriptionRequestResultEvent = 0;
		OnQueryPeersBySubscriptionOptionResultType::Pointer onQueryPeersBySubscriptionOptionResultEvent = 0;
		OnPeersOnlineStatusChangedType::Pointer onPeersOnlineStatusChangedEvent = 0;
		OnSetLocalUserAttributesResultType::Pointer onSetLocalUserAttributesResultEvent = 0;
		OnAddOrUpdateLocalUserAttributesResultType::Pointer onAddOrUpdateLocalUserAttributesResultEvent = 0;
		OnDeleteLocalUserAttributesResultType::Pointer onDeleteLocalUserAttributesResultEvent = 0;
		OnClearLocalUserAttributesResultType::Pointer onClearLocalUserAttributesResultEvent = 0;
		OnGetUserAttributesResultType::Pointer onGetUserAttributesResultEvent = 0;
		OnSetChannelAttributesResultType::Pointer OnSetChannelAttributesResultEvent = 0;
		OnAddOrUpdateChannelAttributesResultType::Pointer onAddOrUpdateChannelAttributesResultEvent = 0;
		OnDeleteChannelAttributesResultType::Pointer onDeleteChannelAttributesResultEvent = 0;
		OnClearChannelAttributesResultType::Pointer onClearChannelAttributesResultEvent = 0;
		OnGetChannelAttributesResultType::Pointer onGetChannelAttributesResultEvent = 0;
		OnGetChannelMemberCountResultType::Pointer onGetChannelMemberCountResultEvent = 0;

		//1.3版本新增 文件+图片消息 （最大30M，服务器最多放七天）
		OnMediaUploadingProgressType::Pointer onMediaUploadingProgressEvent = 0;
		OnMediaDownloadingProgressType::Pointer onMediaDownloadingProgressEvent = 0;
		OnMediaCancelResultType::Pointer onMediaCancelResultEvent = 0;
		OnFileMediaUploadResultType::Pointer onFileMediaUploadResultEvent = 0;
		OnImageMediaUploadResultType::Pointer onImageMediaUploadResultEvent = 0;
		OnFileMessageReceivedFromPeerType::Pointer onFileMessageReceivedFromPeerEvent = 0;
		OnImageMessageReceivedFromPeerType::Pointer onImageMessageReceivedFromPeerEvent = 0;

		OnMediaDownloadToMemoryResultType::Pointer onMediaDownloadToMemoryResultEvent = 0;
		OnMediaDownloadToFileResultType::Pointer onMediaDownloadToFileResultEvent = 0;

		void onLoginSuccess() override { call(onLoginSuccessEvent); }
		void onLoginFailure(LOGIN_ERR_CODE code) override { call(onLoginFailureEvent, code); }
		void onRenewTokenResult(const char* token, RENEW_TOKEN_ERR_CODE code) override { call(onRenewTokenResultEvent, token, code); }
		void onTokenExpired() override { call(onTokenExpiredEvent); }
		void onLogout(LOGOUT_ERR_CODE code) override { call(onLogoutEvent, code); }
		void onConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason) override { call(onConnectionStateChangedEvent, state, reason); }
		void onSendMessageResult(long long id, PEER_MESSAGE_ERR_CODE code) override { call(onSendMessageResultEvent, id, code); }
		void onMessageReceivedFromPeer(const char* id, const IMessage* msg) override { call(onMessageReceivedFromPeerEvent, id, msg); }
		void onQueryPeersOnlineStatusResult(long long id, const PeerOnlineStatus* status, int count, QUERY_PEERS_ONLINE_STATUS_ERR code) override { call(onQueryPeersOnlineStatusResultEvent, id, status, count, code); }
		void onSubscriptionRequestResult(long long id, PEER_SUBSCRIPTION_STATUS_ERR code) override { call(onSubscriptionRequestResultEvent, id, code); }
		void onQueryPeersBySubscriptionOptionResult(long long id, const char* ids[], int count, QUERY_PEERS_BY_SUBSCRIPTION_OPTION_ERR code) override { call(onQueryPeersBySubscriptionOptionResultEvent, id, ids, count, code); }
		void onPeersOnlineStatusChanged(const PeerOnlineStatus status[], int count) override { call(onPeersOnlineStatusChangedEvent, status, count); }
		void onSetLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onSetLocalUserAttributesResultEvent, id, code); }
		void onAddOrUpdateLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onAddOrUpdateLocalUserAttributesResultEvent, id, code); }
		void onDeleteLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onDeleteLocalUserAttributesResultEvent, id, code); }
		void onClearLocalUserAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onClearLocalUserAttributesResultEvent, id, code); }
		void onGetUserAttributesResult(long long id, const char* userId, const RtmAttribute* attribute, int count, ATTRIBUTE_OPERATION_ERR code) override { call(onGetUserAttributesResultEvent, id, userId, attribute, count, code); }
		void onSetChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(OnSetChannelAttributesResultEvent, id, code); }
		void onAddOrUpdateChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onAddOrUpdateChannelAttributesResultEvent, id, code); }
		void onDeleteChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onDeleteChannelAttributesResultEvent, id, code); }
		void onClearChannelAttributesResult(long long id, ATTRIBUTE_OPERATION_ERR code) override { call(onClearChannelAttributesResultEvent, id, code); }
		void onGetChannelAttributesResult(long long id, const IRtmChannelAttribute* attributes[], int count, ATTRIBUTE_OPERATION_ERR code) override { call(onGetChannelAttributesResultEvent, id, attributes, count, code); }
		void onGetChannelMemberCountResult(long long id, const ChannelMemberCount* members, int count, GET_CHANNEL_MEMBER_COUNT_ERR_CODE code) override { call(onGetChannelMemberCountResultEvent, id, members, count, code); }

		//1.3版本新增 文件+图片消息 （最大30M，服务器最多放七天）
		void onMediaUploadingProgress(long long requestId, const MediaOperationProgress& progress) override { call(onMediaUploadingProgressEvent,requestId,progress);}
		void onMediaDownloadingProgress(long long requestId, const MediaOperationProgress& progress) override{ call(onMediaDownloadingProgressEvent,requestId,progress);}
		void onMediaCancelResult(long long requestId, CANCEL_MEDIA_ERR_CODE code) override{ call(onMediaCancelResultEvent,requestId,code);}
		void onFileMediaUploadResult(long long requestId, IFileMessage* fileMessage, UPLOAD_MEDIA_ERR_CODE code) override{ call(onFileMediaUploadResultEvent,requestId,fileMessage,code);}
		void onImageMediaUploadResult(long long requestId, IImageMessage* imageMessage, UPLOAD_MEDIA_ERR_CODE code) override{ call(onImageMediaUploadResultEvent,requestId,imageMessage,code);}
		void onFileMessageReceivedFromPeer(const char* peerId, const IFileMessage* message) override{ call(onFileMessageReceivedFromPeerEvent,peerId,message);}
		void onImageMessageReceivedFromPeer(const char* peerId, const IImageMessage* message) override{ call(onImageMessageReceivedFromPeerEvent,peerId,message);}
		void onMediaDownloadToMemoryResult(long long requestId, const char* memory, long long length, DOWNLOAD_MEDIA_ERR_CODE code) override{ call(onMediaDownloadToMemoryResultEvent,requestId,memory,length,code);}
		void onMediaDownloadToFileResult(long long requestId, DOWNLOAD_MEDIA_ERR_CODE code) override{ call(onMediaDownloadToFileResultEvent,requestId,code);}
	};
}

