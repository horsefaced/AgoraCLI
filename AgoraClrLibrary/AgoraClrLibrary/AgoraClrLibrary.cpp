#include "stdafx.h"
#include "AgoraClrLibrary.h"
#include "../../agorasdk/include/IAgoraRtcChannel.h"

using namespace AgoraClrLibrary;
using namespace System;
using namespace Runtime::InteropServices;

AgoraClr::AgoraClr() :
	rtcEngine(nullptr),
	agoraMediaEngine(nullptr),
	gchs(gcnew List<GCHandle>()),
	agoraEventHandler(new AgoraClrEventHandler),
	agoraPacketObserver(new AgoraClrPacketObserver),
	agoraAudioObserver(new AgoraClrAudioFrameObserver),
	agoraVideoObserver(new AgoraClrVideoFrameObserver),
	agoraMetadataObserver(new AgoraClrMetadataObserver),
	innerVideoSoruce(nullptr),
	innerLocalVideoSink(nullptr),
	innerRemoteVideoSink(nullptr)
{
	VideoFormatPreference = VideoFrameType::FRAME_TYPE_YUV420;
	IsSmoothRenderingEnabled = false;
	IsVideoRotationApplied = false;
	IsVideoMirrorApplied = false;
	IsMultipleChannelVideoFrameWanted = false;
	IsMultipleChannelAudioFrameWanted = false;
	ObservedVideoFramePosition = static_cast<UINT>(EnumVideoObserverPositionType::POSITION_POST_CAPTURER);

	MaxMetadataSize = 1024;

	initializeEventHandler();
	initializePacketObserver();
	initializeRawFrameObserver();
	initializeMetaObserver();
}

AgoraClr::~AgoraClr()
{
	this->release();
	for each (GCHandle handle in gchs) handle.Free();
}

AgoraClr::!AgoraClr()
{
}

int AgoraClr::initialize(String^ vendorkey, [Optional] Nullable<int> areaCode)
{
	auto context = gcnew ClrRtcEngineContext();
	context->vendorKey = vendorkey;
	context->areaCode = areaCode.HasValue ? (EnumAreaCode)areaCode.Value : EnumAreaCode::AREA_CODE_GLOB;
	return this->initialize(context);
}

int AgoraClrLibrary::AgoraClr::initialize(ClrRtcEngineContext^ context)
{
	if (rtcEngine)
		return 0;

	rtcEngine = createAgoraRtcEngine();
	if (rtcEngine == nullptr)
		return -1;

	//auto isOK = rtcEngine->setParameters("{\"che.audio.enable.agc\":false}");

	agora::rtc::RtcEngineContext rtcContext;
	rtcContext.appId = strcopy(MarshalString(context->vendorKey));
	rtcContext.eventHandler = agoraEventHandler;
	rtcContext.areaCode = (int)context->areaCode;
	rtcContext.logConfig = context->logConfig->to();
	int result = rtcEngine->initialize(rtcContext);
	if (result == 0)
	{
		// agora设计中一旦注册了packetObserver就会开启加密,
		// 所以此接口注册移入开启加密的方法中进行
		//rtcEngine->registerPacketObserver(agoraPacketObserver);
		IMediaEngine* temp = nullptr;
		if (!rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE, reinterpret_cast<void**>(&temp)))
		{
			agoraMediaEngine = temp;
			agoraMediaEngine->registerAudioFrameObserver(agoraAudioObserver);
			agoraMediaEngine->registerVideoFrameObserver(agoraVideoObserver);
		}
		rtcEngine->registerMediaMetadataObserver(agoraMetadataObserver, IMetadataObserver::METADATA_TYPE::VIDEO_METADATA);
	}
	return result;
}


void AgoraClr::release()
{
	if (rtcEngine)
	{
		if (agoraMediaEngine)
			agoraMediaEngine->release();
		rtcEngine->release();

		delete agoraEventHandler;
		delete agoraPacketObserver;
		delete agoraAudioObserver;
		delete agoraVideoObserver;

		rtcEngine = nullptr;
	}
}

int AgoraClr::enableVideo()
{
	return rtcEngine->enableVideo();
}

int AgoraClr::disableVideo()
{
	return rtcEngine->disableVideo();
}

int AgoraClr::enableAudio()
{
	return rtcEngine->enableAudio();
}

int AgoraClr::disableAudio()
{
	return rtcEngine->disableAudio();
}

int AgoraClr::setBeautyEffectOptions(bool enabled, ClrBeautyOptions options)
{
	return rtcEngine->setBeautyEffectOptions(enabled, options);
}

AgoraClrChannel^ AgoraClr::createChannel(String^ channelId)
{
	IRtcEngine2* engine2 = dynamic_cast<IRtcEngine2*>(rtcEngine);
	return gcnew AgoraClrChannel(engine2->createChannel(MarshalString(channelId).c_str()));
}

int AgoraClr::startScreenCaptureByScreenRect(ClrRectangle^ screenRect, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params)
{
	return rtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, params);
}

int AgoraClr::startScreenCaptureByWindowId(IntPtr windowId, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params)
{
	return rtcEngine->startScreenCaptureByWindowId(windowId.ToPointer(), regionRect, params);
}

int AgoraClr::setScreenCaptureContentHint(EnumVideoContentHint hint)
{
	return rtcEngine->setScreenCaptureContentHint(static_cast<VideoContentHint>(hint));
}

int AgoraClr::updateScreenCaptureParameters(ClrScreenCaptureParameters^ params)
{
	return rtcEngine->updateScreenCaptureParameters(params);
}

int AgoraClr::setLocalVoiceChanger(VoiceChangerPreset changer)
{
	return rtcEngine->setLocalVoiceChanger(static_cast<VOICE_CHANGER_PRESET>(changer));
}

int AgoraClr::setLocalVoiceReverbPreset(EnumAudioReverbPreset preset)
{
	return rtcEngine->setLocalVoiceReverbPreset(static_cast<AUDIO_REVERB_PRESET>(preset));
}

int AgoraClr::enableSoundPositionIndication(bool enabled)
{
	return rtcEngine->enableSoundPositionIndication(enabled);
}

int AgoraClr::setRemoteVoicePosition(uid_t uid, double pan, double gain)
{
	return rtcEngine->setRemoteVoicePosition(uid, pan, gain);
}

int AgoraClr::startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return rtcEngine->startChannelMediaRelay(config);
}

int AgoraClr::updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return rtcEngine->updateChannelMediaRelay(config);
}

int AgoraClrLibrary::AgoraClr::pauseAllChannelMediaRelay()
{
	return rtcEngine->pauseAllChannelMediaRelay();
}

int AgoraClrLibrary::AgoraClr::resumeAllChannelMediaRelay()
{
	return rtcEngine->resumeAllChannelMediaRelay();
}

int AgoraClr::stopChannelMediaRelay()
{
	return rtcEngine->stopChannelMediaRelay();
}

int AgoraClr::addVideoWatermark(String^ url, ClrWatermarkOptions^ options)
{
	return rtcEngine->addVideoWatermark(MarshalString(url).c_str(), options);
}

int AgoraClr::clearVideoWatermarks()
{
	return rtcEngine->clearVideoWatermarks();
}

int AgoraClr::setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate)
{
	return rtcEngine->setHighQualityAudioParameters(fullband, stereo, fullBitrate);
}

int AgoraClr::startPreview()
{
	return rtcEngine->startPreview();
}

int AgoraClr::stopPreview()
{
	return rtcEngine->stopPreview();
}

int AgoraClr::enableWebSdkInteroperability(bool enabled)
{
	return rtcEngine->enableWebSdkInteroperability(enabled);
}

int AgoraClr::joinChannel(String^ token, String^ channelName, String^ channelInfo, UINT uid)
{
	return rtcEngine->joinChannel(MarshalString(token).c_str(), MarshalString(channelName).c_str(), MarshalString(channelInfo).c_str(), uid);
}

int AgoraClrLibrary::AgoraClr::joinChannel(String^ token, String^ channelName, String^ channelInfo, UINT uid, ClrChannelMediaOptions^ options)
{
	return rtcEngine->joinChannel(MarshalString(token).c_str(), MarshalString(channelName).c_str(), MarshalString(channelInfo).c_str(), uid, options);
}

int AgoraClr::switchChannel(String^ token, String^ channelId)
{
	return rtcEngine->switchChannel(MarshalString(token).c_str(), MarshalString(channelId).c_str());
}

int AgoraClrLibrary::AgoraClr::switchChannel(String^ token, String^ channelId, ClrChannelMediaOptions^ options)
{
	return rtcEngine->switchChannel(MarshalString(token).c_str(), MarshalString(channelId).c_str(), options);
}

int AgoraClr::leaveChannel()
{
	// 如果该频道是加密频道, 用户退出时回知道解除加密, 
	// 所以设置为离开频道时, 自动退出数据包观察器, 不管原来频道是否加密
	rtcEngine->registerPacketObserver(nullptr);
	return rtcEngine->leaveChannel();
}

int AgoraClr::startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect, int bitrate)
{
	return rtcEngine->startScreenCapture(static_cast<HWND>(windowId.ToPointer()), captureFreq, rect->toRaw(), bitrate);
}

int AgoraClr::stopScreenCapture()
{
	return rtcEngine->stopScreenCapture();
}

