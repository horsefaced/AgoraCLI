#pragma once

#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrLibraryEnum.h"

#include <msclr\marshal.h>
#include <string>
#include <iostream>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace agora::rtc;
using namespace msclr::interop;

namespace AgoraClrLibrary {

	static char* strcopy(std::string& source) {
		char* dest = reinterpret_cast<char*>(malloc(sizeof(char) * source.length() + 1));
		if (dest == 0) return nullptr;
		else {
			strcpy(dest, source.c_str());
			return dest;
		}
	}

	static std::string MarshalString(String^ s)
	{
		if (s == nullptr) return std::string();

		IntPtr middleStr = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
		std::string result(reinterpret_cast<char*>(middleStr.ToPointer()));
		Runtime::InteropServices::Marshal::FreeHGlobal(middleStr);
		return result;
	}

	public
	ref class ClrAudioVolumeInfo
	{
	public:
		int uid;
		unsigned int volume; // [0,255]
		unsigned int vad;
		String^ channelId;

		ClrAudioVolumeInfo() {}

		ClrAudioVolumeInfo(const AudioVolumeInfo& info) :
			uid(info.uid),
			volume(info.volume),
			vad(info.vad),
			channelId(gcnew String(info.channelId))
		{

		}
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

		int gatewayRtt;
		double memoryAppUsageRatio;
		double memoryTotalUsageRatio;
		int memoryAppUsageInKbytes;

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

			gatewayRtt = raw.gatewayRtt;
			memoryAppUsageRatio = raw.memoryAppUsageRatio;
			memoryTotalUsageRatio = raw.memoryTotalUsageRatio;
			memoryAppUsageInKbytes = raw.memoryAppUsageInKbytes;
		}
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
			int size = sizeof(unsigned char) * buffer->Length;
			void* tmp = malloc(size);
			Marshal::Copy(buffer, 0, IntPtr(tmp), buffer->Length);
			delete packet.buffer;
			packet.buffer = reinterpret_cast<unsigned char*>(tmp);
			packet.size = buffer->Length;
		}
	};

	public
	ref class ClrAudioFrame
	{
	public:
		EnumAudioFrameType type;
		int samples;
		int bytesPerSample;
		int channels;
		int samplesPerSec;
		array<Byte>^ data;
		int64_t renderTimeMs;
		int avsync_type;

		ClrAudioFrame(agora::media::IAudioFrameObserver::AudioFrame& raw) :
			type(static_cast<EnumAudioFrameType>(raw.type)),
			samples(raw.samples),
			bytesPerSample(raw.bytesPerSample),
			channels(raw.channels),
			samplesPerSec(raw.samplesPerSec),
			renderTimeMs(raw.renderTimeMs),
			avsync_type(raw.avsync_type)
		{
			data = gcnew array<Byte>(samples * bytesPerSample);
			Marshal::Copy(IntPtr(raw.buffer), data, 0, samples * bytesPerSample);
		}

		void writeRaw(agora::media::IAudioFrameObserver::AudioFrame& raw)
		{
			bool sizeModified = (samples * bytesPerSample) != (raw.samples * raw.bytesPerSample);
			raw.type = (agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE)type;
			raw.samples = samples;
			raw.bytesPerSample = bytesPerSample;
			raw.channels = channels;
			raw.samplesPerSec = samplesPerSec;
			raw.renderTimeMs = renderTimeMs;
			raw.avsync_type = avsync_type;
			if (sizeModified) {
				delete raw.buffer;
				raw.buffer = malloc(sizeof(Byte) * data->Length);
			}
			Marshal::Copy(data, 0, IntPtr(raw.buffer), data->Length);
		}

		operator IAudioFrameObserver::AudioFrame* () {
			agora::media::IAudioFrameObserver::AudioFrame* raw = new agora::media::IAudioFrameObserver::AudioFrame();
			writeRaw(*raw);
			return raw;
		}
	};


	public
	ref class ClrVideoFrame
	{
	public:
		EnumVideoFrameType type;
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
		int avsync_type;

		ClrVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& raw) :
			type(static_cast<EnumVideoFrameType>(raw.type)),
			width(raw.width),
			height(raw.height),
			yStride(raw.yStride),
			uStride(raw.uStride),
			vStride(raw.vStride),
			rotation(raw.rotation),
			renderTimeMs(raw.renderTimeMs),
			avsync_type(raw.avsync_type)
		{
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
			int size = width * height;
			int sizeModified = (raw.width * raw.height) != size;

			raw.type = static_cast<IVideoFrameObserver::VIDEO_FRAME_TYPE>(type);
			raw.width = width;
			raw.height = height;
			raw.yStride = yStride;
			raw.uStride = uStride;
			raw.vStride = vStride;
			raw.rotation = rotation;
			raw.renderTimeMs = renderTimeMs;
			raw.avsync_type = avsync_type;

			if (sizeModified)
			{
				raw.yBuffer = malloc(sizeof(Byte) * size);
				raw.uBuffer = malloc(sizeof(Byte) * size / 4);
				raw.vBuffer = malloc(sizeof(Byte) * size / 4);
			}
			Marshal::Copy(ybuffer, 0, IntPtr(raw.yBuffer), size);
			Marshal::Copy(ubuffer, 0, IntPtr(raw.uBuffer), size / 4);
			Marshal::Copy(vbuffer, 0, IntPtr(raw.vBuffer), size / 4);
		}
	};

	public ref class ClrRectangle
	{
	public:
		int x;
		int y;
		int width;
		int height;

		ClrRectangle() : x(0), y(0), width(0), height(0) {}
		ClrRectangle(const agora::rtc::Rectangle& rect) : x(rect.x), y(rect.y), width(rect.width), height(rect.height) {}
		operator agora::rtc::Rectangle() {
			return agora::rtc::Rectangle(x, y, width, height);
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

		operator TranscodingUser* ()
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

		operator RtcImage* ()
		{
			RtcImage* raw = new RtcImage();
			raw->x = x;
			raw->y = y;
			raw->width = width;
			raw->height = height;
			raw->url = strcopy(MarshalString(url));
			return raw;
		}


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
		String^ metadata;
		ClrRtcImage^ watermark;
		ClrRtcImage^ backgroundImage;
		AudioSampleRateType audioSampleRate;
		int audioBitrate;
		int audioChannels;
		AudioCodecProfileType audioCodecProfile;

		ClrLiveTranscoding()
			: width(360), height(640), videoBitrate(400), videoFramerate(15), lowLatency(false), backgroundColor(0x000000), videoGop(30), videoCodecProfile(VideoCodecProfileType::VIDEO_CODEC_PROFILE_HIGH), userCount(0), transcodingUsers(), transcodingExtraInfo(nullptr), audioSampleRate(AudioSampleRateType::AUDIO_SAMPLE_RATE_48000), audioBitrate(48), audioChannels(1)
		{
		}

		operator LiveTranscoding() {
			LiveTranscoding raw;
			raw.width = width;
			raw.height = height;
			raw.videoBitrate = videoBitrate;
			raw.videoFramerate = videoFramerate;
			raw.lowLatency = lowLatency;
			raw.videoGop = videoGop;
			raw.videoCodecProfile = static_cast<VIDEO_CODEC_PROFILE_TYPE>(videoCodecProfile);
			raw.backgroundColor = backgroundColor;
			raw.userCount = userCount;
			raw.transcodingUsers = transcodingUsers;
			raw.transcodingExtraInfo = strcopy(MarshalString(transcodingExtraInfo));
			raw.metadata = strcopy(MarshalString(metadata));
			raw.watermark = watermark;
			raw.backgroundImage = backgroundImage;
			raw.audioSampleRate = static_cast<AUDIO_SAMPLE_RATE_TYPE>(audioSampleRate);
			raw.audioBitrate = audioBitrate;
			raw.audioChannels = audioChannels;
			raw.audioCodecProfile = static_cast<AUDIO_CODEC_PROFILE_TYPE>(audioCodecProfile);
			return raw;
		}
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

		operator InjectStreamConfig() {
			InjectStreamConfig raw;
			raw.width = width;
			raw.height = height;
			raw.videoGop = videoGop;
			raw.videoFramerate = videoFramerate;
			raw.videoBitrate = videoBitrate;
			raw.audioSampleRate = (AUDIO_SAMPLE_RATE_TYPE)audioSampleRate;
			raw.audioBitrate = audioBitrate;
			raw.audioChannels = audioChannels;
			return raw;
		}
	};


	public
	ref class ClrVideoDimensions
	{
	public:
		int width;
		int height;

		ClrVideoDimensions()
			: width(1920), height(1080)
		{
		}
		ClrVideoDimensions(int w, int h)
			: width(w), height(h)
		{
		}
	};

	public ref class ClrScreenCaptureParameters {
	public:
		ClrVideoDimensions^ dimensions;
		int frameRate;
		int bitrate;
		bool captureMouseCursor;

		ClrScreenCaptureParameters() : dimensions(), frameRate(5), bitrate(0), captureMouseCursor(false) {}
		operator agora::rtc::ScreenCaptureParameters() { return agora::rtc::ScreenCaptureParameters(dimensions->width, dimensions->height, frameRate, bitrate, captureMouseCursor); }
	};


	public
	ref class ClrVideoEncoderConfiguration
	{
	public:
		ClrVideoDimensions^ dimensions;
		FrameRate frameRate;
		int minFrameRate;
		int bitrate;
		int minBitrate;
		OrientationMode orientationMode;
		DegradationPreference degradationPreference;
		EnumVideoMirrorModeType mirrorMode;

		ClrVideoEncoderConfiguration(
			const ClrVideoDimensions^ d, FrameRate f,
			int b, OrientationMode m)
			: ClrVideoEncoderConfiguration(d->width, d->height, f, b, m)
		{
		}

		ClrVideoEncoderConfiguration(
			int width, int height, FrameRate f,
			int b, OrientationMode m) : ClrVideoEncoderConfiguration()
		{
			dimensions = gcnew ClrVideoDimensions(width, height);
			frameRate = f;
			bitrate = b;
			orientationMode = m;
		}

		ClrVideoEncoderConfiguration(
			const ClrVideoDimensions^ d, FrameRate f,
			int b, OrientationMode m, EnumVideoMirrorModeType mt)
			: ClrVideoEncoderConfiguration(d->width, d->height, f, b, m, mt)
		{
		}

		ClrVideoEncoderConfiguration(
			int width, int height, FrameRate f,
			int b, OrientationMode m, EnumVideoMirrorModeType mt) : ClrVideoEncoderConfiguration()
		{
			dimensions = gcnew ClrVideoDimensions(width, height);
			frameRate = f;
			bitrate = b;
			orientationMode = m;
		}

		ClrVideoEncoderConfiguration()
			: dimensions(),
			frameRate(FrameRate::FRAME_RATE_FPS_15),
			minFrameRate(-1),
			bitrate(STANDARD_BITRATE),
			minBitrate(DEFAULT_MIN_BITRATE),
			orientationMode(OrientationMode::ORIENTATION_MODE_ADAPTIVE),
			degradationPreference(DegradationPreference::MAINTAIN_QUALITY),
			mirrorMode(EnumVideoMirrorModeType::VIDEO_MIRROR_MODE_AUTO)

		{
		}

		operator VideoEncoderConfiguration() {
			VideoEncoderConfiguration raw;
			raw.dimensions = VideoDimensions(dimensions->width, dimensions->height);
			raw.frameRate = (FRAME_RATE)frameRate;
			raw.minFrameRate = minFrameRate;
			raw.bitrate = bitrate;
			raw.minBitrate = minBitrate;
			raw.orientationMode = (ORIENTATION_MODE)orientationMode;
			raw.degradationPreference = (DEGRADATION_PREFERENCE)degradationPreference;
			raw.mirrorMode = static_cast<VIDEO_MIRROR_MODE_TYPE>(mirrorMode);
			return raw;
		}

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

		operator ExternalVideoFrame* () {
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
			result->buffer = malloc(buffer->Length * sizeof(Byte));
			Marshal::Copy(buffer, 0, IntPtr(result->buffer), buffer->Length);
			return result;
		}
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

	public ref class ClrLocalAudioStats {
	public:
		int numChannels;
		int sentSampleRate;
		int sentBitrate;

		ClrLocalAudioStats() : numChannels(0), sentSampleRate(0), sentBitrate(0) {}
		ClrLocalAudioStats(const LocalAudioStats& stats) : numChannels(stats.numChannels), sentSampleRate(stats.sentSampleRate), sentBitrate(stats.sentBitrate) {}
	};

	public ref class ClrChannelMediaInfo {
	public:
		String^ channel;
		String^ token;
		uid_t uid;

		operator ChannelMediaInfo* () {
			ChannelMediaInfo* info = new ChannelMediaInfo();
			info->channelName = MarshalString(channel).c_str();
			info->token = MarshalString(token).c_str();
			info->uid = uid;
			return info;
		}
	};

	public ref class ClrChannelMediaRelayConfiguration {
	public:
		ClrChannelMediaInfo^ src;
		ClrChannelMediaInfo^ dest;
		int destCount;

		ClrChannelMediaRelayConfiguration() :
			src(nullptr),
			dest(nullptr),
			destCount(0) {}
		operator ChannelMediaRelayConfiguration() {
			ChannelMediaRelayConfiguration config;
			config.srcInfo = src;
			config.destInfos = dest;
			config.destCount = destCount;
			return config;
		}
	};

	public ref class ClrLastmileProbeConfig {
	public:
		bool probeUplink;
		bool probeDownlink;
		unsigned int expectedUplinkBitrate;
		unsigned int expectedDownlinkBitrate;

		operator LastmileProbeConfig() {
			LastmileProbeConfig config;
			config.probeUplink = probeUplink;
			config.probeDownlink = probeDownlink;
			config.expectedUplinkBitrate = expectedUplinkBitrate;
			config.expectedDownlinkBitrate = expectedDownlinkBitrate;
			return config;
		}
	};

	public ref class ClrLastmileProbeOneWayResult {
	public:
		unsigned int packetLossRate;
		unsigned int jitter;
		unsigned int availableBandwidth;

		ClrLastmileProbeOneWayResult() {}

		ClrLastmileProbeOneWayResult(const LastmileProbeOneWayResult& val) :
			packetLossRate(val.packetLossRate),
			jitter(val.jitter),
			availableBandwidth(val.availableBandwidth)
		{}

		operator LastmileProbeOneWayResult() {
			LastmileProbeOneWayResult result;
			result.packetLossRate = packetLossRate;
			result.jitter = jitter;
			result.availableBandwidth = availableBandwidth;
			return result;
		}
	};

	public ref class ClrLastmileProbeResult {
	public:
		LastmileProbeResultState state;
		ClrLastmileProbeOneWayResult^ uplinkReport;
		ClrLastmileProbeOneWayResult^ downlinkReport;
		unsigned int rtt;

		ClrLastmileProbeResult() {}

		ClrLastmileProbeResult(const LastmileProbeResult& val) :
			state(static_cast<LastmileProbeResultState>(val.state)),
			uplinkReport(gcnew ClrLastmileProbeOneWayResult(val.uplinkReport)),
			downlinkReport(gcnew ClrLastmileProbeOneWayResult(val.downlinkReport)),
			rtt(val.rtt)
		{

		}

		operator LastmileProbeResult() {
			LastmileProbeResult result;
			result.state = static_cast<LASTMILE_PROBE_RESULT_STATE>(state);
			result.uplinkReport = uplinkReport->operator LastmileProbeOneWayResult();
			result.downlinkReport = downlinkReport->operator agora::rtc::LastmileProbeOneWayResult();
			result.rtt = rtt;
			return result;
		}
	};

	public ref class ClrMetadata {
	public:
		uid_t uid;
		array<Byte>^ buffer;
		long long timeStampMs;

		ClrMetadata(const IMetadataObserver::Metadata& data) :
			uid(data.uid),
			timeStampMs(data.timeStampMs)
		{
			buffer = gcnew array<Byte>(data.size);
			Marshal::Copy(IntPtr(data.buffer), buffer, 0, data.size);
		}
	};

	public ref class ClrWatermarkOptions {
	public:
		bool visibleInPreview;
		ClrRectangle^ positionInLandscapeMode;
		ClrRectangle^ positionInPortraitMode;

		ClrWatermarkOptions() :
			visibleInPreview(false),
			positionInLandscapeMode(gcnew ClrRectangle()),
			positionInPortraitMode(gcnew ClrRectangle())
		{}

		operator WatermarkOptions() {
			WatermarkOptions options;
			options.visibleInPreview = visibleInPreview;
			options.positionInLandscapeMode = positionInLandscapeMode->operator agora::rtc::Rectangle();
			options.positionInPortraitMode = positionInPortraitMode->operator agora::rtc::Rectangle();
			return options;
		}

	};

	public ref class ClrCameraCaptureConfiguration {
	public:
		EnumCapturerOutputPreference preference;

		operator CameraCapturerConfiguration() {
			CameraCapturerConfiguration config;
			config.preference = static_cast<CAPTURER_OUTPUT_PREFERENCE>(preference);
			return config;
		}
	};
	
	public ref class ClrBeautyOptions {
	public:
		EnumLighteningContrastLevel lighteningContrastLevel;
		float lighteningLevel;
		float smoothnessLevel;
		float rednessLevel;

		ClrBeautyOptions() :
			lighteningLevel(0),
			smoothnessLevel(0),
			rednessLevel(0),
			lighteningContrastLevel(EnumLighteningContrastLevel::LIGHTENING_CONTRAST_NORMAL) {}

		operator BeautyOptions () {
			return BeautyOptions(
				static_cast<BeautyOptions::LIGHTENING_CONTRAST_LEVEL>(lighteningContrastLevel),
				lighteningLevel,
				smoothnessLevel,
				rednessLevel
				);
		}

	};
}