/*
* Windows System Programming - 쓰레드 동기화 기법(2)
* 파일명: Timer.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-08
* 이전 버전 작성 일자:
* 버전 내용: 타이머 기반 동기화 기법 - Timer 기반 동기화 예제
* 이전 버전 내용:
*/

// SetWaitableTimer 함수를 호출하기 위한 매크로
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(
		NULL, // 보안(상속) 속성
		FALSE, // auto-reset 모드로 설정, TRUE로 하면 manual-reset
		NULL // 이름을 붙여줄 경우에 사용하는 인자
	);

	if (!hTimer)
	{
		_tprintf(TEXT("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return -1;
	}

	_tprintf(TEXT("Waiting for 10 seconds...\n"));

	SetWaitableTimer(
		hTimer, // 알람을 설정할 타이머의 핸들
		&liDueTime, // 알람이 울릴 시간
		0, // 타이머를 주기적으로 울리기 위한 인자, 0이면 주기적으로 동작 안함
		NULL, // 완료 루틴 타이머, 이후에 다룸
		NULL, // 완료 루틴 타이머, 이후에 다룸
		FALSE // Resume 인자, 전원 관리와 관련 있는 변수. 기본적으로는 FALSE
	);

	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(TEXT("Timer was signaled\n"));
	MessageBeep(MB_ICONEXCLAMATION);

	return 0;
}