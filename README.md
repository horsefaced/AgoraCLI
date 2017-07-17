# AgoraCLI项目

因为要用到Visual C++，所以在安装.net运行时后，还需要安装 **Visual C++ Redistributable for Visual Studio** 才可以运行。

对了,他们家新的WebRtc版本好像要出来了,你们可以找他们要这个版本看看, 可能会更好的哦.

[Agora声网](http://cn.agora.io)的Windows端SDK只提供了C++的实现, 用在.NET平台上对开发者要求很高. 所以用CLI将其做了一个桥接, 使其可以使用C#进行开发.

支持版本升级到1.11.1，编译能通过，如果使用时发发现有什么新增接口或者参数没有，请提交issue。

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

2017-07-17 更新通信与直播接口实现至 1.11.1, 实现如下接口与事件

拖动语音进度条(setAudioMixingPosition)
int setAudioMixingPosition(int pos /*in ms*/)

伴奏播放已结束回调(onAudioMixingFinished)
virtual void onAudioMixingFinished()

旁路这个API在声网的实现上规定是win32的, 所以你编译成win64的话, 这个接口献认返回0, 而不会有实际效果
配置旁路直播推流(configPublisher)
virtual int configPublisher(const PublisherConfiguration& config);

注册数据包观测器(registerPacketObserver)
int registerPacketObserver(IPacketObserver* observer)
这个方法已经通过代理的形式把内部的实现实现到了AgoraClr上了, 例如
//PacketObserver Part
	public delegate bool onSendAudioPacket(ClrPacket^ packet);
	public delegate bool onSendVideoPacket(ClrPacket^ packet);
	public delegate bool onReceiveAudioPacket(ClrPacket^ packet);
	public delegate bool onReceiveVideoPacket(ClrPacket^ packet);
这一系统方法
