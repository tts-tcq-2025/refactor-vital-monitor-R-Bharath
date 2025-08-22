#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// ---------- Constants for vital thresholds ----------
#define CRITICAL_TEMP_LOW   95.0f
#define CRITICAL_TEMP_HIGH  102.0f
#define PULSE_RATE_LOW      60.0f
#define PULSE_RATE_HIGH     100.0f
#define SPO2_LOW            90.0f

// ---------- Helper: Visual warning effect ----------
static void printVisualEffect(const char* message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

// ---------- Helper: Range check (low + high) ----------
static bool vitalRangeCheck(float vitalValue, float lowThreshold, float highThreshold,
                            const char* message,
                            void (*alarmFunc)(const char*)) {
    if (vitalValue < lowThreshold || vitalValue > highThreshold) {
        alarmFunc(message);
        return false;
    }
    return true;
}

// ---------- Helper: Low threshold check only ----------
static bool vitalLowThresholdCheck(float vitalValue, float lowThreshold,
                                   const char* message,
                                   void (*alarmFunc)(const char*)) {
    if (vitalValue < lowThreshold) {
        alarmFunc(message);
        return false;
    }
    return true;
}

// ---------- Main orchestration ----------
int vitalsOk(float temperature, float pulseRate, float spo2,
             void (*alarmFunc)(const char*)) {
    // If no alarm function passed, use default
    if (alarmFunc == nullptr) {
        alarmFunc = printVisualEffect;
    }

    bool tempOk  = vitalRangeCheck(temperature, CRITICAL_TEMP_LOW, CRITICAL_TEMP_HIGH,
                                   "Temperature is critical!", alarmFunc);
    bool pulseOk = vitalRangeCheck(pulseRate, PULSE_RATE_LOW, PULSE_RATE_HIGH,
                                   "Pulse Rate is out of range!", alarmFunc);
    bool spo2Ok  = vitalLowThresholdCheck(spo2, SPO2_LOW,
                                          "Oxygen Saturation is out of range!", alarmFunc);

    return tempOk && pulseOk && spo2Ok;
}
