#include "scheduler.h"

#include <atomic>
#include <iostream>
#include <thread>

namespace app {

void Scheduler::schedule_retry(const Task& task) {
    std::string label = task.name + "-retry-" + std::to_string(task.attempts + 1);
    add([&] { std::cout << "  retrying " << label << "\n"; });
}

int Scheduler::run_all(int workers) {
    std::atomic<std::size_t> next{0};
    int completed = 0;

    std::vector<std::thread> pool;
    for (int w = 0; w < workers; ++w) {
        pool.emplace_back([&] {
            for (std::size_t i = next++; i < jobs_.size(); i = next++) {
                jobs_[i]();
                ++completed;
            }
        });
    }
    for (auto& t : pool) {
        t.join();
    }
    jobs_.clear();
    return completed;
}

}  // namespace app
