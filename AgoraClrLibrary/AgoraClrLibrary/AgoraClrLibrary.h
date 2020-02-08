// AgoraClrLibrary.h

#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace agora::rtc;

namespace AgoraClrLibrary
{

	static std::string&& MarshalString(String^ s)
	{
		if (s == nullptr)
			return std::string();
		IntPtr middleStr = Runtime::InteropServices::Marshal::StringToHGlobalUni(s);
		std::string result(reinterpret_cast<char*>(middleStr.ToPointer()));
		Runtime::InteropServices::Marshal::FreeHGlobal(middleStr);
		return result;
	}

	public
		enum class VideoProfile
	{										   // res       fps  kbps
		VIDEO_PROFILE_LANDSCAPE_120P = 0,	  // 160x120   15
		VIDEO_PROFILE_LANDSCAPE_120P_3 = 2,	// 120x120   15
		VIDEO_PROFILE_LANDSCAPE_180P = 10,	 // 320x180   15
		VIDEO_PROFILE_LANDSCAPE_180P_3 = 12,   // 180x180   15
		VIDEO_PROFILE_LANDSCAPE_180P_4 = 13,   // 240x180   15
		VIDEO_PROFILE_LANDSCAPE_240P = 20,	 // 320x240   15
		VIDEO_PROFILE_LANDSCAPE_240P_3 = 22,   // 240x240   15
		VIDEO_PROFILE_LANDSCAPE_240P_4 = 23,   // 424x240   15
		VIDEO_PROFILE_LANDSCAPE_360P = 30,	 // 640x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_3 = 32,   // 360x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_4 = 33,   // 640x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_6 = 35,   // 360x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_7 = 36,   // 480x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_8 = 37,   // 480x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_9 = 38,   // 640x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_10 = 39,  // 640x360   24
		VIDEO_PROFILE_LANDSCAPE_360P_11 = 100, // 640x360   24
		VIDEO_PROFILE_LANDSCAPE_480P = 40,	 // 640x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_3 = 42,   // 480x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_4 = 43,   // 640x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_6 = 45,   // 480x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_8 = 47,   // 848x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_9 = 48,   // 848x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_10 = 49,  // 640x480   10
		VIDEO_PROFILE_LANDSCAPE_720P = 50,	 // 1280x720  15
		VIDEO_PROFILE_LANDSCAPE_720P_3 = 52,   // 1280x720  30
		VIDEO_PROFILE_LANDSCAPE_720P_5 = 54,   // 960x720   15
		VIDEO_PROFILE_LANDSCAPE_720P_6 = 55,   // 960x720   30
		VIDEO_PROFILE_LANDSCAPE_1080P = 60,	// 1920x1080 15
		VIDEO_PROFILE_LANDSCAPE_1080P_3 = 62,  // 1920x1080 30
		VIDEO_PROFILE_LANDSCAPE_1080P_5 = 64,  // 1920x1080 60
		VIDEO_PROFILE_LANDSCAPE_1440P = 66,	// 2560x1440 30
		VIDEO_PROFILE_LANDSCAPE_1440P_2 = 67,  // 2560x1440 60
		VIDEO_PROFILE_LANDSCAPE_4K = 70,	   // 3840x2160 30
		VIDEO_PROFILE_LANDSCAPE_4K_3 = 72,	 // 3840x2160 60

		VIDEO_PROFILE_PORTRAIT_120P = 1000,	// 120x160   15
		VIDEO_PROFILE_PORTRAIT_120P_3 = 1002,  // 120x120   15
		VIDEO_PROFILE_PORTRAIT_180P = 1010,	// 180x320   15
		VIDEO_PROFILE_PORTRAIT_180P_3 = 1012,  // 180x180   15
		VIDEO_PROFILE_PORTRAIT_180P_4 = 1013,  // 180x240   15
		VIDEO_PROFILE_PORTRAIT_240P = 1020,	// 240x320   15
		VIDEO_PROFILE_PORTRAIT_240P_3 = 1022,  // 240x240   15
		VIDEO_PROFILE_PORTRAIT_240P_4 = 1023,  // 240x424   15
		VIDEO_PROFILE_PORTRAIT_360P = 1030,	// 360x640   15
		VIDEO_PROFILE_PORTRAIT_360P_3 = 1032,  // 360x360   15
		VIDEO_PROFILE_PORTRAIT_360P_4 = 1033,  // 360x640   30
		VIDEO_PROFILE_PORTRAIT_360P_6 = 1035,  // 360x360   30
		VIDEO_PROFILE_PORTRAIT_360P_7 = 1036,  // 360x480   15
		VIDEO_PROFILE_PORTRAIT_360P_8 = 1037,  // 360x480   30
		VIDEO_PROFILE_PORTRAIT_360P_9 = 1038,  // 360x640   15
		VIDEO_PROFILE_PORTRAIT_360P_10 = 1039, // 360x640   24
		VIDEO_PROFILE_PORTRAIT_360P_11 = 1100, // 360x640   24
		VIDEO_PROFILE_PORTRAIT_480P = 1040,	// 480x640   15
		VIDEO_PROFILE_PORTRAIT_480P_3 = 1042,  // 480x480   15
		VIDEO_PROFILE_PORTRAIT_480P_4 = 1043,  // 480x640   30
		VIDEO_PROFILE_PORTRAIT_480P_6 = 1045,  // 480x480   30
		VIDEO_PROFILE_PORTRAIT_480P_8 = 1047,  // 480x848   15
		VIDEO_PROFILE_PORTRAIT_480P_9 = 1048,  // 480x848   30
		VIDEO_PROFILE_PORTRAIT_480P_10 = 1049, // 480x640   10
		VIDEO_PROFILE_PORTRAIT_720P = 1050,	// 720x1280  15
		VIDEO_PROFILE_PORTRAIT_720P_3 = 1052,  // 720x1280  30
		VIDEO_PROFILE_PORTRAIT_720P_5 = 1054,  // 720x960   15
		VIDEO_PROFILE_PORTRAIT_720P_6 = 1055,  // 720x960   30
		VIDEO_PROFILE_PORTRAIT_1080P = 1060,   // 1080x1920 15
		VIDEO_PROFILE_PORTRAIT_1080P_3 = 1062, // 1080x1920 30
		VIDEO_PROFILE_PORTRAIT_1080P_5 = 1064, // 1080x1920 60
		VIDEO_PROFILE_PORTRAIT_1440P = 1066,   // 1440x2560 30
		VIDEO_PROFILE_PORTRAIT_1440P_2 = 1067, // 1440x2560 60
		VIDEO_PROFILE_PORTRAIT_4K = 1070,	  // 2160x3840 30
		VIDEO_PROFILE_PORTRAIT_4K_3 = 1072,	// 2160x3840 60
		VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_LANDSCAPE_360P,
	};

	public
		enum class ChannelProfile
	{
		CHANNEL_PROFILE_COMMUNICATION = 0,
		CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
		CHANNEL_PROFILE_GAME = 2,
	};

	public
		enum class ClientRoleType
	{
		CLIENT_ROLE_BROADCASTER = 1,
		CLIENT_ROLE_AUDIENCE = 2,
	};

	public
		enum class RenderMode
	{
		RENDER_MODE_HIDDEN = 1,
		RENDER_MODE_FIT = 2,
		RENDER_MODE_ADAPTIVE = 3,
	};

	public
	ref class AudioVolumeInfo
	{
	public:
		int uid;
		unsigned int volume; // [0,255]
	};

