#include "InputHandler.h"
#include <atomic>
#include <Windows.h>

class ApplicationStopper {
public:
    ApplicationStopper(UINT hotkey = Keys::Q);
    ~ApplicationStopper();
    bool isRunning() const; 
private:
    std::atomic<bool> running;
    void SetRunning(bool b);
};