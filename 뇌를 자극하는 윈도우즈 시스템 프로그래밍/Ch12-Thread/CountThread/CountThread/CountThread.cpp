/*
* Windows System Programming - 쓰레드의 생성과 소멸
* 파일명: CountThread.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-07
* 이전 버전 작성 일자:
* 버전 내용: 생성 가능한 쓰레드의 개수를 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_THREADS (1024*10)

// 쓰레드에서 동작할 함수, 쓰레드의 main이 역할을 할 함수
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread num: %d\n"), threadNum);
		Sleep(5000);
	}

	return 0;
}

// 쓰레드의 개수를 기록할 전역변수
DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// 생성 가능한 최대 개수의 쓰레드 생성
	while (1)
	{
		hThread[cntOfThread] =
			CreateThread(
				NULL, // 디폴트 보안(상속) 속성 지정
				0, // 디폴트 스택 사이즈(1M)
				ThreadProc, // 쓰레드 함수
				(LPVOID)cntOfThread, // 쓰레드 함수의 전달 인자
				0, // 디폴트 생성 flag 지정
				&dwThreadID[cntOfThread] // 쓰레드 ID를 전달받기 위한 변수의 주소값
			);
		// 쓰레드 생성 확인
		if (hThread[cntOfThread] == NULL) // NULL인 경우 쓰레드가 생성되지 않은 것
		{
			_tprintf(_T("MAXIMUM Thread Number: %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}

	// 생성한 쓰레드의 갯수만큼 리소스 해제, Usage Count 1씩 감소
	for (DWORD i = 0; i < cntOfThread; i++)
		CloseHandle(hThread[i]);
	return 0;
}