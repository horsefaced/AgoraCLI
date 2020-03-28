#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"
#include "AgoraClrRTMEnum.h"
#include "..\include\common.h"

#include <msclr/marshal_cppstd.h>
#include <tuple>
#include <string>

using namespace agora::rtm;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace AgoraClrLibrary {
	public ref class AutoChars {
	public:
		const char** chars;
		int count;

		AutoChars(List<String^>^ strings) {
			count = strings->Count;
			context = gcnew marshal_context;
			chars = new const char* [count];
			for (int i = 0; i < count; i++) chars[i] = context->marshal_as<const char*>(strings[i]);
		}

		~AutoChars() {
			delete context;
			delete[] chars;
		}

		const char* marshal_as(String^ str) {
			return context->marshal_as<const char*>(str);
		}

	private:
		marshal_context^ context;
	};

	public ref class ClrMessage {
	public:
		property long long ID;
		property EnumMessageType Type;
		property String^ Text;
		property array<Byte>^ Data;
		property long long ServerReceivedTs { long long get() { return ts; }}
		property bool IsOffline;

		ClrMessage() : ts(0)
		{
			ID = 0;
			Type = EnumMessageType::MESSAGE_TYPE_UNDEFINED;
			Text = nullptr;
			Data = nullptr;
			IsOffline = false;
		}

		ClrMessage(IMessage* raw) :
			ts(raw->getServerReceivedTs())
		{
			ID = raw->getMessageId();
			Type = static_cast<EnumMessageType>(raw->getMessageType());
			Text = gcnew String(raw->getText());
			Data = getRawMesageData(raw);
			IsOffline = raw->isOfflineMessage();
		}

		IMessage* toMessage(IRtmService* service) {
			IMessage* raw;
			if (Data == nullptr || Data->Length == 0)
				raw = service->createMessage();
			else {
				auto [rawData, length] = this->rawData();
				raw = service->createMessage(static_cast<const uint8_t*>(rawData), length);
			}

			if (Text != nullptr)
				raw->setText(marshal_as<std::string>(Text).c_str());

			ID = raw->getMessageId();
			return raw;
		}

	private:
		long long id;
		long long ts;

		array<Byte>^ getRawMesageData(IMessage* raw) {
			int size = raw->getRawMessageLength();
			auto result = gcnew array<Byte>(size);
			if (size > 0) Marshal::Copy(IntPtr(reinterpret_cast<void*>(const_cast<char*>(raw->getRawMessageData()))), result, 0, size);
			return result;
		}

		std::tuple<const void*, int> rawData() {
			if (Data == nullptr || Data->Length == 0) return std::make_tuple<const void*, int>(nullptr, 0);
			int size = Data->Length;
			void* raw = malloc(sizeof(char) * size);
			Marshal::Copy(Data, 0, IntPtr(raw), size);
			return std::tuple<const void*, int>(raw, size);
		}

	};

	public ref class ClrSendMessageOptions {
	public:
		bool enableOfflineMessaging;
		bool enableHistoricalMessaging;

		ClrSendMessageOptions() : enableHistoricalMessaging(false), enableOfflineMessaging(false) {}

		operator SendMessageOptions() {
			SendMessageOptions options;
			options.enableHistoricalMessaging = enableHistoricalMessaging;
			options.enableOfflineMessaging = enableOfflineMessaging;
			return options;
		}
	};

	public ref class ClrPeerOnlineStatus {
	public:
		String^ peerId;
		bool isOnline;
		EnumPeerOnlineState onlineState;

		ClrPeerOnlineStatus(const PeerOnlineStatus status) {
			peerId = gcnew String(status.peerId);
			isOnline = status.isOnline;
			onlineState = static_cast<EnumPeerOnlineState>(status.onlineState);
		}
	};

	public ref class ClrRtmAttribute {
	public:
		String^ key;
		String^ value;

		ClrRtmAttribute() : key(nullptr), value(nullptr) {}

		ClrRtmAttribute(const RtmAttribute attr) {
			key = gcnew String(attr.key);
			value = gcnew String(attr.value);
		}

		operator RtmAttribute* () {
			RtmAttribute* attr = new RtmAttribute;
			String^ k = key;
			String^ v = value;
			attr->key = marshal_as<std::string>(k).c_str();
			attr->value = marshal_as<std::string>(v).c_str();
			return attr;
		}

		static void release(const RtmAttribute* attr) {
			delete attr->key;
			delete attr->value;
			delete attr;
		}

		static const RtmAttribute** createAttrs(List<ClrRtmAttribute^>^ attrs) {
			int count = attrs->Count;
			const RtmAttribute** result = new const RtmAttribute * [count];
			for (int i = 0; i < count; i++) result[i] = attrs[i];
			return result;
		}

		static void releaseAttrs(const RtmAttribute** attrs, int count) {
			for (int i = 0; i < count; i++) release(attrs[i]);

			delete[] attrs;
		}
	};

	public ref class ClrRtmChannelAttribute {
	public:
		property String^ key;
		property String^ value;
		property String^ lastUpdateUserId { String^ get() { return userId; }}
		property long long lastUpdateTs { long long get() { return ts; }}

		ClrRtmChannelAttribute() {
			key = nullptr;
			value = nullptr;
			userId = nullptr;
			ts = 0;
		}
		ClrRtmChannelAttribute(const IRtmChannelAttribute* attr) {
			key = gcnew String(attr->getKey());
			value = gcnew String(attr->getValue());
			userId = gcnew String(attr->getLastUpdateUserId());
			ts = attr->getLastUpdateTs();
		}

		IRtmChannelAttribute* write(IRtmChannelAttribute* attr) {
			attr->setKey(marshal_as<std::string>(key).c_str());
			attr->setValue(marshal_as<std::string>(value).c_str());
			return attr;
		}

		static std::tuple<IRtmChannelAttribute**, int> toArray(IRtmService* service, List<ClrRtmChannelAttribute^>^ attrs) {
			int count = attrs->Count;
			IRtmChannelAttribute** tmpAttrs = new IRtmChannelAttribute * [count];
			for (int i = 0; i < count; i++) {
				tmpAttrs[i] = attrs[i]->write(service->createChannelAttribute());
			}
			return std::tuple(tmpAttrs, count);
		}
	private:
		String^ userId;
		long long ts;
	};

	public ref class ClrChannelAttributeOptions {
	public:
		bool enableNotificationToChannelMembers = false;

		ClrChannelAttributeOptions() {}
		ClrChannelAttributeOptions(const ChannelAttributeOptions options) {
			enableNotificationToChannelMembers = options.enableNotificationToChannelMembers;
		}
	};

	public ref class ClrChannelMemberCount {
	public:
		String^ channelId;
		int count;

		ClrChannelMemberCount(const ChannelMemberCount val) :
			channelId(gcnew String(val.channelId)),
			count(val.count)
		{}
	};

	public ref class ClrChannelMember {
	public:
		property String^ UserId { String^ get() { return userId; }}
		property String^ ChannelId { String^ get() { return channelId; } }

		ClrChannelMember(IChannelMember* member) :
			userId(gcnew String(member->getChannelId())),
			channelId(gcnew String(member->getChannelId()))
		{
		}
	private:
		String^ userId;
		String^ channelId;
	};

	public ref class ClrLocalCallInvation {
	public:
		property String^ CalleeId { String^ get() { return calleeId; } }
		property String^ Content;
		property String^ ChannelId;
		property String^ Response { String^ get() { return response; }}
		property EnumLocalInvitationState State { EnumLocalInvitationState get() { return state; }}

		ClrLocalCallInvation(ILocalCallInvitation* lci) :
			calleeId(gcnew String(lci->getCalleeId())),
			response(gcnew String(lci->getResponse())),
			state(static_cast<EnumLocalInvitationState>(lci->getState()))
		{
			Content = gcnew String(lci->getContent());
			ChannelId = gcnew String(lci->getChannelId());
		}

		ILocalCallInvitation* toILCI(IRtmCallManager* manager) {
			ILocalCallInvitation* lci = manager->createLocalCallInvitation(marshal_as<std::string>(CalleeId).c_str());
			lci->setChannelId(marshal_as<std::string>(ChannelId).c_str());
			lci->setContent(marshal_as<std::string>(Content).c_str());
			return lci;
		}

	private:
		String^ calleeId;
		String^ response;
		EnumLocalInvitationState state;

	};

	public ref class ClrRemoteCallInvitation {
	public:
		property String^ CallerId {
			String^ get() { return gcnew String(raw->getCallerId()); }
		}
		property String^ Content {
			String^ get() { return gcnew String(raw->getContent()); }
		}
		property String^ Response {
			String^ get() { return gcnew String(raw->getResponse()); }
			void set(String^ value) { raw->setResponse(marshal_as<std::string>(value).c_str()); }
		}
		property String^ ChannelId {
			String^ get() { return gcnew String(raw->getChannelId()); }
		}
		property EnumRemoteInvitationState State {
			EnumRemoteInvitationState get() { return static_cast<EnumRemoteInvitationState>(raw->getState()); }
		}

		ClrRemoteCallInvitation(IRemoteCallInvitation* rci) : raw(rci)
		{
		}
		~ClrRemoteCallInvitation() { raw->release(); }

		operator IRemoteCallInvitation* () {
			return raw;
		}
	private:
		IRemoteCallInvitation* raw;
	};


}