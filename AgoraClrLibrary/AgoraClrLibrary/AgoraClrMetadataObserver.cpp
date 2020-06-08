#include "stdafx.h"
#include "AgoraClrMetadataObserver.h"
using namespace AgoraClrLibrary;

int AgoraClrMetadataObserver::getMaxMetadataSize()
{
	if (onGetMaxMetadataSizeEvent) return onGetMaxMetadataSizeEvent();
	return 1024;
}

bool AgoraClrMetadataObserver::onReadyToSendMetadata(Metadata& metadata)
{
	if (onReadyToSendMetadataEvent) return onReadyToSendMetadataEvent(metadata);
	return false;
}

void AgoraClrMetadataObserver::onMetadataReceived(const Metadata& metadata)
{
	if (onMetadataReceivedEvent) return onMetadataReceivedEvent(metadata);
}
