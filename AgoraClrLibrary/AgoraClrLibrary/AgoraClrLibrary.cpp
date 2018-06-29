// 这是主 DLL 文件。

#include "stdafx.h"
#include <iostream>
#include "AgoraClrLibrary.h"
#include "AgoraClrEventHandler.h"

using namespace AgoraClrLibrary;
using namespace System;
using namespace System::Runtime::InteropServices;

AgoraClr::AgoraClr()
{
	gchs = gcnew List<GCHandle>();
	rtcEngine = NULL;
	agoraEventHandler = new AgoraClrEventHandler;
	agoraPacketObserver = new AgoraClrPacketObserver;
	agoraRawObserver = new AgoraClrRawFrameObserver;

	initializeEventHandler();
	initializePacketObserver();
	initializeRawFrameObserver();
}

AgoraClr::~AgoraClr()
{
	this->release();
	for each(GCHandle handle in gchs) {
		handle.Free();
	}

	this->!AgoraClr();
}

AgoraClr::!AgoraClr()
{

}

int AgoraClr::initialize(String ^vendorkey)
{
	if (rtcEngine != NULL) return 0;
	rtcEngine = createAgoraRtcEngine();
	if (rtcEngine == NULL) return -1;
	std::string middlestr = MarshalString(vendorkey);;
	agora::rtc::RtcEngineContext context;
	context.appId = middlestr.c_str();
	context.eventHandler = agoraEventHandler;
	int result = rtcEngine->initialize(context);
	if (result == 0) {
		rtcEngine->registerPacketObserver(agoraPacketObserver);
		IMediaEngine* p = NULL;
		if (!rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE, (void**)&p)) {
			agoraMediaEngine = p;
			agoraMediaEngine->registerAudioFrameObserver(agoraRawObserver);
			agoraMediaEngine->registerVideoFrameObserver(agoraRawObserver);
		}
	}
	return result;
}

void AgoraClr::release()
{
	if (rtcEngine != NULL) {
		if (agoraMediaEngine)
			agoraMediaEngine->release();

		delete agoraEventHandler;
		delete agoraPacketObserver;
		delete agoraRawObserver;

		rtcEngine->release();
		rtcEngine = NULL;
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

int AgoraClrLibrary::AgoraClr::enableAudio()
{
	return rtcEngine->enableAudio();
}

int AgoraClrLibrary::AgoraClr::disableAudio()
{
	return rtcEngine->disableAudio();
}

int AgoraClrLibrary::AgoraClr::setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate)
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

int AgoraClrLibrary::AgoraClr::enableWebSdkInteroperability(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableWebSdkInteroperability(enabled);
}

int AgoraClr::joinChannel(String ^ token, String ^ channelName, String ^channelInfo, int uid)
{
	std::string key = MarshalString(token);
	std::string name = MarshalString(channelName);
	std::string info = MarshalString(channelInfo);
	return rtcEngine->joinChannel(key.c_str(), name.c_str(), info.c_str(), uid);
}

int AgoraClr::leaveChannel()
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

int AgoraClrLibrary::AgoraClr::updateScreenCaptureRegion(ClrRect ^ rect)
{
	return rtcEngine->updateScreenCaptureRegion(rect->toRaw());
}

int AgoraClr::renewToken(String ^ token)
{
	return rtcEngine->renewToken(MarshalString(token).c_str());
}

int AgoraClrLibrary::AgoraClr::setEncryptionSecret(String ^ key)
{
	std::string screte = MarshalString(key);
	return rtcEngine->setEncryptionSecret(screte.c_str());
}

int AgoraClrLibrary::AgoraClr::setEncryptionMode(String ^ mode)
{
	return rtcEngine->setEncryptionMode(MarshalString(mode).c_str());
}

int AgoraClr::getCallId(String ^% id)
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

int AgoraClrLibrary::AgoraClr::enableDualStreamMode(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableDualStreamMode(enabled);
}

int AgoraClrLibrary::AgoraClr::setRemoteVideoStreamType(int uid, RemoteVideoStreamType type)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRemoteVideoStreamType(uid, (REMOTE_VIDEO_STREAM_TYPE)type);
}

