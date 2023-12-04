/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: KernelObjProb2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: CloseHandle 함수 사용 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD n = 0;
	while (n < 100)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy waiting

		_fputts(_T("KernelObjProb2.exe\n"), stdout);
		n++;
	}

	return 0;
}