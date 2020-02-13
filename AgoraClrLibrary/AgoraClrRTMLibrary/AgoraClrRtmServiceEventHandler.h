#pragma once

#include "..\..\agorasdk\include\IAgoraRtmService.h"


using namespace agora::rtm;

namespace AgoraClrLibrary {
	
	public class AgoraClrRtmServiceEventHandler: IRtmServiceEventHandler
	{
	public:


		virtual void onLoginSuccess() override;
		virtual void onLoginFailure(LOGIN_ERR_CODE code) override;

	};

}

