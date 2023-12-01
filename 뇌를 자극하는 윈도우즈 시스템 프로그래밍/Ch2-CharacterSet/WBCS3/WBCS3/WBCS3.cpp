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

int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < argc; i++)
		fputws(argv[i], stdout); // 여기에서 컴파일 에러 발생, 데이터 타입이 일치하지 않음

	return 0;
}