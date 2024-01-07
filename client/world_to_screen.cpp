#include "world_to_screen.h"
#include <limits>

Vector4 c_world_to_screen::multiply(Vector4 vec, GLfloat mat[16])
{
	return Vector4(
		vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + vec.w * mat[12],
		vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + vec.w * mat[13],
		vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + vec.w * mat[14],
		vec.x * mat[3] + vec.y * mat[7] + vec.z * mat[11] + vec.w * mat[15]
	);
}

bool c_world_to_screen::world_to_screen(Vector3 point_in_world, Vector2& screen, GLfloat modelview[16], GLfloat projection[16], int screen_height, int screen_width)
{
	Vector4 clip_space_pos = multiply(multiply(Vector4(point_in_world.x, point_in_world.y, point_in_world.z, 1.0f), modelview), projection);

	Vector3 ndc_space_pos = Vector3(clip_space_pos.x / clip_space_pos.w, clip_space_pos.y / clip_space_pos.w, clip_space_pos.z / clip_space_pos.w);

	// nPlane = -1, fPlane = 1
	if (ndc_space_pos.z < -1.0 || ndc_space_pos.z > 1.0)
	{
		return false;
	}

	screen.x = ((ndc_space_pos.x + 1.0f) / 2.0f) * screen_width;
	screen.y = ((1.0f - ndc_space_pos.y) / 2.0f) * screen_height;
	return true;
}