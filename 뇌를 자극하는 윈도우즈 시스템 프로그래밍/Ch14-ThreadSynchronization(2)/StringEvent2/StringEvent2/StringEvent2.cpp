/*
* Windows System Programming - 쓰레드 동기화 기법(2)
* 파일명: StringEvent2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-08
* 이전 버전 작성 일자:
* 버전 내용: 이벤트 기반 동기화 기법 - Manual-Reset 모드를 활용한 Event 기반 동기화 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

// 생성한 쓰레드에서 사용할 함수 선언
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

// main 쓰레드, 생산자의 역할
int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	// Event 생성
	hEvent = CreateEvent(
		NULL, // 보안(상속) 속성, 상속하지 않으므로 NULL
		TRUE, // manual-reset mode로, FALSE로 주면 auto-reset mode
		FALSE, // Non-Signaled 상태로 생성
		NULL // 이름 설정, 여기서는 안쓰므로 NULl
	);

	if (hEvent == NULL) // 이벤트 생성 실패 시
	{
		_tprintf(TEXT("Event object Creation Error\n"));
		return -1;
	}

	// 쓰레드 생성, 소비자1
	hThread[0] = (HANDLE)_beginthreadex(
		NULL, // 보안(상속) 속성, 상속하지 않으므로 NULL
		0, // 쓰레드의 스택 크기, 0으로 줄 경우 디폴트값(1M)
		OutputThreadFunction, // 쓰레드에서 실행할 함수
		NULL, // 함수에 전달할 인자
		0, // 생성과 동시에 실행, 생성하자마자 실행하지 않으려면 CREATE_SUSPENDED 속성
		(unsigned*)&dwThreadID[0] // 쓰레드의 ID를 저장할 변수의 주소값 설정
	);

	// 쓰레드 생성, 소비자2
	hThread[1] = (HANDLE)_beginthreadex(
		NULL, // 보안(상속) 속성, 상속하지 않으므로 NULL
		0, // 쓰레드의 스택 크기, 0으로 줄 경우 디폴트값(1M)
		CountThreadFunction, // 쓰레드에서 실행할 함수
		NULL, // 함수에 전달할 인자
		0, // 생성과 동시에 실행, 생성하자마자 실행하지 않으려면 CREATE_SUSPENDED 속성
		(unsigned*)&dwThreadID[1] // 쓰레드의 ID를 저장할 변수의 주소값 설정
	);

	if (hThread[0] == NULL || hThread[1] == NULL) // 쓰레드 생성 실패 시
	{
		_tprintf(TEXT("Thread object Creation Error\n"));
		return -1;
	}


	// 문자열을 입력받는다. (main 쓰레드 == 생산자)
	_fputts(TEXT("Insert string: "), stdout);
	_fgetts(string, 30, stdin);

	// 이벤트를 Signaled 상태로 변경
	SetEvent(hEvent);

	WaitForMultipleObjects(
		2,
		hThread,
		TRUE,
		INFINITE
	);
	CloseHandle(hEvent);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	// Event가 Signaled 상태가 될 때까지 쓰레드는 블로킹된 상태가 된다.
	WaitForSingleObject(hEvent, INFINITE);
	// 그리고 현재 Event는 manual-reset 모드로 생성
	// WaitForSingleObject 함수 호출 이후에도 계속 Signaled 상태를 유지하게 됨
	// 여기서는 굳이 상태를 변경할 필요가 없으므로 넣지는 않았으나 엄밀히 따지면 넣는 것이 맞음
	// Signaled 상태의 Event를 Non-Signaled로 변경
	// ResetEvent(hEvent);

	// Event가 Signaled 상태가 되면 아래의 문장을 수행

	_fputts(TEXT("Output String: "), stdout);
	_fputts(string, stdout);

	// 임계 영역이 끝이 나면 이벤트를 다시 Signaled 상태로 변경
	// SetEvent(hEvent);

	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	// Event가 Signaled 상태가 될 때까지 쓰레드는 블로킹된 상태가 된다.
	WaitForSingleObject(hEvent, INFINITE);
	// 그리고 현재 Event는 manual-reset 모드로 생성
	// WaitForSingleObject 함수 호출 이후에도 계속 Signaled 상태를 유지하게 됨
	// 여기서는 굳이 상태를 변경할 필요가 없으므로 넣지는 않았으나 엄밀히 따지면 넣는 것이 맞음
	// Signaled 상태의 Event를 Non-Signaled로 변경
	// ResetEvent(hEvent);

	// Event가 Signaled 상태가 되면 아래의 문장을 수행

	_tprintf(TEXT("Output String Length: %lld\n"), _tcslen(string)-1);

	// 임계 영역이 끝이 나면 이벤트를 다시 Signaled 상태로 변경
	// SetEvent(hEvent);

	return 0;
}