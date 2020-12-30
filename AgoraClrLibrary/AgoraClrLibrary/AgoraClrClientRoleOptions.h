#pragma once
#include "AgoraClrLibraryEnum.h"

namespace AgoraClrLibrary {
	public ref class AgoraClrClientRoleOptions
	{
	public:
		EnumAudienceLatencyLevelType audienceLatencyLevel = EnumAudienceLatencyLevelType::AUDIENCE_LATENCY_LEVEL_LOW_LATENCY;

	public:
		operator agora::rtc::ClientRoleOptions() {
			agora::rtc::ClientRoleOptions raw;
			raw.audienceLatencyLevel = static_cast<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>(this->audienceLatencyLevel);
			return raw;
		}
	};
}

