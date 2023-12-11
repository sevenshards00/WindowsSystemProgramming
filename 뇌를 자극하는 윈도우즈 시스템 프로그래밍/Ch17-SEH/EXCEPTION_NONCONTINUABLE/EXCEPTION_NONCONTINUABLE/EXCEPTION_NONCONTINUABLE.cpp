/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: EXCEPTION_NONCONTINUABLE.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: RaiseException �Լ��� �� ��° ���ڷ� EXCEPTION_NONCONTINUABLE�� ����� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// ������ ���� ��Ʈ�� ������ ���ܸ� �����ϴ� �ͺ��� �̿� ���� ����� �������̴�.
#define TEST_EXCEPTION ((DWORD) 0xE0000008L)

void SoftwareException();

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	__try
	{
		RaiseException(
			TEST_EXCEPTION, // �߻� ��ų ������ ����
			//0,
			EXCEPTION_NONCONTINUABLE, // �̰� ���ڷ� ������ ��� ���� ������ EXCEPTION_CONTINUE_EXECUTION�� �������� �ʴ´�.
			NULL, // �߰� ������ ����, ���ٸ� NULL
			NULL // �߰� ������ �����ϱ� ���� ����, ���ٸ� NULL
		);
		_tprintf(TEXT("Working!\n"));
	}
	__except (EXCEPTION_CONTINUE_EXECUTION) // ���� �߻� ���Ŀ��� �̾ �����ϴ� ���� ����
	{
		DWORD exptType = GetExceptionCode();
		if (exptType == TEST_EXCEPTION)
			_tprintf(TEXT("TEST EXCEPTION Occured\n"));
	}
}