/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: DuplicateHandle.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: DuplicateHandle 함수 사용 예제 - 부모 프로세스
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hProcess;
	TCHAR cmdString[1024];

	// 자신의 가짜(Pseudo) 핸들을 복제하여 진짜 핸들을 얻어옴
	DuplicateHandle(
		GetCurrentProcess(), GetCurrentProcess(),
		GetCurrentProcess(), &hProcess, 0,
		TRUE, DUPLICATE_SAME_ACCESS
	);

	// 부모 프로세스의 핸들을 "ChildProcess.exe hProcess" 형식으로 전달
	_stprintf(cmdString, _T("%s %u"), _T("DuplicateHandleChildProcess.exe"), (unsigned)hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	BOOL isSuccess = CreateProcess(
		NULL, cmdString, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	if (isSuccess == FALSE)
	{
		_tprintf(_T("Create Process Failed\n"));
		return -1;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_tprintf(_T("[Parent Process]\n"));
	_tprintf(_T("OOOOOOOOOOOOOOOOOOOOOOPPPS!!!\n"));

	return 0;
}