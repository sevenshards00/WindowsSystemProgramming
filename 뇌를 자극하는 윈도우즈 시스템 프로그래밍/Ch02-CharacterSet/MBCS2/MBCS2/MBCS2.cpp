/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: MBCS2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-01
* 이전 버전 작성 일자:
* 버전 내용: MBCS와 WBCS의 기본적인 이해
* 이전 버전 내용:
*/

#include <iostream>
using std::cout;


int main()
{
	char str[] = "한글입니다";
	int i;

	for (i = 0; i < 5; i++)
		fputc(str[i], stdout);
		// c++로 쓴다면
		// cout << str[i];

	fputs("\n", stdout);

	for (i = 0; i < 10; i++)
		fputc(str[i], stdout);
		// c++로 쓴다면
		// cout << str[i];

	fputs("\n", stdout);
	return 0;
}