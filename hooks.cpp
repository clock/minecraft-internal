#include "hooks.hpp"
#include "include/MinHook.h"
#include <iostream>

namespace hooks {
	void init() {
		MH_Initialize();

		MH_CreateHookApi(L"ws2_32.dll", "WSASend", &hooks::WSASendHook, reinterpret_cast<void**>(&hooks::WSASendOriginal));
		MH_CreateHookApi(L"ws2_32.dll", "WSARecv", &hooks::WSARecvHook, reinterpret_cast<void**>(&hooks::WSARecvOriginal));
		MH_CreateHookApi(L"ws2_32.dll", "recv", &hooks::recvHook, reinterpret_cast<void**>(&hooks::recvOriginal));
		MH_CreateHookApi(L"ws2_32.dll", "send", &hooks::sendHook, reinterpret_cast<void**>(&hooks::sendOriginal));

		MH_EnableHook(MH_ALL_HOOKS);
	}

	void shutdown() {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}

	int __stdcall WSASendHook(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesSent,
		DWORD dwFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

		//printf("WSASend called\n");

		if (GetAsyncKeyState(VK_XBUTTON1))
			return 0;
			
		auto return_buffer = WSASendOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
		return return_buffer;
	}

	int __stdcall WSARecvHook(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesRecvd,
		LPDWORD lpFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
		//printf("WSARecv called\n");

		return WSARecvOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
	}

	int __stdcall recvHook(SOCKET s, char* buf, int len, int flags) {
		//printf("recv called\n");

		return recvOriginal(s, buf, len, flags);
	}

	int __stdcall sendHook(SOCKET s, const char* buf, int len, int flags) {
		//printf("send called\n");

		return sendOriginal(s, buf, len, flags);
	}
}