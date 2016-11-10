# AgoraCLI项目

[Agora声网](http://cn.agora.io)的Windows端SDK只提供了C++的实现, 用在.NET平台上对开发者要求很高. 所以用CLI将其做了一个桥接, 使其可以使用C#进行开发.

支持版本升级到1.7.0

现在实现接口有:

1. IRtcEngine
2. RtcEngineParameters
3. IRtcEngineEventHandler

暂没有实现的接口有:

1. IAudioDeviceManager
2. IAudioDeviceCollection
3. IVideoDeviceManager
4. IVideoDeviceCollection
5. IAudioFrameObserver
6. IVideoFrameObserver