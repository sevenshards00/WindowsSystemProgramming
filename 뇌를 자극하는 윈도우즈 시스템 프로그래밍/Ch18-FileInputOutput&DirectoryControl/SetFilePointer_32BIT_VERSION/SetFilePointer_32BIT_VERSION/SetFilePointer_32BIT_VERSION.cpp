/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: SetFilePointer_32BIT_VERSION.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 파일의 크기 정보를 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = TEXT("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtr = 0;

	// File Write
	hFile = CreateFile(fileName, GENERIC_WRITE,	NULL, NULL,	CREATE_ALWAYS, NULL, NULL);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten,	NULL);
	CloseHandle(hFile);

	// File Read
	hFile = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(TEXT("%s\n"), readBuf);

	// 파일 포인터를 맨 앞으로 이동
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(TEXT("SetFilePointer Error\n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(TEXT("%s\n"), readBuf);

	// 파일 포인터를 맨 뒤로 이동
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * -4, NULL, FILE_END);
	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(TEXT("SetFilePointer Error\n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(TEXT("%s\n"), readBuf);

	return 0;
}