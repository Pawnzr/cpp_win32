#include <Windows.h>

/*
H�m SetTimer trong th? vi?n winuser.h ???c s? d?ng ?? t?o m?t b? h?n gi? (timer) v� thi?t l?p m?t s? ki?n ?? g?i l?i (callback) sau m?t kho?ng th?i gian nh?t ??nh
UINT_PTR SetTimer(
  HWND      hWnd,           // C?a s? m� h�m g?i l?i s? ???c g?i t?i
  UINT_PTR  nIDEvent,       // ID c?a b? h?n gi?
  UINT      uElapse,        // Th?i gian gi?a c�c l?n g?i l?i (miligi�y)
  TIMERPROC lpTimerFunc     // Con tr? ??n h�m g?i l?i
);
*/

int main() {
	UNIT_PTR timerID = SetTimer()
}