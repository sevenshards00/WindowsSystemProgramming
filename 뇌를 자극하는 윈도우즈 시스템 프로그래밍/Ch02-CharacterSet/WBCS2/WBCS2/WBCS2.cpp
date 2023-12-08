/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: WBCS2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#include <iostream>
#include <cstring>

int main()
{
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	wprintf(L"Array Size: %d\n", size);
	wprintf(L"String Length: %d\n", len);

	return 0;
}