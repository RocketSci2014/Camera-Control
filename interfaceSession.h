#ifndef INTERFACE_SESSION_H
#define INTERFACE_SESSION_H

#include "IMAQdxController.h"
#define IMAQdxAttribureBayerAlgorithm "AcquisitionAttributes::Bayer::Algorithm"
#define IMAQdxAttributeFrameRateMode "CameraAttributes::FrameRate::Mode"
#define IMAQdxAttribureFrameRateValue "CameraAttributes::FrameRate::Value"

bool closeIMAQdxSession(IMAQdxSession session);
const char* getInterfaceName(int intNameDx);
bool openIMAQdxSession(IMAQdxSession* session, const char* camName);
bool setupInterfaceNames();

#endif


