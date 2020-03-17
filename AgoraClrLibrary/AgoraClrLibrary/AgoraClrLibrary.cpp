#include "stdafx.h"
#include "AgoraClrLibrary.h"
#include <iostream>

using namespace AgoraClrLibrary;
using namespace System;
using namespace System::Runtime::InteropServices;

AgoraClrLibrary::AgoraClr::AgoraClr()
{
	rtcEngine = nullptr;
	agoraMediaEngine = nullptr;

	gchs = gcnew List<GCHandle>();
	agoraEventHandler = new AgoraClrEventHandler;
	agoraPacketObserver = new AgoraClrPacketObserver;
	agoraRawObserver = new AgoraClrRawFrameObserver;
	agoraMetadataObserver = new AgoraClrMetadataObserver;

	VideoFormatPreference = VideoFrameType::FRAME_TYPE_YUV420;
	IsVideoRotationApplied = false;
	IsVideoMirrorApplied = false;

	MaxMetadataSize = 1024;

	initializeEventHandler();
	initializePacketObserver();
	initializeRawFrameObserver();
	initializeMetaObserver();
}

AgoraClrLibrary::AgoraClr::~AgoraClr()
{
	this->release();
	for each(GCHandle handle in gchs) handle.Free();
}

AgoraClrLibrary::AgoraClr::!AgoraClr()
{
}

int AgoraClrLibrary::AgoraClr::initialize(String^ vendorkey)
{
	if (rtcEngine)
		return 0;

	rtcEngine = createAgoraRtcEngine();
	if (rtcEngine == nullptr)
		return -1;

	agora::rtc::RtcEngineContext context;
	context.appId = strcopy(MarshalString(vendorkey));
	context.eventHandler = agoraEventHandler;
	int result = rtcEngine->initialize(context);
	if (result == 0)
	{
		//需要打开加密的话，请在封装层打开该接口。
// 		rtcEngine->registerPacketObserver(agoraPacketObserver);
		IMediaEngine* temp = nullptr;
		if (!rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE, reinterpret_cast<void**>(&temp)))
		{
			agoraMediaEngine = temp;
			agoraMediaEngine->registerAudioFrameObserver(agoraRawObserver);
			agoraMediaEngine->registerVideoFrameObserver(agoraRawObserver);
		}
		rtcEngine->registerMediaMetadataObserver(agoraMetadataObserver, IMetadataObserver::METADATA_TYPE::VIDEO_METADATA);
	}
	return result;
}

void AgoraClrLibrary::AgoraClr::release()
{
	if (rtcEngine)
	{
		if (agoraMediaEngine)
			agoraMediaEngine->release();

		delete agoraEventHandler;
		delete agoraPacketObserver;
		delete agoraRawObserver;

		rtcEngine->release();
		rtcEngine = nullptr;
	}
}

int AgoraClrLibrary::AgoraClr::enableVideo()
{
	return rtcEngine->enableVideo();
}

int AgoraClrLibrary::AgoraClr::disableVideo()
{
	return rtcEngine->disableVideo();
}

int AgoraClrLibrary::AgoraClr::enableAudio()
{
	return rtcEngine->enableAudio();
}

int AgoraClrLibrary::AgoraClr::disableAudio()
{
	return rtcEngine->disableAudio();
}

int AgoraClrLibrary::AgoraClr::startScreenCaptureByScreenRect(ClrRectangle^ screenRect, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params)
{
	return rtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, params);
}

int AgoraClrLibrary::AgoraClr::startScreenCaptureByWindowId(IntPtr windowId, ClrRectangle^ regionRect, ClrScreenCaptureParameters^ params)
{
	return rtcEngine->startScreenCaptureByWindowId(windowId.ToPointer(), regionRect, params);
}

int AgoraClrLibrary::AgoraClr::setScreenCaptureContentHint(EnumVideoContentHint hint)
{
	return rtcEngine->setScreenCaptureContentHint((VideoContentHint)hint);
}

int AgoraClrLibrary::AgoraClr::updateScreenCaptureParameters(ClrScreenCaptureParameters^ params)
{
	return rtcEngine->updateScreenCaptureParameters(params);
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceChanger(VoiceChangerPreset changer)
{
	return rtcEngine->setLocalVoiceChanger(static_cast<VOICE_CHANGER_PRESET>(changer));
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceReverbPreset(EnumAudioReverbPreset preset)
{
	return rtcEngine->setLocalVoiceReverbPreset(static_cast<AUDIO_REVERB_PRESET>(preset));
}

int AgoraClrLibrary::AgoraClr::enableSoundPositionIndication(bool enabled)
{
	return rtcEngine->enableSoundPositionIndication(enabled);
}

int AgoraClrLibrary::AgoraClr::setRemoteVoicePosition(uid_t uid, double pan, double gain)
{
	return rtcEngine->setRemoteVoicePosition(uid, pan, gain);
}

int AgoraClrLibrary::AgoraClr::startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return rtcEngine->startChannelMediaRelay(config);
}

int AgoraClrLibrary::AgoraClr::updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config)
{
	return rtcEngine->updateChannelMediaRelay(config);
}

int AgoraClrLibrary::AgoraClr::stopChannelMediaRelay()
{
	return rtcEngine->stopChannelMediaRelay();
}

int AgoraClrLibrary::AgoraClr::addVideoWatermark(String^ url, ClrWatermarkOptions^ options)
{
	return rtcEngine->addVideoWatermark(MarshalString(url).c_str(), options);
}

