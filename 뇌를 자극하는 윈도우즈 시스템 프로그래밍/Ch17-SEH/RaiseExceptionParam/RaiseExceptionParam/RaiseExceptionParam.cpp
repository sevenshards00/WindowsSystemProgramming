/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: RaiseExceptionParam.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: RaiseException 함수의 3, 4번째 인자 사용과 GetExceptionInformation()을 통한 예외의 상세 정보를 얻는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 사용자(개발자) 정의 예외
#define STATUS_DEFAULT_USER_DEFINED_EXPT ((DWORD) 0xE0000008L)

void SoftwareException();
DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr);

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	CONST TCHAR* exptString[] = {
		TEXT("Exception String One"),
		TEXT("Exception String Two"),
		TEXT("Exception String Three")
	};

	__try
	{
		RaiseException(
			STATUS_DEFAULT_USER_DEFINED_EXPT, // 발생 시킬 예외의 형태
			0, // 예외 발생 이후의 실행 방식에 제한을 둘 때 지정하는 인자
			3, // 추가 정보의 개수, 없다면 NULL
			(ULONG_PTR*)exptString // 추가 정보를 전달하기 위한 인자, 없다면 NULL
		);
		_tprintf(TEXT("Working!\n"));
	}
	// 예외 필터의 자리에는 함수가 와도 된다.
	// 단, 반환값은 예외필터 정규 표현식일것.
	__except (FilterFunction(GetExceptionInformation())) 
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(TEXT("Recv: exception code : 0x%X\n"), exptType);
	}
}

DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr)
{
	PEXCEPTION_RECORD exptRecord = exptPtr->ExceptionRecord;

	switch (exptRecord->ExceptionCode)
	{
	case STATUS_DEFAULT_USER_DEFINED_EXPT:
		_tprintf(TEXT("Exception code: 0x%X\n"), exptRecord->ExceptionCode);
		_tprintf(TEXT("Exception flags: %d\n"), exptRecord->ExceptionFlags);
		_tprintf(TEXT("Exception param num: %d\n"), exptRecord->NumberParameters);
		_tprintf(TEXT("String One: %s\n"), exptRecord->ExceptionInformation[0]);
		_tprintf(TEXT("String Two: %s\n"), exptRecord->ExceptionInformation[1]);
		_tprintf(TEXT("String Three: %s\n"), exptRecord->ExceptionInformation[2]);
		break;
	default:
		break;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}