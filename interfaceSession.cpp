#include "stdafx.h"
#include "interfaceSession.h"

IMAQdxCameraInformation camInfoArr[256];
uInt32 nCameras = 0;

bool closeIMAQdxSession(IMAQdxSession session) {
	IMAQdxError status = IMAQdxCloseCamera(session);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to close camera.");
		return false;
	}

	return true;
}

/* 
* Get the interface name specified by intNameDx 
* intNameDx: the index of the camera's name in the array
*/
const char* getInterfaceName(int intNameDx) {
	if (intNameDx >= nCameras) {
		return NULL;
	}

	return camInfoArr[intNameDx].InterfaceName;
}

/* Start the camera and set its attributes for acquisition */
bool openIMAQdxSession(IMAQdxSession* session, const char* camName) {
	IMAQdxError status;
	status = IMAQdxOpenCamera(camName, IMAQdxCameraControlModeController, session);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to open camera.\n");
		return false;
	}

	//set attributes for HAMAMATSU ORCA R-2 camera
	status = IMAQdxSetAttribute(
		*session, 
		"AcquisitionAttributes::Bayer::Algorithm", 
		IMAQdxValueTypeString, 
		"Bilinear");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set Bayer algorithm.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session, 
		"AcquisitionAttributes::Bayer::GainB", 
		IMAQdxValueTypeF64,
		1.0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set blue gain.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::Bayer::GainG",
		IMAQdxValueTypeF64,
		1.0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set green gain.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::Bayer::GainR",
		IMAQdxValueTypeF64,
		1.0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set red gain.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::Bayer::Pattern",
		IMAQdxValueTypeString,
		"Use hardware value");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set pattern.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::OutputImageType",
		IMAQdxValueTypeString,
		"Auto");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set output image type.");
		return false;
	}

	/* 16 bits per pixel*/
	status = IMAQdxSetAttribute(
		*session,
		"PixelFormat",
		IMAQdxValueTypeString,
		"Mono16");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set pixel format.");
		return false;
	}

	status = IMAQdxSetAttribute(*session, "OffsetX", IMAQdxValueTypeU32, 0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set x offset.");
		return false;
	}

	status = IMAQdxSetAttribute(*session, "OffsetY", IMAQdxValueTypeU32, 0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set y offset.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::Speed",
		IMAQdxValueTypeString,
		"800 Mbps");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set speed.");
		return false;
	}

	/* Timeout is 5000 ms */
	status = IMAQdxSetAttribute(
		*session,
		"AcquisitionAttributes::Timeout",
		IMAQdxValueTypeU32,
		5000);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set timeout.");
		return false;
	}

	status = IMAQdxSetAttribute(
		*session,
		"CameraAttributes::FrameRate::Mode",
		IMAQdxValueTypeString,
		"Absolute");
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set frame rate mode.");
		return false;
	}

	/* Frame rate 8 frames/s */
	status = IMAQdxSetAttribute(
		*session,
		"CameraAttributes::FrameRate::Value",
		IMAQdxValueTypeF64,
		8.0);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to set frame rate value.");
		return false;
	}

	return true;
}

/* Initialize the interface names */
bool setupInterfaceNames() {
	IMAQdxError status;

	/* Get the array of camera information. Set the array of camera information
	to NULL and specify the the number of cameras first, then write the camera
	information into the array. */
	status = IMAQdxEnumerateCameras(NULL, &nCameras, 1);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to enumerate camers.\n");
		return false;
	}

	status = IMAQdxEnumerateCameras(camInfoArr, &nCameras, 1);
	if (status != IMAQdxErrorSuccess) {
		imaqdxError(status);
		puts("Fail to enumerate camers.\n");
		return false;
	}

	return true;
}