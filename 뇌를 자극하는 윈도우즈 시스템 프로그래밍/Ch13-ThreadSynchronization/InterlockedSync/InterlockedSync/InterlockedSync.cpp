/*
* Windows System Programming - ������ ����ȭ ���(1)
* ���ϸ�: InterlockedSync.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-08
* ���� ���� �ۼ� ����:
* ���� ����: ������� ����ȭ ���(2) - ���Ͷ�(Interlock) �Լ� ��� ����ȭ ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

// ���� ������ ���. -> ������� ���� ����
LONG gTotalCount = 0;

void IncreaseCount()
{
	// gTotalCount++; // �Ӱ� ����(Critical Section)
	InterlockedIncrement(&gTotalCount); // ����� ���� 1 ������Ű�� ���Ͷ� �Լ�.
	// �̿ܿ��� �پ��� ���Ͷ� �Լ��� ����
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

	return 0;
}