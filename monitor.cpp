#include "./monitor.h"
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Threshold constants
#define CRITICAL_TEMP_LOW 95.0f
#define CRITICAL_TEMP_HIGH 102.0f
#define PULSE_RATE_LOW 60.0f
#define PULSE_RATE_HIGH 100.0f
#define SPO2_LOW 90.0f

// Default alarm behavior (can be mocked in test)
void raiseAlarm(const char* message) {
    cout << message << "\n";
}

// Check temperature
bool checkTemperature(float temperature) {
    if (temperature < CRITICAL_TEMP_LOW || temperature > CRITICAL_TEMP_HIGH) {
        raiseAlarm("Temperature is critical!");
        return false;
    }
    return true;
}

// Check pulse
bool checkPulse(float pulseRate) {
    if (pulseRate < PULSE_RATE_LOW || pulseRate > PULSE_RATE_HIGH) {
        raiseAlarm("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

// Check SpO2
bool checkSpO2(float spo2) {
    if (spo2 < SPO2_LOW) {
        raiseAlarm("Oxygen Saturation is out of range!");
        return false;
    }
    return true;
}

// Main check
int vitalsOk(float temperature, float pulseRate, float spo2) {
    bool tempOk = checkTemperature(temperature);
    bool pulseOk = checkPulse(pulseRate);
    bool spo2Ok = checkSpO2(spo2);
    return tempOk && pulseOk && spo2Ok;
}
