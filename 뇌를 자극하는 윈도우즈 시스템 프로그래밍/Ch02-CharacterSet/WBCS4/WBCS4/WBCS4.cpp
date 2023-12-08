/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: WBCS4.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#include <iostream>

// main이 아니라 wmain
// 전달되는 문자열을 유니코드 기반으로 구성하겠다는 의미
// char* argv[] -> wchar_t* argv[]로 변경
int wmain(int argc, wchar_t* argv[]) 
{
	// 1부터 시작하므로 실행파일 명은 제외
	for (int i = 1; i < argc; i++)
	{
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}

	return 0;
}