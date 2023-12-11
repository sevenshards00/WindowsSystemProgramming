/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: GetExceptionCode.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 사전 정의 되어 있는 예외의 구분 방법 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR argv[])
{
	int* p = NULL;
	int sel = 0;

	while (1)
	{
		_tprintf(TEXT("1 for Memory Access Exception\n"));
		_tprintf(TEXT("2 for Divide by 0 Exception\n"));
		_tprintf(TEXT("Select Exception Type [3 for exit]: "));

		_tscanf_s(TEXT("%d"), &sel);

		if (sel == 3)
			break;

		__try
		{
			if (sel == 1)
			{
				*p = 100; // 예외 발생 -> 메모리 참조 예외
				_tprintf(TEXT("value: %d"), *p);
			}
			else // sel == 2
			{
				int n = 0;
				n = 7 / n; // 예외 발생 -> 0으로 나누는 경우
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			DWORD exptType = GetExceptionCode(); // 예외 발생 코드를 받아오는 함수(사실상 매크로)

			switch (exptType)
			{
			case EXCEPTION_ACCESS_VIOLATION: // 메모리 참조 예외
				_tprintf(TEXT("Memory Access Violated\n"));
				break;
			case EXCEPTION_INT_DIVIDE_BY_ZERO: // 0으로 나누는 경우
				_tprintf(TEXT("Divide by Zero\n"));
				break;
			}
		}
	}

	return 0;
}