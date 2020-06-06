#pragma once

#include "..\..\agorasdk\include\IAgoraRtcEngine.h"

using namespace agora::rtc;

namespace AgoraClrLibrary {

	typedef int(__stdcall* PFOnGetMaxMetadataSize)();
	typedef bool(__stdcall* PFOnReadyToSendMetadata)(IMetadataObserver::Metadata&);
	typedef void(__stdcall* PFOnMetadataReceived)(const IMetadataObserver::Metadata&);

	delegate int NativeOnGetMaxMetadataSizeDelegate();
	delegate bool NativeOnReadyToSendMetadataDelegate(IMetadataObserver::Metadata&);
	delegate void NativeOnMetadataReceivedDelegate(const IMetadataObserver::Metadata&);

	public class AgoraClrMetadataObserver : public IMetadataObserver
	{
	public:
		PFOnGetMaxMetadataSize onGetMaxMetadataSizeEvent = 0;
		PFOnReadyToSendMetadata onReadyToSendMetadataEvent = 0;
		PFOnMetadataReceived onMetadataReceivedEvent = 0;

		int getMaxMetadataSize() override;
		bool onReadyToSendMetadata(Metadata& metadata) override;
		void onMetadataReceived(const Metadata& metadata) override;
	};

}

