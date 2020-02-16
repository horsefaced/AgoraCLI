#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"
#include "AgoraClrRTMTypes.h"
#include "AgoraClrRTMEnum.h"

using namespace agora::rtm;

namespace AgoraClrLibrary {
	namespace ChannelEventType {
		using OnJoinSuccessType = ET<void>;
		using OnJoinFailureType = ET<JOIN_CHANNEL_ERR>;
		using OnLeaveType = ET<LEAVE_CHANNEL_ERR>;
		using OnMessageReceivedType = ET<const char*, const IMessage*>;
		using OnSendMessageResultType = ET<long long, CHANNEL_MESSAGE_ERR_CODE>;
		using OnMemberJoinedType = ET<IChannelMember*>;
		using OnMemberLeftType = ET<IChannelMember*>;
		using OnGetMembersType = ET<IChannelMember**, int, GET_MEMBERS_ERR>;
		using OnAttributesUpdatedType = ET<const IRtmChannelAttribute**, int>;
		using OnMemberCountUpdatedType = ET<int>;
	}

	using namespace ChannelEventType;

	public class AgoraClrRTMChannelEventHandlder : public IChannelEventHandler {
	public:
		OnJoinSuccessType::Pointer onJoinSuccessEvent = 0;
		OnJoinFailureType::Pointer onJoinFailureEvent = 0;
		OnLeaveType::Pointer onLeaveEvent = 0;
		OnMessageReceivedType::Pointer onMessageReceivedEvent = 0;
		ChannelEventType::OnSendMessageResultType::Pointer onSendMessageResultEvent = 0;
		OnMemberJoinedType::Pointer onMemberJoinedEvent = 0;
		OnMemberLeftType::Pointer onMemberLeftEvent = 0;
		OnGetMembersType::Pointer onGetMembersEvent = 0;
		OnAttributesUpdatedType::Pointer onAttributesUpdatedEvent = 0;
		OnMemberCountUpdatedType::Pointer onMemberCountUpdatedEvent = 0;

		void onJoinSuccess() override { call(onJoinSuccessEvent); }
		void onJoinFailure(JOIN_CHANNEL_ERR code) override { call(onJoinFailureEvent, code); }
		void onLeave(LEAVE_CHANNEL_ERR code) override { call(onLeaveEvent, code); }
		void onMessageReceived(const char* userId, const IMessage* message) override { call(onMessageReceivedEvent, userId, message); }
		void onSendMessageResult(long long id, CHANNEL_MESSAGE_ERR_CODE code) override
		{
			call(onSendMessageResultEvent, id, code);
		}
		void onMemberJoined(IChannelMember* member) override {
			call(onMemberJoinedEvent, member);
		}
		void onMemberLeft(IChannelMember* member) override {
			call(onMemberLeftEvent, member);
		}
		void onGetMembers(IChannelMember** members, int count, GET_MEMBERS_ERR code) override {
			call(onGetMembersEvent, members, count, code);
		}
		void onAttributesUpdated(const IRtmChannelAttribute* attrs[], int count) override {
			call(onAttributesUpdatedEvent, attrs, count);
		}
		void onMemberCountUpdated(int count) override {
			call(onMemberCountUpdatedEvent, count);
		}

	private:
		template<typename F, typename ...Args>
		inline void call(F&& event, Args&&... args)
		{
			if (event) event(std::forward<Args>(args)...);
		}


	};
}
