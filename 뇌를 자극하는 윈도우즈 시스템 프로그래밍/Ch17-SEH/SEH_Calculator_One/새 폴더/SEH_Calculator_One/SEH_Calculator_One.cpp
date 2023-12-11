/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: SEH_Calculator_One.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ���� ���� EXCEPTION_EXECUTE_HANDLER Ȱ�� ����
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum{DIV=1, MUL, ADD, SUB, QUIT};

DWORD ShowMenu();
BOOL Calculator();

int _tmain(int argc, TCHAR* argv[])
{
	BOOL state;

	do {
		state = Calculator();
	} while (state == TRUE);

	return 0;
}

DWORD ShowMenu()
{
	DWORD sel;
	_fputts(TEXT("-----Menu-----\n"), stdout);
	_fputts(TEXT("Num 1: Divide\n"), stdout);
	_fputts(TEXT("Num 2: Multiply\n"), stdout);
	_fputts(TEXT("Num 3: Add\n"), stdout);
	_fputts(TEXT("Num 4: Subtract\n"), stdout);
	_fputts(TEXT("Num 5: Quit\n"), stdout);
	_fputts(TEXT("Choose One:\n"), stdout);
	_tscanf_s(TEXT("%d"), &sel);

	return sel;
}

BOOL Calculator()
{
	DWORD sel;
	int num1, num2, result;

	sel = ShowMenu();
	if (sel == QUIT)
		return FALSE;

	_fputts(TEXT("Input num1, num2: "), stdout);
	_tscanf_s(TEXT("%d %d"), &num1, &num2);

	__try
	{
		switch (sel)
		{
		case DIV:
			result = num1 / num2; // 0���� ���� ��� DIV/0 ���ܰ� �߻�
			_tprintf(TEXT("%d / %d = %d\n"), num1, num2, result); // ���� �߻� �� �� �κ��� ������� ����
			break;
		case MUL:
			result = num1 * num2;
			_tprintf(TEXT("%d * %d = %d\n"), num1, num2, result);
			break;
		case ADD:
			result = num1 + num2;
			_tprintf(TEXT("%d + %d = %d\n"), num1, num2, result);
			break;
		case SUB:
			result = num1 - num2;
			_tprintf(TEXT("%d - %d = %d\n"), num1, num2, result);
			break;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_fputts(TEXT("Wrong Number Inserted. Try Again!\n"), stdout);
	}

	return TRUE;
}