int AgoraClrLibrary::AgoraClr::clearVideoWatermarks()
{
	return rtcEngine->clearVideoWatermarks();
}

int AgoraClrLibrary::AgoraClr::setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setHighQualityAudioParameters(fullband, stereo, fullBitrate);
}

int AgoraClrLibrary::AgoraClr::startPreview()
{
	return rtcEngine->startPreview();
}

int AgoraClrLibrary::AgoraClr::stopPreview()
{
	return rtcEngine->stopPreview();
}

int AgoraClrLibrary::AgoraClr::enableWebSdkInteroperability(bool enabled)
{
	return rtcEngine->enableWebSdkInteroperability(enabled);
}

int AgoraClrLibrary::AgoraClr::joinChannel(String^ token, String^ channelName, String^ channelInfo, int uid)
{
	return rtcEngine->joinChannel(MarshalString(token).c_str(), MarshalString(channelName).c_str(), MarshalString(channelInfo).c_str(), uid);
}

int AgoraClrLibrary::AgoraClr::switchChannel(String^ token, String^ channelId)
{
	return rtcEngine->switchChannel(MarshalString(token).c_str(), MarshalString(channelId).c_str());
}

int AgoraClrLibrary::AgoraClr::leaveChannel()
{
	return rtcEngine->leaveChannel();
}

int AgoraClrLibrary::AgoraClr::startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect, int bitrate)
{
	return rtcEngine->startScreenCapture((HWND)windowId.ToPointer(), captureFreq, rect->toRaw(), bitrate);
}

int AgoraClrLibrary::AgoraClr::stopScreenCapture()
{
	return rtcEngine->stopScreenCapture();
}

int AgoraClrLibrary::AgoraClr::updateScreenCaptureRegion(ClrRectangle^ rect)
{
	return rtcEngine->updateScreenCaptureRegion(rect);
}

int AgoraClrLibrary::AgoraClr::renewToken(String^ token)
{
	return rtcEngine->renewToken(MarshalString(token).c_str());
}

int AgoraClrLibrary::AgoraClr::setEncryptionSecret(String^ key)
{
	return rtcEngine->setEncryptionSecret(MarshalString(key).c_str());
}

int AgoraClrLibrary::AgoraClr::setEncryptionMode(String^ mode)
{
	return rtcEngine->setEncryptionMode(MarshalString(mode).c_str());
}

int AgoraClrLibrary::AgoraClr::getCallId(String^% id)
{
	agora::util::AString callid;
	int result = rtcEngine->getCallId(callid);
	if (result == 0)
		id = gcnew String(callid.get()->c_str());
	else
		id = nullptr;

	return result;
}

int AgoraClrLibrary::AgoraClr::rate(String^ callid, int rating, String^ desc)
{
	return rtcEngine->rate(MarshalString(callid).c_str(), rating, MarshalString(desc).c_str());
}

int AgoraClrLibrary::AgoraClr::complain(String^ callid, String^ desc)
{
	return rtcEngine->complain(MarshalString(callid).c_str(), MarshalString(desc).c_str());
}

int AgoraClrLibrary::AgoraClr::startEchoTest(int intervalInSeconds)
{
	return rtcEngine->startEchoTest(intervalInSeconds);
}

int AgoraClrLibrary::AgoraClr::stopEchoTest()
{
	return rtcEngine->stopEchoTest();
}

int AgoraClrLibrary::AgoraClr::enableLastmileTest()
{
	return rtcEngine->enableLastmileTest();
}

int AgoraClrLibrary::AgoraClr::disableLastmileTest()
{
	return rtcEngine->disableLastmileTest();
}

int AgoraClrLibrary::AgoraClr::startLastmileProbeTest(ClrLastmileProbeConfig^ config)
{
	return rtcEngine->startLastmileProbeTest(config);
}

int AgoraClrLibrary::AgoraClr::stopLastmileProbeTest()
{
	return rtcEngine->stopLastmileProbeTest();
}

int AgoraClrLibrary::AgoraClr::setVideoProfile(VideoProfile profile, bool swapWidthAndHeight)
{
	return rtcEngine->setVideoProfile((agora::rtc::VIDEO_PROFILE_TYPE)profile, swapWidthAndHeight);
}

int AgoraClrLibrary::AgoraClr::setupLocalVideo(IntPtr view, int renderMode, int uid)
{
	return rtcEngine->setupLocalVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClrLibrary::AgoraClr::setupRemoteVideo(IntPtr view, int renderMode, int uid)
{
	return rtcEngine->setupRemoteVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClrLibrary::AgoraClr::enableDualStreamMode(bool enabled)
{
	return rtcEngine->enableDualStreamMode(enabled);
}

int AgoraClrLibrary::AgoraClr::setRemoteVideoStreamType(int uid, RemoteVideoStreamType type)
{
	return rtcEngine->setRemoteVideoStreamType(uid, static_cast<REMOTE_VIDEO_STREAM_TYPE>(type));
}

int AgoraClrLibrary::AgoraClr::setVideoQualityParameters(bool preferFrameRateOverImageQuality)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setVideoQualityParameters(preferFrameRateOverImageQuality);
}

int AgoraClrLibrary::AgoraClr::setChannelProfile(ChannelProfile profile)
{
	return rtcEngine->setChannelProfile((agora::rtc::CHANNEL_PROFILE_TYPE)profile);
}

int AgoraClrLibrary::AgoraClr::setClientRole(ClientRoleType role)
{
	return rtcEngine->setClientRole((CLIENT_ROLE_TYPE)role);
}

int AgoraClrLibrary::AgoraClr::createDataStream(int% id, bool reliable, bool ordered)
{
	int streamId;
	int result = rtcEngine->createDataStream(&streamId, reliable, ordered);
	id = streamId;
	return result;
}

int AgoraClrLibrary::AgoraClr::sendStreamMessage(int id, String^ data)
{
	std::string dataStr = MarshalString(data);
	return rtcEngine->sendStreamMessage(id, dataStr.c_str(), dataStr.length());
}

int AgoraClrLibrary::AgoraClr::setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	return rtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, static_cast<RAW_AUDIO_FRAME_OP_MODE_TYPE>(mode), samplesPerCall);
}

