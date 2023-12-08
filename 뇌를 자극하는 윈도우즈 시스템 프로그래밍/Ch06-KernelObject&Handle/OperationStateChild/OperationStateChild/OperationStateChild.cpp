/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: OperationStateChild.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: CloseHandle 함수와 프로세스 종료코드 예제
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>

int main(int argc, TCHAR* argv[])
{
	float num1, num2;
	_fputts(_T("Return Value Test\n"), stdout);
	_tscanf(_T("%f %f"), &num1, &num2);

	if (num2 == 0)
		exit(-1); // 또는 return -1;

	_tprintf(_T("Operation Result: %f\n"), num1 / num2);
	
	return 1;
}