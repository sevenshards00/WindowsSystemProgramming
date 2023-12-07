/*
* Windows System Programming - �������� ������ �Ҹ�
* ���ϸ�: CountThreadMultiThread.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-07
* ���� ���� �ۼ� ����:
* ���� ����: ��Ƽ ������ ��ݿ� ������ ��Ÿ�� ���̺귯�� �Լ� ����� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

#define MAX_THREADS (1024*10)

// �����忡�� ������ �Լ�, �������� main�� ������ �� �Լ�
unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread num: %d\n"), threadNum);
		Sleep(5000);
	}

	return 0;
}

// �������� ������ ����� ��������
DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// ���� ������ �ִ� ������ ������ ����
	while (1)
	{
		hThread[cntOfThread] =
			(HANDLE)_beginthreadex(
				NULL, // ����Ʈ ����(���) �Ӽ� ����
				0, // ����Ʈ ���� ������(1M)
				ThreadProc, // ������ �Լ�
				(LPVOID)cntOfThread, // ������ �Լ��� ���� ����
				0, // ����Ʈ ���� flag ����
				(unsigned*) & dwThreadID[cntOfThread] // ������ ID�� ���޹ޱ� ���� ������ �ּҰ�
			);
		// ������ ���� Ȯ��
		if (hThread[cntOfThread] == NULL) // NULL�� ��� �����尡 �������� ���� ��
		{
			_tprintf(_T("MAXIMUM Thread Number: %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}

	// ������ �������� ������ŭ ���ҽ� ����, Usage Count 1�� ����
	for (DWORD i = 0; i < cntOfThread; i++)
		CloseHandle(hThread[i]);
	return 0;
}