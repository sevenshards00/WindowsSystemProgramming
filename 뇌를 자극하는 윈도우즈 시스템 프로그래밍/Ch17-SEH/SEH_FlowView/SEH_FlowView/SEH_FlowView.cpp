/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: SEH_FlowView.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ������ �ڵ鷯 �⺻ ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(TEXT("Start!\n"));

	int* p = NULL;

	__try
	{
		*p = 100; // ���� �߻� (�޸� ���� ����)
		_tprintf(TEXT("value: %d\n"), *p); // ������� �ʴ´�
	}
	// ���� �ڵ鷯 (__except)
	// ���� ���� EXCEPTION_EXECUTE_HANDLER
	// ���� �߻� ���� __try����� ���� �κ��� �ǳʶٰ� __except ����� �����ϰ� ���� �� ���ĸ� ����
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(TEXT("Exception Occurred!\n"));
	}

	_tprintf(TEXT("End!\n"));

	return 0;
}