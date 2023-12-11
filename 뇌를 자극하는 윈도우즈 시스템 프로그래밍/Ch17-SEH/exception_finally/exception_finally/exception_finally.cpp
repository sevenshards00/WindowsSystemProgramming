/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: exception_finally.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 종료 핸들러의 동작 원리 이해
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR str[2];

	__try
	{
		_tcscpy(str, TEXT("abcdefghijklmnopqrstuvwxyz")); // 예외 발생 (메모리 참조 오류)
		_tprintf(TEXT("%s\n"), str);
	}
	// finally 블록은 오류가 발생해도 실행된다
	// 예외적으로 ExitProcess나 ExitThread나 ANSI C의 exit 함수에 의한 강제 종료 발생시 실행되지 않는다.
	__finally
	{
		_tprintf(TEXT("__finally blocked\n"));
	}

	return 0;
}