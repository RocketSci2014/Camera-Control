#ifndef IMAQDX_CONTROL

#define IMAQDX_CONTROL

#include <Windows.h>
#include <SDKDDKVer.h>
#include "NIIMAQdx.h"
#include "nivision.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <direct.h>

bool visionError(int errorValue);
bool imaqdxError(IMAQdxError errorValue);

#endif