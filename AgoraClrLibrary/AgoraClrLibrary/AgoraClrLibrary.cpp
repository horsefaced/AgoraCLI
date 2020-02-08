// 这是主 DLL 文件。

#include "AgoraClrLibrary.h"
#include "AgoraClrEventHandler.h"
#include "stdafx.h"
#include <iostream>

using namespace AgoraClrLibrary;
using namespace System;
using namespace System::Runtime::InteropServices;

AgoraClr::AgoraClr() : rtcEngine(nullptr) : gchs(gcnew List<GCHandle>()) : agoraEventHandler(new AgoraClrEventHandler()) : agoraPacketObserver(new AgoraClrPacketObserver()) : agoraRawObserver(new AgoraClrRawFrameObserver)
{
	initializeEventHandler();
	initializePacketObserver();
	initializeRawFrameObserver();
}

AgoraClr::~AgoraClr()
{
	this->release();
	for (GCHandle handle : gchs) handle.Free();
}

AgoraClr::!AgoraClr()
{
}

int AgoraClr::initialize(String ^ vendorkey)
{
	if (rtcEngine)
		return 0;

	rtcEngine = createAgoraRtcEngine();
	if (rtcEngine == nullptr)
		return -1;

	std::string middlestr = MarshalString(vendorkey);
	
	agora::rtc::RtcEngineContext context{.appId = middlestr.c_str, .eventHandler = agoraEventHandler};

	int result = rtcEngine->initialize(context);
	if (result == 0)
	{
		rtcEngine->registerPacketObserver(agoraPacketObserver);
		agoraMediaEngine = nullptr;
		if (!rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE, reinterpret_cast<void **>(&agoraMediaEngine)))
		{
			agoraMediaEngine->registerAudioFrameObserver(agoraRawObserver);
			agoraMediaEngine->registerVideoFrameObserver(agoraRawObserver);
		}
	}
	return result;
}

void AgoraClr::release()
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

int AgoraClr::setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setHighQualityAudioParameters(fullband, stereo, fullBitrate);
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

int AgoraClr::joinChannel(String ^ token, String ^ channelName, String ^ channelInfo, int uid)
{
	return rtcEngine->joinChannel(MarshalString(token).c_str(), MarshalString(channelName).c_str(), MarshalString(channelInfo).c_str(), uid);
}

int AgoraClr::switchChannel(String^ token, String^ channelId) {
	return rtcEngine->switchChannel(MarshalString(token).c_str(), MarshalString(channelId).c_str());
}

int AgoraClr::leaveChannel()
{
	return rtcEngine->leaveChannel();
}

int AgoraClr::startScreenCapture(IntPtr windowId, int captureFreq, ClrRect ^ rect, int bitrate)
{
	return rtcEngine->startScreenCapture((HWND)windowId.ToPointer(), captureFreq, rect->toRaw(), bitrate);
}

int AgoraClr::stopScreenCapture()
{
	return rtcEngine->stopScreenCapture();
}

int AgoraClr::updateScreenCaptureRegion(ClrRect ^ rect)
{
	return rtcEngine->updateScreenCaptureRegion(rect->toRaw());
}

int AgoraClr::renewToken(String ^ token)
{
	return rtcEngine->renewToken(MarshalString(token).c_str());
}

int AgoraClr::setEncryptionSecret(String ^ key)
{
	std::string screte = MarshalString(key);
	return rtcEngine->setEncryptionSecret(screte.c_str());
}

int AgoraClr::setEncryptionMode(String ^ mode)
{
	return rtcEngine->setEncryptionMode(MarshalString(mode).c_str());
}

int AgoraClr::getCallId(String ^ % id)
{
	agora::util::AString callid;
	int result = rtcEngine->getCallId(callid);
	if (result == 0)
		id = gcnew String(callid.get()->c_str());
	else
		id = nullptr;

	return result;
}

int AgoraClr::rate(String ^ callid, int rating, String ^ desc)
{
	return rtcEngine->rate(MarshalString(callid).c_str(), rating, MarshalString(desc).c_str());
}

