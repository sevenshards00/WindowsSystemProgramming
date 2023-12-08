/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: namedpipe_server.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: �̸� �ִ� �������� �⺻ ���� �ľ� ���� - ����
* ���� ���� ����:
*/

#define BUF_SIZE 1024

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// Ŭ���̾�Ʈ�� ����ϱ� ���� ������ �Լ�
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	// ���������� �̷��� ������ C++11 ���ķδ� �Ұ���
	// LPTSTR pipeName[] = _T("\\\\.\\pipe\\simple_pipe");
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	// ���� Ŭ���̾�Ʈ�� ���������� �����ϱ� ���� ���� ����
	while (1)
	{
		// ������ ����
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX, // Read, Write ��� ����
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // �޽��� ���
			PIPE_UNLIMITED_INSTANCES, // �ִ� ������ ���� (������ ���� �ʰڴ�)
			BUF_SIZE, // ��� ���� ������
			BUF_SIZE, // �Է� ���� ������
			20000, // Ŭ���̾�Ʈ Time-out
			NULL // ����Ʈ ���� �Ӽ�(���)
		);

		// ������ ���� ������ ���
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreateNamedPipe Failed!\n"));
			return -1;
		}

		BOOL isSuccess = 0;

		// ������ ���� ���� ���θ� 3�� �����ڷ� �Ǵ�
		// �����ߴٸ� TRUE, �������� ��쿡�� �����ڵ带 ERROT_PIPE_CONNECTED�ΰ��� Ȯ��
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess) // ������ ������ �����ƴٸ�
			CommToClient(hPipe); // Ŭ���̾�Ʈ�� ��� ����
		else // �����ߴٸ�
			CloseHandle(hPipe); // �ڵ��� ��ȯ, Usage Count�� 1���δ�.

	}
	return 1;
}

// Ŭ���̾�Ʈ�� ����� �ϴ� �κ�
int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	// ������ �ڵ��� ���� �����͸� ���Ź޴´�.
	isSuccess = ReadFile(
		hPipe, // ������ �ڵ�
		fileName, // read ���� ����
		MAX_PATH * sizeof(TCHAR), // read ���� ������
		&fileNameSize, // ������ �������� ���� ũ��
		NULL);

	// ������ ������ �����߰ų� �����Ͱ� ���� ���
	if (!isSuccess || fileNameSize == 0)
	{
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	_tprintf(_T("%s %d\n"), fileName, fileNameSize);
	// ������ ����, �б����.
	FILE* filePtr = _tfopen(fileName, _T("r"));
	_tprintf(_T("%p\n"), filePtr);
	if (filePtr == NULL) // ���� ���濡 �������� ���
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	// EOF�� ���� ������ ������ �о���δ�
	while (!feof(filePtr))
	{
		// fread �Լ��� ���� �����͸� �о���δ�.
		// 1 * 1024 ����Ʈ��ŭ ����
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(
			hPipe, // ������ �ڵ�
			dataBuf, // ������ ������ ����
			bytesRead, // ������ ������ ũ��
			&bytesWritten, // ���� ���۵� ������ ũ��
			NULL);

		// ������ ������ ũ��� ���� ���۵� ������ ũ�Ⱑ �ٸ� ���
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