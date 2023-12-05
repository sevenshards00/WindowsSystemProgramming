/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: EnvParent.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 프로세스 환경변수를 이용하는 예제 - 자식 프로세스
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR value[BUF_SIZE];

	if (GetEnvironmentVariable(_T("Good"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Good"), value);
	if (GetEnvironmentVariable(_T("Hey"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Hey"), value);
	if (GetEnvironmentVariable(_T("Big"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Big"), value);

	Sleep(10000);

	return 0;
}