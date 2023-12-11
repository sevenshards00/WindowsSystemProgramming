/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: TerminationHandlerEx2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 종료 핸들러의 활용 예제(2) - 쓰레드의 동기화(뮤텍스의 소유 및 반환)
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 7

// 전역 변수로 사용. -> 쓰레드는 공유 가능
LONG gTotalCount = 0;

// Mutex 오브젝트를 선언
// 커널에 의해 생성되는 오브젝트이므로 HANDLE값을 가지게 된다.
HANDLE hMutex;

void IncreaseCount()
{
	__try
	{
		// Signaled -> Non-Signaled
		WaitForSingleObject(hMutex, INFINITE); // EnterCriticalSection(&hCriticalSection);
		gTotalCount++; // 임계 영역(Critical Section)

	}
	__finally
	{
		// Non-Signaled -> Signaled
		ReleaseMutex(hMutex); // LeaveCriticalSection(&hCriticalSection);
	}
	}
	

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}

	return 0;
}

int _tmain(int argc, TCHAR argv[])
{
	DWORD dwThreadID[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	// InitializeCriticalSection(&hCriticalSection);
	// 뮤텍스를 생성
	hMutex = CreateMutex(
		NULL, // 디폴트 보안 속성 (상속)
		FALSE, // 누구나 소유할 수 있도록 함 -> 선점형 / TRUE로 설정할 경우 뮤텍스를 생성하는 쓰레드가 우선적으로 소유하게 된다
		NULL // 이름을 정하지 않음
	);

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(
			NULL, // 보안(상속) 속성, 안하므로 NULL
			0, // 쓰레드의 스택 크기, 0으로 주면 디폴트값(1M)
			ThreadProc, // 쓰레드의 main이 될 함수
			NULL, // 쓰레드에 전달할 인자, 없으므로 NULL
			CREATE_SUSPENDED, // 생성 시 즉시 실행 여부를 인자로 전달, CREATE_SUSPENDED를 전달했으므로 바로 실행하지 않는다
			(unsigned*)&dwThreadID[i] // 쓰레드의 ID값을 저장할 주소값을 인자로 전달
		);

		// 쓰레드의 생성이 실패했을 경우
		if (hThread[i] == NULL)
		{
			_tprintf(TEXT("Thread Creation Fault\n"));
			return -1;
		}
	}

	// 모든 쓰레드를 실행 상태로 바꾸는 부분
	// 쓰레드 생성 또한 시간이 걸리는 작업이므로 동시 실행을 위해서 SUSPENDED로 생성 
	// ResumeThread 함수를 통해 모든 쓰레드를 실행 상태로 바꾼다. 
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}

	// 모든 쓰레드의 작업이 끝나기를 기다리는 부분
	WaitForMultipleObjects(
		NUM_OF_GATE, // 관찰할 오브젝트의 갯수
		hThread, // 관찰할 오브젝트를 담고 있는 배열의 주소
		TRUE, // 모든 오브젝트가 Signaled 상태가 되면 값을 반환
		INFINITE // 무한정으로 대기
	);

	_tprintf(TEXT("total count: %d\n"), gTotalCount);

	// 생성한 쓰레드의 커널 오브젝트 Usage Count를 감소 (리소스 해제 요청)
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
		CloseHandle(hThread[i]);

	// 뮤텍스는 커널 오브젝트이므로 핸들을 반환 및 Usage Count 1 감소
	CloseHandle(hMutex); // DeleteCriticalSection(&hCriticalSection);

	return 0;
}