#include "stdafx.h"
#include "AgoraClrMetadataObserver.h"

int AgoraClrLibrary::AgoraClrMetadataObserver::getMaxMetadataSize()
{
	if (onGetMaxMetadataSizeEvent) return onGetMaxMetadataSizeEvent();
	else return 1024;
}

bool AgoraClrLibrary::AgoraClrMetadataObserver::onReadyToSendMetadata(Metadata& metadata)
{
	if (onReadyToSendMetadataEvent) return onReadyToSendMetadataEvent(metadata);
	else return false;
}

void AgoraClrLibrary::AgoraClrMetadataObserver::onMetadataReceived(const Metadata& metadata)
{
	if (onMetadataReceivedEvent) return onMetadataReceivedEvent(metadata);
}