int AgoraClr::updateScreenCaptureRegion(ClrRectangle^ rect)
{
	return rtcEngine->updateScreenCaptureRegion(rect);
}

int AgoraClr::renewToken(String^ token)
{
	return rtcEngine->renewToken(MarshalString(token).c_str());
}

int AgoraClr::setEncryptionSecret(String^ key)
{
	// 设置加密密码时, agora就开启了加密模式, 同时注册数据包观察器
	rtcEngine->registerPacketObserver(agoraPacketObserver);

	return rtcEngine->setEncryptionSecret(MarshalString(key).c_str());
}

int AgoraClr::setEncryptionMode(String^ mode)
{
	return rtcEngine->setEncryptionMode(MarshalString(mode).c_str());
}

int AgoraClrLibrary::AgoraClr::enableEncryption(bool enabled, ClrEncryptionConfig^ config)
{
	return rtcEngine->enableEncryption(enabled, config);
}

int AgoraClrLibrary::AgoraClr::setCloudProxy(EnumCloudProxyType type)
{
	return rtcEngine->setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)type);
}

int AgoraClrLibrary::AgoraClr::enableDeepLearningDenoise(bool enable)
{
	return rtcEngine->enableDeepLearningDenoise(enable);
}

int AgoraClrLibrary::AgoraClr::sendCustomReportMessage(String^ id, String^ category, String^ event, String^ label, int value)
{
	return rtcEngine->sendCustomReportMessage(MarshalString(id).c_str(), MarshalString(category).c_str(), MarshalString(event).c_str(), MarshalString(label).c_str(), value);
}

int AgoraClr::getCallId(String^% id)
{
	agora::util::AString callid;
	int result = rtcEngine->getCallId(callid);
	if (result == 0)
		id = gcnew String(callid.get()->c_str());
	else
		id = nullptr;

	return result;
}

int AgoraClr::rate(String^ callid, int rating, String^ desc)
{
	return rtcEngine->rate(MarshalString(callid).c_str(), rating, MarshalString(desc).c_str());
}

int AgoraClr::complain(String^ callid, String^ desc)
{
	return rtcEngine->complain(MarshalString(callid).c_str(), MarshalString(desc).c_str());
}

int AgoraClr::startEchoTest(int intervalInSeconds)
{
	return rtcEngine->startEchoTest(intervalInSeconds);
}

int AgoraClr::stopEchoTest()
{
	return rtcEngine->stopEchoTest();
}

int AgoraClr::enableLastmileTest()
{
	return rtcEngine->enableLastmileTest();
}

int AgoraClr::disableLastmileTest()
{
	return rtcEngine->disableLastmileTest();
}

int AgoraClr::startLastmileProbeTest(ClrLastmileProbeConfig^ config)
{
	return rtcEngine->startLastmileProbeTest(config);
}

int AgoraClr::stopLastmileProbeTest()
{
	return rtcEngine->stopLastmileProbeTest();
}

int AgoraClr::setVideoProfile(VideoProfile profile, bool swapWidthAndHeight)
{
	return rtcEngine->setVideoProfile(static_cast<agora::rtc::VIDEO_PROFILE_TYPE>(profile), swapWidthAndHeight);
}

int AgoraClr::setupLocalVideo(IntPtr view, int renderMode, UINT uid)
{
	return rtcEngine->setupLocalVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClr::setupLocalVideo(IntPtr view, int renderMode, UINT uid, EnumVideoMirrorModeType mt)
{
	return rtcEngine->setupLocalVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid, static_cast<VIDEO_MIRROR_MODE_TYPE>(mt)));
}

int AgoraClr::setupRemoteVideo(IntPtr view, int renderMode, UINT uid)
{
	return rtcEngine->setupRemoteVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClr::setupRemoteVideo(IntPtr view, int renderMode, UINT uid, EnumVideoMirrorModeType mt)
{
	return rtcEngine->setupRemoteVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid, static_cast<VIDEO_MIRROR_MODE_TYPE>(mt)));
}

int AgoraClr::enableDualStreamMode(bool enabled)
{
	return rtcEngine->enableDualStreamMode(enabled);
}

int AgoraClr::setRemoteVideoStreamType(UINT uid, EnumRemoteVideoStreamType type)
{
	return rtcEngine->setRemoteVideoStreamType(uid, static_cast<REMOTE_VIDEO_STREAM_TYPE>(type));
}

int AgoraClr::setVideoQualityParameters(bool preferFrameRateOverImageQuality)
{
	return rtcEngine->setVideoQualityParameters(preferFrameRateOverImageQuality);
}

int AgoraClr::setChannelProfile(ChannelProfile profile)
{
	return rtcEngine->setChannelProfile(static_cast<agora::rtc::CHANNEL_PROFILE_TYPE>(profile));
}

int AgoraClr::setClientRole(ClientRoleType role)
{
	return rtcEngine->setClientRole(static_cast<CLIENT_ROLE_TYPE>(role));
}

int AgoraClrLibrary::AgoraClr::setClientRole(ClientRoleType role, AgoraClrClientRoleOptions options)
{
	ClientRoleOptions rawOptions = options;
	return rtcEngine->setClientRole(static_cast<CLIENT_ROLE_TYPE>(role), rawOptions);
}

int AgoraClr::createDataStream(int% id, bool reliable, bool ordered)
{
	int streamId;
	int result = rtcEngine->createDataStream(&streamId, reliable, ordered);
	id = streamId;
	return result;
}

int AgoraClrLibrary::AgoraClr::createDataStream(int% id, ClrDataStreamConfig config)
{
	int streamId;
	DataStreamConfig rawConfig = config;
	int result = rtcEngine->createDataStream(&streamId, rawConfig);
	id = streamId;
	return result;
}

int AgoraClr::sendStreamMessage(int id, String^ data)
{
	std::string dataStr = MarshalString(data);
	return rtcEngine->sendStreamMessage(id, dataStr.c_str(), dataStr.length());
}

int AgoraClr::setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	return rtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, static_cast<RAW_AUDIO_FRAME_OP_MODE_TYPE>(mode), samplesPerCall);
}

int AgoraClr::setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	return rtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, static_cast<RAW_AUDIO_FRAME_OP_MODE_TYPE>(mode), samplesPerCall);
}

int AgoraClr::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	return rtcEngine->setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int AgoraClr::muteLocalAudioStream(bool mute)
{
	return rtcEngine->muteLocalAudioStream(mute);
}

int AgoraClr::muteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->muteAllRemoteAudioStreams(mute);
}

int AgoraClr::muteRemoteAudioStream(UINT uid, bool mute)
{
	return rtcEngine->muteRemoteAudioStream(uid, mute);
}

int AgoraClr::muteLocalVideoStream(bool mute)
{
	return rtcEngine->muteLocalVideoStream(mute);
}

int AgoraClr::enableLocalVideo(bool enabled)
{
	return rtcEngine->enableLocalVideo(enabled);
}

int AgoraClr::muteAllRemoteVideoStreams(bool mute)
{
	return rtcEngine->muteAllRemoteVideoStreams(mute);
}

int AgoraClr::muteRemoteVideoStream(UINT uid, bool mute)
{
	return rtcEngine->muteRemoteVideoStream(uid, mute);
}

int AgoraClr::setLocalRenderMode(EnumRenderModeType mode)
{
	return rtcEngine->setLocalRenderMode(static_cast<agora::rtc::RENDER_MODE_TYPE>(mode));
}

int AgoraClr::setLocalRenderMode(EnumRenderModeType mode, EnumVideoMirrorModeType mt)
{
	return rtcEngine->setLocalRenderMode(static_cast<agora::rtc::RENDER_MODE_TYPE>(mode),
		static_cast<VIDEO_MIRROR_MODE_TYPE>(mt));
}

int AgoraClr::setRemoteRenderMode(UINT uid, EnumRenderModeType mode)
{
	return rtcEngine->setRemoteRenderMode(uid, static_cast<agora::rtc::RENDER_MODE_TYPE>(mode));
}

int AgoraClr::setRemoteRenderMode(UINT uid, EnumRenderModeType mode, EnumVideoMirrorModeType mt)
{
	return rtcEngine->setRemoteRenderMode(
		uid, static_cast<agora::rtc::RENDER_MODE_TYPE>(mode),
		static_cast<VIDEO_MIRROR_MODE_TYPE>(mt)
	);
}

int AgoraClr::enableAudioVolumeIndication(int interval, int smooth, bool report_vad)
{
	return rtcEngine->enableAudioVolumeIndication(interval, smooth, report_vad);
}

int AgoraClr::startAudioRecording(String^ path, int sampleRate, AudioRecordingQualityType quality)
{
	return rtcEngine->startAudioRecording(MarshalString(path).c_str(), sampleRate, static_cast<AUDIO_RECORDING_QUALITY_TYPE>(quality));
}

int AgoraClrLibrary::AgoraClr::startAudioRecording(ClrAudioRecordingConfiguration config)
{
	AudioRecordingConfiguration raw = config;
	return rtcEngine->startAudioRecording(raw);
}

int AgoraClr::stopAudioRecording()
{
	return rtcEngine->stopAudioRecording();
}

AgoraClrMediaRecorder^ AgoraClrLibrary::AgoraClr::getMediaRecorder()
{
	return gcnew AgoraClrMediaRecorder(this->rtcEngine);
}

