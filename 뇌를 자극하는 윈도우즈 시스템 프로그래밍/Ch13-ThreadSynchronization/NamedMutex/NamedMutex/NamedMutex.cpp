/*
* Windows System Programming - 쓰레드 동기화 기법(1)
* 파일명: NamedMutex.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-08
* 이전 버전 작성 일자:
* 버전 내용: 커널모드 동기화 기법(3) - NamedMutex 기반 동기화 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex; // 뮤텍스 오브젝트 선언
DWORD dwWaitResult; // WaitForSingleObject의 반환값을 받기 위한 변수

//임계 영역
void ProcessBaseCriticalSection()
{
	// WaitForSingleObject의 반환값을 통해 결과를 확인하기 위해 변수에 저장
	// Signaled 상태에서 Non-Signaled 상태가 된다면 WAIT_OBJECT_0을 반환
	// 그게 아니라면 대기(블로킹)
	// 타임아웃을 설정해놓았다면, 타임아웃 시간이 다 지난 후에는 WAIT_TIMEOUT 반환
	// WAIT_ABANDONED는 정상적으로 뮤텍스의 반환이 이뤄지지 않았을 경우에 반환
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0: // 쓰레드가 뮤텍스를 소유한 경우
		_tprintf(TEXT("Thread got mutex\n"));
		break;
	case WAIT_TIMEOUT: // time-out이 발생한 경우
		_tprintf(TEXT("Time out\n"));
		return;
	case WAIT_ABANDONED: // 뮤텍스의 반환이 적절하게 이뤄지지 않은 경우
		return;
	}

	for (DWORD i = 0; i < 5; i++)
	{
		_tprintf(TEXT("Thread is running: %d\n"), i);
		Sleep(10000);
	}

	ReleaseMutex(hMutex); // Non-Signaled가 된 뮤텍스를 Signaled로
}

int _tmain(int argc, TCHAR* argv[])
{
// 조건부 컴파일을 수행하는 부분
// 0이라면 이름있는 뮤텍스(Named Mutex)를 생성, 아니라면 이름있는 뮤텍스에 접근한다.
// if 1로 설정하고 빌드 후, 실행 파일 명은 NamedMutex.exe로
// 그리고 if 0으로 설정 후 빌드하고 실행 파일명을 OpenMutex.exe로
#if 0
	hMutex = CreateMutex(
		NULL,
		FALSE,
		TEXT("NamedMutex")
	);
#else
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS, // 접근 권한 요청, MUTEX_ALL_ACCESS를 전달하여 접근 권한을 요청한다.
		FALSE, // 상속 관련 인자, 상속을 하지 않으므로 FALSE
		TEXT("NamedMutex") // 뮤텍스에 이름을 설정하였다면 해당 이름의 뮤텍스를 찾는다. 있다면 핸들의 반환과 핸들테이블에 핸들값이 추가된다.
	);
#endif

	if (hMutex == NULL) // 뮤텍스가 제대로 생성되지 않았을 경우
	{
		_tprintf(TEXT("Create Mutex Error: %d\n"), GetLastError());
		return -1;
	}

	// 임계 영역인 함수 호출
	ProcessBaseCriticalSection();

	// 뮤텍스의 핸들을 반환, Usage Count 1감소
	CloseHandle(hMutex);
	return 0;
}