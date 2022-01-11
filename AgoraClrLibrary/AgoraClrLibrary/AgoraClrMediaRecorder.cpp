#include "AgoraClrMediaRecorder.h"

void AgoraClrLibrary::MediaRecorderObserver::onRecorderStateChanged(RecorderState state, RecorderErrorCode error)
{
	if (onRecorderInfoUpdatedEvent) onRecorderStateChangedEvent(state, error);
}

void AgoraClrLibrary::MediaRecorderObserver::onRecorderInfoUpdated(const RecorderInfo& info)
{
	if (onRecorderInfoUpdatedEvent) onRecorderInfoUpdatedEvent(info);
}

int AgoraClrLibrary::AgoraClrMediaRecorder::startRecording(ClrMediaRecorderConfiguration^ config)
{
	if (this->recorder) {
		return this->recorder->startRecording(config);
	}
	else return 0;
}

int AgoraClrLibrary::AgoraClrMediaRecorder::stopRecording()
{
	if (this->recorder) return this->recorder->stopRecording();
	else return 0;
}

void AgoraClrLibrary::AgoraClrMediaRecorder::releaseRecorder()
{
	if (this->recorder) {
		this->recorder->releaseRecorder();
		delete this->recorder;
	}
}

AgoraClrLibrary::AgoraClrMediaRecorder::~AgoraClrMediaRecorder()
{
	this->releaseRecorder();
	for each (GCHandle handle in gchs) handle.Free();
	delete this->observer;
}

AgoraClrLibrary::AgoraClrMediaRecorder::AgoraClrMediaRecorder(IRtcEngine* engine):
	observer(new MediaRecorderObserver),
	gchs(gcnew List<GCHandle>())
{
	this->recorder = IMediaRecorder::getMediaRecorder(engine, this->observer);
	this->bindObserver();
}

void AgoraClrLibrary::AgoraClrMediaRecorder::NativeOnRecorderStateChanged(RecorderState state, RecorderErrorCode error)
{
	if (this->onRecorderStateChanged) {
		this->onRecorderStateChanged(
			static_cast<EnumRecorderState>(state),
			static_cast<EnumRecorderErrorCode>(error));
	}
}

void AgoraClrLibrary::AgoraClrMediaRecorder::NativeOnRecorderInfoUpdated(const RecorderInfo& info)
{
	if (this->onRecorderInfoUpdated)
		this->onRecorderInfoUpdated(gcnew ClrRecorderInfo(info));
}

void AgoraClrLibrary::AgoraClrMediaRecorder::bindObserver()
{
	if (this->observer) {
		this->observer->onRecorderInfoUpdatedEvent = static_cast<OnRecorderInfoUpdated::Pointer>(regEvent(gcnew OnRecorderInfoUpdated::Type(this, &AgoraClrMediaRecorder::NativeOnRecorderInfoUpdated)));
		this->observer->onRecorderStateChangedEvent = static_cast<OnRecorderStateChanged::Pointer>(regEvent(gcnew OnRecorderStateChanged::Type(this, &AgoraClrMediaRecorder::NativeOnRecorderStateChanged)));
	}
}

void* AgoraClrLibrary::AgoraClrMediaRecorder::regEvent(Object^ obj)
{
	gchs->Add(GCHandle::Alloc(obj));
	return Marshal::GetFunctionPointerForDelegate(obj).ToPointer();
}
