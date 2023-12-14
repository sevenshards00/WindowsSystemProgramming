/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: Calculator.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-15
* 이전 버전 작성 일자:
* 버전 내용: DLL 활용 예제 - 계산기
* 이전 버전 내용:
*/
#include "pch.h"
#define _COMPLING_DLL_CALCULATOR
#include "Calculator.h"


LIBSPEC int Add(int a, int b)
{
	return a + b;
}

LIBSPEC int Min(int a, int b)
{
	return a - b;
}

LIBSPEC double Div(double a, double b)
{
	return a / b;
}

LIBSPEC double Mul(double a, double b)
{
	return a * b;
}