#pragma once

#include <functional>
#include <string>
#include <vector>

namespace app {

struct Task {
    std::string name;
    int attempts = 0;
};

class Scheduler {
public:
    void add(std::function<void()> job) { jobs_.push_back(std::move(job)); }

    // Queues a follow-up job that logs a retry of `task`.
    void schedule_retry(const Task& task);

    // Runs every queued job on a small pool of worker threads.
    // Returns how many jobs ran.
    int run_all(int workers = 4);

private:
    std::vector<std::function<void()>> jobs_;
};

}  // namespace app
