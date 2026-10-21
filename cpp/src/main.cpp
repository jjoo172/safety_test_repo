#include <iostream>
#include <vector>

#include "config.h"
#include "registry.h"
#include "scheduler.h"
#include "stats.h"
#include "wire.h"

int main() {
    std::cout << "Hello, world!\n";

    // Config
    const std::string text =
        "name = demo   # service name\n"
        "threads = 4\n"
        "\n"
        "log_level = info\n";
    auto settings = app::to_settings(app::parse_config(text));
    const std::string& level = app::get_or(settings, "log_level");
    const std::string& region = app::get_or(settings, "region");
    std::cout << "config: name=" << app::get_or(settings, "name")
              << " level=" << level << " region=" << region << "\n";

    // Registry
    app::Registry registry;
    registry.add("startup");
    registry.add_with_alias("refresh", "refresh-late");
    std::cout << "registry:\n";
    app::dump(registry);

    // Stats
    std::vector<int> latencies = {1200000000, 900000000, 700000000, 5, 5, 5};
    std::cout << "stats: mean=" << app::mean(latencies)
              << " median=" << app::median(latencies)
              << " mask(32)=" << app::mask_for(32) << "\n";

    // Wire
    std::vector<std::uint8_t> frame(64, 0);
    frame[1] = 0xBE;
    frame[2] = 0xEF;
    if (auto h = app::parse_header(frame, 1)) {
        std::cout << "wire: magic=" << std::hex << h->magic << std::dec
                  << " checksum=" << app::word_checksum(frame.data() + 1, 32)
                  << "\n";
    }

    // Scheduler
    app::Scheduler scheduler;
    for (int i = 0; i < 8; ++i) {
        scheduler.add([] {});
    }
    scheduler.schedule_retry({"sync", 2});
    std::cout << "scheduler: ran " << scheduler.run_all() << " jobs\n";

    return 0;
}
