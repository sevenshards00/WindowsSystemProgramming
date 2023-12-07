/*
* Windows System Programming - 쓰레드의 생성과 소멸
* 파일명: SuspendCount.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 쓰레드의 상태 변경 확인 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	while (1)
	{
		_tprintf(TEXT("Running State!\n"));
		Sleep(10000);
	}

	return 0;
}


int main(int argc, TCHAR* argv[])
{
	DWORD dwThreadID;
	HANDLE hThread;
	DWORD susCnt; // suspend count를 확인하기 위한 변수

	hThread = (HANDLE)_beginthreadex(
		NULL,
		0,
		ThreadProc,
		NULL,
		CREATE_SUSPENDED, // 쓰레드 생성 시 Blocked 상태로 시작, Suspend Count는 1
		(unsigned*)&dwThreadID
	);

	// 쓰레드 생성 확인
	if (hThread == NULL)
		_tprintf(TEXT("Thread creation failed!\n"));

	// Tm
	susCnt = ResumeThread(hThread); // 쓰레드를 다시 Ready 상태로, Suspend Count는 0
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread); // 쓰레드를 다시 Blocked 상태로, Suspend Count는 1
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread); // 쓰레드를 Blocked 상태에서 Suspend Count를 추가, Suspend Count는 2
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread); // Blocked 상태의 쓰레드의 Suspend Count를 1감소, Suspend Count는 1
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread); // Blocked 상태의 쓰레드의 Suspend Count를 1감소, Suspend Count는 0이 되므로 쓰레드는 다시 Ready 상태
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	// 프로세스가 종료되는 것을 막기 위해 쓰레드의 실행을 확인한다
	WaitForSingleObject(hThread, INFINITE);

	return 0;
}