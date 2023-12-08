/*
* Windows System Programming - 쓰레드 동기화 기법(1)
* 파일명: CriticalSectionSyncSemaphore.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-08
* 이전 버전 작성 일자:
* 버전 내용: 커널모드 동기화 기법(2) - Semaphore 기반 동기화 예제
* 이전 버전 내용:
*/

/* '명동교자'라는 가게에 대한 시뮬레이션을 한다고 가정 
* 시뮬레이션 제한 요소:
* 1. 테이블은 총 10개, 동시에 총 10명의 고객만 받을 수 있음
* 2. 점심 시간에 식사를 하러 올 고객은 50명으로 예상됨
* 3. 고객의 식사 시간은 10~30분 사이
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>
#include <time.h>

#define NUM_OF_CUSTOMER 50 // 최대 고객 수
#define RANGE_MIN 10 // 최소 식사 시간 범위
#define RANGE_MAX (30 - RANGE_MIN) // 최대 식사 시간 범위
#define TABLE_CNT 10 // 테이블 수

// 세마포어 선언
HANDLE hSemaphore;
// 난수를 통해 계산한 식사 시간(10~30분)을 저장하는 배열
DWORD randTimeArr[50];
// 테이블 갯수 변화 확인용 변수
DWORD leftTblCnt = TABLE_CNT;
// 총 식사 시간
DWORD total_Time = 0;

// 식사를 하는 상황을 함수로 구현
void TakeMeal(DWORD time)
{
	// 식사를 하기 위해 손님이 들어오는 상황.
	// 테이블 == 세마포어, 손님 == 쓰레드
	// Count가 0이면 Non-Signaled, Count가 1이상이면 Signaled
	WaitForSingleObject(hSemaphore, INFINITE);
	_tprintf(TEXT("Enter Customer: %d \n"), GetCurrentThreadId());
	leftTblCnt--;
	_tprintf(TEXT("Left Table Count: %d\n\n"), leftTblCnt);
	

	// 식사 중
	_tprintf(TEXT("Cumstomer %d having lunch\n"), GetCurrentThreadId());
	Sleep(1000 * time);
	total_Time += time;

	// 식사를 마치고 나감
	// 두 번째 인자는 세마포어의 카운트를 얼마나 증가시킬 것인가를 인자로 받음
	// 통상적으로는 1을 쓰는게 다반사임
	// 최대 카운트를 넘는 값을 증가시킬 경우에는 값은 변경되지 않고 FALSE를 반환
	ReleaseSemaphore(hSemaphore, 1, NULL);
	leftTblCnt++;
	_tprintf(TEXT("Out Customer: %d / Time spent: %d  \n"), GetCurrentThreadId(), time);
	_tprintf(TEXT("Left Table Count: %d\n\n"), leftTblCnt);
}

// 쓰레드의 main이 될 함수
unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	TakeMeal((DWORD)lpParam);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[NUM_OF_CUSTOMER]; // 쓰레드의 ID를 담을 변수
	HANDLE hThread[NUM_OF_CUSTOMER]; // 쓰레드 오브젝트

	// 난수 생성에 현재 시간을 seed로 설정
	// srand는 난수 생성에 사용할 seed를 설정한다.
	srand((unsigned)time(NULL));

	// 쓰레드에 전달할 난수값 총 50개 생성
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		// 난수 생성에 대해서 지식이 부족하여 이 부분은 추가로 정리
		// rand 함수는 0부터 0x7fff(32767)까지의 난수를 정수값으로 반환한다.
		// 그래서 RAND_MAX의 값이 32767인 것.
		// 만약 해당 범위 내에서 0~99까지의 난수를 구하고 싶다면 100의 나머지를 구하면 된다. -> rand() % 100
		// rand() / RAND_MAX 은 0과 1만 나올 수 있는 경우다.
		// 여기서 실수형으로의 형 변환을 통해 0.0 ~ 1.0 사이의 값이 나오게 된다.
		// 아래의 식을 해석하면 (0.0 ~ 1.0 중 하나) * 20 + 10이 된다.
		// 그래서 생성되는 난수는 10~30 사이가 된다.
		randTimeArr[i] = (DWORD)(((double)rand() / (double)RAND_MAX) * RANGE_MAX + RANGE_MIN);

	// 세마포어 생성
	hSemaphore = CreateSemaphore(
		NULL, // 보안(상속) 속성 설정 -> 상속하지 않는다
		TABLE_CNT, // 세마포어 Count 초기값 설정
		TABLE_CNT, // 세마포어 Count 최대값 설정
		NULL // 세마포어의 이름 설정, 없다면 NULL
	);

	// 세마포어 생성에 실패했다면
	if (hSemaphore == NULL)
		_tprintf(TEXT("Create Semaphore Error: %d\n"), GetLastError()); // 에러코드를 출력

	// Customer가 될 쓰레드 생성
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(
			NULL, // 보안(상속) 속성, 상속 안하므로 NULL
			0, // 쓰레드의 스택 크기, 0으로 줬으므로 디폴트(1M)
			ThreadProc, // 쓰레드의 main이 될 함수
			(void*)randTimeArr[i], // 쓰레드에 전달할 인자. 전달 인자 데이터형이 void*이므로 형 변환하여 전달
			CREATE_SUSPENDED, // 쓰레드 생성 시 실행 여부를 전달, 바로 실행하지 않음
			(unsigned*)&dwThreadID[i] // 쓰레드의 ID값을 저장할 주소값을 인자로 설정
		);

		// 쓰레드 생성이 실패했다면
		if (hThread[i] == NULL)
		{
			_tprintf(TEXT("Thread Creation Failed\n"));
			return -1;
		}
	}

	// 쓰레드 생성이 완료되면 순차적으로 쓰레드 실행
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		ResumeThread(hThread[i]);

	// 모든 쓰레드가 Signaled가 될 때까지(작업이 끝날 때까지) 블로킹
	WaitForMultipleObjects(
		NUM_OF_CUSTOMER, // 관찰할 오브젝트의 수
		hThread, // 관찰할 오브젝트를 담고 있는 배열
		TRUE, // 모든 오브젝트가 Signaled 상태가 되면 값을 반환, 하나라도 Signaled가 되서 반환을 원한다면 FALSE
		INFINITE // 무한정 대기
	);

	_tprintf(TEXT("Estimated time to complete meal serving: %d\n"), total_Time);
	_tprintf(TEXT("-----END-----\n"));

	// 쓰레드의 핸들을 반환하는 과정
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		CloseHandle(hThread[i]);

	// 세마포어의 핸들을 반환
	CloseHandle(hSemaphore);
	return 0;
}