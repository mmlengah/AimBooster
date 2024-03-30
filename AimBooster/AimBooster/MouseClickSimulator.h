#include <Windows.h>
#include <memory>
#include <queue>
#include <atomic> 
#include "Position.h"

class MouseClickSimulator {
private:
    void simulateClickAtPosition(int x, int y);

public:
    void click(std::shared_ptr<std::queue<Position>> positions, std::atomic<bool>& running);
};