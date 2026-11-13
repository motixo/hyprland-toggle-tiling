#include "../include/WindowRule.hpp"
int main() {
    for (const auto tile : {true, false}) {
        WindowRule rule{.tile = tile, .workspaceID = 7};
        auto parsed = WindowRule::parse(rule.toString());
        if (!parsed || parsed->tile != tile || parsed->workspaceID != 7) return 1;
    }
    if (WindowRule::parse("-- unrelated config line")) return 1;
}