int AgoraClrLibrary::AgoraClr::setVideoQualityParameters(bool preferFrameRateOverImageQuality)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setVideoQualityParameters(preferFrameRateOverImageQuality);
}

int AgoraClrLibrary::AgoraClr::setVideoCompositingLayout(ClrVideoCompositingLayout ^ sei)
{
	if (sei == nullptr) return rtcEngine->setVideoCompositingLayout(VideoCompositingLayout());
	else return rtcEngine->setVideoCompositingLayout(*sei->toRaw());
}

int AgoraClrLibrary::AgoraClr::clearVideoCompositingLayout()
{
	return rtcEngine->clearVideoCompositingLayout();
}

int AgoraClrLibrary::AgoraClr::configPublisher(ClrPublisherConfiguration ^ config)
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

int AgoraClrLibrary::AgoraClr::setClientRole(ClientRoleType role)
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

int AgoraClrLibrary::AgoraClr::setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRecordingAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int AgoraClrLibrary::AgoraClr::setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setPlaybackAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int AgoraClrLibrary::AgoraClr::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int AgoraClr::muteLocalAudioStream(bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteLocalAudioStream(mute);
}

int AgoraClr::muteAllRemoteAudioStreams(bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteAllRemoteAudioStreams(mute);
}

int AgoraClr::muteRemoteAudioStream(int uid, bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteRemoteAudioStream(uid, mute);
}

int AgoraClr::muteLocalVideoStream(bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteLocalVideoStream(mute);
}

int AgoraClr::enableLocalVideo(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableLocalVideo(enabled);
}

int AgoraClr::muteAllRemoteVideoStream(bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteAllRemoteVideoStreams(mute);
}

int AgoraClr::muteRemoteVideoStream(int uid, bool mute)
{
	RtcEngineParameters params(*rtcEngine);
	return params.muteRemoteVideoStream(uid, mute);
}

int AgoraClr::setPlaybackDeviceVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setPlaybackDeviceVolume(volume);
}

int AgoraClr::setLocalRenderMode(RenderMode mode)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalRenderMode((agora::rtc::RENDER_MODE_TYPE)mode);
}

int AgoraClr::setRemoteRenderMode(int uid, RenderMode mode)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setRemoteRenderMode(uid, (agora::rtc::RENDER_MODE_TYPE)mode);
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

int AgoraClrLibrary::AgoraClr::pauseAudioMixing()
{
	RtcEngineParameters params(*rtcEngine);
	return params.pauseAudioMixing();
}

int AgoraClrLibrary::AgoraClr::resumeAudioMixing()
{
	RtcEngineParameters params(*rtcEngine);
	return params.resumeAudioMixing();
}

int AgoraClrLibrary::AgoraClr::adjustAudioMixingVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustAudioMixingVolume(volume);
}

int AgoraClrLibrary::AgoraClr::getAudioMixingDuration()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getAudioMixingDuration();
}

int AgoraClrLibrary::AgoraClr::getAudioMixingCurrentPosition()
{
	RtcEngineParameters params(*rtcEngine);
	return params.getAudioMixingCurrentPosition();
}

int AgoraClrLibrary::AgoraClr::setAudioMixingPosition(int pos)
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

int AgoraClrLibrary::AgoraClr::setAudioProfile(AudioProfileType profile, AudioScenarioType scenario)
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

int AgoraClr::startRecordingService(String ^ key)
{
	RtcEngineParameters params(*rtcEngine);
	return params.startRecordingService(MarshalString(key).c_str());
}

int AgoraClr::stopRecordingService(String ^ key)
{
	RtcEngineParameters params(*rtcEngine);
	return params.stopRecordingService(MarshalString(key).c_str());
}

int AgoraClr::refreshRecordingServiceStatus()
{
	RtcEngineParameters params(*rtcEngine);
	return params.refreshRecordingServiceStatus();
}

int AgoraClrLibrary::AgoraClr::adjustRecordingSignalVolumne(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustRecordingSignalVolume(volume);
}