int AgoraClrLibrary::AgoraClr::setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	return rtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, static_cast<RAW_AUDIO_FRAME_OP_MODE_TYPE>(mode), samplesPerCall);
}

int AgoraClrLibrary::AgoraClr::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	return rtcEngine->setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int AgoraClrLibrary::AgoraClr::muteLocalAudioStream(bool mute)
{
	return rtcEngine->muteLocalAudioStream(mute);
}

int AgoraClrLibrary::AgoraClr::muteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->muteAllRemoteAudioStreams(mute);
}

int AgoraClrLibrary::AgoraClr::muteRemoteAudioStream(int uid, bool mute)
{
	return rtcEngine->muteRemoteAudioStream(uid, mute);
}

int AgoraClrLibrary::AgoraClr::muteLocalVideoStream(bool mute)
{
	return rtcEngine->muteLocalVideoStream(mute);
}

int AgoraClrLibrary::AgoraClr::enableLocalVideo(bool enabled)
{
	return rtcEngine->enableLocalVideo(enabled);
}

int AgoraClrLibrary::AgoraClr::muteAllRemoteVideoStreams(bool mute)
{
	return rtcEngine->muteAllRemoteVideoStreams(mute);
}

int AgoraClrLibrary::AgoraClr::muteRemoteVideoStream(int uid, bool mute)
{
	return rtcEngine->muteRemoteVideoStream(uid, mute);
}

int AgoraClrLibrary::AgoraClr::setPlaybackDeviceVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setPlaybackDeviceVolume(volume);
}

int AgoraClrLibrary::AgoraClr::setLocalRenderMode(RenderMode mode)
{
	return rtcEngine->setLocalRenderMode((agora::rtc::RENDER_MODE_TYPE)mode);
}

int AgoraClrLibrary::AgoraClr::setRemoteRenderMode(int uid, RenderMode mode)
{
	return rtcEngine->setRemoteRenderMode(uid, (agora::rtc::RENDER_MODE_TYPE)mode);
}

int AgoraClrLibrary::AgoraClr::enableAudioVolumeIndication(int interval, int smooth, bool report_vad)
{
	return rtcEngine->enableAudioVolumeIndication(interval, smooth, report_vad);
}

int AgoraClrLibrary::AgoraClr::startAudioRecording(String^ path, int sampleRate, AudioRecordingQualityType quality)
{
	return rtcEngine->startAudioRecording(MarshalString(path).c_str(), sampleRate, static_cast<AUDIO_RECORDING_QUALITY_TYPE>(quality));
}

int AgoraClrLibrary::AgoraClr::stopAudioRecording()
{
	return rtcEngine->stopAudioRecording();
}

int AgoraClrLibrary::AgoraClr::pauseAudioMixing()
{
	return rtcEngine->pauseAudioMixing();
}

int AgoraClrLibrary::AgoraClr::resumeAudioMixing()
{
	return rtcEngine->resumeAudioMixing();
}

int AgoraClrLibrary::AgoraClr::adjustAudioMixingVolume(int volume)
{
	return rtcEngine->adjustAudioMixingVolume(volume);
}

int AgoraClrLibrary::AgoraClr::getAudioMixingDuration()
{
	return rtcEngine->getAudioMixingDuration();
}

int AgoraClrLibrary::AgoraClr::getAudioMixingCurrentPosition()
{
	return rtcEngine->getAudioMixingCurrentPosition();
}

int AgoraClrLibrary::AgoraClr::setAudioMixingPosition(int pos)
{
	return rtcEngine->setAudioMixingPosition(pos);
}

int AgoraClrLibrary::AgoraClr::startAudioMixing(String^ path, bool loop, bool replace, int cycle)
{
	return rtcEngine->startAudioMixing(MarshalString(path).c_str(), loop, replace, cycle);
}

int AgoraClrLibrary::AgoraClr::stopAudioMixing()
{
	return rtcEngine->stopAudioMixing();
}

int AgoraClrLibrary::AgoraClr::setAudioProfile(AudioProfileType profile, AudioScenarioType scenario)
{
	return rtcEngine->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}

int AgoraClrLibrary::AgoraClr::setLogFile(String^ path)
{
	return rtcEngine->setLogFile(MarshalString(path).c_str());
}

int AgoraClrLibrary::AgoraClr::setLogFilter(unsigned int filter)
{
	return rtcEngine->setLogFilter(filter);
}

int AgoraClrLibrary::AgoraClr::setLogFileSize(unsigned int size)
{
	return rtcEngine->setLogFileSize(size);
}

