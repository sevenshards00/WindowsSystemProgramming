/*
* Windows System Programming - 쓰레드의 생성과 소멸
* 파일명: CountThread.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 1~10까지의 합을 3개의 쓰레드로 나눠서 수행하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;
	
	DWORD numStart = *nPtr;
	DWORD numEnd = *(nPtr + 1);

	DWORD total = 0;
	for (DWORD i = numStart; i <= numEnd; i++)
		total += i;

	return total;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[3]; // 쓰레드의 ID를 받을 변수
	HANDLE hThread[3]; // 생성한 쓰레드의 핸들을 받기 위한 변수

	DWORD paramThread[] = { 1, 3, 4, 7, 8, 10 };
	DWORD total = 0;
	DWORD result = 0;

	// 쓰레드 생성
	hThread[0] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[0]),
			0,
			&dwThreadID[0]
		);

	hThread[1] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[2]),
			0,
			&dwThreadID[1]
		);

	hThread[2] =
		CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)(&paramThread[4]),
			0,
			&dwThreadID[2]
		);

	// 세 쓰레드 중 하나라도 NULL이다 -> 핸들값이 반환되지 않음 -> 생성 실패
	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(TEXT("Thread creation fault!\n"));
		return -1;
	}

	// WaitForMultipleObjects -> WaitForSingleObject와 유사함
	// n개의 리소스를 대상으로 커널 오브젝트가 Signaled 상태가 될 때까지 기다린다
	WaitForMultipleObjects(
		3, // 관찰할 커널 오브젝트의 대상의 수
		hThread, // 커널 오브젝트의 배열 정보
		TRUE, // 모든 커널 오브젝트가 Signaled 상태가 될 때까지 대기한다
		INFINITE // 계속 기다린다
	);

	// 각 쓰레드에서 계산한 값을 합친다.
	GetExitCodeThread(hThread[0], &result);
	total += result;

	GetExitCodeThread(hThread[1], &result);
	total += result;

	GetExitCodeThread(hThread[2], &result);
	total += result;

	_tprintf(TEXT("total (1~10): %d\n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	return 0;
}