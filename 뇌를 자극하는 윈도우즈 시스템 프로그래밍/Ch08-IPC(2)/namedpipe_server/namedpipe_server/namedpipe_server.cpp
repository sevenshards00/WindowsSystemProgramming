/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: namedpipe_server.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 이름 있는 파이프의 기본 원리 파악 예제 - 서버
* 이전 버전 내용:
*/

#define BUF_SIZE 1024

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 클라이언트와 통신하기 위해 선언한 함수
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	// 예제에서는 이렇게 썼으나 C++11 이후로는 불가능
	// LPTSTR pipeName[] = _T("\\\\.\\pipe\\simple_pipe");
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	// 여러 클라이언트가 순차적으로 접속하기 위한 무한 루프
	while (1)
	{
		// 파이프 생성
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX, // Read, Write 모드 지정
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // 메시지 기반
			PIPE_UNLIMITED_INSTANCES, // 최대 파이프 개수 (제한을 두지 않겠다)
			BUF_SIZE, // 출력 버퍼 사이즈
			BUF_SIZE, // 입력 버퍼 사이즈
			20000, // 클라이언트 Time-out
			NULL // 디폴트 보안 속성(상속)
		);

		// 파이프 생성 실패할 경우
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreateNamedPipe Failed!\n"));
			return -1;
		}

		BOOL isSuccess = 0;

		// 파이프 생성 성공 여부를 3항 연산자로 판단
		// 성공했다면 TRUE, 실패했을 경우에는 에러코드를 ERROT_PIPE_CONNECTED인가를 확인
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess) // 파이프 연결이 성공됐다면
			CommToClient(hPipe); // 클라이언트와 통신 개시
		else // 실패했다면
			CloseHandle(hPipe); // 핸들을 반환, Usage Count를 1줄인다.

	}
	return 1;
}

// 클라이언트와 통신을 하는 부분
int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	// 파이프 핸들을 통해 데이터를 수신받는다.
	isSuccess = ReadFile(
		hPipe, // 파이프 핸들
		fileName, // read 버퍼 지정
		MAX_PATH * sizeof(TCHAR), // read 버퍼 사이즈
		&fileNameSize, // 수신한 데이터의 실제 크기
		NULL);

	// 데이터 수신을 실패했거나 데이터가 없는 경우
	if (!isSuccess || fileNameSize == 0)
	{
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	_tprintf(_T("%s %d\n"), fileName, fileNameSize);
	// 파일을 개방, 읽기모드로.
	FILE* filePtr = _tfopen(fileName, _T("r"));
	_tprintf(_T("%p\n"), filePtr);
	if (filePtr == NULL) // 파일 개방에 실패했을 경우
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	// EOF를 만날 때까지 파일을 읽어들인다
	while (!feof(filePtr))
	{
		// fread 함수를 통해 데이터를 읽어들인다.
		// 1 * 1024 바이트만큼 읽음
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(
			hPipe, // 파이프 핸들
			dataBuf, // 전송할 데이터 버퍼
			bytesRead, // 전송할 데이터 크기
			&bytesWritten, // 실제 전송된 데이터 크기
			NULL);

		// 전송할 데이터 크기와 실제 전송된 데이터 크기가 다를 경우
		if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error!\n"));
			break;
		}
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}