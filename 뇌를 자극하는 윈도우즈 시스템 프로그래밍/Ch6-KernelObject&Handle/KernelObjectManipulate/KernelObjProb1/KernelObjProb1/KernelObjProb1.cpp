/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: KernelObjProb1.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: CloseHandle 함수 사용 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernelObjProb2.exe");
	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		0, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);

	return 0;
}