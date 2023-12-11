/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: SEH_Calculator_ContinueExecution.cpp
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

enum { DIV = 1, MUL, ADD, SUB, QUIT };

DWORD ShowMenu();
BOOL Calculator();
DWORD FilterFunction(DWORD exptType);

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

int num1, num2, result;

BOOL Calculator()
{
	DWORD sel;
	

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
	// ���� ���� �κп� �Լ� ȣ�⹮�� �͵� ����� ����.
	// ��, ��ȯ���� �������� ǥ�����̾�� �Ѵ�.
	__except (FilterFunction(GetExceptionCode()))
	{
		_fputts(TEXT("Wrong Number Inserted. Try Again!\n"), stdout);
	}

	return TRUE;
}

DWORD FilterFunction(DWORD exptType)
{
	switch (exptType)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		_tprintf(TEXT("Access violation\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		_tprintf(TEXT("Wrong Number Inserted.\n"));
		_tprintf(TEXT("Input Second Number Again:"));
		_tscanf_s(TEXT("%d"), &num2);
		return EXCEPTION_CONTINUE_EXECUTION; // ���ڸ� �ٽ� �Է� �޾Ƽ� ���ܰ� �߻��� �������� �̾ ���� 
	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}