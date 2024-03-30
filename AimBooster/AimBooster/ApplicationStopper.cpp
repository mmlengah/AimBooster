#include "ApplicationStopper.h"

ApplicationStopper::ApplicationStopper(UINT hotkey) : running(true) { 
    std::function<void()> callback = std::bind(&ApplicationStopper::SetRunning, this, false);
    InputHandler::getInstance().subscribeToKeyEvent({ Keys::CONTROL, hotkey }, callback);
    InputHandler::getInstance().subscribeToKeyEvent({ Keys::CONTROL, Keys::ALT_LEFT, Keys::F4 }, callback);
}

ApplicationStopper::~ApplicationStopper() {

}

bool ApplicationStopper::isRunning() const { 
    return running.load();
}

void ApplicationStopper::SetRunning(bool b)
{
    running = false;
}