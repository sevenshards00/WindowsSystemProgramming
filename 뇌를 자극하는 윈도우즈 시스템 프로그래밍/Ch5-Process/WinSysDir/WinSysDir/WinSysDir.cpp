/*
* Windows System Programming - 프로세스 생성 예제
* 파일명: WinSysDir.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자:
* 버전 내용: 시스템 디렉터리와 Windows 디렉터리 확인 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR sysDir[DIR_LEN];
	TCHAR winDir[DIR_LEN];

	// 시스템 디렉터리 정보 추출
	GetSystemDirectory(sysDir, DIR_LEN);

	// Windows 디렉터리 정보 추출
	GetWindowsDirectory(winDir, DIR_LEN);

	// 디렉터리 정보 출력
	_tprintf(_T("System Dir: %s\n"), sysDir);
	_tprintf(_T("Windows Dir: %s\n"), winDir);

	return 0;
}