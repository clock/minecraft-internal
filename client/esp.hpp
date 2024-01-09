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
#include <gl/GL.h>

struct box_t {
	int x, y, w, h;
};

struct esp_data {
	box_t box = {};
	std::string name;
	int health;
	int max_health;
	float distance;
};

struct block_data {
	BoundingBox bounding_box;
};

namespace esp {

	inline Vector2 screen_size;
	inline GLfloat proj_matrix_arr[16];
	inline GLfloat model_matrix_arr[16];
	inline Matrix proj_matrix;
	inline Matrix model_matrix;
	inline std::vector<esp_data> entity_points;
	inline std::vector<block_data> block_points;
	void update_data();
	bool compute_box(std::shared_ptr<c_entity> player, std::shared_ptr<c_entity> local_player, box_t& box);
	void box(esp_data data);
	void health(esp_data data);
	void name(esp_data data);
	void block_esp();
	void draw();
}