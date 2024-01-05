#include "hooks.hpp"
#include <iostream>

bool hooks::wglSwapBuffersHook(HDC hdc) {
	//printf("wglSwapBuffers called\n");

	return hooks::wglSwapBuffersOriginal(hdc);
}