int AgoraClrLibrary::AgoraClr::adjustPlaybackSignalVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.adjustPlaybackSignalVolume(volume);
}

int AgoraClrLibrary::AgoraClr::setLocalVoicePitch(double pitch)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoicePitch(pitch);
}

int AgoraClrLibrary::AgoraClr::setInEarMonitoringVolume(int volume)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setInEarMonitoringVolume(volume);
}

int AgoraClrLibrary::AgoraClr::setExternalAudioSource(bool enabled, int sampleRate, int channels)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setExternalAudioSource(enabled, sampleRate, channels);
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoiceEqualization((AUDIO_EQUALIZATION_BAND_FREQUENCY)freq, bandGain);
}

int AgoraClrLibrary::AgoraClr::setLocalVoiceReverb(AudioReverbType type, int value)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVoiceReverb((AUDIO_REVERB_TYPE)type, value);
}

int AgoraClrLibrary::AgoraClr::setLocalVideoMirrorMode(VideoMirrorModeType mode)
{
	RtcEngineParameters params(*rtcEngine);
	return params.setLocalVideoMirrorMode((VIDEO_MIRROR_MODE_TYPE)mode);
}

String^ AgoraClrLibrary::AgoraClr::getVersion(int% build)
{
	int version;
	String^ result = gcnew String(rtcEngine->getVersion(&version));
	build = version;
	return result;
}

int AgoraClrLibrary::AgoraClr::enableLoopbackRecording(bool enabled)
{
	RtcEngineParameters params(*rtcEngine);
	return params.enableLoopbackRecording(enabled);
}

int AgoraClrLibrary::AgoraClr::pushAudioFrame(ClrAudioFrameType type, ClrAudioFrame ^ frame, bool wrap)
{
	if (agoraMediaEngine)
		return agoraMediaEngine->pushAudioFrame((agora::media::MEDIA_SOURCE_TYPE) type, frame->toRaw(), wrap);
	else
		return -1;
}

int AgoraClrLibrary::AgoraClr::addPublishStreamUrl(String ^ url, bool transcodingEnabled)
{
	return rtcEngine->addPublishStreamUrl(MarshalString(url).c_str(), transcodingEnabled);
}

int AgoraClrLibrary::AgoraClr::removePublishStreamUrl(String ^ url)
{
	return rtcEngine->removePublishStreamUrl(MarshalString(url).c_str());
}

int AgoraClrLibrary::AgoraClr::setLiveTranscoding(ClrLiveTranscoding ^ transcoding)
{
	LiveTranscoding lt;
	transcoding->writeRaw(lt);
	return rtcEngine->setLiveTranscoding(lt);
}

int AgoraClrLibrary::AgoraClr::addInjectStreamUrl(String ^ url, ClrInjectStreamConfig ^ config)
{
	InjectStreamConfig raw;
	config->writeRaw(raw);
	return rtcEngine->addInjectStreamUrl(MarshalString(url).c_str(), raw);
}

int AgoraClrLibrary::AgoraClr::removeInjectStreamUrl(String ^ url)
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

int AgoraClrLibrary::AgoraClr::playEffect(int soundId, String ^ file, int loopCount, double pitch, double pan, int gain, bool publish)
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

