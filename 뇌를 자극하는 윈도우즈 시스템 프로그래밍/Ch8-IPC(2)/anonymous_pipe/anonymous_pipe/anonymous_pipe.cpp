/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: anonymous_pipe.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: �̸� ���� �������� �⺻ ���� �ľ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hReadPipe, hWritePipe; // pipe handle, �Է°� ��� �� 2���� �ڵ��� �ʿ��ϴ�

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	// ������ ����
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	// �������� ���� ���� �̿��� ������ �۽�(Write)
	WriteFile(
		hWritePipe, // �������� �̸�
		sendString, // Write�� �������� ����
		_tcslen(sendString) * sizeof(TCHAR), // Write�� �������� ũ��
		&bytesWritten, // ������ Write�� �������� ũ�⸦ ������ ������ �ּ�
		NULL);
	
	_tprintf(_T("string send: %s\n"), sendString);

	// �������� �ٸ� ���� ���� �̿��� ������ ����(Read)
	ReadFile(
		hReadPipe, // �������� �̸�
		recvString, // Read�� �������� ����
		bytesWritten, // Read�� �������� ũ��
		&bytesRead, // ������ Read�� �������� ũ�⸦ ������ ������ �ּ�
		NULL);

	recvString[bytesRead / sizeof(TCHAR)] = '\0'; // �������� �� ���� �߰�
	_tprintf(_T("string recv: %s\n"), recvString);

	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	return 0;
}