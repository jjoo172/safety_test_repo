#pragma once

#include <string>
#include <vector>

namespace app {

struct Handler {
    std::string name;
    int priority = 0;
};

struct Snapshot {
    std::vector<Handler> handlers;

    const std::vector<Handler>& items() const { return handlers; }
};

class Registry {
public:
    Handler& add(std::string name, int priority = 0);

    // Registers `name` and an alias that runs just after it.
    void add_with_alias(const std::string& name, const std::string& alias);

    Snapshot snapshot() const;

    std::size_t size() const { return handlers_.size(); }

private:
    std::vector<Handler> handlers_;
};

// Prints every handler in a point-in-time copy of the registry.
void dump(const Registry& registry);

}  // namespace app
