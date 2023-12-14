/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: CompletionRoutinePeriodicTimer.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 완료 루틴 타이머 예제
* 이전 버전 내용:
*/

#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(NULL, FALSE, TEXT("WaitableTimer"));
	if (!hTimer)
	{
		_tprintf(TEXT("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(TEXT("Waiting for 10 seconds...."));

	TCHAR timerArg[] = TEXT("Timer was Signaled\n");

	SetWaitableTimer(hTimer, &liDueTime, 5000, TimerAPCProc, timerArg, FALSE);

	while (1)
		SleepEx(INFINITE, TRUE);

	return 0;
}

VOID CALLBACK TimerAPCProc(LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal)
{
	_tprintf(TEXT("%s"), (TCHAR*)lpArg);
	MessageBeep(MB_ICONEXCLAMATION);
}