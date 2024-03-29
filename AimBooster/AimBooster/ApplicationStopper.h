#include <atomic>
#include <thread>
#include <iostream>
#include <windows.h>

constexpr auto USER_HOTKEY_ID = 1;
constexpr auto CTRL_ALT_F4_HOTKEY_ID = 2;

class ApplicationStopper {
public:
    ApplicationStopper(UINT hotkey);
    ~ApplicationStopper();
    void stop();
    bool shouldStop() const;

private:
    UINT userHotkey;
    std::atomic<bool> stopRequested;
    std::thread stopThread;
    void run();
    void start();
};