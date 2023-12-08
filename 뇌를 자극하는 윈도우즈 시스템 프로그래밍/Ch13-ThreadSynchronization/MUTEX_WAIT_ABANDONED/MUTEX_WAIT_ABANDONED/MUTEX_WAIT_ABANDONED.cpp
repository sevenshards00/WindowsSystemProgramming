/*
* Windows System Programming - 쓰레드 동기화 기법(1)
* 파일명: MUTEX_WAIT_ABANDONED.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-09
* 이전 버전 작성 일자:
* 버전 내용: 커널모드 동기화 기법 - 뮤텍스 기법의 WAIT_ABANDONED에 대한 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

unsigned int WINAPI IncreaseCountOne(LPVOID lpParam)
{
	// hThread1이 뮤텍스를 획득.
	// Signaled 상태에서 Non-Signaled 상태로 바뀐다.
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;

	// 문제는 ReleaseMutex를 하지 않으므로 계속 Signaled 상태를 유지한채 뮤텍스를 반환하지 않고 쓰레드는 종료된다.
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpParam)
{
	DWORD dwWaitResult = 0;
	// 그래서 두 번째 쓰레드는 뮤텍스를 획득하려고 하나, 획득을 하지 못하는 상황.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	// 결과적으로 WAIT_ABANDONED가 나오게 되고, Windows 운영체제는 반환되지 않은 뮤텍스를 처리한다.
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		ReleaseMutex(hMutex);
		break;
	case WAIT_ABANDONED:
		_tprintf(TEXT("WAIT_ABANDONED\n"));
		break;
	}

	gTotalCount++;

	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadIDOne;
	DWORD dwThreadIDTwo;

	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(
		NULL,
		FALSE,
		NULL
	);

	if (hMutex == NULL) // 뮤텍스 생성을 실패한 경우
	{
		_tprintf(TEXT("CreateMutex Error Occured: %d\n"), GetLastError());
		return -1;
	}

	// 무례한 쓰레드 (ㅋㅋㅋ)
	hThreadOne = (HANDLE)_beginthreadex(
		NULL, // 보안(상속) 관련 속성
		0, // 쓰레드의 스택 사이즈, 0이면 기본 크기(1M)
		IncreaseCountOne, // 쓰레드의 메인이 될 함수
		NULL, // 함수에 전달할 인자 목록
		0, // 쓰레드 생성 시 제어 인자, 0일 경우 생성과 함께 바로 실행
		(unsigned*)&dwThreadIDOne // 쓰레드의 ID를 저장할 주소값
	);

	hThreadTwo = (HANDLE)_beginthreadex(
		NULL, // 보안(상속) 관련 속성
		0, // 쓰레드의 스택 사이즈
		IncreaseCountTwo, // 쓰레드의 메인이 될 함수
		NULL, // 함수에 전달할 인자 목록
		CREATE_SUSPENDED, // 쓰레드 생성 시 제어 인자, CREATE_SUSPENDED로 생성 후 바로 실행하지 않음(Blocked 상태, Suspend Count 1)
		(unsigned*)&dwThreadIDTwo // 쓰레드의 ID를 저장할 주소값
	);

	Sleep(1000);
	ResumeThread(hThreadTwo); // hThreadTwo를 실행 상태로 전환 (Blocked -> Ready, Suspend Count 0)

	// 쓰레드가 다시 뮤텍스를 얻는 과정
	WaitForSingleObject(hThreadTwo, INFINITE);
	_tprintf(TEXT("Total Count: %d\n"), gTotalCount);

	// 생성했던 커널 오브젝트의 핸들을 반환, Usage Count 1 감소
	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);
	return 0;
}