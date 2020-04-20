#ifndef __UTIL_H
#define __UTIL_H
#include "main.h"

float scale(float value, float fromLow, float fromHigh, float toLow, float toHigh);
float averageReading(struct State* state);

#endif
