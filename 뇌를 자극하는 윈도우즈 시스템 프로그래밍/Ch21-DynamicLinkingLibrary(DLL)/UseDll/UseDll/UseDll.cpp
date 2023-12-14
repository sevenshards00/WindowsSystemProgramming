/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: UseDll.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-15
* 이전 버전 작성 일자:
* 버전 내용: DLL 활용 예제 - 계산기
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "Calculator.h"

#pragma comment(lib, "Calculator.lib")

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(TEXT("result Add: %d \n"), Add(5, 3));
	_tprintf(TEXT("result Min: %d \n"), Min(5, 3));
	_tprintf(TEXT("result Mul: %e \n"), Mul(5.0, 3.0));
	_tprintf(TEXT("result Div: %e \n"), Div(5.0, 3.0));

	return 0;
}