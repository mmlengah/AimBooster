#pragma once
#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>
#include <windows.h>

class InputHandler {
public:
    static InputHandler& getInstance();
    void subscribeToKeyEvent(const std::vector<UINT>& keyCodes, std::function<void()> callback);
    void unsubscribeFromKeyEvent(const std::vector<UINT>& keyCodes);
    void subscribeToKeyEvent(UINT keyCode, std::function<void()> callback);
    void unsubscribeFromKeyEvent(UINT keyCode);
    void startListening();
    void stopListening();
private:
    InputHandler();
    ~InputHandler();
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    std::atomic<bool> listening;
    std::thread inputThread;
    std::unordered_map<std::string, std::vector<std::function<void()>>> eventSubscribers;
    std::mutex subscribersMutex;

    void listenForKeyEvents();
    void notifyKeyEvent(const std::string& keyCodesHash);
    std::string generateKeyHash(const std::vector<UINT>& keyCodes);
};
