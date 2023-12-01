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

#include <stdio.h>
#include <windows.h>

int wmain(int argc, wchar_t* argv[])
{
	// 예전에 쓰인 책이라 현재의 C++에서 아래의 코드는 불가능
	// 
	// LPSTR str1 = "SBCS Style String 1";
	// LPWSTR str2 = L"WBCS Styple String 1";
	// 
	// 현재 C++은 문자열 리터럴을 char*가 아닌 const char*로 처리하기 때문
	LPCSTR str1 = "SBCS Style String 1";
	LPCWSTR str2 = L"WBCS Styple String 1";

	CHAR arr1[] = "SBCS Style String 2";
	WCHAR arr2[] = L"WBCS Style String 2";

	LPCSTR cStr = arr1;
	LPCWSTR wStr = arr2;

	printf("%s\n", str1);
	printf("%s\n", arr1);

	wprintf(L"%s\n", str2);
	wprintf(L"%s\n", arr2);



	return 0;
}