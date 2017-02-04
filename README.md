# AgoraCLI项目

[Agora声网](http://cn.agora.io)的Windows端SDK只提供了C++的实现, 用在.NET平台上对开发者要求很高. 所以用CLI将其做了一个桥接, 使其可以使用C#进行开发.

支持版本升级到1.8.1，正在把一些1.8.1新增的接口补充上来。

原始数据API部分因为要在managed与unmanaged的内存之间拷贝数据，所以不推荐运算量大的应用使用，如果要使用，推荐直接用声网的Native DLL来实现。

现在实现接口有:

通信接口下的这些接口已实现
- IRtcEngine
- RtcEngineParameters
- IRtcEngineEventHandler
- IAudioFrameObserver
- IVideoFrameObserver
- IAudioDeviceManager
- IAudioDeviceCollection
- IVideoDeviceManager
- IVideoDeviceCollection

暂没有实现的接口有:
- 直播接口
- 信令接口

