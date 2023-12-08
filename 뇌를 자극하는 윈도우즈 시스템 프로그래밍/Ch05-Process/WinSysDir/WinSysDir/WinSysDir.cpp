/*
* Windows System Programming - ���μ��� ���� ����
* ���ϸ�: WinSysDir.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-03
* ���� ���� �ۼ� ����:
* ���� ����: �ý��� ���͸��� Windows ���͸� Ȯ�� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR sysDir[DIR_LEN];
	TCHAR winDir[DIR_LEN];

	// �ý��� ���͸� ���� ����
	GetSystemDirectory(sysDir, DIR_LEN);

	// Windows ���͸� ���� ����
	GetWindowsDirectory(winDir, DIR_LEN);

	// ���͸� ���� ���
	_tprintf(_T("System Dir: %s\n"), sysDir);
	_tprintf(_T("Windows Dir: %s\n"), winDir);

	return 0;
}