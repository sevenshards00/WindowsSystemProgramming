/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: System_Windows_Dir.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 시스템과 Windows 디렉터리 확인 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR sysPathBuf[MAX_PATH];
	TCHAR winPathBuf[MAX_PATH];

	GetSystemDirectory(sysPathBuf, MAX_PATH);
	GetWindowsDirectory(winPathBuf, MAX_PATH);

	_tprintf(TEXT("System dir: %s\n"), sysPathBuf);
	_tprintf(TEXT("Windows dir: %s\n"), winPathBuf);
	return 0;
}