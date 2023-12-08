/*
* Windows System Programming - 커널 오브젝트의 상태(State)
* 파일명: PartAdder.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: 커널 오브젝트의 상태(State)와 종료 코드(Exit Code)의 이해
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 3)
		return 1;

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start; i <= end; i++)
		total += i;

	return total;
}