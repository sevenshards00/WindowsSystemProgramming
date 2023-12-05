/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: EnvParent.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: ���μ��� ȯ�溯���� �̿��ϴ� ���� - �ڽ� ���μ���
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR value[BUF_SIZE];

	if (GetEnvironmentVariable(_T("Good"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Good"), value);
	if (GetEnvironmentVariable(_T("Hey"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Hey"), value);
	if (GetEnvironmentVariable(_T("Big"), value, BUF_SIZE) > 0)
		_tprintf(_T("%s = %s\n"), _T("Big"), value);

	Sleep(10000);

	return 0;
}