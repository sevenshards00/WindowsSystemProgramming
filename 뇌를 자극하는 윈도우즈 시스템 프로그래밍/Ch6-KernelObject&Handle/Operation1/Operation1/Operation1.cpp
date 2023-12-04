/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: Opertaion1.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자:
* 버전 내용: 커널 오브젝트 핸들을 이용한 커널 오브젝트의 조작 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR command[] = _T("Operation2.exe");

	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &pi);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting 상태

		_fputts(_T("Operation1.exe\n"), stdout);
	}
	return 0;
}