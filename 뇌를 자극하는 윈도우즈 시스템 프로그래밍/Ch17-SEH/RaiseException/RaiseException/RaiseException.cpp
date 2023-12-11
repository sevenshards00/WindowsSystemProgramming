/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: RaiseException.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 소프트웨어 예외(사용자 정의 예외) 생성 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SoftwareException();

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	DWORD DefinedException = 0x00;

	// 심각도(31, 30번 비트. 11로 지정할 경우 심각한 에러)
	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	// MS에서 정의한 예외 또는 사용자 정의 예외 (29번 비트, 1일 경우 사용자 지정 예외)
	DefinedException |= 0x01 << 29;

	// 예약(Reserved)된 비트, 반드시 0이어야 하며 굳이 이 부분은 안넣어도 됨
	DefinedException |= 0x00 << 28;

	// 예외 발생 환경 정보(16~27)
	DefinedException |= 0x00 << 16;

	// 예외 종류를 구분하기 위한 코드 (0~15, 실제로 정의할 내용)
	DefinedException |= 0x08;

	__try
	{
		_tprintf(TEXT("Send: exception code: 0x%X \n"), DefinedException);
		RaiseException(
			DefinedException, // 발생 시킬 예외의 형태
			0, // 예외 발생 이후의 실행 방식에 제한을 둘 때 지정하는 인자
			NULL, // 추가 정보의 개수, 없다면 NULL
			NULL // 추가 정보를 전달하기 위한 인자, 없다면 NULL
		);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(TEXT("Recv: exception code : 0x%X\n"), exptType);
	}
}