/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: SEH_Calculator_ContinueExecution.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 예외 필터 EXCEPTION_EXECUTE_HANDLER 활용 예제
* 이전 버전 내용:
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
			result = num1 / num2; // 0으로 나눌 경우 DIV/0 예외가 발생
			_tprintf(TEXT("%d / %d = %d\n"), num1, num2, result); // 예외 발생 시 이 부분은 실행되지 않음
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
	// 예외 필터 부분에 함수 호출문이 와도 상관이 없다.
	// 단, 반환값은 예외필터 표현식이어야 한다.
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
		return EXCEPTION_CONTINUE_EXECUTION; // 숫자만 다시 입력 받아서 예외가 발생한 지점에서 이어서 실행 
	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}