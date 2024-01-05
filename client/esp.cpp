#include "esp.hpp"
#include <iostream>

void esp::run() {

	// make active render info
	auto active_render_info = c_active_render_info();

	// get the viewport
	auto viewport = active_render_info.get_viewport();

	// print out the viewport
	for (int i = 0; i < 16; ++i) {
		std::cout << viewport[i] << std::endl;
	}

	return;
}