	public
	ref class RtcStats
	{
	public:
		unsigned int duration;
		unsigned int txBytes;
		unsigned int rxBytes;

		unsigned int txAudioBytes;
		unsigned int txVideoBytes;

		unsigned int rxAudioBytes;
		unsigned int rxVideoBytes;

		unsigned short txKBitRate;
		unsigned short rxKBitRate;

		unsigned short rxAudioKBitRate;
		unsigned short txAudioKBitRate;

		unsigned short rxVideoKBitRate;
		unsigned short txVideoKBitRate;

		unsigned short lastmileDelay;

		unsigned short txPacketLossRate;
		unsigned short rxPacketLossRate;

		unsigned int userCount;
		double cpuAppUsage;
		double cpuTotalUsage;

		RtcStats(agora::rtc::RtcStats raw)
		{
			duration = raw.duration;
			rxBytes = raw.rxBytes;
			txBytes = raw.txBytes;

			txAudioBytes = raw.txAudioBytes;
			txVideoBytes = raw.txVideoBytes;

			rxAudioBytes = raw.rxAudioBytes;
			rxVideoBytes = raw.rxVideoBytes;

			txKBitRate = raw.txKBitRate;
			rxKBitRate = raw.rxKBitRate;

			rxAudioKBitRate = raw.rxAudioKBitRate;
			txAudioKBitRate = raw.txAudioKBitRate;

			rxVideoKBitRate = raw.rxVideoKBitRate;
			txVideoKBitRate = raw.txVideoKBitRate;

			lastmileDelay = raw.lastmileDelay;

			txPacketLossRate = raw.txPacketLossRate;
			rxPacketLossRate = raw.rxPacketLossRate;

			cpuAppUsage = raw.cpuAppUsage;
			cpuTotalUsage = raw.cpuTotalUsage;
			userCount = raw.userCount;
		}
	};

	public
		enum class UserOfflineType
	{
		USER_OFFLINE_QUIT = 0,
		USER_OFFLINE_DROPPED = 1,
		USER_OFFLINE_BECOME_AUDIENCE = 2,
	};

	public
		enum class RawAudioFrameOPModeType
	{
		RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
		RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
		RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
	};
	public
		enum class AudioRecordingQualityType
	{
		AUDIO_RECORDING_QUALITY_LOW = 0,
		AUDIO_RECORDING_QUALITY_MEDIUM = 1,
		AUDIO_RECORDING_QUALITY_HIGH = 2,
	};

	public enum class QualityAdaptIndication
	{
		/** The quality of the local video stays the same. */
		ADAPT_NONE = 0,
		/** The quality improves because the network bandwidth increases. */
		ADAPT_UP_BANDWIDTH = 1,
		/** The quality worsens because the network bandwidth decreases. */
		ADAPT_DOWN_BANDWIDTH = 2,
	};

	public enum class VideoCodecType
	{
		/** Standard VP8 */
		VIDEO_CODEC_VP8 = 1,
		/** Standard H264 */
		VIDEO_CODEC_H264 = 2,
		/** Enhanced VP8 */
		VIDEO_CODEC_EVP = 3,
		/** Enhanced H264 */
		VIDEO_CODEC_E264 = 4,
	};

	public
	ref class ClrLocalVideoStats
	{
	public:
		int sentBitrate;
		int sentFrameRate;
		int encoderOutputFrameRate;
		int rendererOutputFrameRate;
		int targetBitrate;
		int targetFrameRate;
		QualityAdaptIndication qualityAdaptIndication;
		int encodedBitrate;
		int encodedFrameWidth;
		int encodedFrameHeight;
		int encodedFrameCount;
		VideoCodecType codecType;

		ClrLocalVideoStats(const LocalVideoStats& stats) :
			sentBitrate(stats.sentBitrate),
			sentFrameRate(stats.sentFrameRate),
			encoderOutputFrameRate(stats.encoderOutputFrameRate),
			rendererOutputFrameRate(stats.rendererOutputFrameRate),
			targetBitrate(stats.targetBitrate),
			targetFrameRate(stats.targetFrameRate),
			qualityAdaptIndication((QualityAdaptIndication)stats.qualityAdaptIndication),
			encodedBitrate(stats.encodedBitrate),
			encodedFrameWidth(stats.encodedFrameWidth),
			encodedFrameHeight(stats.encodedFrameHeight),
			encodedFrameCount(stats.encodedFrameCount),
			codecType((VideoCodecType)stats.codecType)
		{}
	};

	public
		enum class RemoteVideoStreamType
	{
		REMOTE_VIDEO_STREAM_HIGH = 0,
		REMOTE_VIDEO_STREAM_LOW = 1,
	};

	public
		enum class MediaDeviceType
	{
		UNKNOWN_AUDIO_DEVICE = -1,
		AUDIO_PLAYOUT_DEVICE = 0,
		AUDIO_RECORDING_DEVICE = 1,
		VIDEO_RENDER_DEVICE = 2,
		VIDEO_CAPTURE_DEVICE = 3,
		AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
	};

	public
	ref class RemoteVideoStats
	{
	public:
		int uid;
		int delay;
		int width;
		int height;
		int receivedBitrate;
		int decoderOutputFrameRate;
		int rendererOutputFrameRate;
		int packedLossRate;

		RemoteVideoStreamType rxStreamType;

		int totalFrozenTime;
		int frozenRate;

		RemoteVideoStats(agora::rtc::RemoteVideoStats stats)
		{
			uid = stats.uid;
			delay = stats.delay;
			width = stats.width;
			height = stats.height;
			receivedBitrate = stats.receivedBitrate;
			decoderOutputFrameRate = stats.decoderOutputFrameRate;
			rendererOutputFrameRate = stats.rendererOutputFrameRate;
			packedLossRate = stats.packetLossRate;

			rxStreamType = (RemoteVideoStreamType)stats.rxStreamType;

			totalFrozenTime = stats.totalFrozenTime;
			frozenRate = stats.frozenRate;
		}
	};

	public
	ref class ClrPacket
	{
	public:
		array<unsigned char>^ buffer;

		ClrPacket() {}
		ClrPacket(IPacketObserver::Packet& packet)
		{
			this->buffer = gcnew array<unsigned char>(packet.size);
			Marshal::Copy(IntPtr(const_cast<void*>(static_cast<const void*>(packet.buffer))), this->buffer, 0, packet.size);
		}

		void writePacket(IPacketObserver::Packet& packet)
		{
			int size = Marshal::SizeOf(buffer[0]) * buffer->Length;
			IntPtr rawBuffer = Marshal::AllocHGlobal(size);
			Marshal::Copy(buffer, 0, rawBuffer, buffer->Length);
			packet.buffer = (unsigned char*)rawBuffer.ToPointer();
			packet.size = buffer->Length;
		}
	};

	public
		enum class ClrAudioFrameType
	{
		FRAME_TYPE_PCM16 = 0, //PCM 16bit little endian
	};

	public
	ref class ClrAudioFrame
	{
	public:
		ClrAudioFrameType type;
		int samples;		//number of samples in this frame
		int bytesPerSample; //number of bytes per sample: 2 for PCM16
		int channels;		//ÉùµÀÊý
		int samplesPerSec;  //²ÉÑùÂÊ
		array<Byte>^ data;
		int64_t renderTimeMs;

		ClrAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& raw)
		{
			type = (ClrAudioFrameType)raw.type, samples = raw.samples, bytesPerSample = raw.bytesPerSample, channels = raw.channels,
				samplesPerSec = raw.samplesPerSec, renderTimeMs = raw.renderTimeMs;

			data = gcnew array<Byte>(samples * bytesPerSample);
			Marshal::Copy(IntPtr(raw.buffer), data, 0, samples * bytesPerSample);
		}

		void writeRaw(agora::media::IAudioFrameObserver::AudioFrame& raw)
		{
			bool sizeModified = (samples * bytesPerSample) != (raw.samples * raw.bytesPerSample);
			raw.type = (agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE)type, raw.samples = samples, raw.bytesPerSample = bytesPerSample,
				raw.channels = channels, raw.samplesPerSec = samplesPerSec, raw.renderTimeMs = renderTimeMs;
			if (sizeModified)
				raw.buffer = Marshal::AllocHGlobal(samples * bytesPerSample).ToPointer();
			Marshal::Copy(data, 0, IntPtr(raw.buffer), samples * bytesPerSample);
		}