int AgoraClr::complain(String ^ callid, String ^ desc)
{
	return rtcEngine->complain(MarshalString(callid).c_str(), MarshalString(desc).c_str());
}

int AgoraClr::startEchoTest()
{
	return rtcEngine->startEchoTest();
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

int AgoraClr::setVideoProfile(VideoProfile profile, bool swapWidthAndHeight)
{
	return rtcEngine->setVideoProfile((agora::rtc::VIDEO_PROFILE_TYPE)profile, swapWidthAndHeight);
}

int AgoraClr::setupLocalVideo(IntPtr view, int renderMode, int uid)
{
	return rtcEngine->setupLocalVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClr::setupRemoteVideo(IntPtr view, int renderMode, int uid)
{
	return rtcEngine->setupRemoteVideo(agora::rtc::VideoCanvas(view.ToPointer(), renderMode, uid));
}

int AgoraClr::enableDualStreamMode(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableDualStreamMode(enabled);
}

int AgoraClr::setRemoteVideoStreamType(int uid, RemoteVideoStreamType type)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRemoteVideoStreamType(uid, (REMOTE_VIDEO_STREAM_TYPE)type);
}

int AgoraClr::setVideoQualityParameters(bool preferFrameRateOverImageQuality)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setVideoQualityParameters(preferFrameRateOverImageQuality);
}

int AgoraClr::setVideoCompositingLayout(ClrVideoCompositingLayout ^ sei)
{
	if (sei == nullptr)
		return rtcEngine->setVideoCompositingLayout(VideoCompositingLayout());
	else
		return rtcEngine->setVideoCompositingLayout(*sei->toRaw());
}

int AgoraClr::clearVideoCompositingLayout()
{
	return rtcEngine->clearVideoCompositingLayout();
}

int AgoraClr::configPublisher(ClrPublisherConfiguration ^ config)
{
#if defined(_WIN32)
	return rtcEngine->configPublisher(*config->toRaw());
#else
	return 0;
#endif
}

int AgoraClr::setChannelProfile(ChannelProfile profile)
{
	return rtcEngine->setChannelProfile((agora::rtc::CHANNEL_PROFILE_TYPE)profile);
}

int AgoraClr::setClientRole(ClientRoleType role)
{
	return rtcEngine->setClientRole((CLIENT_ROLE_TYPE)role);
}

int AgoraClr::createDataStream(int % id)
{
	int streamId;
	int result = rtcEngine->createDataStream(&streamId, true, true);
	id = streamId;
	return result;
}

int AgoraClr::sendStreamMessage(int id, String ^ data)
{
	std::string dataStr = MarshalString(data);
	return rtcEngine->sendStreamMessage(id, dataStr.c_str(), dataStr.length());
}

int AgoraClr::setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRecordingAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int AgoraClr::setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setPlaybackAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int AgoraClr::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int AgoraClr::muteLocalAudioStream(bool mute)
{
	return rtcEngine->muteLocalAudioStream(mute);
}

int AgoraClr::muteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->muteAllRemoteAudioStreams(mute);
}

int AgoraClr::muteRemoteAudioStream(int uid, bool mute)
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

int AgoraClr::muteRemoteVideoStream(int uid, bool mute)
{
	return rtcEngine->muteRemoteVideoStream(uid, mute);
}

int AgoraClr::setPlaybackDeviceVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setPlaybackDeviceVolume(volume);
}

int AgoraClr::setLocalRenderMode(RenderMode mode)
{
	return rtcEngine->setLocalRenderMode((agora::rtc::RENDER_MODE_TYPE)mode);
}

int AgoraClr::setRemoteRenderMode(int uid, RenderMode mode)
{
	return rtcEngine->setRemoteRenderMode(uid, (agora::rtc::RENDER_MODE_TYPE)mode);
}

int AgoraClr::enableAudioVolumeIndication(int interval, int smooth)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableAudioVolumeIndication(interval, smooth);
}

int AgoraClr::startAudioRecording(String ^ path, AudioRecordingQualityType quality)
{
	agora::rtc::RtcEngineParameters param(*rtcEngine);
	return param.startAudioRecording(MarshalString(path).c_str(), (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)quality);
}

