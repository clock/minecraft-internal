#define _WINSOCKAPI_
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdint>
#include "include/MinHook.h"
#include "hooks.hpp"
#include "java.hpp"

void unload(void* instance, const char* reason = "No reason given.");

const wchar_t* title = L"minecraft backtrack";
bool attached = false;

void main_thread(void* instance) {

	// setup console
	attached = AllocConsole() && SetConsoleTitleW(title);
	freopen_s(reinterpret_cast<FILE**>stdin, "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>stdout, "CONOUT$", "w", stdout);

	if (!attached)
		unload(instance);

	// init jvm stuff
	jsize count;

	if (JNI_GetCreatedJavaVMs(&java_instance->vm, 1, &count) != JNI_OK || count == 0)
		unload(instance, "JavaVM not found.\n");

	jint res = java_instance->vm->GetEnv((void**)&java_instance->env, JNI_VERSION_1_8);

	if (res == JNI_EDETACHED)
		res = java_instance->vm->AttachCurrentThread((void**)&java_instance->env, nullptr);

	if (java_instance->env == nullptr)
		unload(instance);

	/*hooks::init();*/

	java_instance->get_loaded_classes();

	// keeping the thread alive
	while (!GetAsyncKeyState(VK_END)) {

		Sleep(1);
	}

	// sleep, shutdown, sleep, unload
	/*Sleep(1000);
	hooks::shutdown();*/
	Sleep(1000);
	unload(instance);
}

void unload(void* instance, const char* reason) {
	printf("Unloading: %s\n", reason);
	auto console_window = GetConsoleWindow();
	FreeConsole();
	PostMessageA(console_window, WM_QUIT, 0, 0);
	FreeLibraryAndExitThread((HMODULE)instance, 0);
}

int __stdcall DllMain(void* instance, unsigned long reason_to_call, void* reserved) {
	if (reason_to_call != DLL_PROCESS_ATTACH)
		return TRUE;

	CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_thread, instance, 0, nullptr));

	return TRUE;
}