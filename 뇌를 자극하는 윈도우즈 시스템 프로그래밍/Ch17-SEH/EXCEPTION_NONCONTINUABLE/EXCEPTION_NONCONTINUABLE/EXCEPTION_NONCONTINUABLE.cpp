/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: EXCEPTION_NONCONTINUABLE.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: RaiseException 함수의 두 번째 인자로 EXCEPTION_NONCONTINUABLE를 사용한 예시
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 이전과 같이 비트에 일일이 예외를 정의하는 것보다 이와 같은 방식이 보편적이다.
#define TEST_EXCEPTION ((DWORD) 0xE0000008L)

void SoftwareException();

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	__try
	{
		RaiseException(
			TEST_EXCEPTION, // 발생 시킬 예외의 형태
			//0,
			EXCEPTION_NONCONTINUABLE, // 이걸 인자로 설정할 경우 예외 필터의 EXCEPTION_CONTINUE_EXECUTION가 동작하지 않는다.
			NULL, // 추가 정보의 개수, 없다면 NULL
			NULL // 추가 정보를 전달하기 위한 인자, 없다면 NULL
		);
		_tprintf(TEXT("Working!\n"));
	}
	__except (EXCEPTION_CONTINUE_EXECUTION) // 예외 발생 이후에도 이어서 실행하는 예외 필터
	{
		DWORD exptType = GetExceptionCode();
		if (exptType == TEST_EXCEPTION)
			_tprintf(TEXT("TEST EXCEPTION Occured\n"));
	}
}