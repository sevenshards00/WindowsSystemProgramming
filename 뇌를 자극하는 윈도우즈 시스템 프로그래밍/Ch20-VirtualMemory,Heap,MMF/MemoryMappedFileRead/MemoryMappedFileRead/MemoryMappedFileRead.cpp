/*
* Windows System Programming - 메모리 관리(Virtual Memory, Heap, MMF)
* 파일명: MemoryMappedFileRead.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: Memory Mapped File 기본 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 파일 핸들 생성
	HANDLE hFile = CreateFile(TEXT("data.dat"), GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		_tprintf(TEXT("Could not open file\n"));

	TCHAR fileData[] = TEXT("Simple Test String :)");
	DWORD numOfByteWritten = 0;
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);

	// 파일 연결 오브젝트 생성
	HANDLE hMapFile = CreateFileMapping(
		hFile, // 파일의 핸들
		NULL, // 보안 속성(상속)
		PAGE_READONLY, // 읽기, 쓰기 권한 지정
		0, // 연결할 메모리 최대 크기의 상위 4바이트 지정(4GB 이상)
		0, // 연결할 메모리 최대 크기의 하위 4바이트 지정(4GB 미만)
		NULL // 이름을 지정할 때 사용. 안쓰므로 NULL
	);

	// 메모리에 연결
	TCHAR* pWrite = (TCHAR*)MapViewOfFile(
		hMapFile, // 앞에서 생성한 파일 연결 오브젝트의 핸들
		FILE_MAP_READ, // 메모리의 접근 권한 지정(읽기, 쓰기)
		0, // 파일의 일부 영역만 선택해서 연결하는 것도 가능. 파일 오프셋의 상위 4바이트
		0, // 파일 오프셋의 하위 4바이트
		0 // 메모리에 연결할 실제 크기를 바이트 단위로 지정, 0으로 지정하면 오프셋부터 파일의 끝까지 메모리에 연결
	);

	if (pWrite == NULL)
		_tprintf(TEXT("Could not map view of file\n"));

	_tprintf(TEXT("String in file: %s\n"), pWrite);

	UnmapViewOfFile(pWrite);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	_tprintf(TEXT("Jobs Done!\n"));
	return 0;
}