int AgoraClr::pauseAudioMixing()
{
	return rtcEngine->pauseAudioMixing();
}

int AgoraClr::resumeAudioMixing()
{
	return rtcEngine->resumeAudioMixing();
}

int AgoraClr::adjustAudioMixingVolume(int volume)
{
	return rtcEngine->adjustAudioMixingVolume(volume);
}

int AgoraClr::getAudioMixingDuration()
{
	return rtcEngine->getAudioMixingDuration();
}

int AgoraClrLibrary::AgoraClr::getAudioFileInfo(String^ filePath)
{
	return rtcEngine->getAudioFileInfo(MarshalString(filePath).c_str());
}

int AgoraClr::getAudioMixingCurrentPosition()
{
	return rtcEngine->getAudioMixingCurrentPosition();
}

int AgoraClr::setAudioMixingPosition(int pos)
{
	return rtcEngine->setAudioMixingPosition(pos);
}

int AgoraClrLibrary::AgoraClr::getAudioTrackCount()
{
	return rtcEngine->getAudioTrackCount();
}

int AgoraClrLibrary::AgoraClr::selectAudioTrack(int index)
{
	return rtcEngine->selectAudioTrack(index);
}

int AgoraClrLibrary::AgoraClr::setAudioMixingPlaybackSpeed(int speed)
{
	return rtcEngine->setAudioMixingPlaybackSpeed(speed);
}

int AgoraClrLibrary::AgoraClr::setAudioMixingDualMonoMode(EnumAudioMixingDualMonoMode mode)
{
	return rtcEngine->setAudioMixingDualMonoMode(static_cast<agora::media::AUDIO_MIXING_DUAL_MONO_MODE>(mode));
}

int AgoraClrLibrary::AgoraClr::startAudioMixing(String^ path, bool loop, bool replace, int cycle, int startPos)
{
	return rtcEngine->startAudioMixing(MarshalString(path).c_str(), loop, replace, cycle, startPos);
}

int AgoraClr::stopAudioMixing()
{
	return rtcEngine->stopAudioMixing();
}

int AgoraClr::setAudioProfile(AudioProfileType profile, AudioScenarioType scenario)
{
	return rtcEngine->setAudioProfile(static_cast<agora::rtc::AUDIO_PROFILE_TYPE>(profile), static_cast<agora::rtc::AUDIO_SCENARIO_TYPE>(scenario));
}

int AgoraClr::setLogFile(String^ path)
{
	return rtcEngine->setLogFile(MarshalString(path).c_str());
}

int AgoraClr::setLogFilter(unsigned int filter)
{
	return rtcEngine->setLogFilter(filter);
}

int AgoraClr::setLogFileSize(unsigned int size)
{
	return rtcEngine->setLogFileSize(size);
}

int AgoraClr::adjustRecordingSignalVolume(int volume)
{
	return rtcEngine->adjustRecordingSignalVolume(volume);
}

int AgoraClrLibrary::AgoraClr::adjustLoopbackRecordingSignalVolume(int volume)
{
	return rtcEngine->adjustLoopbackRecordingSignalVolume(volume);
}

int AgoraClr::adjustUserPlaybackSignalVolume(UINT uid, int volume)
{
	return rtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
}

int AgoraClr::adjustPlaybackSignalVolume(int volume)
{
	return rtcEngine->adjustPlaybackSignalVolume(volume);
}

int AgoraClr::enableLocalAudio(bool enabled)
{
	return rtcEngine->enableLocalAudio(enabled);
}

int AgoraClr::setLocalVoicePitch(double pitch)
{
	return rtcEngine->setLocalVoicePitch(pitch);
}

int AgoraClr::setExternalAudioSource(bool enabled, int sampleRate, int channels)
{
	return rtcEngine->setExternalAudioSource(enabled, sampleRate, channels);
}

int AgoraClrLibrary::AgoraClr::setExternalAudioSourceVolume(int sourcePos, int volume)
{
	return agoraMediaEngine ? agoraMediaEngine->setExternalAudioSourceVolume(sourcePos, volume) : -1;
}

int AgoraClr::pushAudioFrame(int sourcePos, ClrAudioFrame^ frame)
{
	return agoraMediaEngine ? agoraMediaEngine->pushAudioFrame(sourcePos, frame) : -1;
}

int AgoraClr::setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain)
{
	return rtcEngine->setLocalVoiceEqualization(static_cast<AUDIO_EQUALIZATION_BAND_FREQUENCY>(freq), bandGain);
}

int AgoraClr::setLocalVoiceReverb(AudioReverbType type, int value)
{
	return rtcEngine->setLocalVoiceReverb(static_cast<AUDIO_REVERB_TYPE>(type), value);
}

int AgoraClrLibrary::AgoraClr::setVoiceBeautifierPreset(EnumVoiceBeautifierPreset preset)
{
	return rtcEngine->setVoiceBeautifierPreset(static_cast<VOICE_BEAUTIFIER_PRESET>(preset));
}

int AgoraClrLibrary::AgoraClr::setVoiceBeautifierParameters(EnumVoiceBeautifierPreset preset, int param1, int param2)
{
	return rtcEngine->setVoiceBeautifierParameters(static_cast<VOICE_BEAUTIFIER_PRESET>(preset), param1, param2);
}

int AgoraClrLibrary::AgoraClr::setAudioEffectPreset(EnumAudioEffectPreset preset)
{
	return rtcEngine->setAudioEffectPreset(static_cast<AUDIO_EFFECT_PRESET>(preset));
}

int AgoraClrLibrary::AgoraClr::setAudioEffectParameters(EnumAudioEffectPreset preset, int param1, int param2)
{
	return rtcEngine->setAudioEffectParameters(static_cast<AUDIO_EFFECT_PRESET>(preset), param1, param2);
}

int AgoraClrLibrary::AgoraClr::setVoiceConversionPreset(EnumVoiceConversionPreset preset)
{
	return rtcEngine->setVoiceConversionPreset(static_cast<VOICE_CONVERSION_PRESET>(preset));
}

int AgoraClr::setLocalVideoMirrorMode(EnumVideoMirrorModeType mode)
{
	return rtcEngine->setLocalVideoMirrorMode(static_cast<VIDEO_MIRROR_MODE_TYPE>(mode));
}

int AgoraClr::setCameraCapturerConfiguration(ClrCameraCaptureConfiguration^ config)
{
	return rtcEngine->setCameraCapturerConfiguration(config);
}

String^ AgoraClr::getVersion(int% build)
{
	int version;
	String^ result = gcnew String(rtcEngine->getVersion(&version));
	build = version;
	return result;
}

int AgoraClr::enableLoopbackRecording(bool enabled, String^ name)
{
	return rtcEngine->enableLoopbackRecording(enabled, MarshalString(name).c_str());
}

int AgoraClr::addPublishStreamUrl(String^ url, bool transcodingEnabled)
{
	return rtcEngine->addPublishStreamUrl(MarshalString(url).c_str(), transcodingEnabled);
}

int AgoraClr::removePublishStreamUrl(String^ url)
{
	return rtcEngine->removePublishStreamUrl(MarshalString(url).c_str());
}

int AgoraClr::setLiveTranscoding(ClrLiveTranscoding^ transcoding)
{
	return rtcEngine->setLiveTranscoding(transcoding);
}

int AgoraClr::addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config)
{
	return rtcEngine->addInjectStreamUrl(MarshalString(url).c_str(), config);
}

int AgoraClr::removeInjectStreamUrl(String^ url)
{
	return rtcEngine->removeInjectStreamUrl(MarshalString(url).c_str());
}

int AgoraClr::getEffectsVolume()
{
	return rtcEngine->getEffectsVolume();
}

int AgoraClr::setEffectsVolume(int volume)
{
	return rtcEngine->setEffectsVolume(volume);
}

int AgoraClr::setVolumeOfEffect(int soundId, int volume)
{
	return rtcEngine->setVolumeOfEffect(soundId, volume);
}

int AgoraClrLibrary::AgoraClr::playEffect(int soundId, String^ file, int loopCount, double pitch, double pan, int gain, bool publish, int startPos)
{
	return rtcEngine->playEffect(soundId, MarshalString(file).c_str(), loopCount, pitch, pan, gain, publish, startPos);
}

int AgoraClr::stopEffect(int soundId)
{
	return rtcEngine->stopEffect(soundId);
}

int AgoraClr::stopAllEffects()
{
	return rtcEngine->stopAllEffects();
}

int AgoraClr::preloadEffect(int soundId, String^ file)
{
	return rtcEngine->preloadEffect(soundId, MarshalString(file).c_str());
}

int AgoraClr::unloadEffect(int soundId)
{
	return rtcEngine->unloadEffect(soundId);
}

int AgoraClr::pauseEffect(int soundId)
{
	return rtcEngine->pauseEffect(soundId);
}

int AgoraClr::pauseAllEffects()
{
	return rtcEngine->pauseAllEffects();
}

int AgoraClr::resumeEffect(int soundId)
{
	return rtcEngine->resumeEffect(soundId);
}

int AgoraClr::resumeAllEffects()
{
	return rtcEngine->resumeAllEffects();
}

int AgoraClrLibrary::AgoraClr::getEffectDuration(String^ file)
{
	return rtcEngine->getEffectDuration(MarshalString(file).c_str());
}

