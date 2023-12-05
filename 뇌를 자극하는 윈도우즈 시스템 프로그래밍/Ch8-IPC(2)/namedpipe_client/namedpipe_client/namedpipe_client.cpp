/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: namedpipe_client.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 이름 있는 파이프의 기본 원리 파악 예제 - 클라이언트
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

	while (1)
	{
		// 파이프와 연결할 스트림 생성
		hPipe = CreateFile(
			pipeName, // 파이프 이름
			GENERIC_READ | GENERIC_WRITE, // Read, Write 모드 지정
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		// 연결이 되었을 경우에는 break
		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		// ERROR_PIPE_BUSY는 연결 요청이 Pending상태에 놓여있음을 의미함.
		// Pending은 여유분의 파이프가 존재하지 않아서 요청이 수락되려면 잠시 기다려야 되는 상황
		// ERROR_PIPE_BUSY가 발생할 경우에는 다시 시도를 해봐야 함.
		// 그렇다고 계속 연결을 시도할 수는 없으므로 밑에서 Timeout이 되는 경우를 별도로 놔뒀음
		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}

		// Timeout이 되는 경우
		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT; // 메세지 기반으로 모드 변경
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, // 서버 파이프와 연결된 핸들
		&pipeMode, // 변경할 모드 정보
		NULL,
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("SetNamedPipeHandleState failed\n"));
		return 0;
	}

	LPCTSTR fileName = _T("D:\\news.txt");
	DWORD bytesWritten = 0;

	// 데이터 송신
	isSuccess = WriteFile(
		hPipe, // 서버 파이프와 연결된 핸들
		fileName, // 전송할 파일명
		(_tcslen(fileName) + 1) * sizeof(TCHAR), // 메시지의 길이
		&bytesWritten, // 실제 전송한 바이트 수
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("WriteFile failed\n"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (1)
	{
		isSuccess = ReadFile(
			hPipe,
			readDataBuf,
			BUF_SIZE * sizeof(TCHAR),
			&bytesRead,
			NULL);


		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		readDataBuf[bytesRead] = 0;
		_tprintf(_T("%s\n"), readDataBuf);
	}

	CloseHandle(hPipe);
	return 0;
}