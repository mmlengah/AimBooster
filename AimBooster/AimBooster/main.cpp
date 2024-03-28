#include "ApplicationStopper.h"
#include "Keys.h"
#include <iostream>
#include <windows.h>
#include <memory> 

int main() {
    auto appStopper = std::make_unique<ApplicationStopper>(Keys::Q);

    int count = 0;
    while (!appStopper->shouldStop()) {
        std::cout << "Number: " << count++ << std::endl;
        Sleep(100);
    }

    return 0;
}