int AgoraClr::stopAudioRecording()
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopAudioRecording();
}

int AgoraClr::pauseAudioMixing()
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseAudioMixing();
}

int AgoraClr::resumeAudioMixing()
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeAudioMixing();
}

int AgoraClr::adjustAudioMixingVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustAudioMixingVolume(volume);
}

int AgoraClr::getAudioMixingDuration()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getAudioMixingDuration();
}

int AgoraClr::getAudioMixingCurrentPosition()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getAudioMixingCurrentPosition();
}

int AgoraClr::setAudioMixingPosition(int pos)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setAudioMixingPosition(pos);
}

int AgoraClr::startAudioMixing(String ^ path, bool loop, bool replace, int cycle)
{
	RtcEngineParameters params(*rtcEngine);
	return params.startAudioMixing(MarshalString(path).c_str(), loop, replace, cycle);
}

int AgoraClr::stopAudioMixing()
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopAudioMixing();
}

int AgoraClr::setAudioProfile(AudioProfileType profile, AudioScenarioType scenario)
{
	return rtcEngine->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}

int AgoraClr::setLogFile(String ^ path)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLogFile(MarshalString(path).c_str());
}

int AgoraClr::setLogFilter(unsigned int filter)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLogFilter(filter);
}

int AgoraClr::adjustRecordingSignalVolume(int volume)
{
	return rtcEngine->adjustRecordingSignalVolume(volume);
}

int AgoraClr::adjustPlaybackSignalVolume(int volume)
{
	return rtcEngine->adjustPlaybackSignalVolume(volume);
}

int AgoraClr::enableLocalAudio(bool enabled) {
	return rtcEngine->enableLocalAudio(enabled);
}

int AgoraClr::setLocalVoicePitch(double pitch)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoicePitch(pitch);
}

int AgoraClr::setInEarMonitoringVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setInEarMonitoringVolume(volume);
}

int AgoraClr::setExternalAudioSource(bool enabled, int sampleRate, int channels)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setExternalAudioSource(enabled, sampleRate, channels);
}

int AgoraClr::setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoiceEqualization((AUDIO_EQUALIZATION_BAND_FREQUENCY)freq, bandGain);
}

int AgoraClr::setLocalVoiceReverb(AudioReverbType type, int value)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoiceReverb((AUDIO_REVERB_TYPE)type, value);
}

int AgoraClr::setLocalVideoMirrorMode(VideoMirrorModeType mode)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVideoMirrorMode((VIDEO_MIRROR_MODE_TYPE)mode);
}

String ^ AgoraClr::getVersion(int % build)
{
	int version;
	String ^ result = gcnew String(rtcEngine->getVersion(&version));
	build = version;
	return result;
}

int AgoraClr::enableLoopbackRecording(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableLoopbackRecording(enabled);
}

int AgoraClr::pushAudioFrame(ClrAudioFrameType type, ClrAudioFrame ^ frame, bool wrap)
{
	if (agoraMediaEngine)
		return agoraMediaEngine->pushAudioFrame((agora::media::MEDIA_SOURCE_TYPE)type, frame->toRaw(), wrap);
	else
		return -1;
}

int AgoraClr::addPublishStreamUrl(String ^ url, bool transcodingEnabled)
{
	return rtcEngine->addPublishStreamUrl(MarshalString(url).c_str(), transcodingEnabled);
}

int AgoraClr::removePublishStreamUrl(String ^ url)
{
	return rtcEngine->removePublishStreamUrl(MarshalString(url).c_str());
}

int AgoraClr::setLiveTranscoding(ClrLiveTranscoding ^ transcoding)
{
	LiveTranscoding lt;
	transcoding->writeRaw(lt);
	return rtcEngine->setLiveTranscoding(lt);
}

int AgoraClr::addInjectStreamUrl(String ^ url, ClrInjectStreamConfig ^ config)
{
	InjectStreamConfig raw;
	config->writeRaw(raw);
	return rtcEngine->addInjectStreamUrl(MarshalString(url).c_str(), raw);
}

int AgoraClr::removeInjectStreamUrl(String ^ url)
{
	return rtcEngine->removeInjectStreamUrl(MarshalString(url).c_str());
}

