#include "esp.hpp"
#include <iostream>

void esp::run(c_entity* local_player, c_world* world, c_render_manager* render_manager) {

	// make active render info
	auto active_render_info = c_active_render_info();

	// get the viewport
	auto viewport = active_render_info.get_viewport();

	std::cout << "viewport: " << std::endl;

	// print out the viewport
	for (int i = 0; i < 16; ++i) {
		std::cout << viewport[i] << std::endl;
	}

	// get the projection matrix
	auto projection_matrix = active_render_info.get_projection_matrix();

	std::cout << "projection matrix: " << std::endl;

	// print out the projection matrix
	for (int i = 0; i < 16; ++i) {
		std::cout << projection_matrix[i] << std::endl;
	}

	// get the modelview matrix
	auto modelview_matrix = active_render_info.get_modelview_matrix();

	std::cout << "modelview matrix: " << std::endl;

	// print out the modelview matrix
	for (int i = 0; i < 16; ++i) {
		std::cout << modelview_matrix[i] << std::endl;
	}

	// render position
	float pos_x = (float)render_manager->get_render_posx();
	float pos_y = (float)render_manager->get_render_posy();
	float pos_z = (float)render_manager->get_render_posz();

	std::cout << "render position: " << std::endl;
	std::cout << "x: " << pos_x << std::endl;
	std::cout << "y: " << pos_y << std::endl;
	std::cout << "z: " << pos_z << std::endl;

	return;
}