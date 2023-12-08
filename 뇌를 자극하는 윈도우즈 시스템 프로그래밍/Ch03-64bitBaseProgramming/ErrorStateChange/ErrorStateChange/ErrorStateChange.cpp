/*
* Windows System Programming - 64비트 기반 프로그래밍
* 파일명: ErrorStateChange.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-02
* 이전 버전 작성 일자:
* 버전 내용: GetLastError 함수 사용 예시(2)
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain()
{
	// 파일을 개방
	HANDLE hFile = CreateFile(_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("Error code: %d\n"), GetLastError());
	
	// 파일을 새로 생성
	hFile = CreateFile(_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("Error code: %d\n"), GetLastError());
	return 0;
}