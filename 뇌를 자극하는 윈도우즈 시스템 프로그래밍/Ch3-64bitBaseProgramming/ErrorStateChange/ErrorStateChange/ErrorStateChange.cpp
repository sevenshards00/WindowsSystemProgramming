/*
* Windows System Programming - 64��Ʈ ��� ���α׷���
* ���ϸ�: ErrorStateChange.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-02
* ���� ���� �ۼ� ����:
* ���� ����: GetLastError �Լ� ��� ����(2)
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain()
{
	// ������ ����
	HANDLE hFile = CreateFile(_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("Error code: %d\n"), GetLastError());
	
	// ������ ���� ����
	hFile = CreateFile(_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("Error code: %d\n"), GetLastError());
	return 0;
}