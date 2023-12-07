/*
* Windows System Programming - �������� ������ �Ҹ�
* ���ϸ�: SuspendCount.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-07
* ���� ���� �ۼ� ����:
* ���� ����: �������� ���� ���� Ȯ�� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	while (1)
	{
		_tprintf(TEXT("Running State!\n"));
		Sleep(10000);
	}

	return 0;
}


int main(int argc, TCHAR* argv[])
{
	DWORD dwThreadID;
	HANDLE hThread;
	DWORD susCnt; // suspend count�� Ȯ���ϱ� ���� ����

	hThread = (HANDLE)_beginthreadex(
		NULL,
		0,
		ThreadProc,
		NULL,
		CREATE_SUSPENDED, // ������ ���� �� Blocked ���·� ����, Suspend Count�� 1
		(unsigned*)&dwThreadID
	);

	// ������ ���� Ȯ��
	if (hThread == NULL)
		_tprintf(TEXT("Thread creation failed!\n"));

	// Tm
	susCnt = ResumeThread(hThread); // �����带 �ٽ� Ready ���·�, Suspend Count�� 0
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread); // �����带 �ٽ� Blocked ���·�, Suspend Count�� 1
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread); // �����带 Blocked ���¿��� Suspend Count�� �߰�, Suspend Count�� 2
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread); // Blocked ������ �������� Suspend Count�� 1����, Suspend Count�� 1
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread); // Blocked ������ �������� Suspend Count�� 1����, Suspend Count�� 0�� �ǹǷ� ������� �ٽ� Ready ����
	_tprintf(TEXT("suspend count: %d\n"), susCnt);
	Sleep(10000);

	// ���μ����� ����Ǵ� ���� ���� ���� �������� ������ Ȯ���Ѵ�
	WaitForSingleObject(hThread, INFINITE);

	return 0;
}