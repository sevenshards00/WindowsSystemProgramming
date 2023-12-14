/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: MemoryMappedFileSort.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 정적 라이브러리 기본 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "Swap.h"

int _tmain(int argc, TCHAR* argv[])
{
	int a = 10;
	int b = 20;
	_tprintf(TEXT("Before: %d, %d \n"), a, b);

	swap(&a, &b);

	_tprintf(TEXT("After: %d, %d\n"), a, b);

	return 0;
}