#include <atomic>
#include <thread>

class ApplicationStopper {
public:
    ApplicationStopper();
    ~ApplicationStopper();
    void stop();
    bool shouldStop() const;
private:
    std::atomic<bool> stopRequested;
    std::thread stopThread;
    void run();
    void start();
};