int AgoraClr::getEffectsVolume()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getEffectsVolume();
}

int AgoraClr::setEffectsVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setEffectsVolume(volume);
}

int AgoraClr::setVolumeOfEffect(int soundId, int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setVolumeOfEffect(soundId, volume);
}

int AgoraClr::playEffect(int soundId, String ^ file, int loopCount, double pitch, double pan, int gain, bool publish)
{
	RtcEngineParameters params(*rtcEngine);
	return params.playEffect(soundId, MarshalString(file).c_str(), loopCount, pitch, pan, gain, publish);
}

int AgoraClr::stopEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopEffect(soundId);
}

int AgoraClr::stopAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopAllEffects();
}

int AgoraClr::preloadEffect(int soundId, String ^ file)
{
	RtcEngineParameters params(*rtcEngine);
	std::string str = MarshalString(file);
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	int result = params.preloadEffect(soundId, cstr);
	delete cstr;
	return result;
}

int AgoraClr::unloadEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.unloadEffect(soundId);
}

int AgoraClr::pauseEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseEffect(soundId);
}

int AgoraClr::pauseAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseAllEffects();
}

int AgoraClr::resumeEffect(int soundId)
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeEffect(soundId);
}

int AgoraClr::resumeAllEffects()
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeAllEffects();
}

ConnectionStateType AgoraClr::getConnectionState()
{
	return (ConnectionStateType)rtcEngine->getConnectionState();
}

int AgoraClr::setDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
}

int AgoraClr::setVideoEncoderConfiguration(ClrVideoEncoderConfiguration ^ config)
{
	VideoEncoderConfiguration configuration;
	config->writeRaw(configuration);
	return rtcEngine->setVideoEncoderConfiguration(configuration);
}

int AgoraClr::setDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return rtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
}

int AgoraClr::adjustAudioMixingPlayoutVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustAudioMixingPlayoutVolume(volume);
}

int AgoraClr::adjustAudioMixingPublishVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustAudioMixingPublishVolume(volume);
}

int AgoraClr::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setExternalAudioSink(enabled, sampleRate, channels);
}

int AgoraClr::setExternalVideoSource(bool enabled, bool useTexture)
{
	if (agoraMediaEngine)
		return agoraMediaEngine->setExternalVideoSource(enabled, useTexture);
	else
		return -1;
}

int AgoraClr::pushVideoFrame(ClrExternalVideoFrame ^ frame)
{
	if (agoraMediaEngine)
		return agoraMediaEngine->pushVideoFrame(frame->toRaw());
	else
		return -1;
}

int AgoraClr::addVideoWatermark(ClrRtcImage ^ image)
{
	RtcImage i;
	image->writeRaw(i);
	return rtcEngine->addVideoWatermark(i);
}

int AgoraClr::clearVideoWatermark()
{
	return rtcEngine->clearVideoWatermarks();
}

int AgoraClr::setLocalPublishFallbackOption(StreamFallbackOptions option)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalPublishFallbackOption((STREAM_FALLBACK_OPTIONS)option);
}

int AgoraClr::setRemoteSubscribeFallbackOption(StreamFallbackOptions option)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRemoteSubscribeFallbackOption((STREAM_FALLBACK_OPTIONS)option);
}

int AgoraClr::setRemoteDefaultVideoStreamType(RemoteVideoStreamType type)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRemoteDefaultVideoStreamType((REMOTE_VIDEO_STREAM_TYPE)type);
}

String ^ AgoraClr::getErrorDescription(int code)
{
	return gcnew String(rtcEngine->getErrorDescription(code));
}

