/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: MBCS_WBCS2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS


// 사실 정의 안해도 됨
#define UNICODE
#define _UNICODE

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 마찬가지 이유로 문자열 리터럴은 현재 C++에서 안되는 문장.
	// MBCS라면 const char*, WBCS라면 const wchar_t*가 된다.
	// LPTSTR str1 = _T("MBCS or WBCS 1");
	LPCTSTR str1 = _T("MBCS or WBCS 1");
	TCHAR str2[] = _T("MBCS or WBCS 2");
	TCHAR str3[100];
	TCHAR str4[50];

	LPCTSTR pStr = str1;

	_tprintf(_T("string size: %d \n", sizeof(str2)));
	_tprintf(_T("string length: %d \n", sizeof(str2)));

	_fputts(_T("Input String 1: "), stdout);
	_tscanf(_T("%s"), str3);
	_fputts(_T("Input String 2: "), stdout);
	_tscanf(_T("%s"), str4);

	_tcscat(str3, str4);
	_tprintf(_T("String1 + String2: %s \n"), str3);

	return 0;
}