/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: TerminationHandlerEx2.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ���� �ڵ鷯�� Ȱ�� ����(2) - �������� ����ȭ(���ؽ��� ���� �� ��ȯ)
* ���� ���� ����:
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

// ���� ������ ���. -> ������� ���� ����
LONG gTotalCount = 0;

// Mutex ������Ʈ�� ����
// Ŀ�ο� ���� �����Ǵ� ������Ʈ�̹Ƿ� HANDLE���� ������ �ȴ�.
HANDLE hMutex;

void IncreaseCount()
{
	__try
	{
		// Signaled -> Non-Signaled
		WaitForSingleObject(hMutex, INFINITE); // EnterCriticalSection(&hCriticalSection);
		gTotalCount++; // �Ӱ� ����(Critical Section)

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
	// ���ؽ��� ����
	hMutex = CreateMutex(
		NULL, // ����Ʈ ���� �Ӽ� (���)
		FALSE, // ������ ������ �� �ֵ��� �� -> ������ / TRUE�� ������ ��� ���ؽ��� �����ϴ� �����尡 �켱������ �����ϰ� �ȴ�
		NULL // �̸��� ������ ����
	);

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(
			NULL, // ����(���) �Ӽ�, ���ϹǷ� NULL
			0, // �������� ���� ũ��, 0���� �ָ� ����Ʈ��(1M)
			ThreadProc, // �������� main�� �� �Լ�
			NULL, // �����忡 ������ ����, �����Ƿ� NULL
			CREATE_SUSPENDED, // ���� �� ��� ���� ���θ� ���ڷ� ����, CREATE_SUSPENDED�� ���������Ƿ� �ٷ� �������� �ʴ´�
			(unsigned*)&dwThreadID[i] // �������� ID���� ������ �ּҰ��� ���ڷ� ����
		);

		// �������� ������ �������� ���
		if (hThread[i] == NULL)
		{
			_tprintf(TEXT("Thread Creation Fault\n"));
			return -1;
		}
	}

	// ��� �����带 ���� ���·� �ٲٴ� �κ�
	// ������ ���� ���� �ð��� �ɸ��� �۾��̹Ƿ� ���� ������ ���ؼ� SUSPENDED�� ���� 
	// ResumeThread �Լ��� ���� ��� �����带 ���� ���·� �ٲ۴�. 
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}

	// ��� �������� �۾��� �����⸦ ��ٸ��� �κ�
	WaitForMultipleObjects(
		NUM_OF_GATE, // ������ ������Ʈ�� ����
		hThread, // ������ ������Ʈ�� ��� �ִ� �迭�� �ּ�
		TRUE, // ��� ������Ʈ�� Signaled ���°� �Ǹ� ���� ��ȯ
		INFINITE // ���������� ���
	);

	_tprintf(TEXT("total count: %d\n"), gTotalCount);

	// ������ �������� Ŀ�� ������Ʈ Usage Count�� ���� (���ҽ� ���� ��û)
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
		CloseHandle(hThread[i]);

	// ���ؽ��� Ŀ�� ������Ʈ�̹Ƿ� �ڵ��� ��ȯ �� Usage Count 1 ����
	CloseHandle(hMutex); // DeleteCriticalSection(&hCriticalSection);

	return 0;
}