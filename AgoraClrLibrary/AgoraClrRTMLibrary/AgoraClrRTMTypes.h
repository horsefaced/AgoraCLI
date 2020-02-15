#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"

#include <tuple>

using namespace agora::rtm;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace AgoraClrLibrary {
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
}