/*
* Windows System Programming - 메모리 관리(Virtual Memory, Heap, MMF)
* 파일명: DynamicHeap.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 힙(동적 힙, 디폴트 힙) 사용 예제
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	UINT pageSize = sysInfo.dwPageSize;

	// 힙 생성
	HANDLE hHeap = HeapCreate(
		HEAP_NO_SERIALIZE, // 생성된 힙에 메모리 할당 및 해제 시 동기화 처리를 하지 않음
		pageSize * 10, // 초기에 할당할 물리 메모리의 크기, COMMIT 상태
		pageSize * 100 // 힙의 최대 크기, 지정하는 크기만큼 RESERVED 상태
		//0을 전달할 경우 증가 가능한 메모리가 되며 메모리가 허락하는 한도 내에서 힙의 크기 증가
	);

	// 메모리 할당
	int* p = (int*)HeapAlloc(
		hHeap, // 할당할 힙의 핸들
		0, // HEAP_GENERATE_EXCEPTIONS를 인자로 전달하면 오류 발생시 NULL이 아닌 예외 발생.
		// 힙 생성 시 HEAP_NO_SERIALIZE를 인자로 전달한 경우 이 때는 지정하지 않아도 됨
		// HEAP_ZERO_MEMORY가 전달되면 메모리는 0으로 초기화
		sizeof(int) * 10 // 할당하고자 하는 메모리의 크기
	);

	// 메모리 활용
	for (int i = 0; i < 10; i++)
		p[i] = i;

	// 메모리 해제
	HeapFree(
		hHeap, // 할당되어 있는 힙의 핸들
		0, // HEAP_NO_SERIALIZE를 인자로 전달 가능, 이미 생성 시 전달했다면 생략 가능
		p // 해제할 메모리의 시작 주소
	);

	// 힙 소멸
	HeapDestroy(hHeap);

	// 디폴트 힙 사용 예시
	HANDLE hDefaultHeap = GetProcessHeap();
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 30);
	_tcscpy(pDefault, TEXT("Default Heap!"));
	_tprintf(TEXT("%s\n"), pDefault);
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);


	return 0;
}