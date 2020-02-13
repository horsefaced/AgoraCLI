
#include "pch.h"
#include "AgoraClrRTM.h"

#include <msclr/marshal_cppstd.h>
#include <string>

using namespace msclr::interop;

AgoraClrLibrary::AgoraClrRTM::AgoraClrRTM(String^ vendorkey): service(createRtmService())
{
	int result = service->initialize(marshal_as<std::string>(vendorkey).c_str(), nullptr);
	if (result < 0) throw gcnew System::ArgumentException(result.ToString(), "vendorkey");


}

AgoraClrLibrary::AgoraClrRTM::~AgoraClrRTM()
{
	service->release();
}