		agora::media::IAudioFrameObserver::AudioFrame* toRaw()
		{
			agora::media::IAudioFrameObserver::AudioFrame* raw = new agora::media::IAudioFrameObserver::AudioFrame();
			writeRaw(*raw);
			return raw;
		}
	};

	public
		enum class ClrVideoFrameType
	{
		FRAME_TYPE_YUV420 = 0, //YUV 420 format
	};

	public
	ref class ClrVideoFrame
	{
	public:
		ClrVideoFrameType type;
		int width;   //width of video frame
		int height;  //height of video frame
		int yStride; //stride of Y data buffer
		int uStride; //stride of U data buffer
		int vStride; //stride of V data buffer
		array<Byte>^ ybuffer;
		array<Byte>^ ubuffer;
		array<Byte>^ vbuffer;
		int rotation; // rotation of this frame (0, 90, 180, 270)
		int64_t renderTimeMs;

		ClrVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& raw)
		{
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

		void writeRaw(agora::media::IVideoFrameObserver::VideoFrame& raw)
		{
			int sizeModified = (raw.width * raw.height) != (width * height);

			raw.type = (agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE)type, raw.width = width, raw.height = height;
			raw.yStride = yStride, raw.uStride = uStride, raw.vStride = vStride, raw.rotation = rotation, raw.renderTimeMs = renderTimeMs;

			int size = width * height;
			if (sizeModified)
			{
				raw.yBuffer = Marshal::AllocHGlobal(size).ToPointer();
				raw.uBuffer = Marshal::AllocHGlobal(size / 4).ToPointer();
				raw.vBuffer = Marshal::AllocHGlobal(size / 4).ToPointer();
			}
			Marshal::Copy(ybuffer, 0, IntPtr(raw.yBuffer), size);
			Marshal::Copy(ubuffer, 0, IntPtr(raw.uBuffer), size / 4);
			Marshal::Copy(vbuffer, 0, IntPtr(raw.vBuffer), size / 4);
		}
	};

	public
	ref class ClrRegion
	{
	public:
		int uid;
		double x;	  //[0,1]
		double y;	  //[0,1]
		double width;  //[0,1]
		double height; //[0,1]
		int zOrder;	//optional, [0, 100] //0 (default): bottom most, 100: top most

		//  Optional
		//  [0, 1.0] where 0 denotes throughly transparent, 1.0 opaque
		double alpha;

		RenderMode renderMode; //RENDER_MODE_HIDDEN: Crop, RENDER_MODE_FIT: Zoom to fit

		ClrRegion()
			: uid(0), x(0), y(0), width(0), height(0), zOrder(0), alpha(1.0), renderMode(RenderMode::RENDER_MODE_HIDDEN)
		{
		}

		agora::rtc::VideoCompositingLayout::Region* toRaw()
		{
			VideoCompositingLayout::Region* result = new VideoCompositingLayout::Region();
			result->uid = uid, result->x = x, result->y = y, result->width = width, result->height = height;
			result->zOrder = zOrder, result->alpha = alpha;
			return result;
		}

		static agora::rtc::VideoCompositingLayout::Region* toRaws(List<ClrRegion^>^ region)
		{
			int size = sizeof(VideoCompositingLayout::Region) * region->Count;
			VideoCompositingLayout::Region* result = static_cast<VideoCompositingLayout::Region*>(Marshal::AllocHGlobal(size).ToPointer());
			for (int i = 0; i < region->Count; i++)
			{
				result[i] = *region[i]->toRaw();
			}
			return result;
		}
	};

	public
	ref class ClrVideoCompositingLayout
	{
	public:
		int canvasWidth;
		int canvasHeight;
		String^ backgroundColor; //e.g. "#C0C0C0" in RGB
		List<ClrRegion^>^ regions;
		String^ appData;
		ClrVideoCompositingLayout()
			: canvasWidth(0), canvasHeight(0), backgroundColor(nullptr), regions(nullptr), appData(nullptr)
		{
		}

		agora::rtc::VideoCompositingLayout* toRaw()
		{
			VideoCompositingLayout* result = new VideoCompositingLayout();
			result->canvasHeight = canvasHeight, result->canvasWidth = canvasWidth;
			result->backgroundColor = MarshalString(backgroundColor).c_str();
			result->regions = ClrRegion::toRaws(regions), result->regionCount = regions->Count;
			result->appData = MarshalString(appData).c_str(), result->appDataLength = appData->Length;
			return result;
		}
	};

	public
		enum class RtmpStreamLifeCycleType
	{
		RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL = 1,
		RTMP_STREAM_LIFE_CYCLE_BIND2OWNER = 2,
	};

	public
	ref class ClrPublisherConfiguration
	{
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
			: width(640), height(360), framerate(15), bitrate(500), defaultLayout(1), lifecycle(RtmpStreamLifeCycleType::RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL), owner(true)
		{
		}

		agora::rtc::PublisherConfiguration* toRaw()
		{
			PublisherConfiguration* result = new PublisherConfiguration();
			result->width = width;
			result->height = height;
			result->framerate = framerate;
			result->defaultLayout = defaultLayout;
			result->lifecycle = (RTMP_STREAM_LIFE_CYCLE_TYPE)lifecycle;
			result->owner = owner;
			result->publishUrl = MarshalString(publishUrl).c_str();
			result->injectStreamHeight = injectStreamHeight;
			result->injectStreamWidth = injectStreamWidth;
			result->injectStreamUrl = MarshalString(injectStreamUrl).c_str();
			result->publishUrl = MarshalString(publishUrl).c_str();
			result->rawStreamUrl = MarshalString(rawStreamUrl).c_str();
			result->extraInfo = MarshalString(extraInfo).c_str();
			return result;
		}
	};

	public
	ref class ClrRect
	{
	public:
		int top;
		int left;
		int bottom;
		int right;

		ClrRect() : top(0), left(0), bottom(0), right(0) {}
		ClrRect(int t, int l, int b, int r) : top(t), left(l), bottom(b), right(r) {}

		agora::rtc::Rect* toRaw()
		{
			agora::rtc::Rect* result = new agora::rtc::Rect();
			result->top = top;
			result->left = left;
			result->bottom = bottom;
			result->right = right;
			return result;
		}
	};

	public
	ref class ClrTranscodingUser
	{
	public:
		int uid;

		int x;
		int y;
		int width;
		int height;

		int zOrder;
		double alpha;
		int audioChannel;

		ClrTranscodingUser()
			: uid(0), x(0), y(0), width(0), height(0), zOrder(0), alpha(1.0), audioChannel(0)
		{
		}

		TranscodingUser* toRaw()
		{
			TranscodingUser* result = new TranscodingUser();
			result->uid = uid;
			result->x = x;
			result->y = y;
			result->width = width;
			result->height = height;
			result->zOrder = zOrder;
			result->alpha = alpha;
			result->audioChannel = audioChannel;
			return result;
		}
	};

	public
		enum class VideoCodecProfileType
	{
		VIDEO_CODEC_PROFILE_BASELINE = 66,
		VIDEO_CODEC_PROFILE_MAIN = 77,
		VIDEO_CODEC_PROFILE_HIGH = 100,
	};

	public
		enum class AudioSampleRateType
	{
		AUDIO_SAMPLE_RATE_32000 = 32000,
		AUDIO_SAMPLE_RATE_44100 = 44100,
		AUDIO_SAMPLE_RATE_48000 = 48000,
	};

	public
		enum class AudioProfileType // sample rate, bit rate, mono/stereo, speech/music codec
	{
		AUDIO_PROFILE_DEFAULT = 0,					 // use default settings
		AUDIO_PROFILE_SPEECH_STANDARD = 1,			 // 32Khz, 18kbps, mono, speech
		AUDIO_PROFILE_MUSIC_STANDARD = 2,			 // 48Khz, 50kbps, mono, music
		AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3,	 // 48Khz, 50kbps, stereo, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4,		 // 48Khz, 128kbps, mono, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 128kbps, stereo, music
		AUDIO_PROFILE_IOT = 6,
		AUDIO_PROFILE_NUM = 7,
	};

	public
	ref class ClrLiveTranscoding
	{
	public:
		int width;
		int height;
		int videoBitrate;
		int videoFramerate;

		bool lowLatency;

		int videoGop;
		VideoCodecProfileType videoCodecProfile;
		unsigned int backgroundColor;
		unsigned int userCount;
		ClrTranscodingUser^ transcodingUsers;

		String^ transcodingExtraInfo;

		AudioSampleRateType audioSampleRate;
		int audioBitrate;
		int audioChannels;

		ClrLiveTranscoding()
			: width(360), height(640), videoBitrate(400), videoFramerate(15), lowLatency(false), backgroundColor(0x000000), videoGop(30), videoCodecProfile(VideoCodecProfileType::VIDEO_CODEC_PROFILE_HIGH), userCount(0), transcodingUsers(), transcodingExtraInfo(nullptr), audioSampleRate(AudioSampleRateType::AUDIO_SAMPLE_RATE_48000), audioBitrate(48), audioChannels(1)
		{
		}

		void writeRaw(LiveTranscoding& raw)
		{
			raw.width = width;
			raw.height = height;
			raw.videoBitrate = videoBitrate;
			raw.videoFramerate = videoFramerate;
			raw.lowLatency = lowLatency;
			raw.videoGop = videoGop;
			raw.videoCodecProfile = (VIDEO_CODEC_PROFILE_TYPE)videoCodecProfile;
			raw.backgroundColor = backgroundColor;
			raw.userCount = userCount;
			raw.transcodingUsers = transcodingUsers->toRaw();
			raw.transcodingExtraInfo = MarshalString(transcodingExtraInfo).c_str();
			raw.audioSampleRate = (AUDIO_SAMPLE_RATE_TYPE)audioSampleRate;
			raw.audioBitrate = audioBitrate;
			raw.audioChannels = audioChannels;
		}
	};

	public
		enum class AudioScenarioType // set a suitable scenario for your app type
	{
		AUDIO_SCENARIO_DEFAULT = 0,
		AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = 1,
		AUDIO_SCENARIO_EDUCATION = 2,
		AUDIO_SCENARIO_GAME_STREAMING = 3,
		AUDIO_SCENARIO_SHOWROOM = 4,
		AUDIO_SCENARIO_CHATROOM_GAMING = 5,
		AUDIO_SCENARIO_IOT = 6,
		AUDIO_SCENARIO_NUM = 7,
	};

	public
		enum class AudioEqualizationBandFrequency
	{
		AUDIO_EQUALIZATION_BAND_31 = 0,
		AUDIO_EQUALIZATION_BAND_62 = 1,
		AUDIO_EQUALIZATION_BAND_125 = 2,
		AUDIO_EQUALIZATION_BAND_250 = 3,
		AUDIO_EQUALIZATION_BAND_500 = 4,
		AUDIO_EQUALIZATION_BAND_1K = 5,
		AUDIO_EQUALIZATION_BAND_2K = 6,
		AUDIO_EQUALIZATION_BAND_4K = 7,
		AUDIO_EQUALIZATION_BAND_8K = 8,
		AUDIO_EQUALIZATION_BAND_16K = 9,
	};

	public
		enum class AudioReverbType
	{
		AUDIO_REVERB_DRY_LEVEL = 0, // (dB, [-20,10]), the level of the dry signal
		AUDIO_REVERB_WET_LEVEL = 1, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
		AUDIO_REVERB_ROOM_SIZE = 2, // ([0, 100]), the room size of the reflection
		AUDIO_REVERB_WET_DELAY = 3, // (ms, [0, 200]), the length of the initial delay of the wet signal in ms
		AUDIO_REVERB_STRENGTH = 4,  // ([0, 100]), the strength of the late reverberation
	};

	public
		enum class VideoMirrorModeType
	{
		VIDEO_MIRROR_MODE_AUTO = 0,		//determined by SDK
		VIDEO_MIRROR_MODE_ENABLED = 1,  //enabled mirror
		VIDEO_MIRROR_MODE_DISABLED = 2, //disable mirror
	};

	public
	ref class ClrInjectStreamConfig
	{
	public:
		int width;
		int height;
		int videoGop;
		int videoFramerate;
		int videoBitrate;
		AudioSampleRateType audioSampleRate;
		int audioBitrate;
		int audioChannels;

		// width / height default set to 0 means pull the stream with its original resolution
		ClrInjectStreamConfig()
			: width(0), height(0), videoGop(30), videoFramerate(15), videoBitrate(400), audioSampleRate(AudioSampleRateType::AUDIO_SAMPLE_RATE_48000), audioBitrate(48), audioChannels(1)
		{
		}

		void writeRaw(InjectStreamConfig& raw)
		{
			raw.width = width;
			raw.height = height;
			raw.videoGop = videoGop;
			raw.videoFramerate = videoFramerate;
			raw.videoBitrate = videoBitrate;
			raw.audioSampleRate = (AUDIO_SAMPLE_RATE_TYPE)audioSampleRate;
			raw.audioBitrate = audioBitrate;
			raw.audioChannels = audioChannels;
		}
	};

	public
		enum class ConnectionStateType
	{
		CONNECTION_STATE_DISCONNECTED = 1,
		CONNECTION_STATE_CONNECTING = 2,
		CONNECTION_STATE_CONNECTED = 3,
		CONNECTION_STATE_RECONNECTING = 4,
		CONNECTION_STATE_FAILED = 5,
	};

	public
		enum class ConnectionChangedReasonType
	{
		/** 0: The SDK is connecting to Agora's edge server. */
		CONNECTION_CHANGED_CONNECTING = 0,
		/** 1: The SDK has joined the channel successfully. */
		CONNECTION_CHANGED_JOIN_SUCCESS = 1,
		/** 2: The connection between the SDK and Agora's edge server is interrupted. */
		CONNECTION_CHANGED_INTERRUPTED = 2,
		/** 3: The connection between the SDK and Agora's edge server is banned by Agora's edge server. */
		CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
		/** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
		CONNECTION_CHANGED_JOIN_FAILED = 4,
		/** 5: The SDK has left the channel. */
		CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
		/** 6: The connection failed since Appid is not valid. */
		CONNECTION_CHANGED_INVALID_APP_ID = 6,
		/** 7: The connection failed since channel name is not valid. */
		CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
		/** 8: The connection failed since token is not valid, possibly because:

	   - The App Certificate for the project is enabled in Dashboard, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
	   - The uid that you specify in the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method is different from the uid that you pass for generating the token.
	   */
	   CONNECTION_CHANGED_INVALID_TOKEN = 8,
	   /** 9: The connection failed since token is expired. */
	   CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
	   /** 10: The connection is rejected by server. */
	   CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
	   /** 11: The connection changed to reconnecting since SDK has set a proxy server. */
	   CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
	   /** 12: When SDK is in connection failed, the renew token operation will make it connecting. */
	   CONNECTION_CHANGED_RENEW_TOKEN = 12,
	   /** 13: The IP Address of SDK client has changed. i.e., Network type or IP/Port changed by network operator might change client IP address. */
	   CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
	   /** 14: Timeout for the keep-alive of the connection between the SDK and Agora's edge server. The connection state changes to CONNECTION_STATE_RECONNECTING(4). */
	   CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
	};

	public
	ref class ClrVideoDimensions
	{
	public:
		int width;
		int height;

		ClrVideoDimensions()
			: width(640), height(480)
		{
		}
		ClrVideoDimensions(int w, int h)
			: width(w), height(h)
		{
		}
	};

	public
		enum class FrameRate
	{
		FRAME_RATE_FPS_1 = 1,
		FRAME_RATE_FPS_7 = 7,
		FRAME_RATE_FPS_10 = 10,
		FRAME_RATE_FPS_15 = 15,
		FRAME_RATE_FPS_24 = 24,
		FRAME_RATE_FPS_30 = 30,
		FRAME_RATE_FPS_60 = 60,
	};

	public
		enum class OrientationMode
	{
		ORIENTATION_MODE_ADAPTIVE = 0,
		ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
		ORIENTATION_MODE_FIXED_PORTRAIT = 2,
	};

	public
		enum class DegradationPreference
	{
		/** 0: (Default) Degrade the frame rate in order to maintain the video quality. */
		MAINTAIN_QUALITY = 0,
		/** 1: Degrade the video quality in order to maintain the frame rate. */
		MAINTAIN_FRAMERATE = 1,
		/** 2: (For future use) Maintain a balance between the frame rate and video quality. */
		MAINTAIN_BALANCED = 2,
	};

	public
	ref class ClrVideoEncoderConfiguration
	{
	public:
		ClrVideoDimensions dimensions;
		FrameRate frameRate;
		int minFrameRate;
		int bitrate;
		int minBitrate;
		OrientationMode orientationMode;
		DegradationPreference degradationPreference;

		ClrVideoEncoderConfiguration(
			const ClrVideoDimensions d, FrameRate f,
			int b, OrientationMode m)
			: ClrVideoEncoderConfiguration(),
			dimensions(d.width, d.height),
			frameRate(f),
			bitrate(b),
			minBitrate(DEFAULT_MIN_BITRATE),
			orientationMode(m)
		{
		}
		ClrVideoEncoderConfiguration(
			int width, int height, FrameRate f,
			int b, OrientationMode m)
			: ClrVideoEncoderConfiguration(),
			dimensions(width, height),
			frameRate(f),
			bitrate(b),
			minBitrate(DEFAULT_MIN_BITRATE),
			orientationMode(m)
		{
		}
		ClrVideoEncoderConfiguration()
			: dimensions(640, 480),
			frameRate(FrameRate::FRAME_RATE_FPS_15),
			minFrameRate(-1),
			bitrate(STANDARD_BITRATE),
			minBitrate(DEFAULT_MIN_BITRATE),
			orientationMode(OrientationMode::ORIENTATION_MODE_ADAPTIVE),
			degradationPreference(DegradationPreference::MAINTAIN_QUALITY)

		{
		}

		void writeRaw(VideoEncoderConfiguration& raw)
		{
			raw.dimensions = VideoDimensions(dimensions.width, dimensions.height);
			raw.frameRate = (FRAME_RATE)frameRate;
			raw.minFrameRate = minFrameRate;
			raw.bitrate = bitrate;
			raw.minBitrate = minBitrate;
			raw.orientationMode = (ORIENTATION_MODE)orientationMode;
			raw.degradationPreference = (DEGRADATION_PREFERENCE)degradationPreference;
		}
	};

	public
		enum class VideoBufferType
	{
		/** 1: The video buffer in the format of raw data.
			 */
		VIDEO_BUFFER_RAW_DATA = 1,
	};

	/** The video pixel format.
		 */
	public
		enum class VideoPixelFormate
	{
		/** 0: The video pixel format is unknown.
			 */
		VIDEO_PIXEL_UNKNOWN = 0,
		/** 1: The video pixel format is I420.
			 */
			 VIDEO_PIXEL_I420 = 1,
			 /** 2: The video pixel format is BGRA.
				  */
				  VIDEO_PIXEL_BGRA = 2,
				  /** 8: The video pixel format is NV12.
					   */
					   VIDEO_PIXEL_NV12 = 8,
	};

	public
	ref class ClrExternalVideoFrame
	{
	public:
		VideoBufferType type;
		VideoPixelFormate format;
		array<Byte>^ buffer;
		int stride;
		int height;
		int cropLeft;
		int cropTop;
		int cropRight;
		int cropBottom;
		int rotation;
		long long timestamp;

		ExternalVideoFrame* toRaw()
		{
			ExternalVideoFrame* result = new ExternalVideoFrame();
			result->type = (ExternalVideoFrame::VIDEO_BUFFER_TYPE)type;
			result->format = (ExternalVideoFrame::VIDEO_PIXEL_FORMAT)format;
			result->stride = stride;
			result->height = height;
			result->cropLeft = cropLeft;
			result->cropTop = cropTop;
			result->cropRight = cropRight;
			result->cropBottom = cropBottom;
			result->rotation = rotation;
			result->timestamp = timestamp;
			result->buffer = Marshal::AllocHGlobal(buffer->LongLength * sizeof(Byte)).ToPointer();
			Marshal::Copy(buffer, 0, (IntPtr)result->buffer, buffer->LongLength);
			return result;
		}
	};

	public
	ref class ClrRtcImage
	{
	public:
		ClrRtcImage() : url(nullptr),
			x(0),
			y(0),
			width(0),
			height(0)
		{
		}
		/** URL address of the image on the broadcasting video. */
		String^ url;
		/** Horizontal position of the image from the upper left of the broadcasting video. */
		int x;
		/** Vertical position of the image from the upper left of the broadcasting video. */
		int y;
		/** Width of the image on the broadcasting video. */
		int width;
		/** Height of the image on the broadcasting video. */
		int height;

		void writeRaw(RtcImage& raw)
		{
			raw.x = x;
			raw.y = y;
			raw.width = width;
			raw.height = height;
			raw.url = MarshalString(url).c_str();
		}
	};

	public
		enum class StreamFallbackOptions
	{
		STREAM_FALLBACK_OPTION_DISABLED = 0,
		STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
		STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
	};

	public
		enum class RemoteVideoState
	{
		/** 0: The remote video is in the default state, probably due to #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3), #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5), or #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7).
 */
		REMOTE_VIDEO_STATE_STOPPED = 0,

		/** 1: The first remote video packet is received.
		 */
		 REMOTE_VIDEO_STATE_STARTING = 1,

		 /** 2: The remote video stream is decoded and plays normally, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2), #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4), #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6), or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9).
		  */
		  REMOTE_VIDEO_STATE_DECODING = 2,

		  /** 3: The remote video is frozen, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8).
		   */
		   REMOTE_VIDEO_STATE_FROZEN = 3,

		   /** 4: The remote video fails to start, probably due to #REMOTE_VIDEO_STATE_REASON_INTERNAL (0).
			*/
			REMOTE_VIDEO_STATE_FAILED = 4
	};

	public enum class RemoteVideoStateReason
	{
		/** 0: Internal reasons.
 */
		REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,

		/** 1: Network congestion.
		 */
		 REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,

		 /** 2: Network recovery.
		  */
		  REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,

		  /** 3: The local user stops receiving the remote video stream or disables the video module.
		   */
		   REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,

		   /** 4: The local user resumes receiving the remote video stream or enables the video module.
			*/
			REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,

			/** 5: The remote user stops sending the video stream or disables the video module.
			 */
			 REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,

			 /** 6: The remote user resumes sending the video stream or enables the video module.
			  */
			  REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,

			  /** 7: The remote user leaves the channel.
			   */
			   REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,

			   /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions.
				*/
				REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,

				/** 9: The remote media stream switches back to the video stream after the network conditions improve.
				 */
				 REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9

	};

	public
	ref class ClrRemoteAudioStats
	{
	public:
		int uid;
		int quality;
		int networkTransportDelay;
		int jitterBufferDelay;
		int audioLossRate;
		int numChannels;
		int receivedSampleRate;
		int receivedBitrate;
		int totalFrozenTime;
		int frozenRate;

		ClrRemoteAudioStats() {}

		ClrRemoteAudioStats(const RemoteAudioStats& raw) : 
			uid(raw.uid),
			quality(raw.quality),
			networkTransportDelay(raw.networkTransportDelay),
			jitterBufferDelay(raw.jitterBufferDelay),
			audioLossRate(raw.audioLossRate),
			numChannels(raw.numChannels),
			receivedSampleRate(raw.receivedSampleRate),
			receivedBitrate(raw.receivedBitrate),
			totalFrozenTime(raw.totalFrozenTime),
			frozenRate(raw.frozenRate)
		{
		}

		void writeRaw(RemoteAudioStats& raw)
		{
			raw.uid = uid;
			raw.quality = quality;
			raw.networkTransportDelay = networkTransportDelay;
			raw.jitterBufferDelay = jitterBufferDelay;
			raw.audioLossRate = audioLossRate;
			raw.numChannels = numChannels;
			raw.receivedSampleRate = receivedSampleRate;
			raw.receivedBitrate = receivedBitrate;
			raw.totalFrozenTime = totalFrozenTime;
			raw.frozenRate = frozenRate;
		}
	};

	public
		enum class NetworkType
	{
		/** -1: The network type is unknown. */
		NETWORK_TYPE_UNKNOWN = -1,
		/** 0: The SDK disconnects from the network. */
		NETWORK_TYPE_DISCONNECTED = 0,
		/** 1: The network type is LAN. */
		NETWORK_TYPE_LAN = 1,
		/** 2: The network type is Wi-Fi(including hotspots). */
		NETWORK_TYPE_WIFI = 2,
		/** 3: The network type is mobile 2G. */
		NETWORK_TYPE_MOBILE_2G = 3,
		/** 4: The network type is mobile 3G. */
		NETWORK_TYPE_MOBILE_3G = 4,
		/** 5: The network type is mobile 4G. */
		NETWORK_TYPE_MOBILE_4G = 5,
	};

	public
		enum class LocalAudioStreamState
	{
		/** 0: The local audio is in the initial state.
	 */
		LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
		/** 1: The recording device starts successfully.
		 */
		 LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
		 /** 2: The first audio frame encodes successfully.
		  */
		  LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
		  /** 3: The local audio fails to start.
		   */
		   LOCAL_AUDIO_STREAM_STATE_FAILED = 3
	};

	public
		enum class LocalAudioStreamError
	{
		/** 0: The local audio is normal.
	 */
		LOCAL_AUDIO_STREAM_ERROR_OK = 0,
		/** 1: No specified reason for the local audio failure.
		 */
		 LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
		 /** 2: No permission to use the local audio device.
		  */
		  LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
		  /** 3: The microphone is in use.
		   */
		   LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
		   /** 4: The local audio recording fails. Check whether the recording device
			* is working properly.
			*/
			LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
			/** 5: The local audio encoding fails.
			 */
			 LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5
	};

	public
		enum class LocalVideoStreamState
	{
		/** Initial state */
		LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
		/** The capturer starts successfully. */
		LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
		/** The first video frame is successfully encoded. */
		LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
		/** The local video fails to start. */
		LOCAL_VIDEO_STREAM_STATE_FAILED = 3
	};

	public
		enum class LocalVideoStreamError
	{
		/** The local video is normal. */
		LOCAL_VIDEO_STREAM_ERROR_OK = 0,
		/** No specified reason for the local video failure. */
		LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
		/** No permission to use the local video device. */
		LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
		/** The local video capturer is in use. */
		LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
		/** The local video capture fails. Check whether the capturer is working properly. */
		LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
		/** The local video encoding fails. */
		LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5
	};

	public enum class RemoteAudioState
	{
		/** 0: The remote audio is in the default state, probably due to
	 * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
	 * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
	 * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
	 */
		REMOTE_AUDIO_STATE_STOPPED = 0,  // Default state, audio is started or remote user disabled/muted audio stream
		/** 1: The first remote audio packet is received.
		 */
		 REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
		 /** 2: The remote audio stream is decoded and plays normally, probably
		  * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
		  * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
		  * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
		  */
		  REMOTE_AUDIO_STATE_DECODING = 2,  // The first remote audio frame has been decoded or fronzen state ends
		  /** 3: The remote audio is frozen, probably due to
		   * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
		   */
		   REMOTE_AUDIO_STATE_FROZEN = 3,    // Remote audio is frozen, probably due to network issue
		   /** 4: The remote audio fails to start, probably due to
			* #REMOTE_AUDIO_REASON_INTERNAL (0).
			*/
			REMOTE_AUDIO_STATE_FAILED = 4,    // Remote audio play failed
	};

	public enum class RemoteAudioStateReason
	{
		/** 0: Internal reasons.
	 */
		REMOTE_AUDIO_REASON_INTERNAL = 0,
		/** 1: Network congestion.
		 */
		 REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
		 /** 2: Network recovery.
		  */
		  REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
		  /** 3: The local user stops receiving the remote audio stream or
		   * disables the audio module.
		   */
		   REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
		   /** 4: The local user resumes receiving the remote audio stream or
			* enables the audio module.
			*/
			REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
			/** 5: The remote user stops sending the audio stream or disables the
			 * audio module.
			 */
			 REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
			 /** 6: The remote user resumes sending the audio stream or enables the
			  * audio module.
			  */
			  REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
			  /** 7: The remote user leaves the channel.
			   */
			   REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
	};

	public ref class ClrLocalAudioStats {
	public:
		int numChannels;
		int sentSampleRate;
		int sentBitrate;

		ClrLocalAudioStats() : numChannels(0), sentSampleRate(0), sentBitrate(0) {}
		ClrLocalAudioStats(const LocalAudioStats& stats): numChannels(stats.numChannels), sentSampleRate(stats.sentSampleRate), sentBitrate(stats.sentBitrate) {}
	};

	//RtcEngineEventHandler Part
	public
		delegate void onJoinChannelSuccess(String^ channel, int uid, int elapsed);
	public
		delegate void onRejoinChannelSuccess(String^ channel, int uid, int elapsed);
	public
		delegate void onWarning(int warn, String^ msg);
	public
		delegate void onError(int err, String^ msg);
	public
		delegate void onAudioQuality(int uid, int quality, unsigned short delay, unsigned short lost);
	public
		delegate void onAudioVolumeIndication(List<AudioVolumeInfo^>^ speakers, int totalVolume);
	public
		delegate void onLeaveChannel(RtcStats^ stat);
	public
		delegate void onUserJoined(int uid, int elapsed);
	public
		delegate void onUserOffline(int uid, UserOfflineType reason);
	public
		delegate void onRtcStats(RtcStats^ stat);
	public
		delegate void onLocalVideoStats(ClrLocalVideoStats^ stats);
	public
		delegate void onRemoteVideoStats(RemoteVideoStats^ stats);
	public
		delegate void onFirstLocalVideoFrame(int width, int height, int elapsed);
	public
		delegate void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed);
	public
		delegate void onFirstRemoteVideoFrame(int uid, int width, int height, int elapsed);

	public
		delegate void onAudioDeviceStateChanged(String^ deviceid, int deviceType, int deviceState);
	public
		delegate void onVideoDeviceStateChanged(String^ deviceid, int deviceType, int deviceState);

	public
		delegate void onLastmileQuality(int quality);
	public
		delegate void onNetworkQuality(int uid, int txQuality, int rxQuality);

	public
		delegate void onUserMuteAudio(int uid, bool muted);
	public
		delegate void onUserMuteVideo(int uid, bool muted);
	public
		delegate void onUserEnableVideo(int uid, bool enabled);
	public
		delegate void onCameraReady();
	public
		delegate void onVideoStopped();
	public
		delegate void onConnectionInterrupted();
	public
		delegate void onConnectionLost();
	public
		delegate void onConnectionBanned();

	public
		delegate void onRefreshRecordingServiceStatus(int status);
	public
		delegate void onApiCallExecuted(String^ api, int error);
	public
		delegate void onStreamMessage(int uid, int streamId, String^ data);
	public
		delegate void onStreamMessageError(int uid, int streamId, int code, int missed, int cached);
	public
		delegate void onRequestChannelKey();
	public
		delegate void onRequestToken();
	public
		delegate void onAudioMixingFinished();

	public
		delegate void onActiveSpeaker(int uid);

	public
		delegate void onClientRoleChanged(ClientRoleType, ClientRoleType);
	public
		delegate void onAudioDeviceVolumeChanged(MediaDeviceType, int, bool);

	public
		delegate void onStreamUnpublished(String^ url);
	public
		delegate void onStreamPublished(String^ url, int error);
	public
		delegate void onTranscodingUpdated();

	public
		delegate void onConnectionStateChanged(ConnectionStateType state, ConnectionChangedReasonType reason);
	public
		delegate void onTokenPrivilegeWillExpire(String^ token);
	public
		delegate void onFirstLocalAudioFrame(int elapsed);
	public
		delegate void onFirstRemoteAudioFrame(int uid, int elapsed);
	public
		delegate void onUserEnableLocalVideo(int uid, bool enabled);
	public
		delegate void onVideoSizeChanged(int uid, int width, int height, int rotation);
	public
		delegate void onRemoteVideoStateChanged(int uid, RemoteVideoState state, RemoteVideoStateReason reason, int elapsed);
	public
		delegate void onLocalPublishFallbackToAudioOnly(bool);
	public
		delegate void onRemoteSubscribeFallbackToAudioOnly(int uid, bool isFallbackOrRecover);
	public
		delegate void onCameraFocusAreaChanged(int x, int y, int width, int height);
	public
		delegate void onRemoteAudioStats(ClrRemoteAudioStats^ stats);
	public
		delegate void onRemoteAudioTransportStats(int uid, short delay, short lost, short rxKBitRate);
	public
		delegate void onRemoteVideoTransportStats(int uid, short delay, short lost, short rxKBitRate);
	public
		delegate void onAudioMixingBegin();
	public
		delegate void onAudioMixingEnd();
	public
		delegate void onAudioEffectFinished(int soundId);
	public
		delegate void onStreamInjectedStatus(String^ url, int uid, int status);
	public
		delegate void onMediaEngineLoadSuccess();
	public
		delegate void onMediaEngineStartCallSuccess();

	//PacketObserver Part
	public
		delegate bool onSendAudioPacket(ClrPacket^ packet);
	public
		delegate bool onSendVideoPacket(ClrPacket^ packet);
	public
		delegate bool onReceiveAudioPacket(ClrPacket^ packet);
	public
		delegate bool onReceiveVideoPacket(ClrPacket^ packet);

	//Raw Data Part
	public
		delegate bool onRecordAudioFrame(ClrAudioFrame^ frame);
	public
		delegate bool onPlaybackAudioFrame(ClrAudioFrame^ frame);
	public
		delegate bool onPlaybackAudioFrameBeforeMixing(int uid, ClrAudioFrame^ frame);
	public
		delegate bool onMixedAudioFrame(ClrAudioFrame^ frame);

	public
		delegate bool onCaptureVideoFrame(ClrVideoFrame^ frame);
	public
		delegate bool onRenderVideoFrame(int uid, ClrVideoFrame^ frame);

	public
		delegate void onNetworkTypeChanged(NetworkType type);

	public
		delegate void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error);

	public
		delegate void onLocalVideoStateChanged(LocalVideoStreamState state, LocalVideoStreamError error);

	public delegate void onRemoteAudioStateChanged(uid_t, RemoteAudioState, RemoteAudioStateReason, int);

	public delegate void onFirstRemoteAudioDecoded(uid_t, int);

	public delegate void onLocalAudioStats(ClrLocalAudioStats^ stats);

	public
	ref class AgoraClr
	{
	public:
		AgoraClr();
		~AgoraClr();
		!AgoraClr();

		//频道管理
		int initialize(String^ vendorkey);
		void release();
		int setChannelProfile(ChannelProfile profile);
		int setClientRole(ClientRoleType role);
		int joinChannel(String^ token, String^ channelName, String^ channelInfo, int uid);
		int switchChannel(String^ token, String^ channelId);
		int leaveChannel();
		int renewToken(String^ token);
		int enableWebSdkInteroperability(bool enabled);
		ConnectionStateType getConnectionState();

		//频道事件
		onConnectionStateChanged^ onConnectionStateChanged;
		onJoinChannelSuccess^ onJoinChannelSuccess;
		onRejoinChannelSuccess^ onRejoinChannelSuccess;
		onLeaveChannel^ onLeaveChannel;
		onClientRoleChanged^ onClientRoleChanged;
		onUserJoined^ onUserJoined;
		onUserOffline^ onUserOffline;
		onNetworkTypeChanged^ onNetworkTypeChanged;
		onConnectionLost^ onConnectionLost;
		onTokenPrivilegeWillExpire^ onTokenPrivilegeWillExpire;
		onRequestToken^ onRequestToken;

		//音频管理方法
		int enableAudio();
		int disableAudio();
		int setAudioProfile(AudioProfileType profile, AudioScenarioType scenario);
		int adjustRecordingSignalVolume(int volume);
		int adjustPlaybackSignalVolume(int volume);
		int enableLocalAudio(bool enabled);
		int muteLocalAudioStream(bool mute);
		int muteRemoteAudioStream(int uid, bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		int setDefaultMuteAllRemoteAudioStreams(bool mute);

		//视频管理方法
		int enableVideo();
		int disableVideo();
		int setVideoEncoderConfiguration(ClrVideoEncoderConfiguration^ config);
		int setupLocalVideo(IntPtr view, int renderMode, int uid);
		int setupRemoteVideo(IntPtr view, int renderMode, int uid);
		int setLocalRenderMode(RenderMode mode);
		int setRemoteRenderMode(int uid, RenderMode mode);
		int startPreview();
		int stopPreview();
		int enableLocalVideo(bool enabled);
		int muteLocalVideoStream(bool mute);
		int muteRemoteVideoStream(int uid, bool mute);
		int muteAllRemoteVideoStreams(bool mute);
		int setDefaultMuteAllRemoteVideoStreams(bool mute);

		//本地媒体事件
		onLocalAudioStateChanged^ onLocalAudioStateChanged;
		onLocalVideoStateChanged^ onLocalVideoStateChanged;
		onFirstLocalVideoFrame^ onFirstLocalVideoFrame;
		onFirstLocalAudioFrame^ onFirstLocalAudioFrame;

		//远端媒体事件
		onRemoteAudioStateChanged^ onRemoteAudioStateChanged;
		onRemoteVideoStateChanged^ onRemoteVideoStateChanged;
		onUserMuteAudio^ onUserMuteAudio;
		onUserMuteVideo^ onUserMuteVideo;
		onFirstRemoteAudioFrame^ onFirstRemoteAudioFrame;
		onFirstRemoteAudioDecoded^ onFirstRemoteAudioDecoded;
		onFirstRemoteVideoFrame^ onFirstRemoteVideoFrame;

		//数据统计事件
		onRtcStats^ onRtcStats;
		onNetworkQuality^ onNetworkQuality;
		onLocalAudioStats^ onLocalAudioStats;
		onLocalVideoStats^ onLocalVideoStats;
		onRemoteAudioStats^ onRemoteAudioStats;
		onRemoteVideoStats^ onRemoteVideoStats;

		//视频前处理及后处理
		//setBeautyEffectOptions 在2.9.1上只适配iOS与Android,所以不添加

		//屏幕共享
		//todo:screen shared


		int setHightQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate);


		int startScreenCapture(IntPtr windowId, int captureFreq, ClrRect^ rect, int bitrate);
		int stopScreenCapture();
		int updateScreenCaptureRegion(ClrRect^ rect);

		int setEncryptionSecret(String^ key);
		int setEncryptionMode(String^ mode);

		int getCallId(String^% callid);
		int rate(String^ callid, int rating, String^ desc);
		int complain(String^ callid, String^ desc);
		int startEchoTest();
		int stopEchoTest();
		int enableLastmileTest();
		int disableLastmileTest();

		int setVideoProfile(VideoProfile profile, bool swapWidthAndHeight);

		int enableDualStreamMode(bool enabled);
		int setRemoteVideoStreamType(int uid, RemoteVideoStreamType type);
		int setVideoQualityParameters(bool preferFrameRateOverImageQuality);
		int setVideoCompositingLayout(ClrVideoCompositingLayout^ sei);
		int clearVideoCompositingLayout();
		int configPublisher(ClrPublisherConfiguration^ config);

		int createDataStream(int% id);
		int sendStreamMessage(int id, String^ data);

		//Ô­Ê¼Êý¾ÝAPI
		//RtcEngineParameters Part
		int setRecordingAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setPlaybackAudioFrameParameters(int sampleRate, int channel, RawAudioFrameOPModeType mode, int samplesPerCall);
		int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);

		int setPlaybackDeviceVolume(int volume);
		int enableAudioVolumeIndication(int interval, int smooth);
		int startAudioRecording(String^ path, AudioRecordingQualityType quality);
		int stopAudioRecording();
		int pauseAudioMixing();
		int resumeAudioMixing();
		int adjustAudioMixingVolume(int volume);
		int getAudioMixingDuration();
		int getAudioMixingCurrentPosition();
		int setAudioMixingPosition(int pos);
		int startAudioMixing(String^ path, bool loop, bool replace, int cycle);
		int stopAudioMixing();

		int setLogFile(String^ path);
		int setLogFilter(unsigned int filter);

		int setLocalVoicePitch(double pitch);
		int setInEarMonitoringVolume(int volume);

		int setExternalAudioSource(bool enabled, int sampleRate, int channels);

		int setLocalVoiceEqualization(AudioEqualizationBandFrequency freq, int bandGain);
		int setLocalVoiceReverb(AudioReverbType type, int value);
		int setLocalVideoMirrorMode(VideoMirrorModeType mode);
		String^ getVersion(int% build);
		int enableLoopbackRecording(bool enabled);

		int pushAudioFrame(ClrAudioFrameType type, ClrAudioFrame^ frame, bool wrap);

		int addPublishStreamUrl(String^ url, bool transcodingEnabled);
		int removePublishStreamUrl(String^ url);
		int setLiveTranscoding(ClrLiveTranscoding^ transcoding);
		int addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config);
		int removeInjectStreamUrl(String^ url);

		int getEffectsVolume();
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

		//2.3

		int adjustAudioMixingPlayoutVolume(int volume);
		int adjustAudioMixingPublishVolume(int volume);
		int setExternalAudioSink(bool enabled, int sampleRate, int channels);
		int setExternalVideoSource(bool enabled, bool useTexture);
		int pushVideoFrame(ClrExternalVideoFrame^ frame);
		int addVideoWatermark(ClrRtcImage^ image);
		int clearVideoWatermark();

		int setLocalPublishFallbackOption(StreamFallbackOptions option);
		int setRemoteSubscribeFallbackOption(StreamFallbackOptions option);
		int setRemoteDefaultVideoStreamType(RemoteVideoStreamType type);
		String^ getErrorDescription(int code);

		AgoraClrAudioDeviceManager^ getAudioDeviceManager();
		AgoraClrVideoDeviceManager^ getVideoDeviceManager();
		IRtcEngine* getEngine();

		//RtcEngineEventHandler Part

		onWarning^ onWarning;
		onError^ onError;
		onAudioQuality^ onAudioQuality;
		onAudioVolumeIndication^ onAudioVolumeIndication;


		onFirstRemoteVideoDecoded^ onFirstRemoteVideoDecoded;
		onAudioDeviceStateChanged^ onAudioDeviceStateChanged;
		onVideoDeviceStateChanged^ onVideoDeviceStateChanged;
		onLastmileQuality^ onLastmileQuality;
		onUserEnableVideo^ onUserEnableVideo;
		onCameraReady^ onCameraReady;
		onVideoStopped^ onVideoStopped;
		onConnectionInterrupted^ onConnectionInterrupted;
		onConnectionBanned^ onConnectionBanned;

		onApiCallExecuted^ onApiCallExecuted;
		onStreamMessage^ onStreamMessage;
		onStreamMessageError^ onStreamMessageError;
		onRequestChannelKey^ onRequestChannelKey;

		onAudioMixingFinished^ onAudioMixingFinished;

		onActiveSpeaker^ onActiveSpeaker;

		onAudioDeviceVolumeChanged^ onAudioDeviceVolumeChanged;

		onStreamUnpublished^ onStreamUnpublished;
		onStreamPublished^ onStreamPublished;
		onTranscodingUpdated^ onTranscodingUpdated;

		onUserEnableLocalVideo^ onUserEnableLocalVideo;
		onVideoSizeChanged^ onVideoSizeChanged;
		onLocalPublishFallbackToAudioOnly^ onLocalPublishFallbackToAudioOnly;
		onRemoteSubscribeFallbackToAudioOnly^ onRemoteSubscribeFallbackToAudioOnly;
		onCameraFocusAreaChanged^ onCameraFocusAreaChanged;

		onRemoteAudioTransportStats^ onRemoteAudioTransportStats;
		onRemoteVideoTransportStats^ onRemoteVideoTransportStats;
		onAudioMixingBegin^ onAudioMixingBegin;
		onAudioMixingEnd^ onAudioMixingEnd;
		onAudioEffectFinished^ onAudioEffectFinished;
		onStreamInjectedStatus^ onStreamInjectedStatus;
		onMediaEngineLoadSuccess^ onMediaEngineLoadSuccess;
		onMediaEngineStartCallSuccess^ onMediaEngineStartCallSuccess;

		//PacketObserver Part
		onSendAudioPacket^ onSendAudioPacket;
		onSendVideoPacket^ onSendVideoPacket;
		onReceiveAudioPacket^ onReceiveAudioPacket;
		onReceiveVideoPacket^ onReceiveVideoPacket;

		//Raw data Part
		onRecordAudioFrame^ onRecordAudioFrame;
		onPlaybackAudioFrame^ onPlaybackAudioFrame;
		onPlaybackAudioFrameBeforeMixing^ onPlaybackAudioFrameBeforeMixing;
		onMixedAudioFrame^ onMixedAudioFrame;

		onCaptureVideoFrame^ onCaptureVideoFrame;
		onRenderVideoFrame^ onRenderVideoFrame;

	private:
		agora::rtc::IRtcEngine* rtcEngine;

		AgoraClrEventHandler* agoraEventHandler;
		AgoraClrPacketObserver* agoraPacketObserver;
		AgoraClrRawFrameObserver* agoraRawObserver;
		agora::media::IMediaEngine* agoraMediaEngine;

		List<GCHandle>^ gchs;

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
		void NativeOnNetworkQuality(uid_t uid, int txQuality, int rxQuality);
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
		void NativeOnConnectionBanned();

		void NativeOnConnectionInterrupted();
		void NativeOnStreamMessage(uid_t uid, int streamId, const char* data, size_t length);
		void NativeOnStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached);
		void NativeOnRequestChannelKey();
		void NativeOnRequestToken();

		void NativeOnAudioMixingFinished();

		void NativeOnActiveSpeaker(uid_t uid);

		void NativeOnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
		void NativeOnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);

		void NativeOnStreamUnpublished(const char* url);
		void NativeOnStreamPublished(const char* url, int error);
		void NativeOnTranscodingUpdated();

		void NativeOnConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
		void NativeOnTokenPrivilegeWillExpire(const char* token);
		void NativeOnFirstLocalAudioFrame(int elapsed);
		void NativeOnFirstRemoteAudioFrame(uid_t uid, int elapsed);
		void NativeOnUserEnableLocalVideo(uid_t uid, bool enabled);
		void NativeOnVideoSizeChanged(uid_t uid, int width, int height, int rotation);
		void NativeOnRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed);
		void NativeOnLocalPublishFallbackToAudioOnly(bool);
		void NativeOnRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover);
		void NativeOnCameraFocusAreaChanged(int x, int y, int width, int height);
		void NativeOnRemoteAudioStats(const RemoteAudioStats& stats);
		void NativeOnRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		void NativeOnRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		void NativeOnAudioMixingBegin();
		void NativeOnAudioMixingEnd();
		void NativeOnAudioEffectFinished(int soundId);
		void NativeOnStreamInjectedStatus(const char* url, uid_t uid, int status);
		void NativeOnMediaEngineLoadSuccess();
		void NativeOnMediaEngineStartCallSuccess();

		bool NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet);

		bool NativeOnRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnPlaybackAudioFrameBeforeMixing(unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame& frame);
		bool NativeOnMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& frame);

		bool NativeOnCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& frame);
		bool NativeOnRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& frame);

		void NativeOnNetworkTypeChanged(agora::rtc::NETWORK_TYPE type);
		void NativeOnLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error);
		void NativeOnLocalVideoStateChanged(agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error);
		void NativeOnRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed);
		void NativeOnFirstRemoteAudioDecoded(uid_t uid, int elapsed);
		void NativeOnLocalAudioStats(const LocalAudioStats& stats);

		void initializeEventHandler();
		void initializePacketObserver();
		void initializeRawFrameObserver();
		void* regEvent(Object^ obj);
	};
} // namespace AgoraClrLibrary