void *AgoraClr::regEvent(Object ^ obj)
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
	agoraEventHandler->onCameraFocusAreaChangedEvent = PFOnCameraFocusAreaChanged(regEvent(gcnew NativeOnCameraFocusAreaChangedDelegate(this, &AgoraClr::NativeOnCameraFocusAreaChanged)));
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
	agoraRawObserver->onRecordAudioFrameEvent = PFOnRecordAudioFrame(regEvent(gcnew NativeOnRecordAudioFrameDelegate(this, &AgoraClr::NativeOnRecordAudioFrame)));
	agoraRawObserver->onPlaybackAudioFrameEvent = PFOnPlaybackAudioFrame(regEvent(gcnew NativeOnPlaybackAudioFrameDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrame)));
	agoraRawObserver->onPlaybackAudioFrameBeforeMixingEvent = PFOnPlaybackAudioFrameBeforeMixing(regEvent(gcnew NativeOnPlaybackAudioFrameBeforeMixingDelegate(this, &AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing)));
	agoraRawObserver->onMixedAudioFrameEvent = PFOnMixedAudioFrame(regEvent(gcnew NativeOnMixedAudioFrameDelegate(this, &AgoraClr::NativeOnMixedAudioFrame)));

	agoraRawObserver->onCaptureVideoFrameEvent = PFOnCaptureVideoFrame(regEvent(gcnew NativeOnCaptureVideoFrameDelegate(this, &AgoraClr::NativeOnCaptureVideoFrame)));
	agoraRawObserver->onRenderVideoFrameEvent = PFOnRenderVideoFrame(regEvent(gcnew NativeOnRenderVideoFrameDelegate(this, &AgoraClr::NativeOnRenderVideoFrame)));
}

AgoraClrAudioDeviceManager ^ AgoraClr::getAudioDeviceManager()
{
	return gcnew AgoraClrAudioDeviceManager(this);
}

AgoraClrVideoDeviceManager ^ AgoraClr::getVideoDeviceManager()
{
	return gcnew AgoraClrVideoDeviceManager(this);
}

IRtcEngine *AgoraClr::getEngine()
{
	return this->rtcEngine;
}

void AgoraClr::NativeOnJoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccess)
	{
		onJoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnRejoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{
	if (onRejoinChannelSuccess)
	{
		onRejoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnWarning(int warn, const char *msg)
{
	if (onWarning)
	{
		onWarning(warn, gcnew String(msg));
	}
}

void AgoraClr::NativeOnError(int err, const char *msg)
{
	if (onError)
		onError(err, gcnew String(msg));
}

void AgoraClr::NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	if (onAudioQuality)
		onAudioQuality(uid, quality, delay, lost);
}

void AgoraClr::NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo *speakers, unsigned int speakerNumber, int totalVolume)
{
	if (onAudioVolumeIndication)
	{
		List<AudioVolumeInfo ^> ^ list = gcnew List<AudioVolumeInfo ^>();
		for (unsigned int i = 0; i < speakerNumber; i++)
		{
			AudioVolumeInfo ^ info = gcnew AudioVolumeInfo();
			info->uid = speakers[i].uid;
			info->volume = speakers[i].volume;
			list->Add(info);
		}
		onAudioVolumeIndication(list, totalVolume);
	}
}

void AgoraClr::NativeOnLeaveChannel(const agora::rtc::RtcStats &stats)
{
	if (onLeaveChannel)
		onLeaveChannel(gcnew RtcStats(stats));
}

void AgoraClr::NativeOnRtcStats(const agora::rtc::RtcStats &stats)
{
	if (onRtcStats)
	{
		RtcStats ^ rtc = gcnew RtcStats(stats);
		onRtcStats(rtc);
	}
}

void AgoraClr::NativeOnAudioDeviceStateChanged(const char *deviceId, int deviceType, int deviceState)
{
	if (onAudioDeviceStateChanged)
		onAudioDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClr::NativeOnVideoDeviceStateChanged(const char *deviceId, int deviceType, int deviceState)
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
		onClientRoleChanged((ClientRoleType)oldRole, (ClientRoleType)newRole);
}

void AgoraClr::NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChanged)
		onAudioDeviceVolumeChanged((MediaDeviceType)deviceType, volume, muted);
}

void AgoraClr::NativeOnStreamUnpublished(const char *url)
{
	if (onStreamUnpublished)
		onStreamUnpublished(gcnew String(url));
}

void AgoraClr::NativeOnStreamPublished(const char *url, int error)
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
		onConnectionStateChanged((ConnectionStateType)state, (ConnectionChangedReasonType)reason);
}

