#include <sstream>
#include <fstream>
#include "../include/FileService.hpp"
#include "../include/Macros.hpp"
#include "../include/ShellService.hpp"

bool FileService::doesNonEmptyFileExist(std::string path) {
    std::ifstream file(path);
    return file.good() && file.peek() != std::ifstream::traits_type::eof();
};

void FileService::emptyFile(std::string path) {
    std::stringstream cmd;
    cmd << CAT_PATH << " " << NULL_PATH << " > " << path;
    ShellService::exec(cmd.str().c_str());
};

void FileService::createOrOverwriteFile(std::string path, std::string content) {
    std::stringstream cmd;
    cmd << ECHO_PATH << " " << content << " > " << path;
    ShellService::exec(cmd.str().c_str());
};

void FileService::appendToFile(std::string path, std::string content) {
    std::ifstream input(path, std::ios::binary | std::ios::ate);
    const bool nonempty = input.good() && input.tellg() > 0;
    bool needsNewline = false;
    if (nonempty) {
        input.seekg(-1, std::ios::end);
        needsNewline = input.get() != '\n';
    }
    std::ofstream output(path, std::ios::app);
    if (needsNewline) output << '\n';
    output << content << '\n';
};

void FileService::deleteNthLine(std::string path, int n) {
    std::vector<std::string> lines = readLines(path);

    if (n < 0 || n >= static_cast<int>(lines.size())) {
        // Out of bounds, do nothing
        return;
    }

    lines.erase(lines.begin() + n);

    std::ofstream file(path, std::ios::trunc);
    for (const auto& line : lines) file << line << '\n';
}

std::vector<std::string> FileService::readLines(std::string path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
};
