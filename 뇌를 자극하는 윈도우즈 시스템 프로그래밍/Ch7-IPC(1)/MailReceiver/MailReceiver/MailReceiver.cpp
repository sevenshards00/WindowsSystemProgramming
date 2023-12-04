/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: MailReceiver.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: ���Ͻ���(MailSlot)�� ��� ���� - Receiver
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// ����� ���Ͻ����� �ּ�
// \\computerName\mailslot\[path]name
// �Ʒ��� �ּҴ� \\.\mailslot\mailbox��� �� �Ͱ� ����.
// ���⼭ '.'�� �ǹ��ϴ� ���� ���� ��ǻ��, �� �� ��ǻ�͸� ���Ѵ�.
// �������� 127.0.0.1�� ���ٰ� ���� �ȴ�.
#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; // mailslot �ڵ�
	TCHAR messageBox[50];
	DWORD bytesRead; // �� ����Ʈ�� �о��°� Ȯ��

	// mailslot ����
	hMailSlot = CreateMailslot(
		SLOT_NAME, // ���� ������ �̸�, �� �ּҸ� �����ϴ� ��
		0, // ���� ������ ���� ũ�� ����, 0�� �����ϸ� �ý����� ����ϴ� �ִ� ũ��� ����
		MAILSLOT_WAIT_FOREVER, // ���Ͻ����� ���� �о���� �����Ͱ� ä���� ������ ��ٸ��� ���ŷ(Blocking) Ÿ�Ӿƿ� ����
		NULL // ���� �Ӽ� ������ ���, ��Ȯ���� �ڵ��� ��Ӱ� ������ ����.
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n\n"), stdout);
		return 1;
	}

	// Message ����
	_fputts(_T("******** Message ********\n"), stdout);
	while (1)
	{
		// ReadFile �Լ��� ���� ���Ͻ������� ���޵� �����͸� �д´�.
		// ���� ���Ϸκ��� �����͸� �о���� �� ����ϴ� �Լ��ε�, ���⼭�� ���Ͻ������κ��� �����͸� �д´�.
		if(!ReadFile(hMailSlot, // ���Ͻ����� �ڵ��� ���ڷ� ����. �����̶�� ������ �ڵ��� ���ڷ� �����Ѵ�.
			messageBox, // �о� ���� �����͸� ������ ���۸� ����
			sizeof(TCHAR) * 50, // �о���� �������� �ִ� ũ�⸦ ���� 
			&bytesRead, // ������ �о���� ������ ũ�⸦ ����Ʈ ������ �����ϱ� ���� ������ �ּҸ� ����
			NULL)) // ����� ���� ����ϱ� �����Ƿ� NULL�� �����Ѵٰ� ����
		{
			_fputts(_T("Unable to read!\n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(messageBox, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}

		messageBox[bytesRead / sizeof(TCHAR)] = 0; // �������� NULL ���� ����
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot);

	return 0;
}