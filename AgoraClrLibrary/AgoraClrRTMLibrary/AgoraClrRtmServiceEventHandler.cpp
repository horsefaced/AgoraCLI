#include "pch.h"
#include "AgoraClrRtmServiceEventHandler.h"

void AgoraClrLibrary::AgoraClrRtmServiceEventHandler::onLoginSuccess()
{
	if (this->onLoginSuccessEvent) this->onLoginSuccessEvent();
}
