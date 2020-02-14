
#include "pch.h"
#include "AgoraClrRTM.h"

#include <msclr/marshal_cppstd.h>
#include <string>

using namespace msclr::interop;

AgoraClrLibrary::AgoraClrRTM::AgoraClrRTM(String^ vendorkey): service(createRtmService())
{

	int result = service->initialize(marshal_as<std::string>(vendorkey).c_str(), eventHandler);
	if (result < 0) throw gcnew System::ArgumentException(result.ToString(), "vendorkey");

	
}

AgoraClrLibrary::AgoraClrRTM::~AgoraClrRTM()
{
	service->release();
}

int AgoraClrLibrary::AgoraClrRTM::login(String^ token, String^ userId)
{
	return service->login(marshal_as<std::string>(token).c_str(), marshal_as<std::string>(userId).c_str());
}

int AgoraClrLibrary::AgoraClrRTM::logout()
{
	return service->logout();
}

