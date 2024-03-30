#include "InputHandler.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

InputHandler& InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

InputHandler::InputHandler() : listening(false) {}

InputHandler::~InputHandler() {
    stopListening();
}

void InputHandler::subscribeToKeyEvent(const std::vector<UINT>& keyCodes, std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(subscribersMutex);
    std::string keyHash = generateKeyHash(keyCodes);
    eventSubscribers[keyHash].push_back(callback);
}

void InputHandler::unsubscribeFromKeyEvent(const std::vector<UINT>& keyCodes) {
    std::lock_guard<std::mutex> lock(subscribersMutex);
    std::string keyHash = generateKeyHash(keyCodes);
    eventSubscribers.erase(keyHash);
}

void InputHandler::startListening() {
    if (!listening.exchange(true)) {
        inputThread = std::thread(&InputHandler::listenForKeyEvents, this);
    }
}

void InputHandler::stopListening() {
    if (listening.exchange(false)) {
        if (inputThread.joinable()) {
            inputThread.join();
        }
    }
}

void InputHandler::listenForKeyEvents() {
    while (listening) {
        std::unordered_map<std::string, std::vector<std::function<void()>>> subscribersCopy;
        {
            std::lock_guard<std::mutex> lock(subscribersMutex);
            subscribersCopy = eventSubscribers;
        }

        for (const auto& keyValuePair : subscribersCopy) {
            const std::string& keyHash = keyValuePair.first;
            std::istringstream iss(keyHash);
            std::vector<UINT> keys;
            UINT key;
            while (iss >> key) {
                keys.push_back(key);
            }
            bool allPressed = std::all_of(keys.begin(), keys.end(), [](UINT k) {
                return GetAsyncKeyState(k) & 0x8000;
                });

            if (allPressed) {
                notifyKeyEvent(keyHash);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void InputHandler::subscribeToKeyEvent(UINT keyCode, std::function<void()> callback) {
    this->subscribeToKeyEvent(std::vector<UINT>{keyCode}, callback);
}

void InputHandler::unsubscribeFromKeyEvent(UINT keyCode) {
    this->unsubscribeFromKeyEvent(std::vector<UINT>{keyCode});
}


void InputHandler::notifyKeyEvent(const std::string& keyCodesHash) {
    std::vector<std::function<void()>> callbacks;
    {
        std::lock_guard<std::mutex> lock(subscribersMutex);
        if (eventSubscribers.find(keyCodesHash) != eventSubscribers.end()) {
            callbacks = eventSubscribers[keyCodesHash];
        }
    }

    for (auto& callback : callbacks) {
        callback();
    }
}

std::string InputHandler::generateKeyHash(const std::vector<UINT>& keyCodes) {
    std::ostringstream oss;
    for (auto keyCode : keyCodes) {
        oss << keyCode << " ";
    }
    return oss.str().substr(0, oss.str().length() - 1);
}
