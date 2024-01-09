#include "config.hpp"
#include <string>
#include <any>
#include <fstream>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>

std::string get_cheat_config_folder() {
    PWSTR documents_path;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &documents_path))) {
        std::wstring wide_path(documents_path);
        CoTaskMemFree(documents_path);

        // Convert wide string to narrow string
        return std::string(wide_path.begin(), wide_path.end()) + "\\cheat\\";
    }
    return "";
}

void config::init() {
    config::config_folder_path = get_cheat_config_folder();
    CreateDirectoryA(config_folder_path.c_str(), NULL);
    config::get_config_names();

    config::set<bool>("aimbot_enabled", false);
    config::set<float>("aimbot_smoothing", 1.f);
    config::set<float>("aimbot_target_dist", 4.5f);
    config::set<SmoothingMode>("aimbot_smoothing_mode", SmoothingMode::LINEAR);
    config::set<AimbotMode>("aimbot_mode", AimbotMode::ANGLE);

    config::set<bool>("esp_enabled", false);
    config::set<float>("esp_max_distance", 35.f);
    config::set<bool>("esp_player_box", false);
    config::set<bool>("esp_player_health", false);
    config::set<bool>("esp_player_name", false);
    config::set<bool>("esp_block_esp", false);
}

void config::get_config_names() {
    for (const auto& entry : std::filesystem::directory_iterator(config::config_folder_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cfg") {
            config::config_names.push_back(entry.path().string());
        }
    }
}

bool config::save(std::string name) {
    std::ofstream file(config::config_folder_path + name, std::ios::binary);

    for (const auto& [key, value] : settings) {
        uint8_t keyLength = static_cast<uint8_t>(strlen(key.c_str()));
        file.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
        file.write(key.c_str(), strlen(key.c_str()));
        file.write(value.data, sizeof(value));
    }
    file.close();
    return true;
}

bool config::load(std::string name) {
    std::ifstream file(config::config_folder_path + name, std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    while (true) {
        uint8_t keyLength;
        if (!file.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength))) {
            // Reached end of file
            break;
        }

        std::string key;
        key.resize(keyLength);

        if (!file.read(&key[0], keyLength)) {
            return false;
        }

        data value;
        if (!file.read(reinterpret_cast<char*>(&value.data), sizeof(value.data))) {
            return false;
        }

        // Add the key-value pair to your settings
        settings[key] = value;
    }

    file.close();
    return true;
}