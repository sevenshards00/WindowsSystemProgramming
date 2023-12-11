/*
* Windows System Programming - 구조적 예외처리(Structured Exception Handling, SEH)
* 파일명: TerminationHandlerEx1.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-11
* 이전 버전 작성 일자:
* 버전 내용: 종료 핸들러의 활용 예제(1)
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int ReadStringAndWrite(void);

int _tmain(int argc, TCHAR* argv[])
{
	int state = 0;

	while (1)
	{
		state = ReadStringAndWrite();
		if (state == -1)
		{
			_tprintf(TEXT("Some Exception Occurred!\n"));
			break;
		}

		if (state == 0)
		{
			_tprintf(TEXT("Jobs Done!\n"));
			break;
		}
	}

	return 0;
}

int ReadStringAndWrite(void)
{
	FILE* fPtr = NULL;
	TCHAR* strBufPtr = NULL;

	__try
	{
		// 파일 개방
		fPtr = _tfopen(TEXT("string.dat"), TEXT("a+t"));
		if (fPtr == NULL)
			return -1;

		DWORD strLen = 0;
		_tprintf(TEXT("Input String Length(0 to exit): "));
		_tscanf(TEXT("%d"), &strLen);

		if (strLen == 0)
			return 0;

		// 입력받은 문자열을 저장하기 위한 메모리 동적 할당
		strBufPtr = (TCHAR*)malloc(sizeof(TCHAR) * strLen + 1);
		if (strBufPtr == NULL)
			return -1;

		_tprintf(TEXT("Input String:"));
		_tscanf(TEXT("%s"), strBufPtr);


		_ftprintf(fPtr, TEXT("%s\n"), strBufPtr);
	}
	__finally
	{
		// 예외 발생 시 개방했던 파일을 닫는다
		if (fPtr != NULL)
			fclose(fPtr);

		// 예외 발생 시 할당한 메모리를 해제한다
		if (strBufPtr != NULL)
			free(strBufPtr);
	}

	return 1;
}