/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: GetFileInformationByHandle.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 핸들을 이용한 파일의 정보 참조 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

void ShowAttributes(DWORD attrib);
void ShowFileTime(FILETIME t);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt"); // 확인할 파일 이름
	BY_HANDLE_FILE_INFORMATION fileInfo;

	HANDLE hFile = CreateFile(
		fileName,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Open Failed\n"));
		return -1;
	}

	GetFileInformationByHandle(hFile, &fileInfo);
	ShowAttributes(fileInfo.dwFileAttributes);

	// 특성 이외의 추가로 볼 수 있는 정보
	// 4GB 미만 파일
	_tprintf(TEXT("File Size: %u\n"), fileInfo.nFileSizeLow);
	
	_tprintf(TEXT("File Created Time: "));
	ShowFileTime(fileInfo.ftCreationTime);

	_tprintf(TEXT("File Accessed Time: "));
	ShowFileTime(fileInfo.ftLastAccessTime);

	_tprintf(TEXT("File Written Time: "));
	ShowFileTime(fileInfo.ftLastWriteTime);

	CloseHandle(hFile);
	return 0;
}

void ShowAttributes(DWORD attrib)
{
	// AND(&) 연산을 통해 파일의 속성을 비교한다.
	// 일반 파일이라면 다른 특성이 없는 파일을 뜻한다.
	// OS에서는 기본적으로 파일을 FILE_ATTRIBUTE_NORMAL로 생성해도 FILE_ATTRIBUTE_ARCHIVE 속성을 부여한다.
	// 그래서 아래 속성은 나오지 않는다.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
		_tprintf(TEXT("FILE_ATTRIBUTE_NORMAL OR FILE_ATTRIBUTE_ARCHIVE\n"));
	else
	{
		// 읽기 전용 속성이 있을 경우
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(TEXT("FILE_ATTRIBUTE_READONLY\n"));
		// 숨김 파일 속성이 있을 경우
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(TEXT("FILE_ATTRIBUTE_HIDDEN\n"));
	}

	_tprintf(TEXT("\n"));
}

void ShowFileTime(FILETIME t)
{
	TCHAR fileTimeInfo[STRING_LEN];
	FILETIME ft = t;
	SYSTEMTIME stUTC, stLocal;
	
	FileTimeToSystemTime(&ft, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	_stprintf_s(fileTimeInfo, sizeof(fileTimeInfo) / sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

	_tprintf(TEXT("%s\n"), fileTimeInfo);
}