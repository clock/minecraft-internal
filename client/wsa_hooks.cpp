#include "hooks.hpp"

int __stdcall hooks::WSASendHook(
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

	auto return_buffer = hooks::WSASendOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
	return return_buffer;
}

int __stdcall hooks::WSARecvHook(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd,
	LPDWORD lpFlags,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
	//printf("WSARecv called\n");

	return hooks::WSARecvOriginal(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

int __stdcall hooks::recvHook(SOCKET s, char* buf, int len, int flags) {
	//printf("recv called\n");

	return hooks::recvOriginal(s, buf, len, flags);
}

int __stdcall hooks::sendHook(SOCKET s, const char* buf, int len, int flags) {
	//printf("send called\n");

	return hooks::sendOriginal(s, buf, len, flags);
}