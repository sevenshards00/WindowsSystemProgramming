/*
* Windows System Programming - 문자 셋(Character Set)
* 파일명: MBCS1.cpp
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
	char str[] = "ABC한글";
	int size = sizeof(str);
	int len = strlen(str);

	cout << "배열의 크기: " << size << '\n';
	cout << "문자열 길이: " << len << '\n';

	return 0;
}