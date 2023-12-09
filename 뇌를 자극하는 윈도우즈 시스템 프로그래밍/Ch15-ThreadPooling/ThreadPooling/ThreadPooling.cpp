/*
* Windows System Programming - 쓰레드 풀링(Pooling)
* 파일명: ThreadPooling.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-09
* 이전 버전 작성 일자:
* 버전 내용: 기본적인 쓰레드 풀(Thread Pool) 구현
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define WORK_MAX 10000
#define THREAD_MAX 50

// 쓰레드에서 처리할 Work에 대한 정의.
// 반환형이 void, 매개변수도 void인 함수 포인터를 typedef 선언.
typedef void(*WORK)(void);

// 쓰레드 풀의 ADT
DWORD AddWorkToPool(WORK work); // 새로운 Work를 쓰레드 풀에 등록
WORK GetWorkFromPool(void); // 쓰레드 풀에서 Work을 가져올 때 호출하는 함수
DWORD MakeThreadToPool(DWORD numOfThread); // 쓰레드 풀을 생성한 이후 풀에 쓰레드를 생성(등록)하는 함수, 인자의 수만큼 쓰레드 생성
void WorkerThreadFunction(LPVOID lpParam); // 쓰레드가 생성되자마자 호출하는 쓰레드의 main 함수

// 쓰레드 구조체
typedef struct _workerthread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

// Work와 쓰레드 관리를 위한 구조체
struct _threadPool
{
	WORK workList[WORK_MAX]; // Work 등록을 위한 배열

	WorkerThread workerThreadList[THREAD_MAX]; // 각 쓰레드의 정보를 담기 위한 배열
	HANDLE workerEventList[THREAD_MAX]; // 각 쓰레드 별 Event 오브젝트를 담기 위한

	DWORD idxOfCurrentWork; // 처리 1순위 Work 인덱스
	DWORD idxOfLastAddedWork; // 가장 마지막에 추가된 Work의 인덱스

	// Num_Of_Thread
	DWORD threadIdx; // 풀에 있는 쓰레드의 갯수
} gThreadPool; // 전역변수로 사용, 별칭을 붙이는 typedef 선언 없이 구조체 정의

// 뮤텍스 관련 함수 정의 부분 시작

static HANDLE mutex = NULL; // 뮤텍스를 static 전역 변수로 선언 -> 이 파일 내에서만 유효하다.

// 뮤텍스 생성
void InitMutex(void)
{
	mutex = CreateMutex(NULL, FALSE, NULL);

	if (mutex == NULL)
		_tprintf(TEXT("CreateMutex Failed, Error Code: %d\n"), GetLastError());
}
// 뮤텍스의 핸들 반환, Usage Count 1 감소
void CloseMutex(void)
{
	BOOL ret = CloseHandle(mutex);

	if (ret == 0)
		_tprintf(TEXT("CloseHadle Failed, Error Code: %d\n"), GetLastError());
}

// 뮤텍스를 획득
void AcquireMutex(void)
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if (ret == WAIT_FAILED)
		_tprintf(TEXT("Error Occured, Error Code: %d\n"), GetLastError());
}

// 뮤텍스를 반환 (C++이므로 함수 오버로딩 가능)
void ReleaseMutex(void)
{
	BOOL ret = ReleaseMutex(mutex);
	if (ret == 0)
		_tprintf(TEXT("Error Occured, Error Code: %d\n"), GetLastError());
}
// 뮤텍스 관련 함수 정의 부분 끝


// 쓰레드 풀 관련 함수 정의 부분 시작
// 쓰레드 풀에 Work를 등록시키기 위한 함수
DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();
	if (gThreadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		_tprintf(TEXT("AddWorkToPool Failed, Error Code: %d\n"), GetLastError());
		return NULL;
	}

	// Work 등록
	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;

	// Work 등록 후, 대기 중인 쓰레드를 모두 실행시켜서 작업을 처리함
	// 사실 모든 쓰레드를 실행시킬 필요는 없어서 효율성이 떨어짐 -> 개선 가능하다면 개선하는 것이 좋음
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();
	return 1;
}

// 쓰레드 풀에서 Work를 가져올 때 호출되는 함수
// gThreadPool에 대한 접근을 보호하기 위해 정의
WORK GetWorkFromPool()
{
	WORK work = NULL;

	AcquireMutex();

	// 현재 처리해야 할 Work가 없다면
	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];
	ReleaseMutex();

	return work;
}

// 쓰레드 풀 생성
// 전달되는 인자의 값만큼 쓰레드를 생성
DWORD MakeThreadToPool(DWORD numOfThread)
{
	InitMutex();
	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;

		gThreadPool.workerEventList[gThreadPool.threadIdx]
			= CreateEvent(NULL, FALSE, FALSE, NULL);

		hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			(_beginthreadex_proc_type)WorkerThreadFunction,
			(LPVOID)gThreadPool.threadIdx,
			0,
			(unsigned*)&idThread
		);

		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		(gThreadPool.threadIdx++);
	}

	return numOfThread;
}

void WorkerThreadFunction(LPVOID lpParam)
{
	WORK workFunction;
	HANDLE event = gThreadPool.workerEventList[(DWORD)lpParam];

	while (1)
	{
		workFunction = GetWorkFromPool();
		if (workFunction == NULL)
		{
			// Work가 할당될 때까지 Blocked 상태
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}
// 쓰레드 풀 관련 함수 정의 부분 끝

// 단순한 Work Function
void TestFunction()
{
	// i는 static 변수 -> DATA 영역에 할당
	// 쓰레드에 의해 동시 접근이 가능하다
	// 동기화가 필요하지만 현 시점에서는 생략.
	static int i = 0;
	i++;

	_tprintf(TEXT("Good Test -- %d: Processing thread: %d\n\n"), i, GetCurrentThreadId());
}

int _tmain(int argc, TCHAR* argv[])
{
	MakeThreadToPool(3);

	// 다수의 Work를 등록
	for (DWORD i = 0; i < 100; i++)
		AddWorkToPool(TestFunction);

	Sleep(50000);
	return 0;
}