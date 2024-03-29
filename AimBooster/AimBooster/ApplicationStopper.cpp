#include "ApplicationStopper.h"

ApplicationStopper::ApplicationStopper(UINT hotkey) : running(true), userHotkey(hotkey) { // Now starts as true
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
        running = false;
        stopThread.join();
    }
    UnregisterHotKey(NULL, USER_HOTKEY_ID);
}

bool ApplicationStopper::isRunning() const { 
    return running.load();
}

void ApplicationStopper::run() {
    if (!RegisterHotKey(NULL, USER_HOTKEY_ID, MOD_CONTROL, userHotkey)) {
        std::cerr << "Failed to register hotkey." << std::endl;
        return;
    }

    if (!RegisterHotKey(NULL, CTRL_ALT_F4_HOTKEY_ID, MOD_CONTROL | MOD_ALT, VK_F4)) {
        std::cerr << "Failed to register Ctrl + Alt + F4 hotkey." << std::endl;
        return;
    }

    MSG msg = { 0 };

    while (running) { 
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_HOTKEY && (msg.wParam == USER_HOTKEY_ID || msg.wParam == CTRL_ALT_F4_HOTKEY_ID)) {
                std::cout << "Stopping loop..." << std::endl;
                running = false; 
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}