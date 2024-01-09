#include "math.hpp"
#include <cmath>

float math::wrap_angle_to_180(float angle) {
	angle = std::fmod(angle, 360.0f);
	if (angle >= 180.0f)
		angle -= 360.0f;

	if (angle < -180.0f)
		angle += 360.0f;

	return angle;
}

Vector2 math::wrap_angle_to_180(Vector2 angle) {
	return Vector2{
		math::wrap_angle_to_180(angle.x),
		math::wrap_angle_to_180(angle.y),
	};
}

float math::deg_to_rad(float deg) {
	return deg * (math::pi / 180.0f);
}

float math::rad_to_deg(float rad) {
	return rad * (180.0f / math::pi);
}

Vector2 math::get_angles(Vector3 src, Vector3 dst) {
	double d_x = dst.x - src.x;
	double d_y = dst.y - src.y;
	double d_z = dst.z - src.z;

	double hypothenuse = sqrt(d_x * d_x + d_z * d_z);
	float yaw = rad_to_deg(atan2(d_z, d_x)) - 90.f;
	float pitch = rad_to_deg(-atan2(d_y, hypothenuse));

	return Vector2(yaw, pitch);
}