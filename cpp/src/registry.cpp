#include "registry.h"

#include <iostream>
#include <utility>

namespace app {

Handler& Registry::add(std::string name, int priority) {
    handlers_.push_back({std::move(name), priority});
    return handlers_.back();
}

void Registry::add_with_alias(const std::string& name, const std::string& alias) {
    Handler& primary = add(name, static_cast<int>(handlers_.size()) * 10);
    Handler& secondary = add(alias);
    secondary.priority = primary.priority + 1;
}

Snapshot Registry::snapshot() const {
    return Snapshot{handlers_};
}

void dump(const Registry& registry) {
    for (const auto& h : registry.snapshot().items()) {
        std::cout << "  " << h.name << " (priority " << h.priority << ")\n";
    }
}

}  // namespace app
