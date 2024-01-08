#pragma once
#include "java.hpp"
#include <jni.h>
#include "geometry.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include <Windows.h>

struct watermark_data {
	bool display = false;
	std::string value = "cheat_name";
	ImColor color = ImColor(255, 255, 255);
};

namespace misc {
	inline uint32_t spotify_pid = 0;
	inline HWND spotify_hwnd = nullptr;
	inline watermark_data watermark;
	void update_data();
	void draw();
}