#pragma once

#include <unordered_map>
#include <string>

enum SmoothingMode {
    LINEAR,
    EXPONENTIAL,
    SINUSOIDAL,
    LOGARITHMIC,
    LERP,
    SMOOTHSTEP
};

enum AimbotMode {
    ANGLE,
    MOUSE,
};

struct data {
    char data[32];
};

inline std::unordered_map<std::string, data> settings;

namespace config {

    inline std::vector<std::string> config_names;
    inline std::string config_folder_path;

    /*
    template<typename T>
    T get(const char* key) {
        T data;
        memcpy(&data, &settings[key], sizeof(T));
        return data;
    }
    */

    template<typename T>
    T* get(const char* key) {
        if (settings.find(key) == settings.end())
            set<T>(key, T{});
        return reinterpret_cast<T*>(settings[key].data);
    }

    template<typename T>
    void set(const char* key, T val) {
        data buf;
        memset(&buf.data, 0, 32);
        memcpy(buf.data, &val, sizeof(val));
        settings[key] = buf;
    }

    void init();
    bool save(std::string name);
    bool load(std::string name);
    void get_config_names();
}