int AgoraClrLibrary::AgoraClr::adjustRecordingSignalVolume(int volume)
{
	return rtcEngine->adjustRecordingSignalVolume(volume);
}

int AgoraClrLibrary::AgoraClr::adjustPlaybackSignalVolume(int volume)
{
	return rtcEngine->adjustPlaybackSignalVolume(volume);
}

int AgoraClrLibrary::AgoraClr::enableLocalAudio(bool enabled)
{
	return rtcEngine->enableLocalAudio(enabled);
}

int AgoraClrLibrary::AgoraClr::setLocalVoicePitch(double pitch)
{
	return rtcEngine->setLocalVoicePitch(pitch);
}

int AgoraClrLibrary::AgoraClr::setExternalAudioSource(bool enabled, int sampleRate, int channels)
{
	return rtcEngine->setExternalAudioSource(enabled, sampleRate, channels);
}

int AgoraClrLibrary::AgoraClr::pushAudioFrame(ClrAudioFrame^ frame)
{
	return agoraMediaEngine ? agoraMediaEngine->pushAudioFrame(frame) : -1;
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain)
{
	return rtcEngine->setLocalVoiceEqualization(static_cast<AUDIO_EQUALIZATION_BAND_FREQUENCY>(freq), bandGain);
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceReverb(AudioReverbType type, int value)
{
	return rtcEngine->setLocalVoiceReverb(static_cast<AUDIO_REVERB_TYPE>(type), value);
}

int AgoraClrLibrary::AgoraClr::setLocalVideoMirrorMode(VideoMirrorModeType mode)
{
	return rtcEngine->setLocalVideoMirrorMode(static_cast<VIDEO_MIRROR_MODE_TYPE>(mode));
}

int AgoraClrLibrary::AgoraClr::setCameraCapturerConfiguration(ClrCameraCaptureConfiguration^ config)
{
	return rtcEngine->setCameraCapturerConfiguration(config);
}

String^ AgoraClrLibrary::AgoraClr::getVersion(int% build)
{
	int version;
	String^ result = gcnew String(rtcEngine->getVersion(&version));
	build = version;
	return result;
}

int AgoraClrLibrary::AgoraClr::enableLoopbackRecording(bool enabled, String^ name)
{
	return rtcEngine->enableLoopbackRecording(enabled, MarshalString(name).c_str());
}

int AgoraClrLibrary::AgoraClr::addPublishStreamUrl(String^ url, bool transcodingEnabled)
{
	return rtcEngine->addPublishStreamUrl(MarshalString(url).c_str(), transcodingEnabled);
}

int AgoraClrLibrary::AgoraClr::removePublishStreamUrl(String^ url)
{
	return rtcEngine->removePublishStreamUrl(MarshalString(url).c_str());
}

int AgoraClrLibrary::AgoraClr::setLiveTranscoding(ClrLiveTranscoding^ transcoding)
{
	return rtcEngine->setLiveTranscoding(transcoding);
}

int AgoraClrLibrary::AgoraClr::addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config)
{
	return rtcEngine->addInjectStreamUrl(MarshalString(url).c_str(), config);
}

int AgoraClrLibrary::AgoraClr::removeInjectStreamUrl(String^ url)
{
	return rtcEngine->removeInjectStreamUrl(MarshalString(url).c_str());
}

int AgoraClrLibrary::AgoraClr::getEffectsVolume()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getEffectsVolume();
}

int AgoraClrLibrary::AgoraClr::setEffectsVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setEffectsVolume(volume);
}

int AgoraClrLibrary::AgoraClr::setVolumeOfEffect(int soundId, int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setVolumeOfEffect(soundId, volume);
}

int AgoraClrLibrary::AgoraClr::playEffect(int soundId, String^ file, int loopCount, double pitch, double pan, int gain, bool publish)
{
	RtcEngineParameters params(*rtcEngine);
	return params.playEffect(soundId, MarshalString(file).c_str(), loopCount, pitch, pan, gain, publish);
}

int AgoraClrLibrary::AgoraClr::stopEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopEffect(soundId);
}

int AgoraClrLibrary::AgoraClr::stopAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopAllEffects();
}

int AgoraClrLibrary::AgoraClr::preloadEffect(int soundId, String^ file)
{
	return rtcEngine->preloadEffect(soundId, MarshalString(file).c_str());
}

int AgoraClrLibrary::AgoraClr::unloadEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.unloadEffect(soundId);
}

int AgoraClrLibrary::AgoraClr::pauseEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseEffect(soundId);
}

int AgoraClrLibrary::AgoraClr::pauseAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseAllEffects();
}

int AgoraClrLibrary::AgoraClr::resumeEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeEffect(soundId);
}

int AgoraClrLibrary::AgoraClr::resumeAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeAllEffects();
}

AgoraClrLibrary::ConnectionStateType AgoraClrLibrary::AgoraClr::getConnectionState()
{
	return (ConnectionStateType)rtcEngine->getConnectionState();
}

int AgoraClrLibrary::AgoraClr::setDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
}

int AgoraClrLibrary::AgoraClr::setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config)
{
	return rtcEngine->setVideoEncoderConfiguration(config);
}

int AgoraClrLibrary::AgoraClr::setDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
}

int AgoraClrLibrary::AgoraClr::adjustAudioMixingPlayoutVolume(int volume)
{
	return rtcEngine->adjustAudioMixingPlayoutVolume(volume);
}

