/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: namedpipe_client.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: �̸� �ִ� �������� �⺻ ���� �ľ� ���� - Ŭ���̾�Ʈ
* ���� ���� ����:
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
		// �������� ������ ��Ʈ�� ����
		hPipe = CreateFile(
			pipeName, // ������ �̸�
			GENERIC_READ | GENERIC_WRITE, // Read, Write ��� ����
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		// ������ �Ǿ��� ��쿡�� break
		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		// ERROR_PIPE_BUSY�� ���� ��û�� Pending���¿� ���������� �ǹ���.
		// Pending�� �������� �������� �������� �ʾƼ� ��û�� �����Ƿ��� ��� ��ٷ��� �Ǵ� ��Ȳ
		// ERROR_PIPE_BUSY�� �߻��� ��쿡�� �ٽ� �õ��� �غ��� ��.
		// �׷��ٰ� ��� ������ �õ��� ���� �����Ƿ� �ؿ��� Timeout�� �Ǵ� ��츦 ������ ������
		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}

		// Timeout�� �Ǵ� ���
		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT; // �޼��� ������� ��� ����
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, // ���� �������� ����� �ڵ�
		&pipeMode, // ������ ��� ����
		NULL,
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("SetNamedPipeHandleState failed\n"));
		return 0;
	}

	LPCTSTR fileName = _T("D:\\news.txt");
	DWORD bytesWritten = 0;

	// ������ �۽�
	isSuccess = WriteFile(
		hPipe, // ���� �������� ����� �ڵ�
		fileName, // ������ ���ϸ�
		(_tcslen(fileName) + 1) * sizeof(TCHAR), // �޽����� ����
		&bytesWritten, // ���� ������ ����Ʈ ��
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