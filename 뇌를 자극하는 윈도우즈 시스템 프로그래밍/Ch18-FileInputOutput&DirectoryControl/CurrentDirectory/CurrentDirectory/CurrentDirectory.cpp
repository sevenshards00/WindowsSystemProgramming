/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: CurrentDirectory.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 현재 디렉터리에 대한 개념 이해
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STR_LEN 100
TCHAR fileData[] = TEXT("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("abcd.dat");
	TCHAR readBuf[STR_LEN] = { 0, };

	HANDLE hFileWrite = NULL;
	HANDLE hFileRead = NULL;
	DWORD numOfByte = 0;

	// file Write
	hFileWrite = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFileWrite == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Create Error\n"));
		return -1;
	}
		

	WriteFile(hFileWrite, fileData, sizeof(fileData), &numOfByte, NULL);
	CloseHandle(hFileWrite);

	// 현재 디렉터리를 변경
	SetCurrentDirectory(TEXT("D:\\"));

	// file read
	hFileRead = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFileRead == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Open Error\n"));
		return -1;
	}
	ReadFile(hFileRead, readBuf, sizeof(readBuf), &numOfByte, NULL);
	_tprintf(TEXT("%s"), readBuf);
	CloseHandle(hFileRead);
	
	return 0;
}