/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: anonymous_pipe.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 이름 없는 파이프의 기본 원리 파악 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hReadPipe, hWritePipe; // pipe handle, 입력과 출력 총 2개의 핸들이 필요하다

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	// 파이프 생성
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	// 파이프의 한쪽 끝을 이용한 데이터 송신(Write)
	WriteFile(
		hWritePipe, // 파이프의 이름
		sendString, // Write할 데이터의 버퍼
		_tcslen(sendString) * sizeof(TCHAR), // Write할 데이터의 크기
		&bytesWritten, // 실제로 Write한 데이터의 크기를 저장할 변수의 주소
		NULL);
	
	_tprintf(_T("string send: %s\n"), sendString);

	// 파이프의 다른 한쪽 끝을 이용한 데이터 수신(Read)
	ReadFile(
		hReadPipe, // 파이프의 이름
		recvString, // Read할 데이터의 버퍼
		bytesWritten, // Read할 데이터의 크기
		&bytesRead, // 실제로 Read한 데이터의 크기를 저장할 변수의 주소
		NULL);

	recvString[bytesRead / sizeof(TCHAR)] = '\0'; // 마지막에 널 문자 추가
	_tprintf(_T("string recv: %s\n"), recvString);

	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	return 0;
}