int AgoraClrLibrary::AgoraClr::preloadEffect(int soundId, String ^ file)
{
	RtcEngineParameters params(*rtcEngine);
	std::string str = MarshalString(file);
	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	int result = params.preloadEffect(soundId, cstr);
	delete cstr;
	return result;
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
	agoraEventHandler->onRefreshRecordingServiceStatusEvent = PFOnRefreshRecordingServiceStatus(regEvent(gcnew NativeOnRefreshRecordingServiceStatusDelegate(this, &AgoraClr::NativeOnRefreshRecordingServiceStatus)));
	agoraEventHandler->onStreamMessageEvent = PFOnStreamMessage(regEvent(gcnew NativeOnStreamMessageDelegate(this, &AgoraClr::NativeOnStreamMessage)));
	agoraEventHandler->onStreamMessageErrorEvent = PFOnStreamMessageError(regEvent(gcnew NativeOnStreamMessageErrorDelegate(this, &AgoraClr::NativeOnStreamMessageError)));
	agoraEventHandler->onRequestChannelKeyEvent = PFOnRequestChannelKey(regEvent(gcnew NativeOnRequestChannelKeyDelegate(this, &AgoraClr::NativeOnRequestChannelKey)));
	agoraEventHandler->onRequestTokenEvent = PFOnRequestToken(regEvent(gcnew NativeOnRequestTokenDelegate(this, &AgoraClr::NativeOnRequestToken)));

	agoraEventHandler->onAudioMixingFinishedEvent = PFOnAudioMixingFinished(regEvent(gcnew NativeOnAudioMixingFinishedDelegate(this, &AgoraClr::NativeOnAudioMixingFinished)));
	agoraEventHandler->onActiveSpeakerEvent = PFOnActiveSpeaker(regEvent(gcnew NativeOnActiveSpeakerDelegate(this, &AgoraClr::NativeOnActiveSpeaker)));
	agoraEventHandler->onClientRoleChangedEvent = PFOnClientRoleChanged(regEvent(gcnew NativeOnClientRoleChangedDelegate(this, &AgoraClr::NativeOnClientRoleChanged)));
	agoraEventHandler->onAudioDeviceVolumeChangedEvent = PFOnAudioDeviceVolumeChanged(regEvent(gcnew NativeOnAudioDeviceVolumeChangedDelegate(this, &AgoraClr::NativeOnAudioDeviceVolumeChanged)));

	agoraEventHandler->onStreamUrlUnpublishedEvent = PFOnStreamUrlUnpublished(regEvent(gcnew NativeOnStreamUrlUnpublishedDelegate(this, &AgoraClr::NativeOnStreamUrlUnpublished)));
	agoraEventHandler->onStreamPublishedEvent = PFOnStreamPublished(regEvent(gcnew NativeOnStreamPublishedDelegate(this, &AgoraClr::NativeOnStreamPublished)));
	agoraEventHandler->onTranscodingUpdatedEvent = PFOnTranscodingUpdated(regEvent(gcnew NativeOnTranscodingUpdatedDelegate(this, &AgoraClr::NativeOnTranscodingUpdated)));
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

AgoraClrAudioDeviceManager ^ AgoraClrLibrary::AgoraClr::getAudioDeviceManager()
{
	return gcnew AgoraClrAudioDeviceManager(this);
}

AgoraClrVideoDeviceManager ^ AgoraClrLibrary::AgoraClr::getVideoDeviceManager()
{
	return gcnew AgoraClrVideoDeviceManager(this);
}

IRtcEngine * AgoraClrLibrary::AgoraClr::getEngine()
{
	return this->rtcEngine;
}

void AgoraClr::NativeOnJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (onJoinChannelSuccess) {
		onJoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) 
{
	if (onRejoinChannelSuccess) {
		onRejoinChannelSuccess(gcnew String(channel), uid, elapsed);
	}
}

void AgoraClr::NativeOnWarning(int warn, const char* msg) 
{
	if (onWarning) {
		onWarning(warn, gcnew String(msg));
	}
}

void AgoraClr::NativeOnError(int err, const char* msg) 
{
	if (onError) onError(err, gcnew String(msg));
}

void AgoraClr::NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) 
{
	if (onAudioQuality) onAudioQuality(uid, quality, delay, lost);
}

void AgoraClr::NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	if (onAudioVolumeIndication) {
		List<AgoraClrLibrary::AudioVolumeInfo^> ^list = gcnew List<AgoraClrLibrary::AudioVolumeInfo^>();
		for (unsigned int i = 0; i < speakerNumber; i++) {
			AgoraClrLibrary::AudioVolumeInfo ^info = gcnew AgoraClrLibrary::AudioVolumeInfo();
			info->uid = speakers[i].uid;
			info->volume = speakers[i].volume;
			list->Add(info);
		}
		onAudioVolumeIndication(list, totalVolume);
	}
}

