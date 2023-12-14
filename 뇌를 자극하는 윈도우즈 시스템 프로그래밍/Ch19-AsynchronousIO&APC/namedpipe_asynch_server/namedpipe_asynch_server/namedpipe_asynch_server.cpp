/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: namedpipe_asynch_server.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 중첩 I/O 기반 이름 있는 파이프 - 서버
* 이전 버전 내용:
*/

#define BUF_SIZE 1024

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
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, // Read, Write 모드 지정
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // 메시지 기반
			PIPE_UNLIMITED_INSTANCES, // 최대 파이프 개수 (제한을 두지 않겠다)
			BUF_SIZE / 2, // 출력 버퍼 사이즈 / 2
			BUF_SIZE / 2, // 입력 버퍼 사이즈 / 2
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

	
	// 파일을 개방, 읽기모드로.
	FILE* filePtr = NULL;
	_tfopen_s(&filePtr, fileName, _T("r"));
	if (filePtr == NULL) // 파일 개방에 실패했을 경우
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = CreateEvent(
		NULL, // 보안(상속) 속성
		TRUE, // 수동 리셋 모드 결정 여부
		TRUE, // 초기 상태, TRUE 전달시 Signaled
		NULL // 이름을 지정할 때 사용, 안쓴다면 NULL
	);

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;
	DWORD bytesTransfer = 0;

	// EOF를 만날 때까지 파일을 읽어들인다
	while (!feof(filePtr))
	{
		// fread 함수를 통해 데이터를 읽어들인다.
		// 1 * 1024 바이트만큼 읽음
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);
		bytesWrite = bytesRead;
		isSuccess =	WriteFile(
			hPipe, // 파이프 핸들
			dataBuf, // 전송할 데이터 버퍼
			bytesRead, // 전송할 데이터 크기
			&bytesWritten, // 실제 전송된 데이터 크기
			NULL);
		if (!isSuccess && GetLastError() != ERROR_IO_PENDING)
		{
			_tprintf(TEXT("Pipe write message error!\n"));
			break;
		}

		// 다른 작업을 할 수 있는 기회(구간)
		WaitForSingleObject(overlappedInst.hEvent, INFINITE);
		GetOverlappedResult(hPipe, &overlappedInst, &bytesTransfer, FALSE);
		_tprintf(TEXT("Transferred data size: %d \n"), bytesTransfer);
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}