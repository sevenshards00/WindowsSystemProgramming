/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: SYSTEM_INFO.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 시스템 정보 확인 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SYSTEM_INFO si;
	DWORD allocGranularity;
	DWORD pageSize;

	GetSystemInfo(&si);
	pageSize = si.dwPageSize;
	allocGranularity = si.dwAllocationGranularity;

	_tprintf(TEXT("Page Size: %u KByte\n"), pageSize);
	_tprintf(TEXT("Allocation Granularity: %u KByte\n"), allocGranularity);

	return 0;
}