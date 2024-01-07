#pragma once
#include "geometry.h"
#include <Windows.h>
#include <gl/GL.h>

class c_world_to_screen
{
public:
	static Vector4 multiply(Vector4 vec, GLfloat mat[16]);
	static bool world_to_screen(Vector3 point_in_world, Vector2& screen, GLfloat modelview[16], GLfloat projection[16], int screen_height, int screen_width);
};