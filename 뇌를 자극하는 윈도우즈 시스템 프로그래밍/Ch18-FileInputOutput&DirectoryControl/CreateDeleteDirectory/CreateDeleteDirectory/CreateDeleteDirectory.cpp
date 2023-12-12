/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: CreateDeleteDirectory.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 디렉터리 생성 및 소멸 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 1이면 생성, 0이면 삭제
#define CREATE_DIRECTORY 1

int _tmain(int argc, TCHAR* argv[])
{
	// 상대 경로와 절대 경로
	TCHAR dirRelativePath[] = TEXT("RelativePathDirectory");
	TCHAR dirFullPath[] = TEXT("D:\\FullPathDirectory");
// 매크로를 이용하여 조건부 컴파일
#if CREATE_DIRECTORY
	CreateDirectory(dirRelativePath, NULL);
	CreateDirectory(dirFullPath, NULL);
#else
	RemoveDirectory(dirRelativePath);
	RemoveDirectory(dirFullPath);
#endif

	return 0;
}