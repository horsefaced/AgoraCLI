#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "AgoraClrLibraryTypes.h"
#include "..\include\common.h"

using namespace agora::rtc;

namespace AgoraClrLibrary {

	public class NativeVideoSink : public IVideoSink {
	public:
		using OnInitialize = FT<bool>;
		using OnDispose = ET<void>;
		using OnStart = FT<bool>;
		using OnStop = ET<void>;
		using GetBufferType = FT<ExternalVideoFrame::VIDEO_BUFFER_TYPE>;
		using GetPixelFormat = FT<ExternalVideoFrame::VIDEO_PIXEL_FORMAT>;
		using OnRenderRawData = ET<uint8_t*, int, int, int>;

	public:
		OnInitialize::Pointer onInitializeEvent = nullptr;
		OnDispose::Pointer onDisposeEvent = nullptr;
		OnStart::Pointer onStartEvent = nullptr;
		OnStop::Pointer onStopEvent = nullptr;
		GetBufferType::Pointer getBufferTypeEvent = nullptr;
		GetPixelFormat::Pointer getPixelFormatEvent = nullptr;
		OnRenderRawData::Pointer onRenderRawDataEvent = nullptr;

	public:
		virtual bool onInitialize() override;
		virtual void onDispose() override;
		virtual bool onStart() override;
		virtual void onStop() override;
		virtual ExternalVideoFrame::VIDEO_BUFFER_TYPE getBufferType() override;
		virtual ExternalVideoFrame::VIDEO_PIXEL_FORMAT getPixelFormat() override;
		virtual void onRenderRawData(uint8_t* rawData, int width, int height, int rotation) override;
	};

	public interface class ClrVideoSink {
		bool onInitialize();
		bool onStart();
		void onStop();
		void onDispose();
		VideoBufferType getBufferType();
		EnumVideoPixelFormat getPixelFormat();

		void onRenderRawData(array<Byte>^ rawData, int width, int height, int rotation);
	};

	public ref class InnerVideoSink {
	public:
		InnerVideoSink(ClrVideoSink^ clr);
		~InnerVideoSink();
		!InnerVideoSink();

		operator IVideoSink* () {
			return this->raw;
		}
		void dispose();

	private:
		void linkClrToRaw();
		void* regEvent(Object^ obj);

		bool NativeOnInitialize();
		bool NativeOnStart();
		void NativeOnStop();
		void NativeOnDispose();
		
		ExternalVideoFrame::VIDEO_BUFFER_TYPE NativeGetBufferType();
		ExternalVideoFrame::VIDEO_PIXEL_FORMAT NativeGetPixelFormat();
		
		void NativeOnRenderRawData(uint8_t* rawData, int width, int height, int rotation);
	private:
		ClrVideoSink^ clr;
		NativeVideoSink* raw;
		List<GCHandle>^ gchs;
		ExternalVideoFrame::VIDEO_PIXEL_FORMAT pixelFormat;
		int getRawDataSize(ExternalVideoFrame::VIDEO_PIXEL_FORMAT format, int width, int height);
	};
}
