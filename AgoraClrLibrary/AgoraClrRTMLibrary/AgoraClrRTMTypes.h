#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"

#include <msclr/marshal_cppstd.h>
#include <tuple>
#include <string>

using namespace agora::rtm;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace AgoraClrLibrary {
	ref class AutoChars {
	public:
		marshal_context^ context;
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

		std::tuple<const void*, int> rawData() {
			if (Data == nullptr || Data->Length == 0) return std::make_tuple<const void*, int>(nullptr, 0);
			int size = Data->Length;
			void* raw = malloc(sizeof(char) * size);
			Marshal::Copy(Data, 0, IntPtr(raw), size);
			return std::tuple<const void*, int>(raw, size);
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

		ClrRtmAttribute(): key(nullptr), value(nullptr) {}

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
}