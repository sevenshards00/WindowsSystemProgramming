/*
* Windows System Programming - ������ ����ȭ ���(1)
* ���ϸ�: MUTEX_WAIT_ABANDONED.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-09
* ���� ���� �ۼ� ����:
* ���� ����: Ŀ�θ�� ����ȭ ��� - ���ؽ� ����� WAIT_ABANDONED�� ���� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

unsigned int WINAPI IncreaseCountOne(LPVOID lpParam)
{
	// hThread1�� ���ؽ��� ȹ��.
	// Signaled ���¿��� Non-Signaled ���·� �ٲ��.
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;

	// ������ ReleaseMutex�� ���� �����Ƿ� ��� Signaled ���¸� ������ä ���ؽ��� ��ȯ���� �ʰ� ������� ����ȴ�.
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpParam)
{
	DWORD dwWaitResult = 0;
	// �׷��� �� ��° ������� ���ؽ��� ȹ���Ϸ��� �ϳ�, ȹ���� ���� ���ϴ� ��Ȳ.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	// ��������� WAIT_ABANDONED�� ������ �ǰ�, Windows �ü���� ��ȯ���� ���� ���ؽ��� ó���Ѵ�.
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		ReleaseMutex(hMutex);
		break;
	case WAIT_ABANDONED:
		_tprintf(TEXT("WAIT_ABANDONED\n"));
		break;
	}

	gTotalCount++;

	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadIDOne;
	DWORD dwThreadIDTwo;

	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(
		NULL,
		FALSE,
		NULL
	);

	if (hMutex == NULL) // ���ؽ� ������ ������ ���
	{
		_tprintf(TEXT("CreateMutex Error Occured: %d\n"), GetLastError());
		return -1;
	}

	// ������ ������ (������)
	hThreadOne = (HANDLE)_beginthreadex(
		NULL, // ����(���) ���� �Ӽ�
		0, // �������� ���� ������, 0�̸� �⺻ ũ��(1M)
		IncreaseCountOne, // �������� ������ �� �Լ�
		NULL, // �Լ��� ������ ���� ���
		0, // ������ ���� �� ���� ����, 0�� ��� ������ �Բ� �ٷ� ����
		(unsigned*)&dwThreadIDOne // �������� ID�� ������ �ּҰ�
	);

	hThreadTwo = (HANDLE)_beginthreadex(
		NULL, // ����(���) ���� �Ӽ�
		0, // �������� ���� ������
		IncreaseCountTwo, // �������� ������ �� �Լ�
		NULL, // �Լ��� ������ ���� ���
		CREATE_SUSPENDED, // ������ ���� �� ���� ����, CREATE_SUSPENDED�� ���� �� �ٷ� �������� ����(Blocked ����, Suspend Count 1)
		(unsigned*)&dwThreadIDTwo // �������� ID�� ������ �ּҰ�
	);

	Sleep(1000);
	ResumeThread(hThreadTwo); // hThreadTwo�� ���� ���·� ��ȯ (Blocked -> Ready, Suspend Count 0)

	// �����尡 �ٽ� ���ؽ��� ��� ����
	WaitForSingleObject(hThreadTwo, INFINITE);
	_tprintf(TEXT("Total Count: %d\n"), gTotalCount);

	// �����ߴ� Ŀ�� ������Ʈ�� �ڵ��� ��ȯ, Usage Count 1 ����
	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);
	return 0;
}