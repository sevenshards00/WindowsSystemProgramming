/*
* Windows System Programming - 스케줄링 알고리즘과 우선순위
* 파일명: NORMAL_PRIORITY_CLASS.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 우선순위를 적용한 스케줄링 알고리즘이 적용되는 것을 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		//Sleep(10);

		_fputts(_T("NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}