int AgoraClrLibrary::AgoraClr::adjustAudioMixingPublishVolume(int volume)
{
	return rtcEngine->adjustAudioMixingPublishVolume(volume);
}

int AgoraClrLibrary::AgoraClr::getAudioMixingPlayoutVolume()
{
	return rtcEngine->getAudioMixingPlayoutVolume();
}

int AgoraClrLibrary::AgoraClr::getAudioMixingPublishVolume()
{
	return rtcEngine->getAudioMixingPublishVolume();
}

int AgoraClrLibrary::AgoraClr::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	return rtcEngine->setExternalAudioSink(enabled, sampleRate, channels);
}

int AgoraClrLibrary::AgoraClr::pullAudioFrame(ClrAudioFrame^ frame)
{
	return agoraMediaEngine ? agoraMediaEngine->pullAudioFrame(frame) : -1;
}

int AgoraClrLibrary::AgoraClr::setExternalVideoSource(bool enabled, bool useTexture)
{
	return agoraMediaEngine ? agoraMediaEngine->setExternalVideoSource(enabled, useTexture) : -1;
}

int AgoraClrLibrary::AgoraClr::pushVideoFrame(ClrExternalVideoFrame^ frame)
{
	return agoraMediaEngine ? agoraMediaEngine->pushVideoFrame(frame) : -1;
}

int AgoraClrLibrary::AgoraClr::setLocalPublishFallbackOption(StreamFallbackOptions option)
{
	return rtcEngine->setLocalPublishFallbackOption(static_cast<STREAM_FALLBACK_OPTIONS>(option));
}

int AgoraClrLibrary::AgoraClr::setRemoteSubscribeFallbackOption(StreamFallbackOptions option)
{
	return rtcEngine->setRemoteSubscribeFallbackOption(static_cast<STREAM_FALLBACK_OPTIONS>(option));
}

int AgoraClrLibrary::AgoraClr::setRemoteUserPriority(uid_t uid, PriorityType priority)
{
	return rtcEngine->setRemoteUserPriority(uid, static_cast<PRIORITY_TYPE>(priority));
}

int AgoraClrLibrary::AgoraClr::setRemoteDefaultVideoStreamType(RemoteVideoStreamType type)
{
	return rtcEngine->setRemoteDefaultVideoStreamType(static_cast<REMOTE_VIDEO_STREAM_TYPE>(type));
}

String^ AgoraClrLibrary::AgoraClr::getErrorDescription(int code)
{
	return gcnew String(rtcEngine->getErrorDescription(code));
}

void* AgoraClrLibrary::AgoraClr::regEvent(Object^ obj)
{
	gchs->Add(GCHandle::Alloc(obj));
	return Marshal::GetFunctionPointerForDelegate(obj).ToPointer();
}

void AgoraClrLibrary::AgoraClr::initializeEventHandler()
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

	agoraEventHandler->onRemoteAudioMixingEndEvent = reinterpret_cast<stdCall>(regEvent(gcnew Action(this, &AgoraClr::NativeOnRemoteAudioMixingEnd)));
	agoraEventHandler->onRtmpStreamingStateChangedEvent = reinterpret_cast<PFOnRtmpStreamingStateChanged>(regEvent(gcnew NativeOnRtmpStreamingStateChangedDelegate(this, &AgoraClr::NativeOnRtmpStreamingStateChanged)));
	agoraEventHandler->onChannelMediaRelayStateChangedEvent = reinterpret_cast<PFOnChannelMediaRelayStateChanged>(regEvent(gcnew NativeOnChannelMediaRelayStateChangedDelegate(this, &AgoraClr::NativeOnChannelMediaRelayStateChanged)));
	agoraEventHandler->onChannelMediaRelayEventEvnet = reinterpret_cast<PFOnChannelMediaRelayEvent>(regEvent(gcnew NativeOnChannelMediaRelayEventDelegate(this, &AgoraClr::NativeOnChannelMediaRelayEvent)));
	agoraEventHandler->onLastmileProbeResultEvent = reinterpret_cast<PFOnLastmileProbeResult>(regEvent(gcnew NativeOnLastmileProbeResultDelegate(this, &AgoraClr::NativeOnLastmileProbeResult)));
}

void AgoraClrLibrary::AgoraClr::initializePacketObserver()
{
	agoraPacketObserver->onSendAudioPacketEvent = PFOnSendAudioPacket(regEvent(gcnew NativeOnSendAudioPacketDelegate(this, &AgoraClr::NativeOnSendAudioPacket)));
	agoraPacketObserver->onSendVideoPacketEvent = PFOnSendVideoPacket(regEvent(gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClr::NativeOnSendVideoPacket)));
	agoraPacketObserver->onReceiveVideoPacketEvent = PFOnReceiveVideoPacket(regEvent(gcnew NativeOnSendVideoPacketDelegate(this, &AgoraClr::NativeOnReceiveVideoPacket)));
	agoraPacketObserver->onReceiveAudioPacketEvent = PFOnReceiveAudioPacket(regEvent(gcnew NativeOnReceiveAudioPacketDelegate(this, &AgoraClr::NativeOnReceiveAudioPacket)));
}

