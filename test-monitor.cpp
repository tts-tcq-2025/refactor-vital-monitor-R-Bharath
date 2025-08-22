#include <gtest/gtest.h>   // C++ system
#include <vector>          // C++ system
#include <string>          // C++ system

#include "monitor.h"       // Project header

// ---- Mock alarm ----
static std::vector<std::string> capturedMessages;

static void mockAlarm(const char* message) {
    capturedMessages.push_back(message);
}

static void resetMock() {
    capturedMessages.clear();
}

// ---- Tests ----
TEST(Monitor, AllVitalsNormal) {
    resetMock();
    ASSERT_TRUE(vitalsOk(98.6, 75, 95, mockAlarm));
    ASSERT_TRUE(capturedMessages.empty());
}

TEST(Monitor, TemperatureTooLow) {
    resetMock();
    ASSERT_FALSE(vitalsOk(94, 75, 95, mockAlarm));
    ASSERT_EQ(capturedMessages[0], "Temperature is critical!");
}

TEST(Monitor, TemperatureTooHigh) {
    resetMock();
    ASSERT_FALSE(vitalsOk(103, 75, 95, mockAlarm));
    ASSERT_EQ(capturedMessages[0], "Temperature is critical!");
}

TEST(Monitor, PulseTooLow) {
    resetMock();
    ASSERT_FALSE(vitalsOk(98.6, 50, 95, mockAlarm));
    ASSERT_EQ(capturedMessages[0], "Pulse Rate is out of range!");
}

TEST(Monitor, PulseTooHigh) {
    resetMock();
    ASSERT_FALSE(vitalsOk(98.6, 120, 95, mockAlarm));
    ASSERT_EQ(capturedMessages[0], "Pulse Rate is out of range!");
}

TEST(Monitor, SpO2TooLow) {
    resetMock();
    ASSERT_FALSE(vitalsOk(98.6, 80, 85, mockAlarm));
    ASSERT_EQ(capturedMessages[0], "Oxygen Saturation is out of range!");
}