int AgoraClrLibrary::AgoraClr::setEffectPosition(int soundId, int pos)
{
	return rtcEngine->setEffectPosition(soundId, pos);
}

int AgoraClrLibrary::AgoraClr::getEffectCurrentPosition(int soundId)
{
	return rtcEngine->getEffectCurrentPosition(soundId);
}

int AgoraClr::setAudioMixingPitch(int pitch)
{
	return rtcEngine->setAudioMixingPitch(pitch);
}

EnumConnectionStateType AgoraClr::getConnectionState()
{
	return static_cast<EnumConnectionStateType>(rtcEngine->getConnectionState());
}

int AgoraClr::setDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
}

int AgoraClr::setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config)
{
	return rtcEngine->setVideoEncoderConfiguration(config);
}

int AgoraClr::setDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
}

int AgoraClr::adjustAudioMixingPlayoutVolume(int volume)
{
	return rtcEngine->adjustAudioMixingPlayoutVolume(volume);
}

int AgoraClr::adjustAudioMixingPublishVolume(int volume)
{
	return rtcEngine->adjustAudioMixingPublishVolume(volume);
}

int AgoraClr::getAudioMixingPlayoutVolume()
{
	return rtcEngine->getAudioMixingPlayoutVolume();
}

int AgoraClr::getAudioMixingPublishVolume()
{
	return rtcEngine->getAudioMixingPublishVolume();
}

int AgoraClr::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	return rtcEngine->setExternalAudioSink(enabled, sampleRate, channels);
}

int AgoraClr::pullAudioFrame([Out] ClrAudioFrame^% frame)
{
	IAudioFrameObserver::AudioFrame* raw = new IAudioFrameObserver::AudioFrame();
	auto result = agoraMediaEngine->pullAudioFrame(raw);
	if (result == 0) {
		frame = gcnew ClrAudioFrame(*raw);
	}
	return result;
	//return agoraMediaEngine ? agoraMediaEngine->pullAudioFrame(frame) : -1;
}

int AgoraClrLibrary::AgoraClr::setLocalVideoRenderer(ClrVideoSink^ sink)
{
	auto result = rtcEngine->setLocalVideoRenderer(NULL);
	if (innerLocalVideoSink != nullptr) innerLocalVideoSink->dispose();

	if (sink != nullptr) {
		innerLocalVideoSink = gcnew InnerVideoSink(sink);
		result = rtcEngine->setLocalVideoRenderer(innerLocalVideoSink);
	}

	return result;
}

