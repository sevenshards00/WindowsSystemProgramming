/*
* Windows System Programming - ������ ����ȭ ���(2)
* ���ϸ�: Timer.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-08
* ���� ���� �ۼ� ����:
* ���� ����: Ÿ�̸� ��� ����ȭ ��� - Timer ��� ����ȭ ����
* ���� ���� ����:
*/

// SetWaitableTimer �Լ��� ȣ���ϱ� ���� ��ũ��
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(
		NULL, // ����(���) �Ӽ�
		FALSE, // auto-reset ���� ����, TRUE�� �ϸ� manual-reset
		NULL // �̸��� �ٿ��� ��쿡 ����ϴ� ����
	);

	if (!hTimer)
	{
		_tprintf(TEXT("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return -1;
	}

	_tprintf(TEXT("Waiting for 10 seconds...\n"));

	SetWaitableTimer(
		hTimer, // �˶��� ������ Ÿ�̸��� �ڵ�
		&liDueTime, // �˶��� �︱ �ð�
		0, // Ÿ�̸Ӹ� �ֱ������� �︮�� ���� ����, 0�̸� �ֱ������� ���� ����
		NULL, // �Ϸ� ��ƾ Ÿ�̸�, ���Ŀ� �ٷ�
		NULL, // �Ϸ� ��ƾ Ÿ�̸�, ���Ŀ� �ٷ�
		FALSE // Resume ����, ���� ������ ���� �ִ� ����. �⺻�����δ� FALSE
	);

	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(TEXT("Timer was signaled\n"));
	MessageBeep(MB_ICONEXCLAMATION);

	return 0;
}