/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: WBCS1.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#include <iostream>
#include <cstring>
using std::cout;


int main()
{
	wchar_t str_w[] = L"ABC"; // WBCS (Wide Byte Character Set)
	char str_s[] = "ABC"; // SBCS (Single Byte Character Set)
	int size_w = sizeof(str_w);
	int size_s = sizeof(str_s);
	int len_w = wcslen(str_w); // strlen이 아니라 wcslen
	int len_s = strlen(str_s);

	cout << "WBCS 배열의 크기: " << size_w << '\n';
	cout << "WBCS 문자열 길이: " << len_w << '\n';
	cout << "SBCS 배열의 크기: " << size_s << '\n';
	cout << "WBCS 문자열 길이: " << len_s << '\n';

	return 0;
}