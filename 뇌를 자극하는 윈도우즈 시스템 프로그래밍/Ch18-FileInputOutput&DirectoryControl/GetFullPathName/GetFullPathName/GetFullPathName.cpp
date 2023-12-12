/*﻿
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: GetFullPathName.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 파일이름을 기반으로 완전경로를 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <locale.h>




int _tmain(int argc, TCHAR* argv[])
{
	_wsetlocale(LC_ALL, L"korean");

	TCHAR fileName[] = TEXT("data.txt");
	TCHAR fileFullPathName[MAX_PATH];
	LPTSTR filePtr;

	GetFullPathName(
		fileName,
		MAX_PATH,
		fileFullPathName,
		&filePtr
	);

	_tprintf(TEXT("%s\n"), fileFullPathName);
	_tprintf(TEXT("%s\n"), filePtr);
	return 0;
}