void AgoraClrLibrary::AgoraClr::initializeRawFrameObserver()
{
	agoraRawObserver->onRecordAudioFrameEvent = PFOnRecordAudioFrame(regEvent(gcnew NativeOnRecordAudioFrameDelegate(this, &AgoraClr::NativeOnRecordAudioFrame)));
	agoraRawObserver->onPlaybackAudioFrameEvent = PFOnPlaybackAudioFrame(regEvent(gcnew NativeOnPlaybackAudioFrameDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrame)));
	agoraRawObserver->onPlaybackAudioFrameBeforeMixingEvent = PFOnPlaybackAudioFrameBeforeMixing(regEvent(gcnew NativeOnPlaybackAudioFrameBeforeMixingDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing)));
	agoraRawObserver->onMixedAudioFrameEvent = PFOnMixedAudioFrame(regEvent(gcnew NativeOnMixedAudioFrameDelegate(this, &AgoraClr::NativeOnMixedAudioFrame)));

	agoraRawObserver->onCaptureVideoFrameEvent = PFOnCaptureVideoFrame(regEvent(gcnew NativeOnCaptureVideoFrameDelegate(this, &AgoraClr::NativeOnCaptureVideoFrame)));
	agoraRawObserver->onRenderVideoFrameEvent = PFOnRenderVideoFrame(regEvent(gcnew NativeOnRenderVideoFrameDelegate(this, &AgoraClr::NativeOnRenderVideoFrame)));
	agoraRawObserver->onGetVideoFormatePreferenceEvent = reinterpret_cast<PFOnGetVideoFormatePreference>(regEvent(gcnew NativeOnGetVideoFormatePreferenceDelegate(this, &AgoraClr::NativeOnGetVideoFormatPreference)));
	agoraRawObserver->onGetRotationAppliedEvent = reinterpret_cast<PFOnGetRotationApplied>(regEvent(gcnew NativeOnGetRotationAppliedDelegate(this, &AgoraClr::NativeOnGetRotationApplied)));
	agoraRawObserver->onGetMirrorAppliedEvent = reinterpret_cast<PFOnGetMirrorApplied>(regEvent(gcnew NativeOnGetMirrorAppliedDelegate(this, &AgoraClr::NativeOnGetMirrorApplied)));
}

void AgoraClrLibrary::AgoraClr::initializeMetaObserver()
{
	agoraMetadataObserver->onGetMaxMetadataSizeEvent = reinterpret_cast<PFOnGetMaxMetadataSize>(regEvent(gcnew NativeOnGetMaxMetadataSizeDelegate(this, &AgoraClr::NativeGetMaxMetadataSize)));
	agoraMetadataObserver->onReadyToSendMetadataEvent = reinterpret_cast<PFOnReadyToSendMetadata>(regEvent(gcnew NativeOnReadyToSendMetadataDelegate(this, &AgoraClr::NativeOnReadyToSendMetadata)));
	agoraMetadataObserver->onMetadataReceivedEvent = reinterpret_cast<PFOnMetadataReceived>(regEvent(gcnew NativeOnMetadataReceivedDelegate(this, &AgoraClr::NativeOnMetadataReceived)));
}

AgoraClrLibrary::AgoraClrAudioDeviceManager^ AgoraClrLibrary::AgoraClr::getAudioDeviceManager()
{
	return gcnew AgoraClrAudioDeviceManager(this->rtcEngine);
}

AgoraClrLibrary::AgoraClrVideoDeviceManager^ AgoraClrLibrary::AgoraClr::getVideoDeviceManager()
{
	return gcnew AgoraClrVideoDeviceManager(this->rtcEngine);
}

