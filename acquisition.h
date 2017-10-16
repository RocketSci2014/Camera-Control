#ifndef ACQUISITION_H
#define ACQUISITION_H

#include "IMAQdxController.h"
#define IMAQdxAttributeShutterMode "CameraAttributes::Shutter::Mode"
#define IMAQdxAttributeShutterValue "CameraAttributes::Shutter::Value"

float64 getExposureTime();
bool initIntAcquire(IMAQdxSession session);
bool intAcquire(IMAQdxSession session, Image* image);
float64 setExposureTime(float64 expTime);
const char* setOutputDirectory(const char* outDir);
int setImageIndex(int imgIndex);
int setSeriesIndex(int sIndex);

#endif
