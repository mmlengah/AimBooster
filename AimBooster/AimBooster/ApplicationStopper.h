#include "InputHandler.h"
#include <atomic>
#include <Windows.h>

class ApplicationStopper {
public:
    ApplicationStopper(UINT hotkey = Keys::Q);
    ~ApplicationStopper();
    std::atomic<bool>& isRunning();
private:
    std::atomic<bool> running;
    void SetRunning(bool b);
};