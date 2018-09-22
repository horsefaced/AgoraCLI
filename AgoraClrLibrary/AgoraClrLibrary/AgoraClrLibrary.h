// AgoraClrLibrary.h

#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrVideoDeviceManager.h"

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace AgoraClrLibrary {

	static std::string MarshalString(String ^s) {
		if (s == nullptr) return std::string();
		IntPtr middleStr = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
		std::string result((char *)middleStr.ToPointer());
		Runtime::InteropServices::Marshal::FreeHGlobal(middleStr);
		return result;
	}

	public enum class VideoProfile
	{                                   // res       fps  kbps
		VIDEO_PROFILE_120P = 0,         // 160x120   15   65
		VIDEO_PROFILE_120P_3 = 2,       // 120x120   15   50
		VIDEO_PROFILE_180P = 10,        // 320x180   15   140
		VIDEO_PROFILE_180P_3 = 12,      // 180x180   15   100
		VIDEO_PROFILE_180P_4 = 13,      // 240x180   15   120
		VIDEO_PROFILE_240P = 20,        // 320x240   15   200
		VIDEO_PROFILE_240P_3 = 22,      // 240x240   15   140
		VIDEO_PROFILE_240P_4 = 23,      // 424x240   15   220
		VIDEO_PROFILE_360P = 30,        // 640x360   15   400
		VIDEO_PROFILE_360P_3 = 32,      // 360x360   15   260
		VIDEO_PROFILE_360P_4 = 33,      // 640x360   30   600
		VIDEO_PROFILE_360P_6 = 35,      // 360x360   30   400
		VIDEO_PROFILE_360P_7 = 36,      // 480x360   15   320
		VIDEO_PROFILE_360P_8 = 37,      // 480x360   30   490
		VIDEO_PROFILE_480P = 40,        // 640x480   15   500
		VIDEO_PROFILE_480P_3 = 42,      // 480x480   15   400
		VIDEO_PROFILE_480P_4 = 43,      // 640x480   30   750
		VIDEO_PROFILE_480P_6 = 45,      // 480x480   30   600
		VIDEO_PROFILE_480P_8 = 47,		// 848x480   15   610
		VIDEO_PROFILE_480P_9 = 48,		// 848x480   30   930
		VIDEO_PROFILE_720P = 50,        // 1280x720  15   1130
		VIDEO_PROFILE_720P_3 = 52,      // 1280x720  30   1710
		VIDEO_PROFILE_720P_5 = 54,      // 960x720  15    910
		VIDEO_PROFILE_720P_6 = 55,      // 960x720  30    1380
		VIDEO_PROFILE_1080P = 60,       // 1920x1080 15   2080
		VIDEO_PROFILE_1080P_3 = 62,        // 1920x1080 30   3150
		VIDEO_PROFILE_1080P_5 = 64,        // 1920x1080 60   4780
		VIDEO_PROFILE_1440P = 66,        // 2560x1440 30   4850
		VIDEO_PROFILE_1440P_2 = 67,        // 2560x1440 60   7350
		VIDEO_PROFILE_4K = 70,            // 3840x2160 30   8910
		VIDEO_PROFILE_4K_3 = 72,        // 3840x2160 60   13500
		VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_360P,
	};

	public enum class ChannelProfile
	{
		CHANNEL_PROFILE_COMMUNICATION = 0,
		CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
		CHANNEL_PROFILE_GAME = 2,
	};

	public enum class ClientRoleType
	{
		CLIENT_ROLE_BROADCASTER = 1,
		CLIENT_ROLE_AUDIENCE = 2,
	};

	public enum class RenderMode
	{
		RENDER_MODE_HIDDEN = 1,
		RENDER_MODE_FIT = 2,
		RENDER_MODE_ADAPTIVE = 3,
	};

	public ref class AudioVolumeInfo
	{
	public:
		String^ uid;
		unsigned int volume; // [0,255]
	};

	public ref class RtcStats
	{
	public:
		unsigned int duration;
		unsigned int txBytes;
		unsigned int rxBytes;
		unsigned short txKBitRate;
		unsigned short rxKBitRate;

		unsigned short rxAudioKBitRate;
		unsigned short txAudioKBitRate;

		unsigned short rxVideoKBitRate;
		unsigned short txVideoKBitRate;

		unsigned int users;
		double cpuAppUsage;
		double cpuTotalUsage;

		RtcStats(agora::rtc::RtcStats raw) {
			cpuAppUsage = raw.cpuAppUsage;
			cpuTotalUsage = raw.cpuTotalUsage;
			duration = raw.duration;
			rxBytes = raw.rxBytes;
			txBytes = raw.txBytes;
			txKBitRate = raw.txKBitRate;
			rxKBitRate = raw.rxKBitRate;
			rxAudioKBitRate = raw.rxAudioKBitRate;
			txAudioKBitRate = raw.txAudioKBitRate;
			rxVideoKBitRate = raw.rxVideoKBitRate;
			txVideoKBitRate = raw.txVideoKBitRate;
			users = raw.users;
		}
	};

	public enum class UserOfflineType
	{
		USER_OFFLINE_QUIT = 0,
		USER_OFFLINE_DROPPED = 1,
		USER_OFFLINE_BECOME_AUDIENCE = 2,
	};

	public enum class RawAudioFrameOPModeType
	{
		RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
		RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
		RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
	};
	public enum class AudioRecordingQualityType
	{
		AUDIO_RECORDING_QUALITY_LOW = 0,
		AUDIO_RECORDING_QUALITY_MEDIUM = 1,
		AUDIO_RECORDING_QUALITY_HIGH = 2,
	};

	public ref class LocalVideoStats
	{
	public:
		int sentBitrate;
		int sentFrameRate;
	};

	public enum class RemoteVideoStreamType
	{
		REMOTE_VIDEO_STREAM_UNKNOWN = -1,
		REMOTE_VIDEO_STREAM_HIGH = 0,
		REMOTE_VIDEO_STREAM_LOW = 1,
		REMOTE_VIDEO_STREAM_MEDIUM = 2,
	};

	public enum class MediaDeviceType
	{
		UNKNOWN_AUDIO_DEVICE = -1,
		AUDIO_PLAYOUT_DEVICE = 0,
		AUDIO_RECORDING_DEVICE = 1,
		VIDEO_RENDER_DEVICE = 2,
		VIDEO_CAPTURE_DEVICE = 3,
		AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
	};

	public ref class RemoteVideoStats
	{
	public:
		String^ uid;
		int delay;
		int width;
		int height;
		int receivedBitrate;
		int receivedFrameRate;
		RemoteVideoStreamType rxStreamType;

		RemoteVideoStats(agora::rtc::RemoteVideoStats stats) {
			uid = gcnew String(stats.uid);
			delay = stats.delay;
			width = stats.width;
			height = stats.height;
			receivedBitrate = stats.receivedBitrate;
			receivedFrameRate = stats.receivedFrameRate;
			rxStreamType = (RemoteVideoStreamType)stats.rxStreamType;
		}
	};

	public ref class ClrPacket {
	public:
		array<unsigned char>^ buffer;

		ClrPacket() {}
		ClrPacket(IPacketObserver::Packet& packet)
		{
			this->buffer = gcnew array<unsigned char>(packet.size);
			Marshal::Copy(IntPtr(const_cast<void *>(static_cast<const void*>(packet.buffer))), this->buffer, 0, packet.size);
		}

		void writePacket(IPacketObserver::Packet& packet) {
			int size = Marshal::SizeOf(buffer[0]) * buffer->Length;
			IntPtr rawBuffer = Marshal::AllocHGlobal(size);
			Marshal::Copy(buffer, 0, rawBuffer, buffer->Length);
			packet.buffer = (unsigned char*)rawBuffer.ToPointer();
			packet.size = buffer->Length;
		}

	};

	public enum class ClrAudioFrameType {
		FRAME_TYPE_PCM16 = 0,  //PCM 16bit little endian
	};

	public ref class ClrAudioFrame {
	public:
		ClrAudioFrameType type;
		int samples;  //number of samples in this frame
		int bytesPerSample;  //number of bytes per sample: 2 for PCM16
		int channels;  //声道数
		int samplesPerSec;  //采样率
		array<Byte>^ data;
		int64_t renderTimeMs;

		ClrAudioFrame(agora::media::IAudioFrameObserver::AudioFrame & raw) {
			type = (ClrAudioFrameType)raw.type, samples = raw.samples, bytesPerSample = raw.bytesPerSample, channels = raw.channels,
				samplesPerSec = raw.samplesPerSec, renderTimeMs = raw.renderTimeMs;

			data = gcnew array<Byte>(samples * bytesPerSample);
			Marshal::Copy(IntPtr(raw.buffer), data, 0, samples * bytesPerSample);
		}

		void writeRaw(agora::media::IAudioFrameObserver::AudioFrame & raw) {
			bool sizeModified = (samples * bytesPerSample) != (raw.samples * raw.bytesPerSample);
			raw.type = (agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE)type, raw.samples = samples, raw.bytesPerSample = bytesPerSample,
				raw.channels = channels, raw.samplesPerSec = samplesPerSec, raw.renderTimeMs = renderTimeMs;
			if (sizeModified) raw.buffer = Marshal::AllocHGlobal(samples * bytesPerSample).ToPointer();
			Marshal::Copy(data, 0, IntPtr(raw.buffer), samples * bytesPerSample);
		}
	};

	public enum class ClrVideoFrameType {
		FRAME_TYPE_YUV420 = 0,  //YUV 420 format
	};

	public ref class ClrVideoFrame {
	public:
		ClrVideoFrameType type;
		int width;  //width of video frame
		int height;  //height of video frame
		int yStride;  //stride of Y data buffer
		int uStride;  //stride of U data buffer
		int vStride;  //stride of V data buffer
		array<Byte>^ ybuffer;
		array<Byte>^ ubuffer;
		array<Byte>^ vbuffer;
		int rotation; // rotation of this frame (0, 90, 180, 270)
		int64_t renderTimeMs;

		ClrVideoFrame(agora::media::IVideoFrameObserver::VideoFrame & raw) {
			type = (ClrVideoFrameType)raw.type;
			width = raw.width, height = raw.height, yStride = raw.yStride, uStride = raw.uStride, vStride = raw.vStride;
			rotation = raw.rotation, renderTimeMs = raw.renderTimeMs;

			int size = width * height;
			ybuffer = gcnew array<Byte>(size);
			Marshal::Copy(IntPtr(raw.yBuffer), ybuffer, 0, size);
			ubuffer = gcnew array<Byte>(size / 4);
			Marshal::Copy(IntPtr(raw.uBuffer), ubuffer, 0, size / 4);
			vbuffer = gcnew array<Byte>(size / 4);
			Marshal::Copy(IntPtr(raw.vBuffer), vbuffer, 0, size / 4);
		}

		void writeRaw(agora::media::IVideoFrameObserver::VideoFrame & raw) {
			int sizeModified = (raw.width * raw.height) != (width * height);

			raw.type = (agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE)type, raw.width = width, raw.height = height;
			raw.yStride = yStride, raw.uStride = uStride, raw.vStride = vStride, raw.rotation = rotation, raw.renderTimeMs = renderTimeMs;

			int size = width * height;
			if (sizeModified) {
				raw.yBuffer = Marshal::AllocHGlobal(size).ToPointer();
				raw.uBuffer = Marshal::AllocHGlobal(size / 4).ToPointer();
				raw.vBuffer = Marshal::AllocHGlobal(size / 4).ToPointer();
			}
			Marshal::Copy(ybuffer, 0, IntPtr(raw.yBuffer), size);
			Marshal::Copy(ubuffer, 0, IntPtr(raw.uBuffer), size / 4);
			Marshal::Copy(vbuffer, 0, IntPtr(raw.vBuffer), size / 4);
		}
	};

	public ref class ClrRegion {
	public:
		String^ uid;
		double x;//[0,1]
		double y;//[0,1]
		double width;//[0,1]
		double height;//[0,1]
		int zOrder; //optional, [0, 100] //0 (default): bottom most, 100: top most

		//  Optional
		//  [0, 1.0] where 0 denotes throughly transparent, 1.0 opaque
		double alpha;

		RenderMode renderMode;//RENDER_MODE_HIDDEN: Crop, RENDER_MODE_FIT: Zoom to fit

		ClrRegion()
			:uid()
			, x(0)
			, y(0)
			, width(0)
			, height(0)
			, zOrder(0)
			, alpha(1.0)
			, renderMode(RenderMode::RENDER_MODE_HIDDEN)
		{}

		agora::rtc::VideoCompositingLayout::Region* toRaw() {
			VideoCompositingLayout::Region* result = new VideoCompositingLayout::Region();
			result->uid = MarshalString(uid).c_str(), result->x = x, result->y = y, result->width = width, result->height = height;
			result->zOrder = zOrder, result->alpha = alpha;
			return result;
		}

		static agora::rtc::VideoCompositingLayout::Region* toRaws(List<ClrRegion^>^ region) {
			int size = sizeof(VideoCompositingLayout::Region) * region->Count;
			VideoCompositingLayout::Region* result = static_cast<VideoCompositingLayout::Region*>(Marshal::AllocHGlobal(size).ToPointer());
			for (int i = 0; i < region->Count; i++) {
				result[i] = *region[i]->toRaw();
			}
			return result;
		}
	};

	public ref class ClrVideoCompositingLayout
	{
	public:
		int canvasWidth;
		int canvasHeight;
		String^ backgroundColor;//e.g. "#C0C0C0" in RGB
		List<ClrRegion^>^ regions;
		String^ appData;
		ClrVideoCompositingLayout()
			:canvasWidth(0)
			, canvasHeight(0)
			, backgroundColor(nullptr)
			, regions(nullptr)
			, appData(nullptr)
		{}

		agora::rtc::VideoCompositingLayout* toRaw() {
			VideoCompositingLayout* result = new VideoCompositingLayout();
			result->canvasHeight = canvasHeight, result->canvasWidth = canvasWidth;
			result->backgroundColor = MarshalString(backgroundColor).c_str();
			result->regions = ClrRegion::toRaws(regions), result->regionCount = regions->Count;
			result->appData = MarshalString(appData).c_str(), result->appDataLength = appData->Length;
			return result;
		}
	};

	public enum class RtmpStreamLifeCycleType
	{
		RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL = 1,
		RTMP_STREAM_LIFE_CYCLE_BIND2OWNER = 2,
	};

	public ref class ClrPublisherConfiguration {
	public:
		int width;
		int height;
		int framerate;
		int bitrate;
		int defaultLayout;
		RtmpStreamLifeCycleType lifecycle;
		bool owner;
		int injectStreamWidth = 0;
		int injectStreamHeight = 0;
		String^ injectStreamUrl = nullptr;
		String^ publishUrl = nullptr;
		String^ rawStreamUrl = nullptr;
		String^ extraInfo = nullptr;

		ClrPublisherConfiguration()
			: width(640)
			, height(360)
			, framerate(15)
			, bitrate(500)
			, defaultLayout(1)
			, lifecycle(RtmpStreamLifeCycleType::RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL)
			, owner(true)
		{}

		agora::rtc::PublisherConfiguration* toRaw() {
			PublisherConfiguration* result = new PublisherConfiguration();
			result->width = width; result->height = height;
			result->framerate = framerate; result->defaultLayout = defaultLayout;
			result->lifecycle = (RTMP_STREAM_LIFE_CYCLE_TYPE)lifecycle;
			result->owner = owner; result->publishUrl = MarshalString(publishUrl).c_str();
			result->injectStreamHeight = injectStreamHeight;
			result->injectStreamWidth = injectStreamWidth;
			result->injectStreamUrl = MarshalString(injectStreamUrl).c_str();
			result->publishUrl = MarshalString(publishUrl).c_str();
			result->rawStreamUrl = MarshalString(rawStreamUrl).c_str();
			result->extraInfo = MarshalString(extraInfo).c_str();
			return result;
		}
	};

	public ref class ClrRect {
	public:
		int top;
		int left;
		int bottom;
		int right;

		ClrRect() : top(0), left(0), bottom(0), right(0) {}
		ClrRect(int t, int l, int b, int r) : top(t), left(l), bottom(b), right(r) {}

		agora::rtc::Rect* toRaw() {
			agora::rtc::Rect* result = new agora::rtc::Rect();
			result->top = top;
			result->left = left;
			result->bottom = bottom;
			result->right = right;
			return result;
		}
	};

	public enum class AudioProfileType// sample rate, bit rate, mono/stereo, speech/music codec
	{
		AUDIO_PROFILE_DEFAULT = 0, // use default settings
		AUDIO_PROFILE_SPEECH_STANDARD = 1, // 32Khz, 18kbps, mono, speech
		AUDIO_PROFILE_MUSIC_STANDARD = 2, // 48Khz, 50kbps, mono, music
		AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3, // 48Khz, 50kbps, stereo, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4, // 48Khz, 128kbps, mono, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 128kbps, stereo, music
		AUDIO_PROFILE_NUM = 6,
	};

	public enum class AudioScenarioType// set a suitable scenario for your app type
	{
		AUDIO_SCENARIO_DEFAULT = 0,
		AUDIO_SCENARIO_CHATROOM = 1,
		AUDIO_SCENARIO_EDUCATION = 2,
		AUDIO_SCENARIO_GAME_STREAMING = 3,
		AUDIO_SCENARIO_SHOWROOM = 4,
		AUDIO_SCENARIO_NUM = 5,
	};



	//RtcEngineEventHandler Part
	public delegate void onJoinChannelSuccess(String ^channel, String^ uid, int elapsed);
	public delegate void onRejoinChannelSuccess(String ^channel, String^ uid, int elapsed);
	public delegate void onWarning(int warn, String ^msg);
	public delegate void onError(int err, String ^msg);
	public delegate void onAudioQuality(String^ uid, int quality, unsigned short delay, unsigned short lost);
	public delegate void onAudioVolumeIndication(List<AudioVolumeInfo^>^ speakers, int totalVolume);
	public delegate void onLeaveChannel(RtcStats ^stat);
	public delegate void onUserJoined(String^ uid, int elapsed);
	public delegate void onUserOffline(String^ uid, UserOfflineType reason);
	public delegate void onRtcStats(RtcStats ^stat);
	public delegate void onLocalVideoStats(LocalVideoStats ^stats);
	public delegate void onRemoteVideoStats(RemoteVideoStats ^stats);
	public delegate void onFirstLocalVideoFrame(int width, int height, int elapsed);
	public delegate void onFirstRemoteVideoDecoded(String^ uid, int width, int height, int elapsed);
	public delegate void onFirstRemoteVideoFrame(String^ uid, int width, int height, int elapsed);

	public delegate void onAudioDeviceStateChanged(String ^deviceid, int deviceType, int deviceState);
	public delegate void onVideoDeviceStateChanged(String ^deviceid, int deviceType, int deviceState);

	public delegate void onLastmileQuality(int quality);
	public delegate void onNetworkQuality(String^ uid, int txQuality, int rxQuality);

	public delegate void onUserMuteAudio(String^ uid, bool muted);
	public delegate void onUserMuteVideo(String^ uid, bool muted);
	public delegate void onUserEnableVideo(String^ uid, bool enabled);
	public delegate void onCameraReady();
	public delegate void onVideoStopped();
	public delegate void onConnectionInterrupted();
	public delegate void onConnectionLost();
	public delegate void onRefreshRecordingServiceStatus(int status);
	public delegate void onApiCallExecuted(String ^api, int error);
	public delegate void onStreamMessage(String^ uid, int streamId, String ^data);
	public delegate void onStreamMessageError(String^ uid, int streamId, int code, int missed, int cached);
	public delegate void onRequestChannelKey();
	public delegate void onAudioMixingFinished();

	public delegate void onActiveSpeaker(String^ uid);

	public delegate void onClientRoleChanged(ClientRoleType, ClientRoleType);
	public delegate void onAudioDeviceVolumeChanged(MediaDeviceType, int, bool);

	//PacketObserver Part
	public delegate bool onSendAudioPacket(ClrPacket^ packet);
	public delegate bool onSendVideoPacket(ClrPacket^ packet);
	public delegate bool onReceiveAudioPacket(ClrPacket^ packet);
	public delegate bool onReceiveVideoPacket(ClrPacket^ packet);

	//Raw Data Part
	public delegate bool onRecordAudioFrame(ClrAudioFrame^ frame);
	public delegate bool onPlaybackAudioFrame(ClrAudioFrame^ frame);
	public delegate bool onPlaybackAudioFrameBeforeMixing(String^ uid, ClrAudioFrame^ frame);
	public delegate bool onCaptureVideoFrame(ClrVideoFrame^ frame);
	public delegate bool onRenderVideoFrame(String^ uid, ClrVideoFrame^ frame);

	public ref class AgoraClr
	{
	public:
		AgoraClr();
		~AgoraClr();
		!AgoraClr();

		int initialize(String ^vendorkey);
		void release();

		int enableVideo();
		int disableVideo();

		int enableAudio();
		int disableAudio();
		int setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate);

		int startPreview();
		int stopPreview();

		int enableWebSdkInteroperability(bool enabled);

		int joinChannel(String ^channelKey, String ^channelName, String ^channelInfo, String^ uid);
		int leaveChannel();

		int startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect);
		int stopScreenCapture();
		int updateScreenCaptureRegion(ClrRect^ rect);

		int renewChannelKey(String ^channelKey);

		int setEncryptionSecret(String ^key);
		int setEncryptionMode(String ^mode);


		int getCallId(String^ %callid);
		int rate(String ^callid, int rating, String ^desc);
		int complain(String ^callid, String ^desc);
		int startEchoTest();
		int stopEchoTest();
		int enableLastmileTest();
		int disableLastmileTest();

		int setVideoProfile(VideoProfile profile, bool swapWidthAndHeight);
		int setupLocalVideo(IntPtr view, int renderMode, String^ uid);
		int setupRemoteVideo(IntPtr view, int renderMode, String^ uid);
		int enableDualStreamMode(bool enabled);
		int setRemoteVideoStreamType(String^ uid, RemoteVideoStreamType type);
		int setVideoQualityParameters(bool preferFrameRateOverImageQuality);
		int setVideoCompositingLayout(ClrVideoCompositingLayout^ sei);
		int clearVideoCompositingLayout();
		int configPublisher(ClrPublisherConfiguration^ config);
		int setChannelProfile(ChannelProfile profile);
		int setClientRole(ClientRoleType role, String^ permissionKey);

		int createDataStream(int %id);
		int sendStreamMessage(int id, String ^data);

		//原始数据API
		//RtcEngineParameters Part
		int setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);

		int muteLocalAudioStream(bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		int muteRemoteAudioStream(String^ uid, bool mute);
		int muteLocalVideoStream(bool mute);
		int enableLocalVideo(bool enabled);
		int muteAllRemoteVideoStream(bool mute);
		int muteRemoteVideoStream(String^ uid, bool mute);
		int setPlaybackDeviceVolume(int volume);
		int setLocalRenderMode(RenderMode mode);
		int setRemoteRenderMode(String^ uid, RenderMode mode);
		int enableAudioVolumeIndication(int interval, int smooth);
		int startAudioRecording(String ^path, AudioRecordingQualityType quality);
		int stopAudioRecording();
		int pauseAudioMixing();
		int resumeAudioMixing();
		int adjustAudioMixingVolume(int volume);
		int getAudioMixingDuration();
		int getAudioMixingCurrentPosition();
		int setAudioMixingPosition(int pos);
		int startAudioMixing(String ^path, bool loop, bool replace, int cycle);
		int stopAudioMixing();
		int setAudioProfile(AudioProfileType profile, AudioScenarioType scenario);
		int setLogFile(String ^path);
		int setLogFilter(unsigned int filter);
		int startRecordingService(String ^key);
		int stopRecordingService(String ^key);
		int refreshRecordingServiceStatus();
		int adjustRecodingSignalVolumne(int volume);
		int adjustPlaybackSignalVolume(int volume);

		int setLocalVoicePitch(double pitch);
		int setInEarMonitoringVolume(int volume);

		int setExternalAudioSource(bool enabled, int sampleRate, int channels);

		AgoraClrAudioDeviceManager^ getAudioDeviceManager();
		AgoraClrVideoDeviceManager^ getVideoDeviceManager();
		IRtcEngine* getEngine();

		//RtcEngineEventHandler Part
		onJoinChannelSuccess ^onJoinChannelSuccess;
		onRejoinChannelSuccess ^onRejoinChannelSuccess;
		onWarning ^onWarning;
		onError ^onError;
		onAudioQuality ^onAudioQuality;
		onAudioVolumeIndication ^onAudioVolumeIndication;
		onLeaveChannel ^onLeaveChannel;
		onUserJoined ^onUserJoined;
		onUserOffline ^onUserOffline;
		onRtcStats ^onRtcStats;
		onLocalVideoStats ^onLocalVideoStats;
		onRemoteVideoStats ^onRemoteVideoStats;
		onFirstLocalVideoFrame ^onFirstLocalVideoFrame;
		onFirstRemoteVideoDecoded ^onFirstRemoteVideoDecoded;
		onFirstRemoteVideoFrame ^onFirstRemoteVideoFrame;
		onAudioDeviceStateChanged ^onAudioDeviceStateChanged;
		onVideoDeviceStateChanged ^onVideoDeviceStateChanged;
		onLastmileQuality ^onLastmileQuality;
		onNetworkQuality^ onNetworkQuality;
		onUserMuteAudio ^onUserMuteAudio;
		onUserMuteVideo ^onUserMuteVideo;
		onUserEnableVideo ^onUserEnableVideo;
		onCameraReady ^onCameraReady;
		onVideoStopped ^onVideoStopped;
		onConnectionInterrupted ^onConnectionInterrupted;
		onConnectionLost ^onConnectionLost;
		onRefreshRecordingServiceStatus ^onRefreshRecordingServiceStatus;
		onApiCallExecuted ^onApiCallExecuted;
		onStreamMessage ^onStreamMessage;
		onStreamMessageError ^onStreamMessageError;
		onRequestChannelKey^ onRequestChannelKey;
		onAudioMixingFinished^ onAudioMixingFinished;

		onActiveSpeaker^ onActiveSpeaker;

		onClientRoleChanged^ onClientRoleChanged;
		onAudioDeviceVolumeChanged^ onAudioDeviceVolumeChanged;

		//PacketObserver Part
		onSendAudioPacket ^onSendAudioPacket;
		onSendVideoPacket ^onSendVideoPacket;
		onReceiveAudioPacket ^onReceiveAudioPacket;
		onReceiveVideoPacket ^onReceiveVideoPacket;

		//Raw data Part
		onRecordAudioFrame ^onRecordAudioFrame;
		onPlaybackAudioFrame ^onPlaybackAudioFrame;
		onPlaybackAudioFrameBeforeMixing ^onPlaybackAudioFrameBeforeMixing;
		onCaptureVideoFrame ^onCaptureVideoFrame;
		onRenderVideoFrame ^onRenderVideoFrame;

	private:
		agora::rtc::IRtcEngine *rtcEngine;

		AgoraClrEventHandler *agoraEventHandler;
		AgoraClrPacketObserver *agoraPacketObserver;
		AgoraClrRawFrameObserver *agoraRawObserver;

		List<GCHandle> ^gchs;

		//Native Agora Event Handler
		void NativeOnJoinChannelSuccess(const char* channel, const char* uid, int elapsed);
		void NativeOnRejoinChannelSuccess(const char* channel, const char* uid, int elapsed);
		void NativeOnWarning(int warn, const char* msg);
		void NativeOnError(int err, const char* msg);
		void NativeOnAudioQuality(const char* uid, int quality, unsigned short delay, unsigned short lost);
		void NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
		void NativeOnLeaveChannel(const agora::rtc::RtcStats& stats);
		void NativeOnRtcStats(const agora::rtc::RtcStats& stats);
		void NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnLastmileQuality(int quality);
		void NativeOnNetworkQuality(const char* uid, int txQuality, int rxQuality);
		void NativeOnFirstLocalVideoFrame(int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoDecoded(const char* uid, int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoFrame(const char* uid, int width, int height, int elapsed);
		void NativeOnUserJoined(const char* uid, int elapsed);
		void NativeOnUserOffline(const char* uid, USER_OFFLINE_REASON_TYPE reason);
		void NativeOnUserMuteAudio(const char* uid, bool muted);
		void NativeOnUserMuteVideo(const char* uid, bool muted);
		void NativeOnUserEnableVideo(const char* uid, bool enabled);
		void NativeOnApiCallExecuted(const char* api, int error);
		void NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats);
		void NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats);
		void NativeOnCameraReady();
		void NativeOnVideoStopped();
		void NativeOnConnectionLost();
		void NativeOnConnectionInterrupted();
		void NativeOnRefreshRecordingServiceStatus(int status);
		void NativeOnStreamMessage(const char* uid, int streamId, const char* data, size_t length);
		void NativeOnStreamMessageError(const char* uid, int streamId, int code, int missed, int cached);
		void NativeOnRequestChannelKey();
		void NativeOnAudioMixingFinished();

		void NativeOnActiveSpeaker(const char* uid);
		
		void NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
		void NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);

		bool NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet);

		bool NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrameBeforeMixing(const char* uid, agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnRenderVideoFrame(const char* uid, agora::media::IVideoFrameObserver::VideoFrame& frame);

		void initializeEventHandler();
		void initializePacketObserver();
		void initializeRawFrameObserver();
		void* regEvent(Object^ obj);



	};
}
