/*
* Windows System Programming - 쓰레드 동기화 기법(1)
* 파일명: CriticalSectionSync.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-08
* 이전 버전 작성 일자:
* 버전 내용: 유저모드 동기화 기법(1) - Critical Section 기반 동기화 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

// 전역 변수로 사용. -> 쓰레드는 공유 가능
LONG gTotalCount = 0;

// Critical Section 오브젝트를 선언
CRITICAL_SECTION hCriticalSection;

void IncreaseCount()
{
	// 임계 영역 진입 전 쓰레드는 EnterCriticalSection 함수를 호출하여 크리티컬 섹션 오브젝트를 얻게됨
	// 크리티컬 섹션 오브젝트를 얻은 쓰레드가 이미 있는 경우, 다른 쓰레드가 해당 함수를 호출하면 블로킹 상태가 됨
	// LeaveCriticalSection 함수를 호출해서 크리티컬 섹션 오브젝트를 반환하면 블로킹 상태에서 빠져나오게 된다.
	EnterCriticalSection(&hCriticalSection);
	gTotalCount++; // 임계 영역(Critical Section)
	LeaveCriticalSection(&hCriticalSection);
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

	// Critical Section 오브젝트 초기화
	InitializeCriticalSection(&hCriticalSection);

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

	// Critical Section 오브젝트 역시 오브젝트(커널 오브젝트는 아님)이므로 리소스 해제.
	DeleteCriticalSection(&hCriticalSection);

	return 0;
}