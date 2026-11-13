#include "../include/WindowRule.hpp"
#include <regex>

std::string WindowRule::toString() {
    std::string mode = this->tile ? "tile = true" : "float = true";
    return "hl.window_rule({ match = { workspace = \"" +
           std::to_string(this->workspaceID) + "\" }, " + mode + " })";
}

std::optional<WindowRule> WindowRule::parse(const std::string& line) {
    static const std::regex pattern(
        R"htt(^\s*hl\.window_rule\(\{\s*match\s*=\s*\{\s*workspace\s*=\s*"(-?[0-9]+)"\s*\}\s*,\s*(tile|float)\s*=\s*true\s*\}\)\s*$)htt");
    std::smatch match;
    if (!std::regex_match(line, match, pattern)) return std::nullopt;
    return WindowRule{.tile = match[2] == "tile", .workspaceID = std::stoi(match[1])};
}