void AgoraClr::NativeOnLeaveChannel(const agora::rtc::RtcStats& stats) 
{
	if (onLeaveChannel) {
		AgoraClrLibrary::RtcStats ^rtc = gcnew AgoraClrLibrary::RtcStats(stats);
		onLeaveChannel(rtc);
	}
}

void AgoraClr::NativeOnRtcStats(const agora::rtc::RtcStats& stats)
{
	if (onRtcStats) {
		AgoraClrLibrary::RtcStats ^rtc = gcnew AgoraClrLibrary::RtcStats(stats);
		onRtcStats(rtc);
	}
}

void AgoraClr::NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onAudioDeviceStateChanged) onAudioDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);	
}

void AgoraClr::NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	if (onVideoDeviceStateChanged) onVideoDeviceStateChanged(gcnew String(deviceId), deviceType, deviceState);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioMixingFinished()
{
	if (onAudioMixingFinished) onAudioMixingFinished();
}

void AgoraClrLibrary::AgoraClr::NativeOnActiveSpeaker(uid_t uid)
{
	if (onActiveSpeaker) onActiveSpeaker(uid);
}

void AgoraClrLibrary::AgoraClr::NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	if (onClientRoleChanged) onClientRoleChanged((ClientRoleType)oldRole, (ClientRoleType)newRole);
}

void AgoraClrLibrary::AgoraClr::NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	if (onAudioDeviceVolumeChanged) onAudioDeviceVolumeChanged((MediaDeviceType)deviceType, volume, muted);
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamUrlUnpublished(const char * url)
{
	if (onStreamUrlUnpublished) onStreamUrlUnpublished(gcnew String(url));
}

void AgoraClrLibrary::AgoraClr::NativeOnStreamPublished(const char* url, int error)
{
	if (onStreamPublished) onStreamPublished(gcnew String(url), error);
}

void AgoraClrLibrary::AgoraClr::NativeOnTranscodingUpdated()
{
	if (onTranscodingUpdated) onTranscodingUpdated();
}

void AgoraClr::NativeOnLastmileQuality(int quality) 
{
	if (onLastmileQuality) onLastmileQuality(quality);
}

void AgoraClrLibrary::AgoraClr::NativeOnNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	if (onNetworkQuality) onNetworkQuality(uid, txQuality, rxQuality);
}

void AgoraClr::NativeOnFirstLocalVideoFrame(int width, int height, int elapsed) 
{
	if (onFirstLocalVideoFrame) onFirstLocalVideoFrame(width, height, elapsed);
}

void AgoraClr::NativeOnFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) 
{
	if (onFirstRemoteVideoDecoded) onFirstRemoteVideoDecoded(uid, width, height, elapsed);
}

void AgoraClr::NativeOnFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) 
{
	if (onFirstRemoteVideoFrame) onFirstRemoteVideoFrame(uid, width, height, elapsed);
}

void AgoraClr::NativeOnUserJoined(uid_t uid, int elapsed) 
{
	if (onUserJoined) onUserJoined(uid, elapsed);
}

void AgoraClr::NativeOnUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	if (onUserOffline) onUserOffline(uid, (AgoraClrLibrary::UserOfflineType)reason);
}

void AgoraClr::NativeOnUserMuteAudio(uid_t uid, bool muted)
{
	if (onUserMuteAudio) onUserMuteAudio(uid, muted);
}

void AgoraClr::NativeOnUserMuteVideo(uid_t uid, bool muted)
{
	if (onUserMuteVideo) onUserMuteVideo(uid, muted);
}

void AgoraClr::NativeOnUserEnableVideo(uid_t uid, bool enabled)
{
	if (onUserEnableVideo) onUserEnableVideo(uid, enabled);
}

void AgoraClr::NativeOnApiCallExecuted(const char* api, int error)
{
	if (onApiCallExecuted) onApiCallExecuted(gcnew String(api), error);
}

void AgoraClr::NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats)
{
	if (onLocalVideoStats) {
		AgoraClrLibrary::LocalVideoStats ^s = gcnew AgoraClrLibrary::LocalVideoStats();
		s->sentBitrate = stats.sentBitrate;
		s->sentFrameRate = stats.sentFrameRate;
		onLocalVideoStats(s);
	}
}