int AgoraClrLibrary::AgoraClr::setRemoteVideoRenderer(uid_t uid, ClrVideoSink^ sink)
{
	auto result = rtcEngine->setRemoteVideoRenderer(uid, NULL);
	if (innerRemoteVideoSink != nullptr) innerRemoteVideoSink->dispose();

	if (sink != nullptr) {
		innerRemoteVideoSink = gcnew InnerVideoSink(sink);
		result = rtcEngine->setRemoteVideoRenderer(uid, innerRemoteVideoSink);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::setVideoSource(ClrVideoSource^ source)
{
	auto result = rtcEngine->setVideoSource(NULL);
	if (innerVideoSoruce != nullptr) innerVideoSoruce->dispose();

	if (source != nullptr) {
		innerVideoSoruce = gcnew InnerVideoSource(source);
		result = rtcEngine->setVideoSource(innerVideoSoruce);
	}

	return result;
}

int AgoraClr::setExternalVideoSource(bool enabled, bool useTexture)
{
	return agoraMediaEngine ? agoraMediaEngine->setExternalVideoSource(enabled, useTexture) : -1;
}

int AgoraClr::pushVideoFrame(ClrExternalVideoFrame^ frame)
{
	return agoraMediaEngine ? agoraMediaEngine->pushVideoFrame(frame) : -1;
}

int AgoraClr::setLocalPublishFallbackOption(StreamFallbackOptions option)
{
	return rtcEngine->setLocalPublishFallbackOption(static_cast<STREAM_FALLBACK_OPTIONS>(option));
}

int AgoraClr::setRemoteSubscribeFallbackOption(StreamFallbackOptions option)
{
	return rtcEngine->setRemoteSubscribeFallbackOption(static_cast<STREAM_FALLBACK_OPTIONS>(option));
}

int AgoraClr::setRemoteUserPriority(uid_t uid, PriorityType priority)
{
	return rtcEngine->setRemoteUserPriority(uid, static_cast<PRIORITY_TYPE>(priority));
}

int AgoraClr::setRemoteDefaultVideoStreamType(EnumRemoteVideoStreamType type)
{
	return rtcEngine->setRemoteDefaultVideoStreamType(static_cast<REMOTE_VIDEO_STREAM_TYPE>(type));
}

String^ AgoraClr::getErrorDescription(int code)
{
	return gcnew String(rtcEngine->getErrorDescription(code));
}

void* AgoraClr::regEvent(Object^ obj)
{
	gchs->Add(GCHandle::Alloc(obj));
	return Marshal::GetFunctionPointerForDelegate(obj).ToPointer();
}

void AgoraClr::initializeEventHandler()
{
	agoraEventHandler->onJoinChannelSuccessEvent = PFOnJoinChannelSuccess(regEvent(gcnew NativeOnJoinChannelSuccessDelegate(this, &AgoraClr::NativeOnJoinChannelSuccess)));
	agoraEventHandler->onRejoinChannelSuccessEvent = PFOnRejoinChannelSuccess(regEvent(gcnew NativeOnRejoinChannelSuccessDelegate(this, &AgoraClr::NativeOnRejoinChannelSuccess)));
	agoraEventHandler->onWarningEvent = PFOnWarning(regEvent(gcnew NativeOnWarningDelegate(this, &AgoraClr::NativeOnWarning)));
	agoraEventHandler->onErrorEvent = PFOnError(regEvent(gcnew NativeOnErrorDelegate(this, &AgoraClr::NativeOnError)));
	agoraEventHandler->onAudioQualityEvent = PFOnAudioQuality(regEvent(gcnew NativeOnAudioQualityDelegate(this, &AgoraClr::NativeOnAudioQuality)));
	agoraEventHandler->onAudioVolumeIndicationEvent = PFOnAudioVolumeIndication(regEvent(gcnew NativeOnAudioVolumeIndicationDelegate(this, &AgoraClr::NativeOnAudioVolumeIndication)));
	agoraEventHandler->onLeaveChannelEvent = PFOnLeaveChannel(regEvent(gcnew NativeOnLeaveChannelDelegate(this, &AgoraClr::NativeOnLeaveChannel)));
	agoraEventHandler->onRtcStatsEvent = PFOnRtcStats(regEvent(gcnew NativeOnRtcStatsDelegate(this, &AgoraClr::NativeOnRtcStats)));
	agoraEventHandler->onAudioDeviceStateChangedEvent = PFOnAudioDeviceStateChanged(regEvent(gcnew NativeOnAudioDeviceStateChangedDelegate(this, &AgoraClr::NativeOnAudioDeviceStateChanged)));
	agoraEventHandler->onVideoDeviceStateChangedEvent = PFOnVideoDeviceStateChanged(regEvent(gcnew NativeOnVideoDeviceStateChangedDelegate(this, &AgoraClr::NativeOnVideoDeviceStateChanged)));
	agoraEventHandler->onLastmileQualityEvent = PFOnLastmileQuality(regEvent(gcnew NativeOnLastmileQualityDelegate(this, &AgoraClr::NativeOnLastmileQuality)));
	agoraEventHandler->onNetworkQualityEvent = PFOnNetworkQuality(regEvent(gcnew NativeOnNetworkQualityDelegate(this, &AgoraClr::NativeOnNetworkQuality)));
	agoraEventHandler->onFirstLocalVideoFrameEvent = PFOnFirstLocalVideoFrame(regEvent(gcnew NativeOnFirstLocalVideoFrameDelegate(this, &AgoraClr::NativeOnFirstLocalVideoFrame)));
	agoraEventHandler->onFirstRemoteVideoDecodedEvent = PFOnFirstRemoteVideoDecoded(regEvent(gcnew NativeOnFirstRemoteVideoDecodedDelegate(this, &AgoraClr::NativeOnFirstRemoteVideoDecoded)));
	agoraEventHandler->onFirstRemoteVideoFrameEvent = PFOnFirstRemoteVideoFrame(regEvent(gcnew NativeOnFirstRemoteVideoFrameDelegate(this, &AgoraClr::NativeOnFirstRemoteVideoFrame)));
	agoraEventHandler->onUserJoinedEvent = PFOnUserJoined(regEvent(gcnew NativeOnUserJoinedDelegate(this, &AgoraClr::NativeOnUserJoined)));
	agoraEventHandler->onUserOfflineEvent = PFOnUserOffline(regEvent(gcnew NativeOnUserOfflineDelegate(this, &AgoraClr::NativeOnUserOffline)));
	agoraEventHandler->onUserMuteAudioEvent = PFOnUserMuteAudio(regEvent(gcnew NativeOnUserMuteAudioDelegate(this, &AgoraClr::NativeOnUserMuteAudio)));
	agoraEventHandler->onUserMuteVideoEvent = PFOnUserMuteVideo(regEvent(gcnew NativeOnUserMuteVideoDelegate(this, &AgoraClr::NativeOnUserMuteVideo)));
	agoraEventHandler->onUserEnableVideoEvent = PFOnUserEnableVideo(regEvent(gcnew NativeOnUserEnableVideoDelegate(this, &AgoraClr::NativeOnUserEnableVideo)));
	agoraEventHandler->onApiCallExecutedEvent = PFOnApiCallExecuted(regEvent(gcnew NativeOnApiCallExecutedDelegate(this, &AgoraClr::NativeOnApiCallExecuted)));
	agoraEventHandler->onLocalVideoStatsEvent = PFOnLocalVideoStats(regEvent(gcnew NativeOnLocalVideoStatsDelegate(this, &AgoraClr::NativeOnLocalVideoStats)));
	agoraEventHandler->onRemoteVideoStatsEvent = PFOnRemoteVideoStats(regEvent(gcnew NativeOnRemoteVideoStatsDelegate(this, &AgoraClr::NativeOnRemoteVideoStats)));
	agoraEventHandler->onCameraReadyEvent = PFOnCameraReady(regEvent(gcnew NativeOnCameraReadyDelegate(this, &AgoraClr::NativeOnCameraReady)));
	agoraEventHandler->onVideoStoppedEvent = PFOnVideoStopped(regEvent(gcnew NativeOnVideoStoppedDelegate(this, &AgoraClr::NativeOnVideoStopped)));
	agoraEventHandler->onConnectionLostEvent = PFOnConnectionLost(regEvent(gcnew NativeOnConnectionLostDelegate(this, &AgoraClr::NativeOnConnectionLost)));
	agoraEventHandler->onConnectionBannedEvent = PFOnConnectionBanned(regEvent(gcnew NativeOnConnectionBannedDelegate(this, &AgoraClr::NativeOnConnectionBanned)));

	agoraEventHandler->onConnectionInterruptedEvent = PFOnConnectionInterrupted(regEvent(gcnew NativeOnConnectionInterruptedDelegate(this, &AgoraClr::NativeOnConnectionInterrupted)));
	agoraEventHandler->onStreamMessageEvent = PFOnStreamMessage(regEvent(gcnew NativeOnStreamMessageDelegate(this, &AgoraClr::NativeOnStreamMessage)));
	agoraEventHandler->onStreamMessageErrorEvent = PFOnStreamMessageError(regEvent(gcnew NativeOnStreamMessageErrorDelegate(this, &AgoraClr::NativeOnStreamMessageError)));
	agoraEventHandler->onRequestChannelKeyEvent = PFOnRequestChannelKey(regEvent(gcnew NativeOnRequestChannelKeyDelegate(this, &AgoraClr::NativeOnRequestChannelKey)));
	agoraEventHandler->onRequestTokenEvent = PFOnRequestToken(regEvent(gcnew NativeOnRequestTokenDelegate(this, &AgoraClr::NativeOnRequestToken)));

	agoraEventHandler->onAudioMixingFinishedEvent = PFOnAudioMixingFinished(regEvent(gcnew NativeOnAudioMixingFinishedDelegate(this, &AgoraClr::NativeOnAudioMixingFinished)));
	agoraEventHandler->onActiveSpeakerEvent = PFOnActiveSpeaker(regEvent(gcnew NativeOnActiveSpeakerDelegate(this, &AgoraClr::NativeOnActiveSpeaker)));
	agoraEventHandler->onClientRoleChangedEvent = PFOnClientRoleChanged(regEvent(gcnew NativeOnClientRoleChangedDelegate(this, &AgoraClr::NativeOnClientRoleChanged)));
	agoraEventHandler->onAudioDeviceVolumeChangedEvent = PFOnAudioDeviceVolumeChanged(regEvent(gcnew NativeOnAudioDeviceVolumeChangedDelegate(this, &AgoraClr::NativeOnAudioDeviceVolumeChanged)));

	agoraEventHandler->onStreamUnpublishedEvent = PFOnStreamUnpublished(regEvent(gcnew NativeOnStreamUnpublishedDelegate(this, &AgoraClr::NativeOnStreamUnpublished)));
	agoraEventHandler->onStreamPublishedEvent = PFOnStreamPublished(regEvent(gcnew NativeOnStreamPublishedDelegate(this, &AgoraClr::NativeOnStreamPublished)));
	agoraEventHandler->onTranscodingUpdatedEvent = PFOnTranscodingUpdated(regEvent(gcnew NativeOnTranscodingUpdatedDelegate(this, &AgoraClr::NativeOnTranscodingUpdated)));

	agoraEventHandler->onConnectionStateChangedEvent = PFOnConnectionStateChanged(regEvent(gcnew NativeOnConnectionStateChangedDelegate(this, &AgoraClr::NativeOnConnectionStateChanged)));
	agoraEventHandler->onTokenPrivilegeWillExpireEvent = PFOnTokenPrivilegeWillExpire(regEvent(gcnew NativeOnTokenPrivilegeWillExpireDelegate(this, &AgoraClr::NativeOnTokenPrivilegeWillExpire)));
	agoraEventHandler->onFirstLocalAudioFrameEvent = PFOnFirstLocalAudioFrame(regEvent(gcnew NativeOnFirstLocalAudioFrameDelegate(this, &AgoraClr::NativeOnFirstLocalAudioFrame)));
	agoraEventHandler->onFirstRemoteAudioFrameEvent = PFOnFirstRemoteAudioFrame(regEvent(gcnew NativeOnFirstRemoteAudioFrameDelegate(this, &AgoraClr::NativeOnFirstRemoteAudioFrame)));
	agoraEventHandler->onUserEnableLocalVideoEvent = PFOnUserEnableLocalVideo(regEvent(gcnew NativeOnUserEnableLocalVideoDelegate(this, &AgoraClr::NativeOnUserEnableLocalVideo)));
	agoraEventHandler->onVideoSizeChangedEvent = PFOnVideoSizeChanged(regEvent(gcnew NativeOnVideoSizeChangedDelegate(this, &AgoraClr::NativeOnVideoSizeChanged)));
	agoraEventHandler->onRemoteVideoStateChangedEvent = PFOnRemoteVideoStateChanged(regEvent(gcnew NativeOnRemoteVideoStateChangedDelegate(this, &AgoraClr::NativeOnRemoteVideoStateChanged)));
	agoraEventHandler->onLocalPublishFallbackToAudioOnlyEvent = PFOnLocalPublishFallbackToAudioOnly(regEvent(gcnew NativeOnLocalPublishFallbackToAudioOnlyDelegate(this, &AgoraClr::NativeOnLocalPublishFallbackToAudioOnly)));
	agoraEventHandler->onRemoteSubscribeFallbackToAudioOnlyEvent = PFOnRemoteSubscribeFallbackToAudioOnly(regEvent(gcnew NativeOnRemoteSubscribeFallbackToAudioOnlyDelegate(this, &AgoraClr::NativeOnRemoteSubscribeFallbackToAudioOnly)));
	agoraEventHandler->onRemoteAudioStatsEvent = PFOnRemoteAudioStats(regEvent(gcnew NativeOnRemoteAudioStatsDelegate(this, &AgoraClr::NativeOnRemoteAudioStats)));
	agoraEventHandler->onRemoteAudioTransportStatsEvent = PFOnRemoteAudioTransportStats(regEvent(gcnew NativeOnRemoteAudioTransportStatsDelegate(this, &AgoraClr::NativeOnRemoteAudioTransportStats)));
	agoraEventHandler->onRemoteVideoTransportStatsEvent = PFOnRemoteVideoTransportStats(regEvent(gcnew NativeOnRemoteVideoTransportStatsDelegate(this, &AgoraClr::NativeOnRemoteVideoTransportStats)));
	agoraEventHandler->onAudioMixingBeginEvent = PFOnAudioMixingBegin(regEvent(gcnew NativeOnAudioMixingBeginDelegate(this, &AgoraClr::NativeOnAudioMixingBegin)));
	agoraEventHandler->onAudioMixingEndEvent = PFOnAudioMixingEnd(regEvent(gcnew NativeOnAudioMixingEndDelegate(this, &AgoraClr::NativeOnAudioMixingEnd)));
	agoraEventHandler->onAudioEffectFinishedEvent = PFOnAudioEffectFinished(regEvent(gcnew NativeOnAudioEffectFinishedDelegate(this, &AgoraClr::NativeOnAudioEffectFinished)));
	agoraEventHandler->onStreamInjectedStatusEvent = PFOnStreamInjectedStatus(regEvent(gcnew NativeOnStreamInjectedStatusDelegate(this, &AgoraClr::NativeOnStreamInjectedStatus)));
	agoraEventHandler->onMediaEngineLoadSuccessEvent = PFOnMediaEngineLoadSuccess(regEvent(gcnew NativeOnMediaEngineLoadSuccessDelegate(this, &AgoraClr::NativeOnMediaEngineLoadSuccess)));
	agoraEventHandler->onMediaEngineStartCallSuccessEvent = PFOnMediaEngineStartCallSuccess(regEvent(gcnew NativeOnMediaEngineStartCallSuccessDelegate(this, &AgoraClr::NativeOnMediaEngineStartCallSuccess)));
	agoraEventHandler->onNetworkTypeChangedEvent = PFOnNetworkTypeChanged(regEvent(gcnew NativeOnNetworkTypeChangedDelegate(this, &AgoraClr::NativeOnNetworkTypeChanged)));
	agoraEventHandler->onLocalAudioStateChangedEvent = PFOnLocalAudioStateChanged(regEvent(gcnew NativeOnLocalAudioStateChangedDelegate(this, &AgoraClr::NativeOnLocalAudioStateChanged)));
	agoraEventHandler->onLocalVideoStateChangedEvent = PFOnLocalVideoStateChanged(regEvent(gcnew NativeOnLocalVideoStateChangedDelegate(this, &AgoraClr::NativeOnLocalVideoStateChanged)));
	agoraEventHandler->onRemoteAudioStateChangedEvent = PFOnRemoteAudioStateChanged(regEvent(gcnew NativeOnRemoteAudioStateChangedDelegate(this, &AgoraClr::NativeOnRemoteAudioStateChanged)));
	agoraEventHandler->onFirstRemoteAudioDecodedEvent = PFOnFirstRemoteAudioDecoded(regEvent(gcnew NativeOnFirstRemoteAudioDecodedDelegate(this, &AgoraClr::NativeOnFirstRemoteAudioDecoded)));
	agoraEventHandler->onLocalAudioStatsEvent = PFOnLocalAudioStats(regEvent(gcnew NativeOnLocalAudioStatsDelegate(this, &AgoraClr::NativeOnLocalAudioStats)));
	agoraEventHandler->onAudioMixingStateChangedEvent = PFOnAudioMixingStateChanged(regEvent(gcnew NativeOnAudioMixingStateChangedDelegate(this, &AgoraClr::NativeOnAudioMixingStateChanged)));
	agoraEventHandler->onRemoteAudioMixingBeginEvent = PFOnRemoteAudioMixingBegin(regEvent(gcnew Action(this, &AgoraClr::NativeOnRemoteAudioMixingBegin)));

	agoraEventHandler->onRemoteAudioMixingEndEvent = static_cast<stdCall>(regEvent(gcnew Action(this, &AgoraClr::NativeOnRemoteAudioMixingEnd)));
	agoraEventHandler->onRtmpStreamingStateChangedEvent = static_cast<PFOnRtmpStreamingStateChanged>(regEvent(gcnew NativeOnRtmpStreamingStateChangedDelegate(this, &AgoraClr::NativeOnRtmpStreamingStateChanged)));
	agoraEventHandler->onChannelMediaRelayStateChangedEvent = static_cast<PFOnChannelMediaRelayStateChanged>(regEvent(gcnew NativeOnChannelMediaRelayStateChangedDelegate(this, &AgoraClr::NativeOnChannelMediaRelayStateChanged)));
	agoraEventHandler->onChannelMediaRelayEventEvnet = static_cast<PFOnChannelMediaRelayEvent>(regEvent(gcnew NativeOnChannelMediaRelayEventDelegate(this, &AgoraClr::NativeOnChannelMediaRelayEvent)));
	agoraEventHandler->onLastmileProbeResultEvent = static_cast<PFOnLastmileProbeResult>(regEvent(gcnew NativeOnLastmileProbeResultDelegate(this, &AgoraClr::NativeOnLastmileProbeResult)));

	agoraEventHandler->onAudioPublishStateChangedEvent = static_cast<OnAudioPublishStateChanged::Pointer>(regEvent(gcnew OnAudioPublishStateChanged::Type(this, &AgoraClr::NativeOnAudioPublishStateChanged)));
	agoraEventHandler->onVideoPublishStateChangedEvent = static_cast<OnVideoPublishStateChanged::Pointer>(regEvent(gcnew OnVideoPublishStateChanged::Type(this, &AgoraClr::NativeOnVideoPublishStateChanged)));
	agoraEventHandler->onAudioSubscribeStateChangedEvent = static_cast<OnAudioSubscribeStateChanged::Pointer>(regEvent(gcnew OnAudioSubscribeStateChanged::Type(this, &AgoraClr::NativeOnAudioSubscribeStateChanged)));
	agoraEventHandler->onVideoSubscribeStateChangedEvent = static_cast<OnVideoSubscribeStateChanged::Pointer>(regEvent(gcnew OnVideoSubscribeStateChanged::Type(this, &AgoraClr::NativeOnVideoSubscribeStateChanged)));
	agoraEventHandler->onFirstLocalAudioFramePublishedEvent = static_cast<OnFirstLocalAudioFramePublished::Pointer>(regEvent(gcnew OnFirstLocalAudioFramePublished::Type(this, &AgoraClr::NativeOnFirstLocalAudioFramePublished)));
	agoraEventHandler->onFirstLocalVideoFramePublishedEvent = static_cast<OnFirstLocalVideoFramePublished::Pointer>(regEvent(gcnew OnFirstLocalVideoFramePublished::Type(this, &AgoraClr::NativeOnFirstLocalVideoFramePublished)));

	agoraEventHandler->onRtmpStreamingEventEvent = static_cast<OnRtmpStreamingEvent::Pointer>(regEvent(gcnew OnRtmpStreamingEvent::Type(this, &AgoraClr::NativeOnRtmpStreamingEvent)));
	agoraEventHandler->onRequestAudioFileInfoEvent = static_cast<OnRequestAudioFileInfo::Pointer>(regEvent(gcnew OnRequestAudioFileInfo::Type(this, &AgoraClr::NativeOnRequestAudioFileInfo)));
}

void AgoraClr::initializePacketObserver()
{
	agoraPacketObserver->onSendAudioPacketEvent = PFOnSendAudioPacket(regEvent(gcnew NativeOnSendAudioPacketDelegate(this, &AgoraClr::NativeOnSendAudioPacket)));
	agoraPacketObserver->onSendVideoPacketEvent = PFOnSendVideoPacket(regEvent(gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClr::NativeOnSendVideoPacket)));
	agoraPacketObserver->onReceiveVideoPacketEvent = PFOnReceiveVideoPacket(regEvent(gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClr::NativeOnReceiveVideoPacket)));
	agoraPacketObserver->onReceiveAudioPacketEvent = PFOnReceiveAudioPacket(regEvent(gcnew NativeOnReceiveAudioPacketDelegate(this, &AgoraClr::NativeOnReceiveAudioPacket)));
}

