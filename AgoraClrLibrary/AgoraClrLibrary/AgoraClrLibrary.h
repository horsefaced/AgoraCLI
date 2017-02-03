// AgoraClrLibrary.h

#pragma once
#include "include\IAgoraRtcEngine.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Collections::Generic;

namespace AgoraClrLibrary {

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

	public enum class RenderMode
	{
		RENDER_MODE_HIDDEN = 1,
		RENDER_MODE_FIT = 2,
		RENDER_MODE_ADAPTIVE = 3,
	};

	public ref class AudioVolumeInfo
	{
	public:
		int uid;
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
		unsigned int users;
		double cpuAppUsage;
		double cpuTotalUsage;
	};

	public enum class UserOfflineType
	{
		USER_OFFLINE_QUIT = 0,
		USER_OFFLINE_DROPPED = 1,
	};

	public enum class RawAudioFrameOPModeType
	{
		RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
		RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
		RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
	};

	public ref class LocalVideoStats
	{
	public:
		int sentBitrate;
		int sentFrameRate;
	};

	public ref class RemoteVideoStats
	{
	public:
		int uid;
		int delay;
		int width;
		int height;
		int receivedBitrate;
		int receivedFrameRate;
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

	public ref struct ClrAudioFrame {
		ClrAudioFrameType type;
		int samples;  //number of samples in this frame
		int bytesPerSample;  //number of bytes per sample: 2 for PCM16
		int channels;  //声道数
		int samplesPerSec;  //采样率
		array<Byte>^ data;
		int64_t renderTimeMs;

		ClrAudioFrame(agora::media::IAudioFrameObserver::AudioFrame raw) {
			type = (ClrAudioFrameType)raw.type, samples = raw.samples, bytesPerSample = raw.bytesPerSample, channels = raw.channels,
				samplesPerSec = raw.samplesPerSec, renderTimeMs = raw.renderTimeMs;

			data = gcnew array<Byte>(samples * bytesPerSample);
			Marshal::Copy(IntPtr(raw.buffer), data, 0, samples * bytesPerSample);
		}

		void writeRaw(agora::media::IAudioFrameObserver::AudioFrame & raw) {
			bool sizeModified = (samples * bytesPerSample) == (raw.samples * raw.bytesPerSample);
			raw.type = (agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE)type, raw.samples = samples, raw.bytesPerSample = bytesPerSample,
				raw.channels = channels, raw.samplesPerSec = samplesPerSec, raw.renderTimeMs = renderTimeMs;
			if (sizeModified) raw.buffer = Marshal::AllocHGlobal(samples * bytesPerSample).ToPointer();
			Marshal::Copy(data, 0, IntPtr(raw.buffer), samples * bytesPerSample);
		}
	};

	public enum class ClrVideoFrameType {
		FRAME_TYPE_YUV420 = 0,  //YUV 420 format
	};

	public ref struct ClrVideoFrame {
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

		ClrVideoFrame(agora::media::IVideoFrameObserver::VideoFrame raw) {
			type = (ClrVideoFrameType)raw.type;
			width = raw.width, height = raw.height, yStride = raw.yStride, uStride = raw.uStride, vStride = raw.vStride;
			rotation = raw.rotation, renderTimeMs = raw.renderTimeMs;

			int size = width + height;
			ybuffer = gcnew array<Byte>(size);
			Marshal::Copy(IntPtr(raw.yBuffer), ybuffer, 0, size);
			ubuffer = gcnew array<Byte>(size / 4);
			Marshal::Copy(IntPtr(raw.uBuffer), ubuffer, 0, size / 4);
			vbuffer = gcnew array<Byte>(size / 4);
			Marshal::Copy(IntPtr(raw.vBuffer), vbuffer, 0, size / 4);
		}

		void writeRaw(agora::media::IVideoFrameObserver::VideoFrame & raw) {
			int sizeModified = (raw.width + raw.height) == (width + height);
			raw.type = (agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE)type, raw.width = width, raw.height = height;
			raw.yStride = yStride, raw.uStride = uStride, raw.vStride = vStride, raw.rotation = rotation, raw.renderTimeMs = renderTimeMs;

			int size = width + height;
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

	//RtcEngineEventHandler Part
	public delegate void onJoinChannelSuccess(String ^channel, int uid, int elapsed);
	public delegate void onRejoinChannelSuccess(String ^channel, int uid, int elapsed);
	public delegate void onWarning(int warn, String ^msg);
	public delegate void onError(int err, String ^msg);
	public delegate void onAudioQuality(int uid, int quality, unsigned short delay, unsigned short lost);
	public delegate void onAudioVolumeIndication(List<AudioVolumeInfo^>^ speakers, int totalVolume);
	public delegate void onLeaveChannel(RtcStats ^stat);
	public delegate void onUserJoined(int uid, int elapsed);
	public delegate void onUserOffline(int uid, UserOfflineType reason);
	public delegate void onRtcStats(RtcStats ^stat);
	public delegate void onLocalVideoStats(LocalVideoStats ^stats);
	public delegate void onRemoteVideoStats(RemoteVideoStats ^stats);
	public delegate void onFirstLocalVideoFrame(int width, int height, int elapsed);
	public delegate void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed);
	public delegate void onFirstRemoteVideoFrame(int uid, int width, int height, int elapsed);
	public delegate void onAudioDeviceStateChanged(String ^deviceid, int deviceType, int deviceState);
	public delegate void onVideoDeviceStateChanged(String ^deviceid, int deviceType, int deviceState);
	public delegate void onLastmileQuality(int quality);
	public delegate void onUserMuteAudio(int uid, bool muted);
	public delegate void onUserMuteVideo(int uid, bool muted);
	public delegate void onUserEnableVideo(int uid, bool enabled);
	public delegate void onCameraReady();
	public delegate void onVideoStopped();
	public delegate void onConnectionInterrupted();
	public delegate void onConnectionLost();
	public delegate void onRefreshRecordingServiceStatus(int status);
	public delegate void onApiCallExecuted(String ^api, int error);
	public delegate void onStreamMessage(int uid, int streamId, String ^data);
	public delegate void onStreamMessageError(int uid, int streamId, int code, int missed, int cached);
	
	//PacketObserver Part
	public delegate bool onSendAudioPacket(ClrPacket^& packet);
	public delegate bool onSendVideoPacket(ClrPacket^& packet);
	public delegate bool onReceiveAudioPacket(ClrPacket^& packet);
	public delegate bool onReceiveVideoPacket(ClrPacket^& packet);

	//Raw Data Part
	public delegate bool onRecodingAudioFrame(ClrAudioFrame^& frame);
	public delegate bool onPlaybackAudioFrame(ClrAudioFrame^& frame);
	public delegate bool onPlaybackAudioFrameBeforeMixing(int uid, ClrAudioFrame^& frame);
	public delegate bool onCaptureVideoFrame(ClrVideoFrame^& frame);
	public delegate bool onRenderVideoFrame(int uid, ClrVideoFrame^& frame);

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

		int startPreview();
		int stopPreview();

		int joinChannel(String ^channelKey, String ^channelName, String ^channelInfo, int uid);
		int leaveChannel();

		int startScreenCapture(IntPtr windowId);
		int setScreenCaptureWindow(IntPtr windowId);
		int stopScreenCapture();

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
		int setupLocalVideo(IntPtr view, int renderMode, int uid);
		int setupRemoteVideo(IntPtr view, int renderMode, int uid);
		int setChannelProfile(ChannelProfile profile);

		int createDataStream(int %id);
		int sendStreamMessage(int id, String ^data);

		//原始数据API
		//RtcEngineParameters Part
		int setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);

		int muteLocalAudioStream(bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		int muteRemoteAudioStream(int uid, bool mute);
		int muteLocalVideoStream(bool mute);
		int enableLocalVideo(bool enabled);
		int muteAllRemoteVideoStream(bool mute);
		int muteRemoteVideoStream(int uid, bool mute);
		int setPlaybackDeviceVolume(int volume);
		int setLocalRenderMode(RenderMode mode);
		int setRemoteRenderMode(int uid, RenderMode mode);
		int enableAudioVolumeIndication(int interval, int smooth);
		int startAudioRecording(String ^path);
		int stopAudioRecording();
		int pauseAudioMixing();
		int resumeAudioMixing();
		int adjustAudioMixingVolume(int volume);
		int getAudioMixingDuration();
		int getAudioMixingCurrentPosition();
		int startAudioMixing(String ^path, bool loop, bool replace, int cycle);
		int stopAudioMixing();
		int setLogFile(String ^path);
		int setLogFilter(unsigned int filter);
		int startRecordingService(String ^key);
		int stopRecordingService(String ^key);
		int refreshRecordingServiceStatus();
		int adjustRecodingSignalVolumne(int volume);
		int adjustPlaybackSignalVolume(int volume);


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

		//PacketObserver Part
		onSendAudioPacket ^onSendAudioPacket;
		onSendVideoPacket ^onSendVideoPacket;
		onReceiveAudioPacket ^onReceiveAudioPacket;
		onReceiveVideoPacket ^onReceiveVideoPacket;

		//Raw data Part
		onRecodingAudioFrame ^onRecodingAudioFrame;
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
		void NativeOnJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		void NativeOnRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		void NativeOnWarning(int warn, const char* msg);
		void NativeOnError(int err, const char* msg);
		void NativeOnAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
		void NativeOnAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
		void NativeOnLeaveChannel(const agora::rtc::RtcStats& stats);
		void NativeOnRtcStats(const agora::rtc::RtcStats& stats);
		void NativeOnAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		void NativeOnLastmileQuality(int quality);
		void NativeOnFirstLocalVideoFrame(int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
		void NativeOnFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
		void NativeOnUserJoined(uid_t uid, int elapsed);
		void NativeOnUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
		void NativeOnUserMuteAudio(uid_t uid, bool muted);
		void NativeOnUserMuteVideo(uid_t uid, bool muted);
		void NativeOnUserEnableVideo(uid_t uid, bool enabled);
		void NativeOnApiCallExecuted(const char* api, int error);
		void NativeOnLocalVideoStats(const agora::rtc::LocalVideoStats& stats);
		void NativeOnRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats);
		void NativeOnCameraReady();
		void NativeOnVideoStopped();
		void NativeOnConnectionLost();
		void NativeOnConnectionInterrupted();
		void NativeOnRefreshRecordingServiceStatus(int status);
		void NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length);
		void NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached);

		bool NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet);

		bool NativeOnRecodingAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& frame);

		void initializeEventHandler();
		void initializePacketObserver();
		void initializeRawFrameObserver();
		void* regEvent(Object^ obj);

		static std::string MarshalString(String ^s) {
			if (s == nullptr) return std::string();
			IntPtr middleStr = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
			std::string result((char *)middleStr.ToPointer());
			Runtime::InteropServices::Marshal::FreeHGlobal(middleStr);
			return result;
		}


	};
}