void AgoraClr::NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	if (onRemoteVideoStats) {
		AgoraClrLibrary::RemoteVideoStats ^s = gcnew AgoraClrLibrary::RemoteVideoStats(stats);

		onRemoteVideoStats(s);
	}
}

void AgoraClr::NativeOnCameraReady() 
{
	if (onCameraReady) onCameraReady();
}

void AgoraClr::NativeOnVideoStopped()
{
	if (onVideoStopped) onVideoStopped();
}

void AgoraClr::NativeOnConnectionLost()
{
	if (onConnectionLost) onConnectionLost();
}

void AgoraClrLibrary::AgoraClr::NativeOnConnectionBanned()
{
	if (onConnectionBanned) onConnectionBanned();
}

void AgoraClr::NativeOnConnectionInterrupted()
{
	if (onConnectionInterrupted) onConnectionInterrupted();
}

void AgoraClr::NativeOnRefreshRecordingServiceStatus(int status)
{
	if (onRefreshRecordingServiceStatus) onRefreshRecordingServiceStatus(status);
}

void AgoraClr::NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length)
{
	if (onStreamMessage) onStreamMessage(uid, streamId, gcnew String(data));
}

void AgoraClr::NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached)
{
	if (onStreamMessageError) onStreamMessageError(uid, streamId, code, missed, cached);
}

void AgoraClrLibrary::AgoraClr::NativeOnRequestChannelKey()
{
	if (onRequestChannelKey) onRequestChannelKey();
}

void AgoraClrLibrary::AgoraClr::NativeOnRequestToken()
{
	if (onRequestToken) onRequestToken();
}

bool AgoraClrLibrary::AgoraClr::NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet & packet)
{
	bool result = true;
	if (onSendAudioPacket) {
		ClrPacket ^managedPacket = gcnew ClrPacket(packet);
		result = onSendAudioPacket(managedPacket);
		if (result) managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet & packet)
{
	bool result = true;
	if (onSendVideoPacket) {
		AgoraClrLibrary::ClrPacket^ managedPacket = gcnew AgoraClrLibrary::ClrPacket(packet);
		result = onSendVideoPacket(managedPacket);
		if (result) managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet & packet)
{
	bool result = true;
	if (onSendVideoPacket) {
		AgoraClrLibrary::ClrPacket^ managedPacket = gcnew AgoraClrLibrary::ClrPacket(packet);
		result = onReceiveAudioPacket(managedPacket);
		if (result) managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet & packet)
{
	bool result = true;
	if (onSendVideoPacket) {
		AgoraClrLibrary::ClrPacket^ managedPacket = gcnew AgoraClrLibrary::ClrPacket(packet);
		result = onReceiveVideoPacket(managedPacket);
		if (result) managedPacket->writePacket(packet);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame & frame)
{
	bool result = true;
	if (onRecordAudioFrame) {
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onRecordAudioFrame(clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame & frame)
{
	bool result = true;
	if (onPlaybackAudioFrame) {
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrame(clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame & frame)
{
	bool result = true;
	if (onPlaybackAudioFrameBeforeMixing) {
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onPlaybackAudioFrameBeforeMixing(uid, clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame & frame)
{
	bool result = true;
	if (onMixedAudioFrame) {
		ClrAudioFrame^ clrFrame = gcnew ClrAudioFrame(frame);
		result = onMixedAudioFrame(clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame & frame)
{
	bool result = true;
	if (onCaptureVideoFrame) {
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onCaptureVideoFrame(clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

bool AgoraClrLibrary::AgoraClr::NativeOnRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame & frame)
{
	bool result = true;
	if (onRenderVideoFrame) {
		ClrVideoFrame^ clrFrame = gcnew ClrVideoFrame(frame);
		result = onRenderVideoFrame(uid, clrFrame);
		if (result) clrFrame->writeRaw(frame);
	}
	return result;
}

