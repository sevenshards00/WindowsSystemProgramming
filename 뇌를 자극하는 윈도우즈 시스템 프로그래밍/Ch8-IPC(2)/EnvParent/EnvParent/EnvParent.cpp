/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: EnvParent.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 프로세스 환경변수를 이용하는 예제 - 부모 프로세스
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SetEnvironmentVariable(_T("Good"), _T("Morning"));
	SetEnvironmentVariable(_T("Hey"), _T("Ho!"));
	SetEnvironmentVariable(_T("Big"), _T("Boy"));

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("EnvChild.exe");

	CreateProcess(
		NULL, command, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		NULL, // 부모 프로세스의 환경변수 등록
		NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	

	return 0;
}