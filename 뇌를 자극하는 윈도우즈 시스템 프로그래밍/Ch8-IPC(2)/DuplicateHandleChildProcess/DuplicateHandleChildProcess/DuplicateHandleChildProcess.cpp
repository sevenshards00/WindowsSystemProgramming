/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: DuplicateHandleChildProcess.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: DuplicateHandle �Լ� ��� ���� - �ڽ� ���μ���
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hParent = (HANDLE)_ttoi(argv[1]);
	DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

	_tprintf(_T("[Child Process]\n"));

	if (isSuccess == WAIT_FAILED)
	{
		_tprintf(_T("WAIT_FAILED returned!\n"));
		Sleep(10000);
		return -1;
	}
	else
	{
		_tprintf(_T("General Lee said, \"Don't inform "));
		_tprintf(_T("the enemy my death\""));
	}

	Sleep(10000);
	return 0;
}