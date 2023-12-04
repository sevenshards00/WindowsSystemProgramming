/*
* Windows System Programming - 커널 오브젝트의 상태(State)
* 파일명: NonstopAdderManager.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: 커널 오브젝트의 상태(State)와 종료 코드(Exit Code)의 이해
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1 = { 0, };
	PROCESS_INFORMATION pi2 = { 0, };

	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE,
		0, NULL, NULL, &si1, &pi1);
	CreateProcess(NULL, command2, NULL, NULL, TRUE,
		0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)
		return -1;

	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("Total: %d\n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}