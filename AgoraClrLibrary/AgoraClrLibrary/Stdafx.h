// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#include "../../agorasdk/include/AgoraBase.h"
#include "../../agorasdk/include/IAgoraLog.h"
#include "../../agorasdk/include/IAgoraMediaEngine.h"
#include "../../agorasdk/include/IAgoraRtcEngine.h"
#include "../../agorasdk/include/IAgoraService.h"
#include "../../agorasdk/include/IAgoraRtcChannel.h"
#include "../include/common.h"

#if defined _M_IX86
#pragma comment(lib, "../../agorasdk/x86/agora_rtc_sdk.lib")
#elif defined _M_X64
#pragma comment(lib, "../../agorasdk/x86_64/agora_rtc_sdk.lib")
#endif
//#pragma comment(lib, "../../agorasdk/lib/libagora_segmentation_extension.lib")
