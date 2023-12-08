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

// warning 메시지가 나온다
// 기본적으로 .NET 컴파일러에서는 해당 매크로를 기본으로 삽입해주기 때문.
#define UNICODE
#define _UNICODE

// MBCS 기반으로 컴파일하겠다면 아래의 지시자로 정의된 매크로를 무효화하면 된다.
// #undef UNICODE
// #undef _UNICODE

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