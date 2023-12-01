/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: MBCS_WBCS1.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#define UNICODE
#define _UNICODE

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int wmain()
{
	TCHAR str[] = _T("1234567");
	int size = sizeof(str);
	printf("string length: %d\n", size);

	return 0;
}