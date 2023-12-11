/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: __try__finally.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 기본적인 종료 핸들러 예제
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	int a, b;
	// __try ~ __finally (둘이 하나를 이룬다)
	// try 블록
	// 예외발생 가능 구역 + 예외처리 이후 실행위치(얼마나 건너뛸 것인가)를 고려
	// try 블록에서 빠져나오게 되는 대표적인 상황 = return, continue, break, goto, "예외상황"
	__try
	{
		_tprintf(TEXT("Input Num to Divide [ a / b ]: "));
		_tscanf(TEXT("%d / %d"), &a, &b);

		if (b == 0)
			return -1;
	}
	// finally 블록
	// try 블록을 한 줄이라도 실행하게 되면 반드시 finally 블록을 실행
	// finally 블록이 실행될 때 return문에 의해 반환되는 값은 컴파일러가 만드는 임시변수에 저장
	// 그리고 finally 블록을 실행하고 난 뒤에 return이 수행된다
	__finally
	{
		_tprintf(TEXT("__finally blocked\n"));
	}

	_tprintf(TEXT("result: %d\n"), a / b);

	return 0;
}