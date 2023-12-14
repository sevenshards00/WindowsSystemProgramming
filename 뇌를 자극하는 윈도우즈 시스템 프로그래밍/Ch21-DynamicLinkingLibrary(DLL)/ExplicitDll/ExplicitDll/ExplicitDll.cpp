/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: ExplicitDll.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 명시적 DLL 활용 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "SwapDll.h"

typedef void (*SWAP_FUNC)(int*, int*);

int _tmain(int argc, TCHAR* argv[])
{
	HMODULE hinstLib;
	SWAP_FUNC SwapFunction;

	hinstLib = LoadLibrary(TEXT("SwapDll"));
	if (hinstLib == NULL)
	{
		_tprintf(TEXT("LoadLibrary Failed\n"));
		return -1;
	}

	SwapFunction = (SWAP_FUNC)GetProcAddress(hinstLib, "swap");
	if (SwapFunction == NULL)
	{
		_tprintf(TEXT("GetProcAddress failed\n"));
		return -1;
	}

	int a = 10;
	int b = 20;
	_tprintf(TEXT("Before: %d, %d \n"), a, b);

	SwapFunction(&a, &b);
	_tprintf(TEXT("After: %d, %d\n"), a, b);

	BOOL isSuccess = FreeLibrary(hinstLib);
	if (isSuccess == NULL)
	{
		_tprintf(TEXT("FreeLibrary failed\n"));
		return -1;
	}

	return 0;
}