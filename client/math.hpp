#pragma once
#include "geometry.h"

namespace math {
	constexpr float pi = 3.14159265358979323846f;
	
	float wrap_angle_to_180(float angle);
	Vector2 wrap_angle_to_180(Vector2 angle);
	float rad_to_deg(float rad);
	float deg_to_rad(float deg);
	Vector2 get_angles(Vector3 src, Vector3 dst);
}