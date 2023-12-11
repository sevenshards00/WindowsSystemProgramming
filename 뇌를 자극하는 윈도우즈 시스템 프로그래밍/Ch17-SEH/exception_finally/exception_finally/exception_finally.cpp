/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: exception_finally.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ���� �ڵ鷯�� ���� ���� ����
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR str[2];

	__try
	{
		_tcscpy(str, TEXT("abcdefghijklmnopqrstuvwxyz")); // ���� �߻� (�޸� ���� ����)
		_tprintf(TEXT("%s\n"), str);
	}
	// finally ����� ������ �߻��ص� ����ȴ�
	// ���������� ExitProcess�� ExitThread�� ANSI C�� exit �Լ��� ���� ���� ���� �߻��� ������� �ʴ´�.
	__finally
	{
		_tprintf(TEXT("__finally blocked\n"));
	}

	return 0;
}