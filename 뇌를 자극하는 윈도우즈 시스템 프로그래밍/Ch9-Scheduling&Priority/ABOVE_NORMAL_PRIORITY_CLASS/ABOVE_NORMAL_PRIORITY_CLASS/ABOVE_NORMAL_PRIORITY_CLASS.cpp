/*
* Windows System Programming - 스케줄링 알고리즘과 우선순위
* 파일명: ABOVE_NORMAL_PRIORITY_CLASS.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 우선순위를 적용한 스케줄링 알고리즘이 적용되는 것을 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 우선순위 NORMAL_PRIORITY_CLASS를 부여할 자식 프로세스
	STARTUPINFO si_Normal = { 0, };
	PROCESS_INFORMATION pi_Normal = { 0, };
	TCHAR cmdNormal[] = _T("NORMAL_PRIORITY_CLASS.exe");

	// 우선순위 BELOW_NORMAL_PRIORITY_CLASS를 부여할 자식 프로세스
	STARTUPINFO si_Below = { 0, };
	PROCESS_INFORMATION pi_Below = { 0, };
	TCHAR cmdBelow[] = _T("BELOW_NORMAL_PRIORITY_CLASS.exe");

	si_Normal.cb = sizeof(si_Normal);
	si_Below.cb = sizeof(si_Below);

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);


	// 자식 프로세스 생성
	CreateProcess(
		NULL,cmdNormal, NULL, NULL, TRUE,
		0, NULL, NULL, &si_Normal, &pi_Normal);

	CreateProcess(
		NULL, cmdBelow, NULL, NULL, TRUE,
		0, NULL, NULL, &si_Below, &pi_Below);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		//Sleep(10);

		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}