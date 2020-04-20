#ifndef __BUTTON_DRIVER_H
#define __BUTTON_DRIVER_H

#include "stm32f407xx.h"

void Button_Init(void);
int Button_Press(int sw);
int Button_Press_Debounced(int sw);

#endif
