#include "MouseClickSimulator.h"

void MouseClickSimulator::simulateClickAtPosition(int x, int y) {
    // Set mouse position
    SetCursorPos(x, y);
    // Simulate mouse down and up events for a left-click
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}

void MouseClickSimulator::click(std::shared_ptr<std::queue<Position>> positions) {
    while (!positions->empty()) { 
        Position pos = positions->front();
        simulateClickAtPosition(pos.x, pos.y);
        positions->pop();
    }
}