void AgoraClr::initializeRawFrameObserver()
{
	agoraAudioObserver->onRecordAudioFrameEvent = PFOnRecordAudioFrame(regEvent(gcnew NativeOnRecordAudioFrameDelegate(this, &AgoraClr::NativeOnRecordAudioFrame)));
	agoraAudioObserver->onPlaybackAudioFrameEvent = PFOnPlaybackAudioFrame(regEvent(gcnew NativeOnPlaybackAudioFrameDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrame)));
	agoraAudioObserver->onPlaybackAudioFrameBeforeMixingEvent = PFOnPlaybackAudioFrameBeforeMixing(regEvent(gcnew NativeOnPlaybackAudioFrameBeforeMixingDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing)));
	agoraAudioObserver->onMixedAudioFrameEvent = PFOnMixedAudioFrame(regEvent(gcnew NativeOnMixedAudioFrameDelegate(this, &AgoraClr::NativeOnMixedAudioFrame)));
	agoraAudioObserver->isMultipleChannelFrameWantedEvent = static_cast<PFIsMultipleChannelFrameWanted>(regEvent(gcnew NativeIsMultipleChannelFrameWantedDelegate(this, &AgoraClr::NativeIsMultipleChannelAudioFrameWanted)));

	agoraVideoObserver->onCaptureVideoFrameEvent = PFOnCaptureVideoFrame(regEvent(gcnew NativeOnCaptureVideoFrameDelegate(this, &AgoraClr::NativeOnCaptureVideoFrame)));
	agoraVideoObserver->onPreEncodeVideoFrameEvent = PFOnPreEncodeVideoFrame(regEvent(gcnew NativeOnPreEncodeVideoFrameDelegate(this, &AgoraClr::NativeOnPreEncodeVideoFrame)));
	agoraVideoObserver->getSmoothRenderingEnabledEvent = PFGetSmoothRenderingEnabled(regEvent(gcnew NativeGetSmoothRenderingEnabledDelegate(this, &AgoraClr::NativeOnGetSmoothRenderingEnabled)));
	agoraVideoObserver->onRenderVideoFrameEvent = PFOnRenderVideoFrame(regEvent(gcnew NativeOnRenderVideoFrameDelegate(this, &AgoraClr::NativeOnRenderVideoFrame)));
	agoraVideoObserver->onGetVideoFormatPreferenceEvent = static_cast<PFOnGetVideoFormatPreference>(regEvent(gcnew NativeOnGetVideoFormatePreferenceDelegate(this, &AgoraClr::NativeOnGetVideoFormatPreference)));
	agoraVideoObserver->onGetRotationAppliedEvent = static_cast<PFOnGetRotationApplied>(regEvent(gcnew NativeOnGetRotationAppliedDelegate(this, &AgoraClr::NativeOnGetRotationApplied)));
	agoraVideoObserver->onGetMirrorAppliedEvent = static_cast<PFOnGetMirrorApplied>(regEvent(gcnew NativeOnGetMirrorAppliedDelegate(this, &AgoraClr::NativeOnGetMirrorApplied)));
	agoraVideoObserver->isMultipleChannelFrameWantedEvent = static_cast<PFIsMultipleChannelFrameWanted>(regEvent(gcnew NativeIsMultipleChannelFrameWantedDelegate(this, &AgoraClr::NativeIsMultipleChannelVideoFrameWanted)));
	agoraVideoObserver->getObservedFramePositionEvent = static_cast<PFGetObservedFramePosition>(regEvent(gcnew NativeGetObservedFramePositionDelegate(this, &AgoraClr::NativeObservedVideoFramePosition)));
	agoraVideoObserver->onRenderVideoFrameExEvent = PFOnRenderVideoFrameEx(regEvent(gcnew NativeOnRenderVideoFrameExDelegate(this, &AgoraClr::NativeOnRenderVideoFrameEx)));
}

