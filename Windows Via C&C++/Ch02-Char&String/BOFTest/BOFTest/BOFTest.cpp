/*
* Windows VIA C/C++ 5th Edition - 문자와 문자열로 작업하기
* 파일명: BOFTest.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2024-01-26
* 이전 버전 작성 일자:
* 버전 내용: 기존 C 런타임 라이브러리를 대체하는 안전 문자열 함수 사용 예시
* 이전 버전 내용:
*/

#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR *argv[])
{
	TCHAR szBefore[5] = { TEXT('A'), TEXT('A'), TEXT('A'), TEXT('A'), '\0' };
	TCHAR szBuffer[10] = { TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), TEXT('-'), '\0' };
	TCHAR szAfter[5] = { TEXT('B'), TEXT('B'), TEXT('B'), TEXT('B'), '\0' };

	// 디스어셈블리를 통해서 확인할 수 있음.
	// vs2022 기준 C/C++ 컴파일러에서는 디버그 모드에서 0xfd가 아니라 0xfe로 채워진다.
	errno_t result = _tcscpy_s(szBuffer, _countof(szBuffer), TEXT("0123456789"));
}