#pragma once
#include <memory>
#include "c_render_manager.hpp"
#include "c_minecraft.hpp"

namespace globals {
	inline bool imgui_init = false;
	inline bool menu_open = false;
	inline std::unique_ptr<c_render_manager> render_manager;
	inline std::unique_ptr<c_minecraft> minecraft;
	inline std::unique_ptr<c_world>world;
}