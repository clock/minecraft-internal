#pragma once
#define _WINSOCKAPI_
#include <WinSock2.h>

namespace hooks {

	void init();
	void shutdown();

	inline int(__stdcall* WSASendOriginal)(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesSent,
		DWORD dwFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

	int __stdcall WSASendHook(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesSent,
		DWORD dwFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

	inline int(__stdcall* WSARecvOriginal)(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesRecvd,
		LPDWORD lpFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

	int __stdcall WSARecvHook(
		SOCKET s,
		LPWSABUF lpBuffers,
		DWORD dwBufferCount,
		LPDWORD lpNumberOfBytesRecvd,
		LPDWORD lpFlags,
		LPWSAOVERLAPPED lpOverlapped,
		LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

	int __stdcall recvHook(SOCKET s, char* buf, int len, int flags);

	inline int(__stdcall* recvOriginal)(
		SOCKET s, char* buf, int len, int flags);

	int __stdcall sendHook(SOCKET s, const char* buf, int len, int flags);

	inline int(__stdcall* sendOriginal)(
		SOCKET s, const char* buf, int len, int flags);

	inline bool(__stdcall* wglSwapBuffersOriginal) (HDC hdc);

	bool __stdcall wglSwapBuffersHook(HDC hdc);
}