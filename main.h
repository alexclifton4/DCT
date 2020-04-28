#ifndef __MAIN_H
#define __MAIN_H

// Constants for scaling
#define ADC_MIN 0
#define ADC_MAX 4095
#define VOLTAGE_MIN 10
#define VOLTAGE_MAX -10
#define CURRENT_MIN 0
#define CURRENT_MAX 100
#define RESISTANCE_MIN 0
#define RESISTANCE_MAX 50
#define CAPACITANCE_MIN 0.1
#define CAPACITANCE_MAX 100
#define AVERAGE_READINGS 100

// Stores which mode the system is in
enum Mode{Voltage, Current, Resistance, Capacitance};

// Struct to hold state information
struct State {
	enum Mode currentMode;
	int showLive;
	int readings[AVERAGE_READINGS]; // Holds the most recent readings to average them
	int readingsIndex;
	float offset;
	float mostRecentAverage;
};

#endif
