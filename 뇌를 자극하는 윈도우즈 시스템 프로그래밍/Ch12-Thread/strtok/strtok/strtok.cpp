/*
* Windows System Programming - 쓰레드의 생성과 소멸
* 파일명: strtok.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 문자열을 토큰으로 나누는 strtok_s 사용 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 문자열 선언 시 다음과 같이 이어서 작성해도 하나의 문자열이 된다.
	TCHAR string[] =
		TEXT("Hey, get a life!")
		TEXT("You don't even have two pennies to rub together.");
	// strtok_s에 의해서 분리된 후의 남은 문자열이 들어가는 변수
	TCHAR* context = NULL;

	// 토큰(token)으로 쪼개기 위한 기준(구분자, Separator)을 정의.
	TCHAR seps[] = TEXT(" ,.!");

	// 토큰 분리 조건, 문자열 설정 및 첫 번째 토큰 반환
	// 그래서 첫 token에는 Hey가 들어간다.
	TCHAR* token = _tcstok_s(string, seps, &context);

	// 반복문을 통해 토큰을 계속 출력
	while(token != NULL)
	{
		_tprintf(TEXT("%s\n"), token);
		token = _tcstok_s(NULL, seps, &context);
	}

	return 0;
}