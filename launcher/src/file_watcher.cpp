#include "file_watcher.hpp"

#include <chrono>
#include <print>

FileWatcher::FileWatcher(
    std::filesystem::path const& watch_path,
    std::filesystem::path const& binary_path
)
    : watch_path_{watch_path}, binary_path_{binary_path}
{
}

bool FileWatcher::change_detected()
{
    try {
        for (auto const& file :
             std::filesystem::recursive_directory_iterator(watch_path_)) {
            if (file.is_regular_file()) {
                if (std::filesystem::last_write_time(file) >
                    std::filesystem::last_write_time(binary_path_)) {
                    std::println(
                        "latest file write:\t{}",
                        std::filesystem::last_write_time(file)
                    );
                    std::println(
                        "latest binary write:\t{}",
                        std::filesystem::last_write_time(binary_path_)
                    );
                    return true;
                }
            }
        }
    } catch (std::filesystem::filesystem_error const&) {
    }

    return false;
}
