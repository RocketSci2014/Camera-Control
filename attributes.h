#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "IMAQdxController.h"

bool getAvailableAttributes(IMAQdxSession sessionID);
uInt32 getImageHeight(IMAQdxSession session);
uInt32 getImageWidth(IMAQdxSession session);
#endif

