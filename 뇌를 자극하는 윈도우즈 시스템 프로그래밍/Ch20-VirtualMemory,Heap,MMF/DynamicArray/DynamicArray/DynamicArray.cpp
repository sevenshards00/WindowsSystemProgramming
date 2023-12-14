/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: DynamicArray.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: SEH 기반의 가상 메모리 컨트롤 - 동적 배열 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_PAGE 10

int* nextPageAddr;
DWORD pageCnt = 0;
DWORD pageSize;
int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sysInfo;

	GetSystemInfo(&sysInfo);
	pageSize = sysInfo.dwPageSize; // 페이지 사이즈

	// MAX_PAGE의 수 만큼 페이지를 RESERVE 상태로
	baseAddr = VirtualAlloc(
		NULL, // 임의의 주소로 할당
		MAX_PAGE * pageSize, // 예약할 메모리의 크기
		MEM_RESERVE, // RESERVE 상태로
		PAGE_NOACCESS // NO ACCESS
	);

	if (baseAddr == NULL) // 메모리 할당이 안됐다면
		_tprintf(TEXT("VitualAlloc reserve failed\n"));

	lpPtr = (int*)baseAddr; // 배열의 시작 주소를 가리키는 것과 동일
	nextPageAddr = (int*)baseAddr;

	// page fault 발생 시 예외처리
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++)
	{
		__try
		{
			lpPtr[i] = i; // 배열처럼 접근, 범위를 넘어가면 예외 발생
		}
		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{
			ExitProcess(GetLastError()); // 문제 발생 시 종료
		}
	}

	// 저장한 배열의 데이터 출력
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++)
		_tprintf(TEXT("%d "), lpPtr[i]);

	// 할당한 가상 메모리 해제
	BOOL isSuccess = VirtualFree(
		baseAddr, // 헤제할 메모리의 시작 주소
		0, // 해제할 메모리 크기의 단위, MEM_RELEASE의 경우에는 반드시 0
		MEM_RELEASE // MEM_DECOMMIT은 RESERVE 상태로, MEM_RELEASE는 FREE 상태로 
	);

	if (isSuccess) // 메모리 해제가 됐다면
		_tprintf(TEXT("Release Done!\n"));
	else // 안됐다면
		_tprintf(TEXT("Release Failed\n"));

	return 0;
}

// 사실 여기가 핵심.
// 예외가 발생할 때마다 추가로 COMMIT 상태로 바꾸는 과정을 구현했다.
int PageFaultExceptionFilter(DWORD exptCode)
{
	// 예외의 원인이 'page fault'가 아니라면
	if (exptCode != EXCEPTION_ACCESS_VIOLATION)
	{
		_tprintf(TEXT("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(TEXT("Exception is a page fault\n"));

	if (pageCnt >= MAX_PAGE) // 최대 페이지의 수를 넘은 경우
	{
		_tprintf(TEXT("Exception: out of pages\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// RESERVED된 가상 메모리 공간을 COMMIT 상태로
	LPVOID lpvResult = VirtualAlloc(
		(LPVOID)nextPageAddr,
		pageSize,
		MEM_COMMIT,
		PAGE_READWRITE
	);

	if (lpvResult == NULL) // COMMIT이 안됐다면
	{
		_tprintf(TEXT("VirtualAlloc Failed\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
		_tprintf(TEXT("Allocating Another Page\n"));

	pageCnt++;
	nextPageAddr += pageSize / sizeof(int); // 실수할 수 있으므로 주의

	return EXCEPTION_CONTINUE_EXECUTION; // page fault가 발생한 지점부터 이어서 실행
}