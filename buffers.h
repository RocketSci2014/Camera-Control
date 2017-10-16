#ifndef BUFFERS_H
#define BUFFER_H

#include "IMAQdxController.h"

void clearBuffer();
Image* getBuffer();
Image* initBuffer();
bool saveCurrentImage();
Image* setBuffer(Image* input);
int setImageIndex(int imgIndex);
const char* setOutputDirectory(const char* outDir);
int setSeriesIndex(int sIndex);

#endif

