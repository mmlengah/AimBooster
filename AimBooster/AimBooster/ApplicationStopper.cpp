#include "ApplicationStopper.h"
#include <iostream>
#include <windows.h>

constexpr auto HOTKEY_ID = 1;

ApplicationStopper::ApplicationStopper() : stopRequested(false) {
    start();
}

ApplicationStopper::~ApplicationStopper() {
    stop();
}

void ApplicationStopper::start() {
    stopThread = std::thread(&ApplicationStopper::run, this);
}

void ApplicationStopper::stop() {
    if (stopThread.joinable()) {
        stopRequested = true;
        stopThread.join();
    }
    UnregisterHotKey(NULL, HOTKEY_ID);
}

bool ApplicationStopper::shouldStop() const {
    return stopRequested.load();
}

void ApplicationStopper::run() {
    if (!RegisterHotKey(NULL, HOTKEY_ID, MOD_CONTROL, 0x51)) {
        std::cerr << "Failed to register hotkey." << std::endl;
        return;
    }

    MSG msg = { 0 };

    while (!stopRequested) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID) {
                std::cout << "Stopping loop..." << std::endl;
                stopRequested = true;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
