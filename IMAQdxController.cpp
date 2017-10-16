#include "IMAQdxController.h"
#include "acquisition.h"
#include "attributes.h"
#include "interfaceSession.h"
#include "buffers.h"

int main() {

	// set up a new session
	if (!setupInterfaceNames()) {
		return -1;
	}
		
	const char* camName = getInterfaceName(0);
	IMAQdxSession session;
	 
	if (!openIMAQdxSession(&session, camName)) {
		return - 1;
	}

	// get available attributes
	if (!getAvailableAttributes(session)) {
		return -1;
	}

	// get the size of the image
	uInt32 height = getImageHeight(session);
	uInt32 width = getImageWidth(session);
	printf("Height: %d Width: %d\n", height, width);

	// acquire a image, exposure time 100 ms
	initIntAcquire(session);
	Image* image = initBuffer();
	intAcquire(session, image);

	// save image
	if (!saveCurrentImage()) {
		return -1;
	}

	// close session
	if (!closeIMAQdxSession(session)) {
		return -1;
	}

	// clear image buffer
	clearBuffer();
}

/* print the error in IMAQdx */
bool imaqdxError(IMAQdxError errorValue) {
	if (errorValue) {
		char errorText[256];
		IMAQdxGetErrorString(errorValue, errorText, 256);
		printf("%s\n", errorText);
		return true;
	}
	return false;
}

/* print the error in NI VISION */
bool visionError(int errorValue) {
	if ((errorValue != TRUE) && (imaqGetLastError() != ERR_SUCCESS)) {
		char *tempErrorText = imaqGetErrorText(imaqGetLastError());
		printf("%s\n", tempErrorText);
		imaqDispose(tempErrorText);
		return true;
	}
	return false;
}
