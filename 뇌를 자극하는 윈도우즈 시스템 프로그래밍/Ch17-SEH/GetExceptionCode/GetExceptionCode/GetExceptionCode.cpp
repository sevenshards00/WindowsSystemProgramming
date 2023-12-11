/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: GetExceptionCode.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ���� ���� �Ǿ� �ִ� ������ ���� ��� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR argv[])
{
	int* p = NULL;
	int sel = 0;

	while (1)
	{
		_tprintf(TEXT("1 for Memory Access Exception\n"));
		_tprintf(TEXT("2 for Divide by 0 Exception\n"));
		_tprintf(TEXT("Select Exception Type [3 for exit]: "));

		_tscanf_s(TEXT("%d"), &sel);

		if (sel == 3)
			break;

		__try
		{
			if (sel == 1)
			{
				*p = 100; // ���� �߻� -> �޸� ���� ����
				_tprintf(TEXT("value: %d"), *p);
			}
			else // sel == 2
			{
				int n = 0;
				n = 7 / n; // ���� �߻� -> 0���� ������ ���
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			DWORD exptType = GetExceptionCode(); // ���� �߻� �ڵ带 �޾ƿ��� �Լ�(��ǻ� ��ũ��)

			switch (exptType)
			{
			case EXCEPTION_ACCESS_VIOLATION: // �޸� ���� ����
				_tprintf(TEXT("Memory Access Violated\n"));
				break;
			case EXCEPTION_INT_DIVIDE_BY_ZERO: // 0���� ������ ���
				_tprintf(TEXT("Divide by Zero\n"));
				break;
			}
		}
	}

	return 0;
}