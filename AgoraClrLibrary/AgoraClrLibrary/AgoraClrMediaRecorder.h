#pragma once

#include "..\..\agorasdk\include\IAgoraRtcEngine.h"
#include "..\include\common.h"
#include "AgoraClrLibraryTypes.h"

using namespace agora::rtc;
using namespace System;
using namespace System::Collections::Generic;
using namespace Runtime::InteropServices;

namespace AgoraClrLibrary {

	public enum class EnumMediaRecorderContainerFormat {
		FORMAT_MP4 = 1,
		FORMAT_FLV = 2,
	};

	public enum class EnumMediaRecorderStreamType {
		STREAM_TYPE_AUDIO = 0x01,
		STREAM_TYPE_VIDEO = 0x02,
		STREAM_TYPE_BOTH = STREAM_TYPE_AUDIO | STREAM_TYPE_VIDEO,
	};

	public ref class ClrMediaRecorderConfiguration {
	public:
		String^ storagePath;
		EnumMediaRecorderContainerFormat format;
		EnumMediaRecorderStreamType streamType;
		int maxDurationMs;
		int recorderInfoUpdateInterval;

		ClrMediaRecorderConfiguration():
			storagePath(nullptr),
			format(EnumMediaRecorderContainerFormat::FORMAT_MP4),
			streamType(EnumMediaRecorderStreamType::STREAM_TYPE_BOTH),
			maxDurationMs(120000),
			recorderInfoUpdateInterval(0) {}

		operator MediaRecorderConfiguration() {
			return MediaRecorderConfiguration(
				MarshalString(storagePath).c_str(),
				static_cast<MediaRecorderContainerFormat>(format),
				static_cast<MediaRecorderStreamType>(streamType),
				maxDurationMs,
				recorderInfoUpdateInterval);
		}
	};

	public enum class EnumRecorderState {
		RECORDER_STATE_ERROR = -1,
		RECORDER_STATE_START = 2,
		RECORDER_STATE_STOP = 3,
	};

	public enum class EnumRecorderErrorCode {
		RECORDER_ERROR_NONE = 0,
		RECORDER_ERROR_WRITE_FAILED = 1,
		RECORDER_ERROR_NO_STREAM = 2,
		RECORDER_ERROR_OVER_MAX_DURATION = 3,
		RECORDER_ERROR_CONFIG_CHANGED = 4,
		RECORDER_ERROR_CUSTOM_STREAM_DETECTED = 5,
	};

	public ref class ClrRecorderInfo {
	public:
		String^ fileName;
		unsigned int durationMs;
		unsigned int fileSize;

		ClrRecorderInfo() {}
		ClrRecorderInfo(const RecorderInfo info) {
			fileName = gcnew String(info.fileName);
			durationMs = info.durationMs;
			fileSize = info.fileSize;
		}
	};

	using OnRecorderStateChanged = ET<RecorderState, RecorderErrorCode>;
	using OnRecorderInfoUpdated = ET<const RecorderInfo&>;

	public class MediaRecorderObserver : public IMediaRecorderObserver {
	public:
		OnRecorderStateChanged::Pointer onRecorderStateChangedEvent = nullptr;
		OnRecorderInfoUpdated::Pointer onRecorderInfoUpdatedEvent = nullptr;
	public:
		void onRecorderStateChanged(RecorderState state, RecorderErrorCode error);
		void onRecorderInfoUpdated(const RecorderInfo& info);
	};

	public ref class AgoraClrMediaRecorder
	{
	public:
		int startRecording(ClrMediaRecorderConfiguration^ config);
		int stopRecording();
		void releaseRecorder();
	public:
		AT<EnumRecorderState, EnumRecorderErrorCode>::Type^ onRecorderStateChanged;
		AT<ClrRecorderInfo^>::Type^ onRecorderInfoUpdated;

		~AgoraClrMediaRecorder();

		AgoraClrMediaRecorder(IRtcEngine* engine);
	private:
		void NativeOnRecorderStateChanged(RecorderState state, RecorderErrorCode error);
		void NativeOnRecorderInfoUpdated(const RecorderInfo& info);
	private:
		void* regEvent(Object^ obj);
		void bindObserver();
	private:
		IMediaRecorder* recorder = nullptr;
		MediaRecorderObserver* observer = nullptr;
		List<GCHandle>^ gchs;
	};

}
