/*
* Windows System Programming - �������� ������ �Ҹ�
* ���ϸ�: CountThread.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-07
* ���� ���� �ۼ� ����:
* ���� ����: 1~10������ ���� 3���� ������� ������ �����ϴ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;
	
	DWORD numStart = *nPtr;
	DWORD numEnd = *(nPtr + 1);

	DWORD total = 0;
	for (DWORD i = numStart; i <= numEnd; i++)
		total += i;

	return total;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[3]; // �������� ID�� ���� ����
	HANDLE hThread[3]; // ������ �������� �ڵ��� �ޱ� ���� ����

	DWORD paramThread[] = { 1, 3, 4, 7, 8, 10 };
	DWORD total = 0;
	DWORD result = 0;

	// ������ ����
	hThread[0] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[0]),
			0,
			&dwThreadID[0]
		);

	hThread[1] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[2]),
			0,
			&dwThreadID[1]
		);

	hThread[2] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[4]),
			0,
			&dwThreadID[2]
		);

	// �� ������ �� �ϳ��� NULL�̴� -> �ڵ鰪�� ��ȯ���� ���� -> ���� ����
	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(TEXT("Thread creation fault!\n"));
		return -1;
	}

	// WaitForMultipleObjects -> WaitForSingleObject�� ������
	// n���� ���ҽ��� ������� Ŀ�� ������Ʈ�� Signaled ���°� �� ������ ��ٸ���
	WaitForMultipleObjects(
		3, // ������ Ŀ�� ������Ʈ�� ����� ��
		hThread, // Ŀ�� ������Ʈ�� �迭 ����
		TRUE, // ��� Ŀ�� ������Ʈ�� Signaled ���°� �� ������ ����Ѵ�
		INFINITE // ��� ��ٸ���
	);

	// �� �����忡�� ����� ���� ��ģ��.
	GetExitCodeThread(hThread[0], &result);
	total += result;

	GetExitCodeThread(hThread[1], &result);
	total += result;

	GetExitCodeThread(hThread[2], &result);
	total += result;

	_tprintf(TEXT("total (1~10): %d\n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	return 0;
}