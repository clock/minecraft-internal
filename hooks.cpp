#include "hooks.hpp"
#include "include/MinHook.h"
#include <iostream>

namespace hooks {
	void init() {
		MH_Initialize();

		MH_CreateHookApi(L"ws2_32.dll", "WSASend", &hooks::WSASendHook, reinterpret_cast<void**>(&hooks::WSASendOriginal));
		MH_CreateHookApi(L"ws2_32.dll", "WSARecv", &hooks::WSARecvHook, reinterpret_cast<void**>(&hooks::WSARecvOriginal));
		
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

		printf("WSASend called\n");

		return WSASendOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
	}

	int __stdcall WSARecvHook(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesRecvd,
		LPDWORD lpFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

		printf("WSARecv called\n");

		return WSARecvOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
	}
}