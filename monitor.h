#pragma once

// Main function: check all vitals
// alarmFunc is optional: defaults to internal visual effect printer
int vitalsOk(float temperature, float pulseRate, float spo2,
             void (*alarmFunc)(const char*) = nullptr);
