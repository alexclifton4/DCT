#ifndef __MODES_H
#define __MODES_H
#include "main.h"

void switchToVoltage(struct State* state);
void switchToCurrent(struct State* state);
void switchToResistance(struct State* state);
void switchToCapacitance(struct State* state);
void switchToFrequency(struct State* state);

void updateVoltage(struct State* state);
void updateCurrent(struct State* state);
void updateResistance(struct State* state);
void updateFrequency(struct State* state);

void tickFrequency(struct State* state);
void tickCapacitance(struct State* state);

#endif