void AgoraClr::initializeMetaObserver()
{
	agoraMetadataObserver->onGetMaxMetadataSizeEvent = static_cast<PFOnGetMaxMetadataSize>(regEvent(gcnew NativeOnGetMaxMetadataSizeDelegate(this, &AgoraClr::NativeGetMaxMetadataSize)));
	agoraMetadataObserver->onReadyToSendMetadataEvent = static_cast<PFOnReadyToSendMetadata>(regEvent(gcnew NativeOnReadyToSendMetadataDelegate(this, &AgoraClr::NativeOnReadyToSendMetadata)));
	agoraMetadataObserver->onMetadataReceivedEvent = static_cast<PFOnMetadataReceived>(regEvent(gcnew NativeOnMetadataReceivedDelegate(this, &AgoraClr::NativeOnMetadataReceived)));
}

AgoraClrAudioDeviceManager^ AgoraClr::getAudioDeviceManager()
{
	return gcnew AgoraClrAudioDeviceManager(this->rtcEngine);
}

AgoraClrVideoDeviceManager^ AgoraClr::getVideoDeviceManager()
{
	return gcnew AgoraClrVideoDeviceManager(this->rtcEngine);
}

void AgoraClr::NativeOnJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccess)
	{
		onJoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccess)
	{
		onRejoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnWarning(int warn, const char* msg)
{
	if (onWarning)
	{
		onWarning(warn, gcnew String(msg));
	}
}

void AgoraClr::NativeOnError(int err, const char* msg)
{
	if (onError)
		onError(err, gcnew String(msg));
}

void AgoraClr::NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	if (onAudioQuality)
		onAudioQuality(uid, quality, delay, lost);
}

void AgoraClr::NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	if (onAudioVolumeIndication)
	{
		List<ClrAudioVolumeInfo^>^ list = gcnew List<ClrAudioVolumeInfo^>();
		for (unsigned int i = 0; i < speakerNumber; i++)
			list->Add(gcnew ClrAudioVolumeInfo(speakers[i]));

		onAudioVolumeIndication(list, totalVolume);
	}
}

void AgoraClr::NativeOnLeaveChannel(const agora::rtc::RtcStats& stats)
{
	if (onLeaveChannel)
		onLeaveChannel(gcnew ClrRtcStats(stats));
}

void AgoraClr::NativeOnRtcStats(const agora::rtc::RtcStats& stats)
{
	if (onRtcStats)
	{
		ClrRtcStats^ rtc = gcnew ClrRtcStats(stats);
		onRtcStats(rtc);
	}
}

void AgoraClr::NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onAudioDeviceStateChanged)
		onAudioDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClr::NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onVideoDeviceStateChanged)
		onVideoDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClr::NativeOnAudioMixingFinished()
{
	if (onAudioMixingFinished)
		onAudioMixingFinished();
}

void AgoraClr::NativeOnActiveSpeaker(uid_t uid)
{
	if (onActiveSpeaker)
		onActiveSpeaker(uid);
}

void AgoraClr::NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	if (onClientRoleChanged)
		onClientRoleChanged(static_cast<ClientRoleType>(oldRole), static_cast<ClientRoleType>(newRole));
}

void AgoraClr::NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChanged)
		onAudioDeviceVolumeChanged(static_cast<MediaDeviceType>(deviceType), volume, muted);
}

void AgoraClr::NativeOnStreamUnpublished(const char* url)
{
	if (onStreamUnpublished)
		onStreamUnpublished(gcnew String(url));
}

void AgoraClr::NativeOnStreamPublished(const char* url, int error)
{
	if (onStreamPublished)
		onStreamPublished(gcnew String(url), error);
}

void AgoraClr::NativeOnTranscodingUpdated()
{
	if (onTranscodingUpdated)
		onTranscodingUpdated();
}

void AgoraClr::NativeOnConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (onConnectionStateChanged)
		onConnectionStateChanged(static_cast<EnumConnectionStateType>(state), static_cast<EnumConnectionChangedReasonType>(reason));
}

void AgoraClr::NativeOnTokenPrivilegeWillExpire(const char* token)
{
	if (onTokenPrivilegeWillExpire)
		onTokenPrivilegeWillExpire(gcnew String(token));
}

void AgoraClr::NativeOnFirstLocalAudioFrame(int elapsed)
{
	if (onFirstLocalAudioFrame)
		onFirstLocalAudioFrame(elapsed);
}

void AgoraClr::NativeOnFirstRemoteAudioFrame(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioFrame)
		onFirstRemoteAudioFrame(uid, elapsed);
}

void AgoraClr::NativeOnUserEnableLocalVideo(uid_t uid, bool enabled)
{
	if (onUserEnableLocalVideo)
		onUserEnableLocalVideo(uid, enabled);
}

void AgoraClr::NativeOnVideoSizeChanged(uid_t uid, int width, int height, int rotation)
{
	if (onVideoSizeChanged)
		onVideoSizeChanged(uid, width, height, rotation);
}

void AgoraClr::NativeOnRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	if (onRemoteVideoStateChanged)
		onRemoteVideoStateChanged(uid, static_cast<EnumRemoteVideoState>(state), static_cast<EnumRemoteVideoStateReason>(reason), elapsed);
}

void AgoraClr::NativeOnLastmileQuality(int quality)
{
	if (onLastmileQuality)
		onLastmileQuality(quality);
}

void AgoraClr::NativeOnNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQuality)
		onNetworkQuality(uid, txQuality, rxQuality);
}

void AgoraClr::NativeOnFirstLocalVideoFrame(int width, int height, int elapsed)
{
	if (onFirstLocalVideoFrame)
		onFirstLocalVideoFrame(width, height, elapsed);
}

void AgoraClr::NativeOnFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
	if (onFirstRemoteVideoDecoded)
		onFirstRemoteVideoDecoded(uid, width, height, elapsed);
}

void AgoraClr::NativeOnFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{
	if (onFirstRemoteVideoFrame)
		onFirstRemoteVideoFrame(uid, width, height, elapsed);
}

void AgoraClr::NativeOnUserJoined(uid_t uid, int elapsed)
{
	if (onUserJoined)
		onUserJoined(uid, elapsed);
}

void AgoraClr::NativeOnUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	if (onUserOffline)
		onUserOffline(uid, static_cast<UserOfflineType>(reason));
}

void AgoraClr::NativeOnNetworkTypeChanged(NETWORK_TYPE type)
{
	if (onNetworkTypeChanged)
		onNetworkTypeChanged(static_cast<NetworkType>(type));
}

void AgoraClr::NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	if (onLocalAudioStateChanged)
		onLocalAudioStateChanged(static_cast<LocalAudioStreamState>(state), static_cast<LocalAudioStreamError>(error));
}

void AgoraClr::NativeOnLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
{
	if (onLocalVideoStateChanged)
		onLocalVideoStateChanged(static_cast<LocalVideoStreamState>(state), static_cast<LocalVideoStreamError>(error));
}

void AgoraClr::NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChanged)
		onRemoteAudioStateChanged(uid, static_cast<EnumRemoteAudioState>(state), static_cast<EnumRemoteAudioStateReason>(reason), elapsed);
}

void AgoraClr::NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioDecoded)
		onFirstRemoteAudioDecoded(uid, elapsed);
}

void AgoraClr::NativeOnLocalAudioStats(const LocalAudioStats& stats)
{
	if (onLocalAudioStats)
		onLocalAudioStats(gcnew ClrLocalAudioStats(stats));
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_REASON_TYPE reason)
{
	if (onAudioMixingStateChanged)
		onAudioMixingStateChanged(static_cast<AudioMixingStateType>(state), static_cast<AudioMixingReasonType>(reason));
}

void AgoraClr::NativeOnRemoteAudioMixingBegin()
{
	if (onRemoteAudioMixingBegin)
		onRemoteAudioMixingBegin();
}

void AgoraClr::NativeOnRemoteAudioMixingEnd()
{
	if (onRemoteAudioMixingEnd)
		onRemoteAudioMixingEnd();
}

void AgoraClr::NativeOnRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE error)
{
	if (onRtmpStreamingStateChanged)
		onRtmpStreamingStateChanged(gcnew String(url), static_cast<EnumRtmpStreamPublishState>(state), static_cast<EnumRtmpStreamPublishError>(error));
}

void AgoraClr::NativeOnChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error)
{
	if (onChannelMediaRelayStateChanged)
		onChannelMediaRelayStateChanged(static_cast<EnumChannelMediaRelayState>(state), static_cast<EnumChannelMediaRelayError>(error));
}

void AgoraClr::NativeOnChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event)
{
	if (onChannelMediaRelayEvent)
		onChannelMediaRelayEvent(static_cast<EnumChannelMediaRelayEvent>(event));
}

