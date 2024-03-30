#include "ApplicationStopper.h"

ApplicationStopper::ApplicationStopper(UINT hotkey) : running(true) { 
    std::function<void()> callback = std::bind(&ApplicationStopper::SetRunning, this, false);
    InputHandler::getInstance().subscribeToKeyEvent({ Keys::CONTROL, hotkey }, callback);
    InputHandler::getInstance().subscribeToKeyEvent({ Keys::ALT_LEFT, Keys::F4 }, callback);
}

ApplicationStopper::~ApplicationStopper() {

}

std::atomic<bool>& ApplicationStopper::isRunning() {
    return running;
}

void ApplicationStopper::SetRunning(bool b)
{
    running = false;
}