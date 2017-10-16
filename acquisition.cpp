#include "stdafx.h"
#include "acquisition.h"

using namespace std::chrono;
using namespace std;

/* The original value of the exposure time is set to be 100 ms*/
float64 exposureTime = 100.0;

/* The actual index of the internal buffer*/
uInt32 internalBuffDx;

uInt32 getInternalBufferIndex() {
	return internalBuffDx;
}

float64 getExposureTime() {
	return exposureTime;
}

/* 
* Initialize the internal acquisition and set the exposure time 
* expTime: the exposure time
*/
bool initIntAcquire(IMAQdxSession session){
	IMAQdxError status;

	// set the shutter mode
	status = IMAQdxSetAttribute(session, "CameraAttributes::Shutter::Mode", IMAQdxValueTypeString, "Relative");
	if (status != IMAQdxErrorSuccess) {
		puts("Fail to set the shutter mode.");
		return false;
	}

	// set the value of the exposure time 
	status = IMAQdxSetAttribute(session, "CameraAttributes::Shutter::Value", IMAQdxValueTypeU32, exposureTime);
	if (status != IMAQdxErrorSuccess) {
		puts("Fail to set exposure time.");
		return false;
	}

	// configure grab
	status = IMAQdxConfigureGrab(session);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Acquisition failed.\n");
		return false;
	}

	return true;
}

/* Implement the internal acquisition */
bool intAcquire(IMAQdxSession session, Image* image) {
	IMAQdxError status;

	// Start capture
	status = IMAQdxConfigureGrab(session);
	if (status != IMAQdxErrorSuccess) {
		puts("Acquisition failed.\n");
		return false;
	}

	// acquire a image
	high_resolution_clock::time_point begin = high_resolution_clock::now();

	/* 
	*The acquired image is transfered from the internal buffer to the image buffer. 
	* The index of the internal buffer is sequential and the total number of internal 
	* is 10 according to the manual of the ORCA R2 camera. 
	*/
	status = IMAQdxGrab(session, image, 1, &internalBuffDx);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to take image.");
		return false;
	}

	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double, std::milli> time = end - begin;
	printf("time: %f ms, buffer: %d\n", time, internalBuffDx);

	return true;
}

float64 setExposureTime(float64 expTime) {
	exposureTime = expTime;
	return exposureTime;
}

