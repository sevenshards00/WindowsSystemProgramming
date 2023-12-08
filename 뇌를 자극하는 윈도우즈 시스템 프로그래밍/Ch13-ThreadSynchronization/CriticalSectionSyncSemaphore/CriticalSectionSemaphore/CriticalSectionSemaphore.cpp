/*
* Windows System Programming - ������ ����ȭ ���(1)
* ���ϸ�: CriticalSectionSyncSemaphore.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-08
* ���� ���� �ۼ� ����:
* ���� ����: Ŀ�θ�� ����ȭ ���(2) - Semaphore ��� ����ȭ ����
* ���� ���� ����:
*/

/* '������'��� ���Կ� ���� �ùķ��̼��� �Ѵٰ� ���� 
* �ùķ��̼� ���� ���:
* 1. ���̺��� �� 10��, ���ÿ� �� 10���� ���� ���� �� ����
* 2. ���� �ð��� �Ļ縦 �Ϸ� �� ���� 50������ �����
* 3. ���� �Ļ� �ð��� 10~30�� ����
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>
#include <time.h>

#define NUM_OF_CUSTOMER 50 // �ִ� �� ��
#define RANGE_MIN 10 // �ּ� �Ļ� �ð� ����
#define RANGE_MAX (30 - RANGE_MIN) // �ִ� �Ļ� �ð� ����
#define TABLE_CNT 10 // ���̺� ��

// �������� ����
HANDLE hSemaphore;
// ������ ���� ����� �Ļ� �ð�(10~30��)�� �����ϴ� �迭
DWORD randTimeArr[50];
// ���̺� ���� ��ȭ Ȯ�ο� ����
DWORD leftTblCnt = TABLE_CNT;
// �� �Ļ� �ð�
DWORD total_Time = 0;

// �Ļ縦 �ϴ� ��Ȳ�� �Լ��� ����
void TakeMeal(DWORD time)
{
	// �Ļ縦 �ϱ� ���� �մ��� ������ ��Ȳ.
	// ���̺� == ��������, �մ� == ������
	// Count�� 0�̸� Non-Signaled, Count�� 1�̻��̸� Signaled
	WaitForSingleObject(hSemaphore, INFINITE);
	_tprintf(TEXT("Enter Customer: %d \n"), GetCurrentThreadId());
	leftTblCnt--;
	_tprintf(TEXT("Left Table Count: %d\n\n"), leftTblCnt);
	

	// �Ļ� ��
	_tprintf(TEXT("Cumstomer %d having lunch\n"), GetCurrentThreadId());
	Sleep(1000 * time);
	total_Time += time;

	// �Ļ縦 ��ġ�� ����
	// �� ��° ���ڴ� ���������� ī��Ʈ�� �󸶳� ������ų ���ΰ��� ���ڷ� ����
	// ��������δ� 1�� ���°� �ٹݻ���
	// �ִ� ī��Ʈ�� �Ѵ� ���� ������ų ��쿡�� ���� ������� �ʰ� FALSE�� ��ȯ
	ReleaseSemaphore(hSemaphore, 1, NULL);
	leftTblCnt++;
	_tprintf(TEXT("Out Customer: %d / Time spent: %d  \n"), GetCurrentThreadId(), time);
	_tprintf(TEXT("Left Table Count: %d\n\n"), leftTblCnt);
}

// �������� main�� �� �Լ�
unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	TakeMeal((DWORD)lpParam);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[NUM_OF_CUSTOMER]; // �������� ID�� ���� ����
	HANDLE hThread[NUM_OF_CUSTOMER]; // ������ ������Ʈ

	// ���� ������ ���� �ð��� seed�� ����
	// srand�� ���� ������ ����� seed�� �����Ѵ�.
	srand((unsigned)time(NULL));

	// �����忡 ������ ������ �� 50�� ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		// ���� ������ ���ؼ� ������ �����Ͽ� �� �κ��� �߰��� ����
		// rand �Լ��� 0���� 0x7fff(32767)������ ������ ���������� ��ȯ�Ѵ�.
		// �׷��� RAND_MAX�� ���� 32767�� ��.
		// ���� �ش� ���� ������ 0~99������ ������ ���ϰ� �ʹٸ� 100�� �������� ���ϸ� �ȴ�. -> rand() % 100
		// rand() / RAND_MAX �� 0�� 1�� ���� �� �ִ� ����.
		// ���⼭ �Ǽ��������� �� ��ȯ�� ���� 0.0 ~ 1.0 ������ ���� ������ �ȴ�.
		// �Ʒ��� ���� �ؼ��ϸ� (0.0 ~ 1.0 �� �ϳ�) * 20 + 10�� �ȴ�.
		// �׷��� �����Ǵ� ������ 10~30 ���̰� �ȴ�.
		randTimeArr[i] = (DWORD)(((double)rand() / (double)RAND_MAX) * RANGE_MAX + RANGE_MIN);

	// �������� ����
	hSemaphore = CreateSemaphore(
		NULL, // ����(���) �Ӽ� ���� -> ������� �ʴ´�
		TABLE_CNT, // �������� Count �ʱⰪ ����
		TABLE_CNT, // �������� Count �ִ밪 ����
		NULL // ���������� �̸� ����, ���ٸ� NULL
	);

	// �������� ������ �����ߴٸ�
	if (hSemaphore == NULL)
		_tprintf(TEXT("Create Semaphore Error: %d\n"), GetLastError()); // �����ڵ带 ���

	// Customer�� �� ������ ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(
			NULL, // ����(���) �Ӽ�, ��� ���ϹǷ� NULL
			0, // �������� ���� ũ��, 0���� �����Ƿ� ����Ʈ(1M)
			ThreadProc, // �������� main�� �� �Լ�
			(void*)randTimeArr[i], // �����忡 ������ ����. ���� ���� ���������� void*�̹Ƿ� �� ��ȯ�Ͽ� ����
			CREATE_SUSPENDED, // ������ ���� �� ���� ���θ� ����, �ٷ� �������� ����
			(unsigned*)&dwThreadID[i] // �������� ID���� ������ �ּҰ��� ���ڷ� ����
		);

		// ������ ������ �����ߴٸ�
		if (hThread[i] == NULL)
		{
			_tprintf(TEXT("Thread Creation Failed\n"));
			return -1;
		}
	}

	// ������ ������ �Ϸ�Ǹ� ���������� ������ ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		ResumeThread(hThread[i]);

	// ��� �����尡 Signaled�� �� ������(�۾��� ���� ������) ���ŷ
	WaitForMultipleObjects(
		NUM_OF_CUSTOMER, // ������ ������Ʈ�� ��
		hThread, // ������ ������Ʈ�� ��� �ִ� �迭
		TRUE, // ��� ������Ʈ�� Signaled ���°� �Ǹ� ���� ��ȯ, �ϳ��� Signaled�� �Ǽ� ��ȯ�� ���Ѵٸ� FALSE
		INFINITE // ������ ���
	);

	_tprintf(TEXT("Estimated time to complete meal serving: %d\n"), total_Time);
	_tprintf(TEXT("-----END-----\n"));

	// �������� �ڵ��� ��ȯ�ϴ� ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMER; i++)
		CloseHandle(hThread[i]);

	// ���������� �ڵ��� ��ȯ
	CloseHandle(hSemaphore);
	return 0;
}