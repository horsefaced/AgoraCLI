# AgoraCLI项目

[Agora声网](http://cn.agora.io)的Windows端SDK只提供了C++的实现, 用在.NET平台上对开发者要求很高. 所以用CLI将其做了一个桥接, 使其可以使用C#进行开发.

支持版本升级到1.9，编译能通过，如果使用时发发现有什么新增接口或者参数没有，请提交issue。

原始数据API部分因为要在managed与unmanaged的内存之间拷贝数据，所以不推荐运算量大的应用使用，如果要使用，推荐直接用声网的Native DLL来实现。

通信与直播功能下的这些接口已实现
- IRtcEngine
- RtcEngineParameters
- IRtcEngineEventHandler
- IAudioFrameObserver
- IVideoFrameObserver
- IAudioDeviceManager
- IAudioDeviceCollection
- IVideoDeviceManager
- IVideoDeviceCollection


信令接口声网自身还处有一些内测接口，这些接口就没有实现。等他们有发新的版本了，再跟进实现。
同时，信令接口现在实现只处于能编译通过，是否可以正常使用还没有测试，请使用的朋友自己考虑。

如果使用过程中有发现BUG，请提交issue。本人会尽快处理，如果各位能自行处理后把结果pull上来就更好了。