void AgoraClr::NativeOnLastmileProbeResult(const LastmileProbeResult& result)
{
	if (onLastmileProbeResult)
		onLastmileProbeResult(gcnew ClrLastmileProbeResult(result));
}

int AgoraClr::NativeGetMaxMetadataSize()
{
	return MaxMetadataSize;
}

bool AgoraClr::NativeOnReadyToSendMetadata(IMetadataObserver::Metadata& metadata)
{
	return onReadyToSendMetadata ? onReadyToSendMetadata(gcnew ClrMetadata(metadata)) : false;
}

void AgoraClr::NativeOnMetadataReceived(const IMetadataObserver::Metadata& metadata)
{
	if (onMetadataReceived)
		onMetadataReceived(gcnew ClrMetadata(metadata));
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	if (onVideoPublishStateChanged)
		onVideoPublishStateChanged(
			gcnew String(channel),
			(EnumStreamPublishState)oldState,
			(EnumStreamPublishState)newState,
			elapseSinceLastState
		);
}

void AgoraClrLibrary::AgoraClr::NativeOnVideoPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	if (this->onVideoPublishStateChanged)
		this->onVideoPublishStateChanged(
			gcnew String(channel),
			(EnumStreamPublishState)oldState,
			(EnumStreamPublishState)newState,
			elapseSinceLastState
		);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	if (this->onAudioSubscribeStateChanged)
		this->onAudioSubscribeStateChanged(
			gcnew String(channel),
			uid,
			(EnumStreamSubscribeState)oldState,
			(EnumStreamSubscribeState)newState,
			elapseSinceLastState
		);
}

void AgoraClrLibrary::AgoraClr::NativeOnVideoSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	if (this->onVideoSubscribeStateChanged)
		this->onVideoSubscribeStateChanged(
			gcnew String(channel),
			uid,
			(EnumStreamSubscribeState)oldState,
			(EnumStreamSubscribeState)newState,
			elapseSinceLastState
		);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstLocalAudioFramePublished(int elapse)
{
	if (this->onFirstLocalAudioFramePublished)
		this->onFirstLocalAudioFramePublished(elapse);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstLocalVideoFramePublished(int elapse)
{
	if (this->onFirstLocalVideoFramePublished)
		this->onFirstLocalVideoFramePublished(elapse);
}

void AgoraClrLibrary::AgoraClr::NativeOnRtmpStreamingEvent(const char* url, RTMP_STREAMING_EVENT code)
{
	if (this->onRtmpStreamingEvent)
		this->onRtmpStreamingEvent(gcnew String(url), (EnumRtmpStreamingEvent)code);
}

void AgoraClrLibrary::AgoraClr::NativeOnRequestAudioFileInfo(const AudioFileInfo& info, AUDIO_FILE_INFO_ERROR error)
{
	if (onRequestAudioFileInfo) onRequestAudioFileInfo(gcnew ClrAudioFileInfo(info), static_cast<EnumAudioFileInfoError>(error));
}

void AgoraClr::NativeOnUserMuteAudio(uid_t uid, bool muted)
{
	if (onUserMuteAudio)
		onUserMuteAudio(uid, muted);
}

void AgoraClr::NativeOnUserMuteVideo(uid_t uid, bool muted)
{
	if (onUserMuteVideo)
		onUserMuteVideo(uid, muted);
}

void AgoraClr::NativeOnUserEnableVideo(uid_t uid, bool enabled)
{
	if (onUserEnableVideo)
		onUserEnableVideo(uid, enabled);
}

void AgoraClr::NativeOnApiCallExecuted(int err, const char* api, const char* result)
{
	if (onApiCallExecuted)
		onApiCallExecuted(err, gcnew String(api), gcnew String(result));
}

void AgoraClr::NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats)
{
	if (onLocalVideoStats)
		onLocalVideoStats(gcnew ClrLocalVideoStats(stats));
}

void AgoraClr::NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	if (onRemoteVideoStats)
	{
		ClrRemoteVideoStats^ s = gcnew ClrRemoteVideoStats(stats);

		onRemoteVideoStats(s);
	}
}

void AgoraClr::NativeOnCameraReady()
{
	if (onCameraReady)
		onCameraReady();
}

void AgoraClr::NativeOnVideoStopped()
{
	if (onVideoStopped)
		onVideoStopped();
}

void AgoraClr::NativeOnConnectionLost()
{
	if (onConnectionLost)
		onConnectionLost();
}

void AgoraClr::NativeOnConnectionBanned()
{
	if (onConnectionBanned)
		onConnectionBanned();
}

void AgoraClr::NativeOnConnectionInterrupted()
{
	if (onConnectionInterrupted)
		onConnectionInterrupted();
}

void AgoraClr::NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length)
{
	if (onStreamMessage)
		onStreamMessage(uid, streamId, gcnew String(data));
}

void AgoraClr::NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached)
{
	if (onStreamMessageError)
		onStreamMessageError(uid, streamId, code, missed, cached);
}

void AgoraClr::NativeOnRequestChannelKey()
{
	if (onRequestChannelKey)
		onRequestChannelKey();
}

void AgoraClr::NativeOnRequestToken()
{
	if (onRequestToken)
		onRequestToken();
}

void AgoraClr::NativeOnLocalPublishFallbackToAudioOnly(bool FallbackOrRecover)
{
	if (onLocalPublishFallbackToAudioOnly)
		onLocalPublishFallbackToAudioOnly(FallbackOrRecover);
}

void AgoraClr::NativeOnRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover)
{
	if (onRemoteSubscribeFallbackToAudioOnly)
		onRemoteSubscribeFallbackToAudioOnly(uid, isFallbackOrRecover);
}

void AgoraClr::NativeOnRemoteAudioStats(const RemoteAudioStats& stats)
{
	if (onRemoteAudioStats)
		onRemoteAudioStats(gcnew ClrRemoteAudioStats(stats));
}

void AgoraClr::NativeOnRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteAudioTransportStats)
		onRemoteAudioTransportStats(uid, delay, lost, rxKBitRate);
}

void AgoraClr::NativeOnRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteVideoTransportStats)
		onRemoteVideoTransportStats(uid, delay, lost, rxKBitRate);
}

void AgoraClr::NativeOnAudioMixingBegin()
{
	if (onAudioMixingBegin)
		onAudioMixingBegin();
}

void AgoraClr::NativeOnAudioMixingEnd()
{
	if (onAudioMixingEnd)
		onAudioMixingEnd();
}

void AgoraClr::NativeOnAudioEffectFinished(int soundId)
{
	if (onAudioEffectFinished)
		onAudioEffectFinished(soundId);
}

void AgoraClr::NativeOnStreamInjectedStatus(const char* url, uid_t uid, int status)
{
	if (onStreamInjectedStatus)
		onStreamInjectedStatus(gcnew String(url), uid, status);
}

void AgoraClr::NativeOnMediaEngineLoadSuccess()
{
	if (onMediaEngineLoadSuccess)
		onMediaEngineLoadSuccess();
}

void AgoraClr::NativeOnMediaEngineStartCallSuccess()
{
	if (onMediaEngineStartCallSuccess)
		onMediaEngineStartCallSuccess();
}

bool AgoraClr::NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendAudioPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onSendAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onSendVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
{
	bool result = true;
	if (onRecordAudioFrame)
	{
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onRecordAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
{
	bool result = true;
	if (onPlaybackAudioFrame)
	{
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame& frame)
{
	bool result = true;
	if (onPlaybackAudioFrameBeforeMixing)
	{
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrameBeforeMixing(uid, clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
{
	bool result = true;
	if (onMixedAudioFrame)
	{
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onMixedAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame)
{
	bool result = true;
	if (onCaptureVideoFrame)
	{
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onCaptureVideoFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnPreEncodeVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame)
{
	bool result = true;
	if (onPreEncodeVideoFrame)
	{
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onPreEncodeVideoFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnGetSmoothRenderingEnabled()
{
	return IsSmoothRenderingEnabled;
}

bool AgoraClr::NativeOnRenderVideoFrame(uid_t uid, agora::media::IVideoFrameObserver::VideoFrame& frame)
{
	bool result = true;
	if (onRenderVideoFrame)
	{
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onRenderVideoFrame(uid, clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}
bool AgoraClr::NativeOnRenderVideoFrameEx(const char* channelId, uid_t uid, agora::media::IVideoFrameObserver::VideoFrame& frame)
{
	bool result = true;
	if (onRenderVideoFrameEx)
	{
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onRenderVideoFrameEx(gcnew String(channelId), uid, clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

IVideoFrameObserver::VIDEO_FRAME_TYPE AgoraClr::NativeOnGetVideoFormatPreference()
{
	return static_cast<IVideoFrameObserver::VIDEO_FRAME_TYPE>(VideoFormatPreference);
}

bool AgoraClr::NativeOnGetRotationApplied()
{
	return IsVideoRotationApplied;
}

bool AgoraClr::NativeOnGetMirrorApplied()
{
	return IsVideoMirrorApplied;
}

bool AgoraClr::NativeIsMultipleChannelVideoFrameWanted()
{
	return IsMultipleChannelVideoFrameWanted;
}

bool AgoraClr::NativeIsMultipleChannelAudioFrameWanted()
{
	return IsMultipleChannelAudioFrameWanted;
}

UINT AgoraClr::NativeObservedVideoFramePosition()
{
	return ObservedVideoFramePosition;
}
