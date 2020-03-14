# AgoraCLI项目
# 2020-02-10 19:14
#  2.9分支进行了更新, 本次更新是破坏性的,暂时留在2.9分支上,大家可以进适配测试, 一个月后.如果没有问题将合并进 master 分支中.

因为要用到Visual C++，所以在安装.net运行时后，还需要安装 **Visual C++ Redistributable for Visual Studio** 才可以运行。

对了,他们家新的WebRtc版本好像要出来了,你们可以找他们要这个版本看看, 可能会更好的哦.

[Agora声网](http://cn.agora.io)的Windows端SDK只提供了C++的实现, 用在.NET平台上对开发者要求很高. 所以用CLI将其做了一个桥接, 使其可以使用C#进行开发.

~~原始数据API部分因为要在managed与unmanaged的内存之间拷贝数据，所以不推荐运算量大的应用使用，如果要使用，推荐直接用声网的Native DLL来实现~~

发现声网现在也改成这样子了, 原来Native DLL的实现方式只能有一个DLL被加载, 现在也改成事件形式了.

通信与直播功能下的接口都已实现

信令接口声网自身还处有一些内测接口，这些接口就没有实现。等他们有发新的版本了，再跟进实现。
~~ 同时，信令接口现在实现只处于能编译通过，是否可以正常使用还没有测试，请使用的朋友自己考虑。~~

如果使用过程中有发现BUG，请提交issue。本人会尽快处理，如果各位能自行处理后把结果pull上来就更好了。

## 2020-20-16 13:20
添加RTM实时消息服务

## 2020-02-10 19:01
居然一年没有更新了, 现在更新到2.9.1版本, 本版本是破坏性更新, 很多API与类都进行了不兼容的改变, 具体请参考Agora官方文档. 各位要升级的话要慎重行事.

**信令服务移除**

**移除部分文档上已经没有的接口**

## 2019-02-06 19:54
升级Master分支至2.3，要以前版本的请到各自版本的分支去拿

## 2019-02-06 19:28
onStreamUrlUnpublished 改为 onStreamUnpublished

添加下列函数
```c#
		int setLocalPublishFallbackOption(StreamFallbackOptions option);
		int setRemoteSubscribeFallbackOption(StreamFallbackOptions option);
		int setRemoteDefaultVideoStreamType(RemoteVideoStreamType type);
		String^ getErrorDescription(int code);
```

添加下列回调
```c#
onTokenPrivilegeWillExpire
onConnectionStateChanged
onFirstLocalAudioFrame
onFirstRemoteAudioFrame
onUserEnableLocalVideo
onVideoSizeChanged
onRemoteVideoStateChanged
onLocalPublishFallbackToAudioOnly
onRemoteSubscribeFallbackToAudioOnly
onCameraFocusAreaChanged
onRemoteAudioStats
onRemoteAudioTransportStats
onRemoteVideoTransportStats
onRemoteAudioMixingBegin
onRemoteAudioMixingEnd
onAudioEffectFinished
onStreamInjectedStatus
onMediaEngineLoadSuccess
onMediaEngineStartCallSuccess
```

## 2019-02-06 12:22
修改 muteAllRemoteVideoStream 为 muteAllRemoteVideoStreams

添加下列函数
```c#
		ConnectionStateType getConnectionState();
		int setDefaultMuteAllRemoteAudioStreams(bool mute);
		int setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config);
		int setDefaultMuteAllRemoteVideoStreams(bool mute);
		int adjustAudioMixingPlayoutVolume(int volume);
		int adjustAudioMixingPublishVolume(int volume);
		int setExternalAudioSink(bool enabled, int sampleRate, int channels);
		int setExternalVideoSource(bool enabled, bool useTexture);
		int pushVideoFrame(ClrExternalVideoFrame^ frame);
		int addVideoWatermark(ClrRtcImage^ image);
		int clearVideoWatermark();
```

## 2019-02-01
因2.3.0以后，声网就不再支持录制接口，转而由Recording SDK来提供，于是相应删除
```c#
startRecordingService
stopRecordingService
refreshRecordingServiceStatus
onRefreshRecordingServiceStatus
```
## 2018-12-07
修改ClrLiveTranscoding不能设置transcodingUsers的BUG

## 2018-07-20
修改信令中 messageInstantSend 方法不能处理中文的BUG

## 2018-07-19
修改[枚举设备列表BUG](https://github.com/horsefaced/AgoraCLI/issues/18)的issue

<<<<<<< HEAD
=======
## 2018-06-30
新增以下接口
```c#
        int	getEffectsVolume();
	    int setEffectsVolume(int volume);
		int setVolumeOfEffect(int soundId, int volume);
		int playEffect(int soundId, String^ file, int loopCount, double pitch, double pan, int gain, bool publish);
		int stopEffect(int soundId);
		int stopAllEffects();
		int preloadEffect(int soundId, String^ file);
		int unloadEffect(int soundId);
		int pauseEffect(int soundId);
		int pauseAllEffects();
		int resumeEffect(int soundId);
		int resumeAllEffects();
```

>>>>>>> 2.3
## 2018-06-27
合并2.1分支进入主分支，2.2因为删除了一些头文件，造成不兼容，新开2.2分支进行开发，原2.1的一些没有开发完的功能将在2.2分支上实现

## 2018-05-10
<h1>声网的2.2sdk删除了一些头文件，造成项目不兼容，请大家先不要升级到2.2</h1>

## 2018-04-17
新增事件
```c#
void onStreamUrlUnpublished(String^ url);
void onStreamPublished(String^ url, int error);
void onTranscodingUpdated();
```

## 2018-03-13
因为2.1版本声网进行了很大的改动，所以2.0（含）以前的版本进入2.0分支，需要的用户请使用2.0这个分支。2.1版本在2.1分支开发中，以后会并入master分支中。

新增以下接口
```c#
int setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain);
int setLocalVoiceReverb(AudioReverbType type, int value);
int setLocalVideoMirrorMode(VideoMirrorModeType mode);
String^ getVersion(int% build);
int enableLoopbackRecording(bool enabled);
int pushAudioFrame(ClrAudioFrameType type, ClrAudioFrame ^frame, bool wrap);
int addPublishStreamUrl(String^ url, bool transcodingEnabled);
int removePublishStreamUrl(String^ url);
int setLiveTranscoding(ClrLiveTranscoding ^transcoding);
int addInjectStreamUrl(String^ url, ClrInjectStreamConfig ^config);
int removeInjectStreamUrl(String^ url);
```

新增以下事件
```c#
virtual void onConnectionBanned()
virtual void onRequestToken();
virtual bool onMixedAudioFrame(AudioFrame& audioFrame);

```

官方依然没有在2.1的SDK上加入 pushExternalAudioFrame 这个方法。

## 2018-02-06
2.0版本上声网有一个bug，[摄像头占用问题](https://github.com/horsefaced/AgoraCLI/issues/16)，这个问题在2.0.2版本上就没有，大家可以先把agora_rtc_sdk.dll直接换成2.0.2的。

## 2017-12-13 更新版本至 2.0
2.0版本中 IMediaEngine 接口新加了 registerVideoRenderFactory 与 pushAudioFrame ，但是官方文档里并没有，所以暂时不实现，等官方明确了这两个接口是干嘛的后在实现。
同时，官方文档里说2.0版本新加了 pushExternalAudioFrame	推送外部音频帧 这个方法，但实际上并没有。而且在咨询了官方后，声网表示并没有在2.0上发布这个方法，所以这个方法就没有出现在 CLI 项目里，请注意，这不是一个BUG。

## 2017-11-05 更新信令至 1.14
项目所包含的SDK已经是1.14的了, 但官方文档还是1.12的. 原来我实现的信令接口是非常早期的版本, 在 1.12 的官方文档上删除了非常多的接口与事件, 但为了向下兼容还是什么的原因, 有一些事件还在头文件中存在, 这部分我暂时不去删除它, 但在以后的版本中会进行删除,大家请照官方的文档来进行开发, 也尽量不要用内测部分的接口, 虽然我也加了上去, 但不建议各位使用.

## 2017-11-04 更新通信与直播接口实现至 1.14.0, 新增接口

新增 API setAudioProfile() 设置音频参数和应用场景
```c++
int setAudioProfile(AudioProfileType profile, AudioScenarioType scenario)
```
新增 API setLocalVoicePitch() 提供基础变声功能
```c++
int setLocalVoicePicth(double pitch)
```

直播场景: 新增 API setInEarMonitoringVolume() 提供调节耳返音量功能
```c++
int setInEarMonitoringVolumne(int volumne)
```

## 2017-09-23 更新通信与直播接口实现至 1.13.0, 修改如下接口与事件

添加更新屏幕截图区域(updateScreenCaptureRegion)接口
```c++
int updateScreenCaptureRegion(const Rect *rect)
```

## 2017-07-28 更新通信与直播接口实现至 1.12.0, 修改如下接口与事件

**因声网在1.12.0修改内部多个实现参数, 所以本版本无法与1.11.1兼容, 请测试后使用**

配置旁路直播推流(configPublisher), 修改PublishConfiguration内容, 添加injectStream的部分.
```c++
virtual int configPublisher(ClrPublisherConfiguration config);
```

添加监测到活跃用户回调(onActiveSpeaker)事件
```c++
virtual void onActiveSpeaker(int uid);
```

修改开启屏幕共享(startScreenCapture)
```C++
int startScreenCapture(IntPtr windowsId, int captureFreq, ClrRect rect);
```

修改开始客户端录音 (startAudioRecording), 添加AudioRecordingQualityType参数
```c++
int startAudioRecording (const char* filePath, AudioRecordingQuality quality)
```

删除 int setScreenCaptureWindow(IntPtr windowId); 方法


## 2017-07-17 更新通信与直播接口实现至 1.11.1, 实现如下接口与事件

拖动语音进度条(setAudioMixingPosition)
```c++
int setAudioMixingPosition(int pos /*in ms*/)
```
伴奏播放已结束回调(onAudioMixingFinished)
```c++
virtual void onAudioMixingFinished()
```
旁路这个API在声网的实现上规定是win32的, 所以你编译成win64的话, 这个接口献认返回0, 而不会有实际效果
配置旁路直播推流(configPublisher)
```c++
virtual int configPublisher(const PublisherConfiguration& config);
```
注册数据包观测器(registerPacketObserver)
```c++
int registerPacketObserver(IPacketObserver* observer)
```
这个方法已经通过代理的形式把内部的实现实现到了AgoraClr上了, 例如
```c++
//PacketObserver Part

public delegate bool onSendAudioPacket(ClrPacket^ packet);
public delegate bool onSendVideoPacket(ClrPacket^ packet);
public delegate bool onReceiveAudioPacket(ClrPacket^ packet);
public delegate bool onReceiveVideoPacket(ClrPacket^ packet);
```
这一系统方法
