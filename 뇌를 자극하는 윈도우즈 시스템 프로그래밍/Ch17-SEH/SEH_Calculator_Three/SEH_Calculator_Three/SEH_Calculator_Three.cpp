/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: SEH_Calculator_Three.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 핸들러의 중첩 예제(종료 핸들러, 예외 핸들러)
* 이전 버전 내용:
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

	__try // 예외 핸들러의 try 블록
	{
		__try // 종료 핸들러의 try 블록 (중첩)
		{
			switch (sel)
			{
			case DIV:
				// 여기서 함수를 호출, 예외가 발생할 경우 호출했던 함수로 복귀
				// try의 나머지 부분의 실행을 생략하고 예외처리(__except 블록으로)
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
		// 종료 핸들러 (try를 블록을 실행하고 빠져나오게 되면 무조건 실행)
		// 만약 이 부분이 finally로 감싸져있지 않았다면 예외가 발생하는 경우 종료 핸들러 부분은 볼 수가 없다.
		__finally 
		{
			_fputts(TEXT("End Operation!\n\n"), stdout);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) // 예외 핸들러 (예외가 발생할 경우에 실행)
	{
		_fputts(TEXT("Wrong Number Inserted. Try Again!\n"), stdout);
	}
	return TRUE;
}

void Divide(int a, int b)
{
	_tprintf(TEXT("%d / %d = %d\n"), a, b, a / b); // 예외는 여기서 발생, 하지만 처리는 여기서 하지 않는다.
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