/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: APCQueue.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: APC Queue 기본 예제
* 이전 버전 내용:
*/

#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

VOID CALLBACK APCProc(ULONG_PTR);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread = GetCurrentThread();

	QueueUserAPC(APCProc, hThread, (ULONG_PTR)1);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)2);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)3);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)4);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)5);

	Sleep(5000);
	SleepEx(INFINITE, TRUE);
	return 0;
}

VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	_tprintf(TEXT("Asynchronous procedure call num %u\n"), (DWORD)dwParam);
}