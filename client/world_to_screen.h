#pragma once
#include "geometry.h"
#include <Windows.h>
#include <gl/GL.h>

class c_world_to_screen
{
public:
	static Vector4 multiply(Vector4 v, Matrix m);
	static bool world_to_screen(Vector3 point, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2& screenPos);
};