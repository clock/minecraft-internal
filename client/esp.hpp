#pragma once
#include "java.hpp"
#include <jni.h>
#include <Windows.h>
#include <gl/GL.h>
#include "c_entity.hpp"
#include "c_world.hpp"
#include "c_active_render_info.hpp"
#include "c_render_manager.hpp"
#include "geometry.h"
#include <vector>

struct box_t {
	int x, y, w, h;
};

struct esp_data {
	box_t box = {};
	std::string name;
	int health;
	int max_health;
};

namespace esp {

	// put in config
	const int max_distance = 35;

	inline std::vector<esp_data> entity_points;
	void update_data();
	bool compute_box(std::shared_ptr<c_entity> player, std::shared_ptr<c_entity> local_player, c_active_render_info render_info, box_t& box);
	void box(esp_data data);
	void health(esp_data data);
	void name(esp_data data);
	void draw();
}