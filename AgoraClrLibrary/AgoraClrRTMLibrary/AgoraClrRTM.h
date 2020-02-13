#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"

#include <memory>

using namespace agora::rtm;
using namespace System;

namespace AgoraClrLibrary {
	
	public ref class AgoraClrRTM
	{
	public:
		AgoraClrRTM(String^ vendorkey);
		~AgoraClrRTM();
	private:
		IRtmService* service;
	};

}