void AgoraClrLibrary::AgoraClr::NativeOnJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccess)
	{
		onJoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccess)
	{
		onRejoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnWarning(int warn, const char* msg)
{
	if (onWarning)
	{
		onWarning(warn, gcnew String(msg));
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnError(int err, const char* msg)
{
	if (onError)
		onError(err, gcnew String(msg));
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	if (onAudioQuality)
		onAudioQuality(uid, quality, delay, lost);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	if (onAudioVolumeIndication)
	{
		List<ClrAudioVolumeInfo^>^ list = gcnew List<ClrAudioVolumeInfo^>();
		for (unsigned int i = 0; i < speakerNumber; i++)
			list->Add(gcnew ClrAudioVolumeInfo(speakers[i]));

		onAudioVolumeIndication(list, totalVolume);
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnLeaveChannel(const agora::rtc::RtcStats& stats)
{
	if (onLeaveChannel)
		onLeaveChannel(gcnew RtcStats(stats));
}

void AgoraClrLibrary::AgoraClr::NativeOnRtcStats(const agora::rtc::RtcStats& stats)
{
	if (onRtcStats)
	{
		RtcStats^ rtc = gcnew RtcStats(stats);
		onRtcStats(rtc);
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onAudioDeviceStateChanged)
		onAudioDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClrLibrary::AgoraClr::NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onVideoDeviceStateChanged)
		onVideoDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingFinished()
{
	if (onAudioMixingFinished)
		onAudioMixingFinished();
}

void AgoraClrLibrary::AgoraClr::NativeOnActiveSpeaker(uid_t uid)
{
	if (onActiveSpeaker)
		onActiveSpeaker(uid);
}

void AgoraClrLibrary::AgoraClr::NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	if (onClientRoleChanged)
		onClientRoleChanged((ClientRoleType)oldRole, (ClientRoleType)newRole);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChanged)
		onAudioDeviceVolumeChanged((MediaDeviceType)deviceType, volume, muted);
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamUnpublished(const char* url)
{
	if (onStreamUnpublished)
		onStreamUnpublished(gcnew String(url));
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamPublished(const char* url, int error)
{
	if (onStreamPublished)
		onStreamPublished(gcnew String(url), error);
}

void AgoraClrLibrary::AgoraClr::NativeOnTranscodingUpdated()
{
	if (onTranscodingUpdated)
		onTranscodingUpdated();
}

void AgoraClrLibrary::AgoraClr::NativeOnConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (onConnectionStateChanged)
		onConnectionStateChanged((ConnectionStateType)state, (ConnectionChangedReasonType)reason);
}

void AgoraClrLibrary::AgoraClr::NativeOnTokenPrivilegeWillExpire(const char* token)
{
	if (onTokenPrivilegeWillExpire)
		onTokenPrivilegeWillExpire(gcnew String(token));
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstLocalAudioFrame(int elapsed)
{
	if (onFirstLocalAudioFrame)
		onFirstLocalAudioFrame(elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstRemoteAudioFrame(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioFrame)
		onFirstRemoteAudioFrame(uid, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnUserEnableLocalVideo(uid_t uid, bool enabled)
{
	if (onUserEnableLocalVideo)
		onUserEnableLocalVideo(uid, enabled);
}

void AgoraClrLibrary::AgoraClr::NativeOnVideoSizeChanged(uid_t uid, int width, int height, int rotation)
{
	if (onVideoSizeChanged)
		onVideoSizeChanged(uid, width, height, rotation);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	if (onRemoteVideoStateChanged)
		onRemoteVideoStateChanged(uid, (RemoteVideoState)state, (RemoteVideoStateReason)reason, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnLastmileQuality(int quality)
{
	if (onLastmileQuality)
		onLastmileQuality(quality);
}

void AgoraClrLibrary::AgoraClr::NativeOnNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQuality)
		onNetworkQuality(uid, txQuality, rxQuality);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstLocalVideoFrame(int width, int height, int elapsed)
{
	if (onFirstLocalVideoFrame)
		onFirstLocalVideoFrame(width, height, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
	if (onFirstRemoteVideoDecoded)
		onFirstRemoteVideoDecoded(uid, width, height, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{
	if (onFirstRemoteVideoFrame)
		onFirstRemoteVideoFrame(uid, width, height, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnUserJoined(uid_t uid, int elapsed)
{
	if (onUserJoined)
		onUserJoined(uid, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	if (onUserOffline)
		onUserOffline(uid, (UserOfflineType)reason);
}

void AgoraClrLibrary::AgoraClr::NativeOnNetworkTypeChanged(NETWORK_TYPE type)
{
	if (onNetworkTypeChanged)
		onNetworkTypeChanged((NetworkType)type);
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	if (onLocalAudioStateChanged)
		onLocalAudioStateChanged((LocalAudioStreamState)state, (LocalAudioStreamError)error);
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
{
	if (onLocalVideoStateChanged)
		onLocalVideoStateChanged((LocalVideoStreamState)state, (LocalVideoStreamError)error);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChanged)
		onRemoteAudioStateChanged(uid, (RemoteAudioState)state, (RemoteAudioStateReason)reason, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioDecoded)
		onFirstRemoteAudioDecoded(uid, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalAudioStats(const LocalAudioStats& stats)
{
	if (onLocalAudioStats)
		onLocalAudioStats(gcnew ClrLocalAudioStats(stats));
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error)
{
	if (onAudioMixingStateChanged)
		onAudioMixingStateChanged(static_cast<AudioMixingStateType>(state), static_cast<AudioMixingErrorType>(error));
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioMixingBegin()
{
	if (onRemoteAudioMixingBegin)
		onRemoteAudioMixingBegin();
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioMixingEnd()
{
	if (onRemoteAudioMixingEnd)
		onRemoteAudioMixingEnd();
}

void AgoraClrLibrary::AgoraClr::NativeOnRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error)
{
	if (onRtmpStreamingStateChanged)
		onRtmpStreamingStateChanged(gcnew String(url), static_cast<RtmpStreamPublishState>(state), static_cast<RtmpStreamPublishError>(error));
}

void AgoraClrLibrary::AgoraClr::NativeOnChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error)
{
	if (onChannelMediaRelayStateChanged)
		onChannelMediaRelayStateChanged(static_cast<ChannelMediaRelayState>(state), static_cast<ChannelMediaRelayError>(error));
}

void AgoraClrLibrary::AgoraClr::NativeOnChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event)
{
	if (onChannelMediaRelayEvent)
		onChannelMediaRelayEvent(static_cast<ChannelMediaRelayEvent>(event));
}

void AgoraClrLibrary::AgoraClr::NativeOnLastmileProbeResult(const LastmileProbeResult& result)
{
	if (onLastmileProbeResult)
		onLastmileProbeResult(gcnew ClrLastmileProbeResult(result));
}

int AgoraClrLibrary::AgoraClr::NativeGetMaxMetadataSize()
{
	return MaxMetadataSize;
}

bool AgoraClrLibrary::AgoraClr::NativeOnReadyToSendMetadata(IMetadataObserver::Metadata& metadata)
{
	return onReadyToSendMetadata ? onReadyToSendMetadata(gcnew ClrMetadata(metadata)) : false;
}

void AgoraClrLibrary::AgoraClr::NativeOnMetadataReceived(const IMetadataObserver::Metadata& metadata)
{
	if (onMetadataReceived)
		onMetadataReceived(gcnew ClrMetadata(metadata));
}

void AgoraClrLibrary::AgoraClr::NativeOnUserMuteAudio(uid_t uid, bool muted)
{
	if (onUserMuteAudio)
		onUserMuteAudio(uid, muted);
}

void AgoraClrLibrary::AgoraClr::NativeOnUserMuteVideo(uid_t uid, bool muted)
{
	if (onUserMuteVideo)
		onUserMuteVideo(uid, muted);
}

void AgoraClrLibrary::AgoraClr::NativeOnUserEnableVideo(uid_t uid, bool enabled)
{
	if (onUserEnableVideo)
		onUserEnableVideo(uid, enabled);
}

void AgoraClrLibrary::AgoraClr::NativeOnApiCallExecuted(int err, const char* api, const char* result)
{
	if (onApiCallExecuted)
		onApiCallExecuted(err, gcnew String(api), gcnew String(result));
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats)
{
	if (onLocalVideoStats)
		onLocalVideoStats(gcnew ClrLocalVideoStats(stats));
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	if (onRemoteVideoStats)
	{
		RemoteVideoStats^ s = gcnew RemoteVideoStats(stats);

		onRemoteVideoStats(s);
	}
}

void AgoraClrLibrary::AgoraClr::NativeOnCameraReady()
{
	if (onCameraReady)
		onCameraReady();
}

void AgoraClrLibrary::AgoraClr::NativeOnVideoStopped()
{
	if (onVideoStopped)
		onVideoStopped();
}

void AgoraClrLibrary::AgoraClr::NativeOnConnectionLost()
{
	if (onConnectionLost)
		onConnectionLost();
}

void AgoraClrLibrary::AgoraClr::NativeOnConnectionBanned()
{
	if (onConnectionBanned)
		onConnectionBanned();
}

void AgoraClrLibrary::AgoraClr::NativeOnConnectionInterrupted()
{
	if (onConnectionInterrupted)
		onConnectionInterrupted();
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length)
{
	if (onStreamMessage)
		onStreamMessage(uid, streamId, gcnew String(data));
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached)
{
	if (onStreamMessageError)
		onStreamMessageError(uid, streamId, code, missed, cached);
}

void AgoraClrLibrary::AgoraClr::NativeOnRequestChannelKey()
{
	if (onRequestChannelKey)
		onRequestChannelKey();
}

void AgoraClrLibrary::AgoraClr::NativeOnRequestToken()
{
	if (onRequestToken)
		onRequestToken();
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalPublishFallbackToAudioOnly(bool FallbackOrRecover)
{
	if (onLocalPublishFallbackToAudioOnly)
		onLocalPublishFallbackToAudioOnly(FallbackOrRecover);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover)
{
	if (onRemoteSubscribeFallbackToAudioOnly)
		onRemoteSubscribeFallbackToAudioOnly(uid, isFallbackOrRecover);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioStats(const RemoteAudioStats& stats)
{
	if (onRemoteAudioStats)
		onRemoteAudioStats(gcnew ClrRemoteAudioStats(stats));
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteAudioTransportStats)
		onRemoteAudioTransportStats(uid, delay, lost, rxKBitRate);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	if (onRemoteVideoTransportStats)
		onRemoteVideoTransportStats(uid, delay, lost, rxKBitRate);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingBegin()
{
	if (onAudioMixingBegin)
		onAudioMixingBegin();
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingEnd()
{
	if (onAudioMixingEnd)
		onAudioMixingEnd();
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioEffectFinished(int soundId)
{
	if (onAudioEffectFinished)
		onAudioEffectFinished(soundId);
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamInjectedStatus(const char* url, uid_t uid, int status)
{
	if (onStreamInjectedStatus)
		onStreamInjectedStatus(gcnew String(url), uid, status);
}

void AgoraClrLibrary::AgoraClr::NativeOnMediaEngineLoadSuccess()
{
	if (onMediaEngineLoadSuccess)
		onMediaEngineLoadSuccess();
}

void AgoraClrLibrary::AgoraClr::NativeOnMediaEngineStartCallSuccess()
{
	if (onMediaEngineStartCallSuccess)
		onMediaEngineStartCallSuccess();
}

bool AgoraClrLibrary::AgoraClr::NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
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

bool AgoraClrLibrary::AgoraClr::NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
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

bool AgoraClrLibrary::AgoraClr::NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
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

bool AgoraClrLibrary::AgoraClr::NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
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

bool AgoraClrLibrary::AgoraClr::NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
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

bool AgoraClrLibrary::AgoraClr::NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
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

bool AgoraClrLibrary::AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame& frame)
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

bool AgoraClrLibrary::AgoraClr::NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame)
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

bool AgoraClrLibrary::AgoraClr::NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame)
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

bool AgoraClrLibrary::AgoraClr::NativeOnRenderVideoFrame(uid_t uid, agora::media::IVideoFrameObserver::VideoFrame& frame)
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

IVideoFrameObserver::VIDEO_FRAME_TYPE AgoraClrLibrary::AgoraClr::NativeOnGetVideoFormatPreference()
{
	return static_cast<IVideoFrameObserver::VIDEO_FRAME_TYPE>(VideoFormatPreference);
}

bool AgoraClrLibrary::AgoraClr::NativeOnGetRotationApplied()
{
	return IsVideoRotationApplied;
}

bool AgoraClrLibrary::AgoraClr::NativeOnGetMirrorApplied()
{
	return IsVideoMirrorApplied;
}
