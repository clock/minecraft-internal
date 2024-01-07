#pragma once
#include <Windows.h>

namespace gui {
	void init(HDC hdc);
	void shutdown();
	void draw();
	void begin();
	void end();

	// this will be in the config system in the future
	inline float slide = 0.f;
}