void AgoraClr::NativeOnTokenPrivilegeWillExpire(const char *token)
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
		onRemoteVideoStateChanged(uid, (RemoteVideoState)state, (RemoteVideoStateReason)reason, elapsed);
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
		onUserOffline(uid, (UserOfflineType)reason);
}

void AgoraClr::NativeOnNetworkTypeChanged(NETWORK_TYPE type) 
{
	if (onNetworkTypeChanged) onNetworkTypeChanged((NetworkType)type);
}

void AgoraClr::NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	if (onLocalAudioStateChanged) onLocalAudioStateChanged((LocalAudioStreamState)state, (LocalAudioStreamError)error);
}

void AgoraClr::NativeOnLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
{
	if (onLocalVideoStateChanged) onLocalVideoStateChanged((LocalVideoStreamState)state, (LocalVideoStreamError)error);
}

void AgoraClrLibrary::AgoraClr::NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	if (onRemoteAudioStateChanged) onRemoteAudioStateChanged(uid, (RemoteAudioState)state, (RemoteAudioStateReason)reason, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed)
{
	if (onFirstRemoteAudioDecoded) onFirstRemoteAudioDecoded(uid, elapsed);
}

void AgoraClrLibrary::AgoraClr::NativeOnLocalAudioStats(const LocalAudioStats& stats)
{
	if (onLocalAudioStats) onLocalAudioStats(gcnew ClrLocalAudioStats(stats));
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

void AgoraClr::NativeOnApiCallExecuted(const char *api, int error)
{
	if (onApiCallExecuted)
		onApiCallExecuted(gcnew String(api), error);
}

void AgoraClr::NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats &stats)
{
	if (onLocalVideoStats)
		onLocalVideoStats(gcnew ClrLocalVideoStats(stats));
}

void AgoraClr::NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats &stats)
{
	if (onRemoteVideoStats)
	{
		RemoteVideoStats ^ s = gcnew RemoteVideoStats(stats);

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

void AgoraClr::NativeOnStreamMessage(uid_t uid, int streamId, const char *data, size_t length)
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

void AgoraClr::NativeOnCameraFocusAreaChanged(int x, int y, int width, int height)
{
	if (onCameraFocusAreaChanged)
		onCameraFocusAreaChanged(x, y, width, height);
}

void AgoraClr::NativeOnRemoteAudioStats(const RemoteAudioStats &stats)
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

void AgoraClr::NativeOnStreamInjectedStatus(const char *url, uid_t uid, int status)
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

bool AgoraClr::NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet &packet)
{
	bool result = true;
	if (onSendAudioPacket)
	{
		ClrPacket ^ managedPacket = gcnew ClrPacket(packet);
		result = onSendAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet &packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket ^ managedPacket = gcnew ClrPacket(packet);
		result = onSendVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet &packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket ^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveAudioPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet &packet)
{
	bool result = true;
	if (onSendVideoPacket)
	{
		ClrPacket ^ managedPacket = gcnew ClrPacket(packet);
		result = onReceiveVideoPacket(managedPacket);
		if (result)
			managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClr::NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &frame)
{
	bool result = true;
	if (onRecordAudioFrame)
	{
		ClrAudioFrame ^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onRecordAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &frame)
{
	bool result = true;
	if (onPlaybackAudioFrame)
	{
		ClrAudioFrame ^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame &frame)
{
	bool result = true;
	if (onPlaybackAudioFrameBeforeMixing)
	{
		ClrAudioFrame ^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrameBeforeMixing(uid, clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &frame)
{
	bool result = true;
	if (onMixedAudioFrame)
	{
		ClrAudioFrame ^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onMixedAudioFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame &frame)
{
	bool result = true;
	if (onCaptureVideoFrame)
	{
		ClrVideoFrame ^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onCaptureVideoFrame(clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClr::NativeOnRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame &frame)
{
	bool result = true;
	if (onRenderVideoFrame)
	{
		ClrVideoFrame ^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onRenderVideoFrame(uid, clrFrame);
		if (result)
			clrFrame->writeRaw(frame);
	}
	return result;
}
