#include "buffers.h"

/* The image buffer */
Image* image = NULL;

/* The output directory of the acquired images */
const char * outputDirectory = "C:/git/Acquisition/C/MIAcquire";

/* Indices of the file name */
int imageIndex = 1;
int seriesIndex = 1;

void clearBuffer() {
	// dispose image
	imaqDispose(image);
}

Image* getBuffer() {
	return image;
}

Image* initBuffer() {
	// initialize the image buffer, 16-bit
	image = imaqCreateImage(IMAQ_IMAGE_U16, 0);
	return image;
}

/* save the image in the buffer to a tiff file */
bool saveCurrentImage() {
	// make series folder
	char seriesName[256];
	sprintf(seriesName, "%s/Series%d", outputDirectory, seriesIndex);
	mkdir(seriesName);

	// write image to a tiff 
	char fileName[256];
	sprintf(fileName, "%s/Series%d/s%d_%d.tiff",
		outputDirectory,
		seriesIndex,
		seriesIndex,
		imageIndex);
	int result = imaqWriteFile(image, fileName, NULL);
	if (result != ERR_SUCCESS) {
		visionError(result);
		return false;
	}

	return true;
}

Image* setBuffer(Image* input) {
	image = input;
	return image;
}

int setImageIndex(int imgIndex) {
	imageIndex = imgIndex;
	return imageIndex;
}

const char* setOutputDirectory(const char* outDir) {
	outputDirectory = outDir;
	return outputDirectory;
}

int setSeriesIndex(int sIndex) {
	seriesIndex = sIndex;
	return seriesIndex;
}