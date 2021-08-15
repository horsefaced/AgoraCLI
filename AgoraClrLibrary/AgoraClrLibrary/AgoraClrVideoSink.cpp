#include "AgoraClrVideoSink.h"

bool AgoraClrLibrary::NativeVideoSink::onInitialize()
{
    if (this->onInitializeEvent)
        return this->onInitializeEvent();
    return false;
}

void AgoraClrLibrary::NativeVideoSink::onDispose()
{
    if (this->onDisposeEvent) this->onDisposeEvent();
}

bool AgoraClrLibrary::NativeVideoSink::onStart()
{
    if (this->onStartEvent) return this->onStartEvent();
    return false;
}

void AgoraClrLibrary::NativeVideoSink::onStop()
{
    if (this->onStopEvent) this->onStopEvent();
}

ExternalVideoFrame::VIDEO_BUFFER_TYPE AgoraClrLibrary::NativeVideoSink::getBufferType()
{
    if (this->getBufferTypeEvent) return this->getBufferTypeEvent();
    else return ExternalVideoFrame::VIDEO_BUFFER_TYPE::VIDEO_BUFFER_RAW_DATA;
}

ExternalVideoFrame::VIDEO_PIXEL_FORMAT AgoraClrLibrary::NativeVideoSink::getPixelFormat()
{
    if (this->getPixelFormatEvent) return this->getPixelFormatEvent();
    else return ExternalVideoFrame::VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_NV21;
}

void AgoraClrLibrary::NativeVideoSink::onRenderRawData(uint8_t* rawData, int width, int height, int rotation)
{
    if (this->onRenderRawDataEvent) this->onRenderRawDataEvent(rawData, width, height, rotation);
}

AgoraClrLibrary::InnerVideoSink::InnerVideoSink(ClrVideoSink^ clr):
    clr(clr),
    raw(new NativeVideoSink()),
    gchs(gcnew List<GCHandle>()),
    pixelFormat(ExternalVideoFrame::VIDEO_PIXEL_NV21)
{
    this->linkClrToRaw();
}

AgoraClrLibrary::InnerVideoSink::~InnerVideoSink()
{
    dispose();
}

AgoraClrLibrary::InnerVideoSink::!InnerVideoSink()
{
    dispose();
}

void AgoraClrLibrary::InnerVideoSink::dispose()
{
    delete raw;
    for each (GCHandle handle in gchs) handle.Free();
}

void AgoraClrLibrary::InnerVideoSink::linkClrToRaw()
{
    this->raw->onInitializeEvent = static_cast<NativeVideoSink::OnInitialize::Pointer>(regEvent(gcnew NativeVideoSink::OnInitialize::Type(this, &InnerVideoSink::NativeOnInitialize)));
    this->raw->onDisposeEvent = static_cast<NativeVideoSink::OnDispose::Pointer>(regEvent(gcnew NativeVideoSink::OnDispose::Type(this, &InnerVideoSink::NativeOnDispose)));
    this->raw->onStartEvent = static_cast<NativeVideoSink::OnStart::Pointer>(regEvent(gcnew NativeVideoSink::OnStart::Type(this, &InnerVideoSink::NativeOnStart)));
    this->raw->onStopEvent = static_cast<NativeVideoSink::OnStop::Pointer>(regEvent(gcnew NativeVideoSink::OnStop::Type(this, &InnerVideoSink::NativeOnStop)));
    this->raw->onRenderRawDataEvent = static_cast<NativeVideoSink::OnRenderRawData::Pointer>(regEvent(gcnew NativeVideoSink::OnRenderRawData::Type(this, &InnerVideoSink::NativeOnRenderRawData)));
    this->raw->getBufferTypeEvent = static_cast<NativeVideoSink::GetBufferType::Pointer>(regEvent(gcnew NativeVideoSink::GetBufferType::Type(this, &InnerVideoSink::NativeGetBufferType)));
    this->raw->getPixelFormatEvent = static_cast<NativeVideoSink::GetPixelFormat::Pointer>(regEvent(gcnew NativeVideoSink::GetPixelFormat::Type(this, &InnerVideoSink::NativeGetPixelFormat)));
}

void* AgoraClrLibrary::InnerVideoSink::regEvent(Object^ obj)
{
    gchs->Add(GCHandle::Alloc(obj));
    return Marshal::GetFunctionPointerForDelegate(obj).ToPointer();
}

bool AgoraClrLibrary::InnerVideoSink::NativeOnInitialize()
{
    return clr->onInitialize();
}

bool AgoraClrLibrary::InnerVideoSink::NativeOnStart()
{
    return clr->onStart();
}

void AgoraClrLibrary::InnerVideoSink::NativeOnStop()
{
    clr->onStop();
}

void AgoraClrLibrary::InnerVideoSink::NativeOnDispose()
{
    clr->onDispose();
}

ExternalVideoFrame::VIDEO_BUFFER_TYPE AgoraClrLibrary::InnerVideoSink::NativeGetBufferType()
{
    return static_cast<ExternalVideoFrame::VIDEO_BUFFER_TYPE>(clr->getBufferType());
}

ExternalVideoFrame::VIDEO_PIXEL_FORMAT AgoraClrLibrary::InnerVideoSink::NativeGetPixelFormat()
{
    this->pixelFormat = static_cast<ExternalVideoFrame::VIDEO_PIXEL_FORMAT>(clr->getPixelFormat());
    return this->pixelFormat;
}

void AgoraClrLibrary::InnerVideoSink::NativeOnRenderRawData(uint8_t* rawData, int width, int height, int rotation)
{
    auto size = this->getRawDataSize(this->pixelFormat, width, height);
    auto buffer = gcnew array<Byte>(size);
    Marshal::Copy(IntPtr(rawData), buffer, 0, size);
    clr->onRenderRawData(buffer, width, height, rotation);
}

int AgoraClrLibrary::InnerVideoSink::getRawDataSize(ExternalVideoFrame::VIDEO_PIXEL_FORMAT format, int width, int height)
{
    switch (format) {
    case ExternalVideoFrame::VIDEO_PIXEL_UNKNOWN:
    case ExternalVideoFrame::VIDEO_PIXEL_I420:
    case ExternalVideoFrame::VIDEO_PIXEL_NV21:
    case ExternalVideoFrame::VIDEO_PIXEL_IMC2:
    case ExternalVideoFrame::VIDEO_PIXEL_NV12:
        return width * height * 3 / 2;
    case ExternalVideoFrame::VIDEO_PIXEL_I422:
        return width * height * 2;
    case ExternalVideoFrame::VIDEO_PIXEL_ARGB:
    case ExternalVideoFrame::VIDEO_PIXEL_RGBA:
    case ExternalVideoFrame::VIDEO_PIXEL_BGRA:
        return width * height * 4;
    }
}



