/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: SearchPath.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: SearchPath 사용 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf(TEXT("Insert name of the file to find: "));
	_tscanf_s(TEXT("%s"), fileName, _countof(fileName)); // _countof(filename) == sizeof(fileName)/sizeof(TCHAR)

	result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);

	if (result == 0)
		_tprintf(TEXT("File not found!\n"));
	else
	{
		_tprintf(TEXT("File path: %s\n"), bufFilePath);
		_tprintf(TEXT("File name: %s\n"), lpFilePart);
	}
	return 0;
}