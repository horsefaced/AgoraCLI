﻿#pragma once

#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrEventHandler.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrRawFrameObserver.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrLibraryEnum.h"

#include "windef.h"

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
			strcpy_s(dest, source.length() + 1, source.c_str());
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
		UINT uid;
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
	ref class ClrRtcStats
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

		ClrRtcStats(agora::rtc::RtcStats raw)
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
		UINT txPacketLossRate;
		int captureFrameRate;

		ClrLocalVideoStats(const LocalVideoStats& stats) :
			sentBitrate(stats.sentBitrate),
			sentFrameRate(stats.sentFrameRate),
			encoderOutputFrameRate(stats.encoderOutputFrameRate),
			rendererOutputFrameRate(stats.rendererOutputFrameRate),
			targetBitrate(stats.targetBitrate),
			targetFrameRate(stats.targetFrameRate),
			qualityAdaptIndication(static_cast<QualityAdaptIndication>(stats.qualityAdaptIndication)),
			encodedBitrate(stats.encodedBitrate),
			encodedFrameWidth(stats.encodedFrameWidth),
			encodedFrameHeight(stats.encodedFrameHeight),
			encodedFrameCount(stats.encodedFrameCount),
			codecType(static_cast<VideoCodecType>(stats.codecType)),
			txPacketLossRate(stats.txPacketLossRate),
			captureFrameRate(stats.captureFrameRate)
		{}
	};

	public
	ref class ClrRemoteVideoStats
	{
	public:
		UINT uid;
		int delay;
		int width;
		int height;
		int receivedBitrate;
		int decoderOutputFrameRate;
		int rendererOutputFrameRate;
		int packedLossRate;
		EnumRemoteVideoStreamType rxStreamType;
		int totalFrozenTime;
		int frozenRate;
		int totalActiveTime;
		int publishDuration;

		ClrRemoteVideoStats(agora::rtc::RemoteVideoStats stats)
		{
			uid = stats.uid;
			delay = stats.delay;
			width = stats.width;
			height = stats.height;
			receivedBitrate = stats.receivedBitrate;
			decoderOutputFrameRate = stats.decoderOutputFrameRate;
			rendererOutputFrameRate = stats.rendererOutputFrameRate;
			packedLossRate = stats.packetLossRate;

			rxStreamType = static_cast<EnumRemoteVideoStreamType>(stats.rxStreamType);

			totalFrozenTime = stats.totalFrozenTime;
			frozenRate = stats.frozenRate;
			totalActiveTime = stats.totalActiveTime;

			publishDuration = stats.publishDuration;
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
			packet.buffer = static_cast<unsigned char*>(tmp);
			packet.size = buffer->Length;
		}
	};

	public
	ref class ClrAudioFrame
	{
	private:
		agora::media::IAudioFrameObserver::AudioFrame* raw=nullptr;
	public:
		EnumAudioFrameType type;
		int samples;
		int bytesPerSample;
		int channels;
		int samplesPerSec;
		array<Byte>^ data;
		int64_t renderTimeMs;
		int avsync_type;

		ClrAudioFrame() {}

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
			raw.type = static_cast<agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE>(type);
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
			if(raw)
				return raw;
			raw = new agora::media::IAudioFrameObserver::AudioFrame();
			writeRaw(*raw);
			return raw;
		}

		~ClrAudioFrame()
		{
			if(raw)
			{
				delete raw;
				raw = nullptr;
			}
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
	private:
		agora::rtc::Rect* result=nullptr;
	public:
		int top;
		int left;
		int bottom;
		int right;

		ClrRect() : top(0), left(0), bottom(0), right(0) {}
		ClrRect(int t, int l, int b, int r) : top(t), left(l), bottom(b), right(r) {}

		agora::rtc::Rect* toRaw()
		{
			if(result)
				return result;
			result = new agora::rtc::Rect();
			result->top = top;
			result->left = left;
			result->bottom = bottom;
			result->right = right;
			return result;
		}
		~ClrRect()
		{
			if(result)
			{
				delete result;
				result = nullptr;
			}
		}
	};

	public
	ref class ClrTranscodingUser
	{
	private:
		TranscodingUser* result=nullptr;
	public:
		UINT uid;

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
			if(result)
				return result;
			result = new TranscodingUser();
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

		~ClrTranscodingUser()
		{
			if(result)
			{
				delete result;
				result=nullptr;
			}
		}
	};

	public
	ref class ClrRtcImage
	{
	private:
		RtcImage* raw = nullptr;
	public:
		ClrRtcImage() : url(nullptr),
			x(0),
			y(0),
			width(0),
			height(0),
			zOrder(0),
			alpha(0)
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
		int zOrder;
		double alpha;

		operator RtcImage* ()
		{
			if(raw)
				return raw;
			raw = new RtcImage();
			raw->x = x;
			raw->y = y;
			raw->width = width;
			raw->height = height;
			raw->url = strcopy(MarshalString(url));
			raw->zOrder = zOrder;
			raw->alpha = alpha;
			return raw;
		}

		RtcImage* getRaw() {
			auto raw = new RtcImage();
			raw->x = x;
			raw->y = y;
			raw->width = width;
			raw->height = height;
			raw->url = strcopy(MarshalString(url));
			raw->zOrder = zOrder;
			raw->alpha = alpha;
			return raw;
		}

		~ClrRtcImage()
		{
			if(raw)
			{
				delete raw;
				raw=nullptr;
			}
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
		String^ metadata = nullptr;
		List<ClrRtcImage^>^ watermark = nullptr;
		List<ClrRtcImage^>^ backgroundImage = nullptr;
		AudioSampleRateType audioSampleRate;
		int audioBitrate;
		int audioChannels;
		AudioCodecProfileType audioCodecProfile;

		ClrLiveTranscoding()
			: width(360), height(640), videoBitrate(400), 
			videoFramerate(15), lowLatency(false), 
			backgroundColor(0x000000), videoGop(30), 
			videoCodecProfile(VideoCodecProfileType::VIDEO_CODEC_PROFILE_HIGH),
			userCount(0), transcodingUsers(), 
			transcodingExtraInfo(nullptr), 
			audioSampleRate(AudioSampleRateType::AUDIO_SAMPLE_RATE_48000), 
			audioBitrate(48), audioChannels(1)
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
			if (watermark != nullptr) {
				delete[] this->watermarks;
				this->watermarks = new RtcImage[watermark->Count];
				for each (ClrRtcImage ^ image in watermark) {
					this->watermarks = image->getRaw();
					this->watermarks++;
				}
				raw.watermark = this->watermarks;
				raw.watermarkCount = watermark->Count;
			}
			else {
				raw.watermark = nullptr;
				raw.watermarkCount = 0;
			}

			if (backgroundImage != nullptr) {
				delete[] this->backgroundImages;
				this->backgroundImages = new RtcImage[backgroundImage->Count];
				for each (ClrRtcImage ^ image in backgroundImage) {
					this->backgroundImages = image->getRaw();
					this->backgroundImages++;
				}
				raw.backgroundImage = this->backgroundImages;
				raw.backgroundImageCount = backgroundImage->Count;
			}
			else {
				raw.backgroundImage = nullptr;
				raw.backgroundImageCount = backgroundImage->Count;
			}

			raw.audioSampleRate = static_cast<AUDIO_SAMPLE_RATE_TYPE>(audioSampleRate);
			raw.audioBitrate = audioBitrate;
			raw.audioChannels = audioChannels;
			raw.audioCodecProfile = static_cast<AUDIO_CODEC_PROFILE_TYPE>(audioCodecProfile);
			return raw;
		}

		~ClrLiveTranscoding() {
			delete[] watermarks;
			delete[] backgroundImages;
		}
	private:
		RtcImage* watermarks = nullptr;
		RtcImage* backgroundImages = nullptr;
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
			raw.audioSampleRate = static_cast<AUDIO_SAMPLE_RATE_TYPE>(audioSampleRate);
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
		bool windowFocus;
		List<IntPtr> excludeWindows;

		ClrScreenCaptureParameters() : 
			dimensions(), 
			frameRate(5), 
			bitrate(0), 
			captureMouseCursor(false), 
			windowFocus(false),
			excludeWindows(gcnew List<IntPtr>())
		{}
		operator agora::rtc::ScreenCaptureParameters() { 
			auto result = agora::rtc::ScreenCaptureParameters(
				dimensions->width, 
				dimensions->height, 
				frameRate, 
				bitrate, 
				captureMouseCursor,
				windowFocus); 
			result.excludeWindowCount = this->excludeWindows.Count;
			if (result.excludeWindowCount == 0) result.excludeWindowList = NULL;
			else {
				result.excludeWindowList = new view_t[result.excludeWindowCount];
				for (int i = 0; i < result.excludeWindowCount; i++) {
					result.excludeWindowList[i] = this->excludeWindows[i].ToPointer();
				}
			}
			return result;
		}
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
			raw.frameRate = static_cast<FRAME_RATE>(frameRate);
			raw.minFrameRate = minFrameRate;
			raw.bitrate = bitrate;
			raw.minBitrate = minBitrate;
			raw.orientationMode = static_cast<ORIENTATION_MODE>(orientationMode);
			raw.degradationPreference = static_cast<DEGRADATION_PREFERENCE>(degradationPreference);
			raw.mirrorMode = static_cast<VIDEO_MIRROR_MODE_TYPE>(mirrorMode);
			return raw;
		}

	};


	public
	ref class ClrExternalVideoFrame
	{
	private:
		ExternalVideoFrame* result = nullptr;
	public:
		VideoBufferType type;
		EnumVideoPixelFormat format;
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
			if(result)
				return result;
			result = new ExternalVideoFrame();
			result->type = static_cast<ExternalVideoFrame::VIDEO_BUFFER_TYPE>(type);
			result->format = static_cast<ExternalVideoFrame::VIDEO_PIXEL_FORMAT>(format);
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

		~ClrExternalVideoFrame()
		{
			if(result)
			{
				free(result->buffer);
				result->buffer=nullptr;
				delete result;
				result = nullptr;
			}
		}
	};


	public
	ref class ClrRemoteAudioStats
	{
	public:
		UINT uid;
		int quality;
		int networkTransportDelay;
		int jitterBufferDelay;
		int audioLossRate;
		int numChannels;
		int receivedSampleRate;
		int receivedBitrate;
		int totalFrozenTime;
		int frozenRate;
		int totalActiveTime;
		int publishDuration;
		int qoeQuality;
		int qualityChangedReason;
		int mosValue;

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
			frozenRate(raw.frozenRate),
			totalActiveTime(raw.totalActiveTime),
			publishDuration(raw.publishDuration),
			qoeQuality(raw.qoeQuality),
			qualityChangedReason(raw.qualityChangedReason),
			mosValue(raw.mosValue)
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
			raw.totalActiveTime = totalActiveTime;
			raw.publishDuration = publishDuration;
			raw.qoeQuality = qoeQuality;
			raw.qualityChangedReason = qualityChangedReason;
			raw.mosValue = mosValue;
		}
	};

	public ref class ClrLocalAudioStats {
	public:
		int numChannels;
		int sentSampleRate;
		int sentBitrate;
		UINT txPacketLossRate;

		ClrLocalAudioStats() : numChannels(0), sentSampleRate(0), sentBitrate(0), txPacketLossRate(0) {}
		ClrLocalAudioStats(const LocalAudioStats& stats) : 
			numChannels(stats.numChannels), 
			sentSampleRate(stats.sentSampleRate), 
			sentBitrate(stats.sentBitrate),
			txPacketLossRate(stats.txPacketLossRate)
		{}
	};

	public ref class ClrChannelMediaInfo {
	private:
		ChannelMediaInfo* info = nullptr;
	public:
		String^ channel;
		String^ token;
		uid_t uid;

		operator ChannelMediaInfo* () {
			if(info)
				return  info;
			info = new ChannelMediaInfo();
			info->channelName = MarshalString(channel).c_str();
			info->token = MarshalString(token).c_str();
			info->uid = uid;
			return info;
		}

		~ClrChannelMediaInfo()
		{
			if(info)
			{
				delete info;
				info=nullptr;
			}
		}
	};

	public ref class ClrChannelMediaOptions {
	public:
		bool autoSubscribeAudio;
		bool autoSubscribeVideo;
		bool publishLocalAudio;
		bool publishLocalVideo;

		ClrChannelMediaOptions() :
			autoSubscribeAudio(true),
			autoSubscribeVideo(true),
			publishLocalAudio(true),
			publishLocalVideo(true)
		{}

		operator ChannelMediaOptions () {
			ChannelMediaOptions result;
			result.autoSubscribeAudio = autoSubscribeAudio;
			result.autoSubscribeVideo = autoSubscribeVideo;
			result.publishLocalAudio = publishLocalAudio;
			result.publishLocalVideo = publishLocalVideo;
			return result;
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
		float sharpnessLevel;

		ClrBeautyOptions() :
			lighteningLevel(0),
			smoothnessLevel(0),
			rednessLevel(0),
			sharpnessLevel(0),
			lighteningContrastLevel(EnumLighteningContrastLevel::LIGHTENING_CONTRAST_NORMAL) {}

		operator BeautyOptions () {
			return BeautyOptions(
				static_cast<BeautyOptions::LIGHTENING_CONTRAST_LEVEL>(lighteningContrastLevel),
				lighteningLevel,
				smoothnessLevel,
				rednessLevel,
				sharpnessLevel
				);
		}

	};

	public ref class ClrEncryptionConfig {
	public:
		String^ key;
		EnumEncryptionMode mode;
		array<UINT8>^ salt;

		ClrEncryptionConfig() : mode(EnumEncryptionMode::AES_128_XTS), key(nullptr), salt(gcnew array<UINT8>(32)) {}

		operator EncryptionConfig() {
			auto result = EncryptionConfig();
			result.encryptionKey = key == nullptr ? NULL : MarshalString(key).c_str();
			result.encryptionMode = (ENCRYPTION_MODE)mode;
			Marshal::Copy(salt, 0, IntPtr(result.encryptionKdfSalt), sizeof(result.encryptionKdfSalt));
			return result;
		}
	};

	public ref class ClrLogConfig {
	public:
		String^ filePath = nullptr;
		int fileSize = -1;
		EnumLogLevel level = EnumLogLevel::LOG_LEVEL_INFO;

		LogConfig to() {
			auto result = LogConfig();
			result.filePath = filePath == nullptr ? NULL : MarshalString(filePath).c_str();
			result.fileSize = fileSize;
			result.level = (agora::LOG_LEVEL)level;
			return result;
		}
	};

	public ref class ClrRtcEngineContext {
	public:
		String^ vendorKey = nullptr;
		EnumAreaCode areaCode = EnumAreaCode::AREA_CODE_GLOB;
		ClrLogConfig^ logConfig = gcnew ClrLogConfig();
	};

	public ref class ClrDataStreamConfig {
	public:
		bool syncWithAudio;
		bool ordered;

		operator DataStreamConfig() {
			auto result = DataStreamConfig();
			result.ordered = ordered;
			result.syncWithAudio = syncWithAudio;
			return result;
		}
	};
	
	public ref class ClrAudioRecordingConfiguration {
	public:
		String^ filePath;
		AudioRecordingQualityType recordingQuality;
		EnumAudioRecordingPosition recordingPosition;
		int recordingSampleRate;

		operator AudioRecordingConfiguration () {
			auto result = AudioRecordingConfiguration();
			result.filePath = filePath == nullptr ? NULL : MarshalString(filePath).c_str();
			result.recordingQuality = (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)recordingQuality;
			result.recordingPosition = (agora::rtc::AUDIO_RECORDING_POSITION)recordingPosition;
			result.recordingSampleRate = recordingSampleRate;
			return result;
		}
	}; 

	public ref class ClrAudioFileInfo {
	public:
		String^ filePath;
		int durationMs;

		ClrAudioFileInfo(){}
		ClrAudioFileInfo(AudioFileInfo info) :filePath(gcnew String(info.filePath)), durationMs(info.durationMs){}

		operator AudioFileInfo() {
			auto result = AudioFileInfo();
			result.filePath = filePath == nullptr ? NULL : MarshalString(filePath).c_str();
			result.durationMs = durationMs;
			return result;
		}
	};

	public ref class ClrEchoTestConfiguration {
	public:
		IntPtr view;
		bool enableAudio;
		bool enableVideo;
		String^ token;
		String^ channelId;

		ClrEchoTestConfiguration(): view(nullptr), enableAudio(true), enableVideo(true), token(nullptr), channelId(nullptr) {}
		operator agora::rtc::EchoTestConfiguration() {
			return EchoTestConfiguration(view.ToPointer(), enableAudio, enableVideo, MarshalString(token).c_str(), MarshalString(channelId).c_str());
		}
	};

	public ref class ClrThumbImageBuffer {
	public:
		array<unsigned char>^ buffer;
		int width;
		int height;

		ClrThumbImageBuffer(const agora::rtc::ThumbImageBuffer& buffer)
		{
			this->buffer = gcnew array<unsigned char>(buffer.length);
			Marshal::Copy(IntPtr(const_cast<void*>(static_cast<const void*>(buffer.buffer))), this->buffer, 0, buffer.length);
		}
	};

	public ref class ClrScreenCaptureSourceInfo {
	public:
		EnumScreenCaptureSourceType type;
		IntPtr sourceId;
		String^ sourceName;
		ClrThumbImageBuffer thumbImage;
		ClrThumbImageBuffer iconImage;
		String^ processPath;
		String^ sourceTitle;
		bool primaryMonitor;

		ClrScreenCaptureSourceInfo(const agora::rtc::ScreenCaptureSourceInfo& info) :
			type(static_cast<EnumScreenCaptureSourceType>(info.type)),
			sourceId(info.sourceId),
			sourceName(gcnew String(info.sourceName)),
			thumbImage(info.thumbImage),
			iconImage(info.iconImage),
			processPath(gcnew String(info.processPath)),
			primaryMonitor(info.primaryMonitor)
		{

		}

	};

	public ref class ClrScreenCaptureSourceInfoList {
	public:
		List<ClrScreenCaptureSourceInfo^>^ infos;

		ClrScreenCaptureSourceInfoList(agora::rtc::IScreenCaptureSourceList* list) : infos(gcnew List<ClrScreenCaptureSourceInfo^>())
		{
			this->list = list;
			for (int i = 0; i < list->getCount(); i++) {
				infos->Add(gcnew ClrScreenCaptureSourceInfo(list->getSourceInfo(i)));
			}
		}

		~ClrScreenCaptureSourceInfoList() {
			if (this->list) this->list->release();
		}
	private:
		agora::rtc::IScreenCaptureSourceList* list = nullptr;
	};

	public ref class ClrSize {
	public:
		int width;
		int height;

		operator tagSIZE () {
			return tagSIZE{ width, height };
		}
	};
 }