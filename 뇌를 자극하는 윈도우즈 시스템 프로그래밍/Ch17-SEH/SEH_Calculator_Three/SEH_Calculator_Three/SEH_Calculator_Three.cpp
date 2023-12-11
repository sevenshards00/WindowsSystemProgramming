/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: SEH_Calculator_Three.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: �ڵ鷯�� ��ø ����(���� �ڵ鷯, ���� �ڵ鷯)
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, SUB, QUIT };

DWORD ShowMenu();
BOOL Calculator();

void Divide(int, int);
void Multiply(int, int);
void Add(int, int);
void Subtract(int, int);

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

	__try // ���� �ڵ鷯�� try ���
	{
		__try // ���� �ڵ鷯�� try ��� (��ø)
		{
			switch (sel)
			{
			case DIV:
				// ���⼭ �Լ��� ȣ��, ���ܰ� �߻��� ��� ȣ���ߴ� �Լ��� ����
				// try�� ������ �κ��� ������ �����ϰ� ����ó��(__except �������)
				Divide(num1, num2);
				break;
			case MUL:
				Multiply(num1, num2);
				break;
			case ADD:
				Add(num1, num2);
				break;
			case SUB:
				Subtract(num1, num2);
				break;
			}
		}
		// ���� �ڵ鷯 (try�� ����� �����ϰ� ���������� �Ǹ� ������ ����)
		// ���� �� �κ��� finally�� ���������� �ʾҴٸ� ���ܰ� �߻��ϴ� ��� ���� �ڵ鷯 �κ��� �� ���� ����.
		__finally 
		{
			_fputts(TEXT("End Operation!\n\n"), stdout);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) // ���� �ڵ鷯 (���ܰ� �߻��� ��쿡 ����)
	{
		_fputts(TEXT("Wrong Number Inserted. Try Again!\n"), stdout);
	}
	return TRUE;
}

void Divide(int a, int b)
{
	_tprintf(TEXT("%d / %d = %d\n"), a, b, a / b); // ���ܴ� ���⼭ �߻�, ������ ó���� ���⼭ ���� �ʴ´�.
}

void Multiply(int a, int b)
{
	_tprintf(TEXT("%d * %d = %d\n"), a, b, a * b);
}

void Add(int a, int b)
{
	_tprintf(TEXT("%d + %d = %d\n"), a, b, a + b);
}

void Subtract(int a, int b)
{
	_tprintf(TEXT("%d - %d = %d\n"), a, b, a - b);
}