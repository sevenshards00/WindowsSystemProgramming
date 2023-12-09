/*
* Windows System Programming - ������ Ǯ��(Pooling)
* ���ϸ�: ThreadPooling.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-09
* ���� ���� �ۼ� ����:
* ���� ����: �⺻���� ������ Ǯ(Thread Pool) ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define WORK_MAX 10000
#define THREAD_MAX 50

// �����忡�� ó���� Work�� ���� ����.
// ��ȯ���� void, �Ű������� void�� �Լ� �����͸� typedef ����.
typedef void(*WORK)(void);

// ������ Ǯ�� ADT
DWORD AddWorkToPool(WORK work); // ���ο� Work�� ������ Ǯ�� ���
WORK GetWorkFromPool(void); // ������ Ǯ���� Work�� ������ �� ȣ���ϴ� �Լ�
DWORD MakeThreadToPool(DWORD numOfThread); // ������ Ǯ�� ������ ���� Ǯ�� �����带 ����(���)�ϴ� �Լ�, ������ ����ŭ ������ ����
void WorkerThreadFunction(LPVOID lpParam); // �����尡 �������ڸ��� ȣ���ϴ� �������� main �Լ�

// ������ ����ü
typedef struct _workerthread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

// Work�� ������ ������ ���� ����ü
struct _threadPool
{
	WORK workList[WORK_MAX]; // Work ����� ���� �迭

	WorkerThread workerThreadList[THREAD_MAX]; // �� �������� ������ ��� ���� �迭
	HANDLE workerEventList[THREAD_MAX]; // �� ������ �� Event ������Ʈ�� ��� ����

	DWORD idxOfCurrentWork; // ó�� 1���� Work �ε���
	DWORD idxOfLastAddedWork; // ���� �������� �߰��� Work�� �ε���

	// Num_Of_Thread
	DWORD threadIdx; // Ǯ�� �ִ� �������� ����
} gThreadPool; // ���������� ���, ��Ī�� ���̴� typedef ���� ���� ����ü ����

// ���ؽ� ���� �Լ� ���� �κ� ����

static HANDLE mutex = NULL; // ���ؽ��� static ���� ������ ���� -> �� ���� �������� ��ȿ�ϴ�.

// ���ؽ� ����
void InitMutex(void)
{
	mutex = CreateMutex(NULL, FALSE, NULL);

	if (mutex == NULL)
		_tprintf(TEXT("CreateMutex Failed, Error Code: %d\n"), GetLastError());
}
// ���ؽ��� �ڵ� ��ȯ, Usage Count 1 ����
void CloseMutex(void)
{
	BOOL ret = CloseHandle(mutex);

	if (ret == 0)
		_tprintf(TEXT("CloseHadle Failed, Error Code: %d\n"), GetLastError());
}

// ���ؽ��� ȹ��
void AcquireMutex(void)
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if (ret == WAIT_FAILED)
		_tprintf(TEXT("Error Occured, Error Code: %d\n"), GetLastError());
}

// ���ؽ��� ��ȯ (C++�̹Ƿ� �Լ� �����ε� ����)
void ReleaseMutex(void)
{
	BOOL ret = ReleaseMutex(mutex);
	if (ret == 0)
		_tprintf(TEXT("Error Occured, Error Code: %d\n"), GetLastError());
}
// ���ؽ� ���� �Լ� ���� �κ� ��


// ������ Ǯ ���� �Լ� ���� �κ� ����
// ������ Ǯ�� Work�� ��Ͻ�Ű�� ���� �Լ�
DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();
	if (gThreadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		_tprintf(TEXT("AddWorkToPool Failed, Error Code: %d\n"), GetLastError());
		return NULL;
	}

	// Work ���
	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;

	// Work ��� ��, ��� ���� �����带 ��� ������Ѽ� �۾��� ó����
	// ��� ��� �����带 �����ų �ʿ�� ��� ȿ������ ������ -> ���� �����ϴٸ� �����ϴ� ���� ����
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();
	return 1;
}

// ������ Ǯ���� Work�� ������ �� ȣ��Ǵ� �Լ�
// gThreadPool�� ���� ������ ��ȣ�ϱ� ���� ����
WORK GetWorkFromPool()
{
	WORK work = NULL;

	AcquireMutex();

	// ���� ó���ؾ� �� Work�� ���ٸ�
	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];
	ReleaseMutex();

	return work;
}

// ������ Ǯ ����
// ���޵Ǵ� ������ ����ŭ �����带 ����
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
			// Work�� �Ҵ�� ������ Blocked ����
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}
// ������ Ǯ ���� �Լ� ���� �κ� ��

// �ܼ��� Work Function
void TestFunction()
{
	// i�� static ���� -> DATA ������ �Ҵ�
	// �����忡 ���� ���� ������ �����ϴ�
	// ����ȭ�� �ʿ������� �� ���������� ����.
	static int i = 0;
	i++;

	_tprintf(TEXT("Good Test -- %d: Processing thread: %d\n\n"), i, GetCurrentThreadId());
}

int _tmain(int argc, TCHAR* argv[])
{
	MakeThreadToPool(3);

	// �ټ��� Work�� ���
	for (DWORD i = 0; i < 100; i++)
		AddWorkToPool(TestFunction);

	Sleep(50000);
	return 0;
}