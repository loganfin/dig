#pragma once

#include <filesystem>

class FileWatcher {
public:
    FileWatcher(
        std::filesystem::path const& watch_path,
        std::filesystem::path const& binary_path
    );

    bool change_detected();

private:
    std::filesystem::path watch_path_;
    std::filesystem::path binary_path_;
};
