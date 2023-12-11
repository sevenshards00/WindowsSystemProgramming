/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: SEH_FlowView.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 예외적 핸들러 기본 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(TEXT("Start!\n"));

	int* p = NULL;

	__try
	{
		*p = 100; // 예외 발생 (메모리 참조 오류)
		_tprintf(TEXT("value: %d\n"), *p); // 실행되지 않는다
	}
	// 예외 핸들러 (__except)
	// 예외 필터 EXCEPTION_EXECUTE_HANDLER
	// 예외 발생 이후 __try블록의 남은 부분을 건너뛰고 __except 블록을 실행하고 나서 그 이후를 실행
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(TEXT("Exception Occurred!\n"));
	}

	_tprintf(TEXT("End!\n"));

	return 0;
}