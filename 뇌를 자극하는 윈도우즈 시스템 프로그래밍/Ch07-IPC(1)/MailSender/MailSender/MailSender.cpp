/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: MailSender.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: ���Ͻ���(MailSlot)�� ��� ���� - Sender
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
	TCHAR message[50];
	DWORD bytesWritten; // �� ����Ʈ�� �о��°� Ȯ��

	// mailslot�� �޽����� �����ϱ� ���� ������ ��Ʈ�� ����
	hMailSlot = CreateFile(
		SLOT_NAME, // ���� ������ �ּ�, �� �ش� �ּ��� ���Ͻ����� �����Ѵ�.
		GENERIC_WRITE, // ���� ���
		FILE_SHARE_READ, // ������ ���� ���, ���⼭�� ���� �б� ���� ����
		NULL, // ���� �Ӽ� ����, �ڵ� ��Ӱ� �����ִ� �κ�. ���⼭�� ����Ʈ �Ӽ� ������ ���� NULL ���
		OPEN_EXISTING, // ������ ������ ����. ���ٸ� �Լ� ȣ�� ����. Receiver�� ���� ���Ͻ����� �����Ǿ� �ִ� ��Ȳ.
		FILE_ATTRIBUTE_NORMAL, // ������ �Ӽ�. ���ٸ� Ư���� ���� ���� ����. �Ϲ������� �̰� ���ٰ� ���� ��.
		NULL // ������ �����ϴ� ���ϰ� ������ Ư���� ������ �� ������ ���鶧 ���Ǵ� ���� ����. �Ϲ������� NULL ���.
	); // �Լ� ȣ���� �����ϸ� ������ �ڵ��� ��ȯ��.

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot stream!\n"), stdout);
		return 1;
	}

	// Message �۽�
	while (1)
	{
		// ���ڿ��� �Է¹޴´�.
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		// WriteFile �Լ��� ���� ���Ͻ������� �����͸� �����Ѵ�.
		if (!WriteFile(hMailSlot, // �����͸� ������ ������ �����Ѵ�. ���⼭�� �����͸� ���Ͻ��Կ� �����Ѵ�(������).
			message, // ������ �����Ͱ� ����Ǿ� �ִ� ���۸� �����Ѵ�.
			_tcslen(message) * sizeof(TCHAR), // ������ ������ ũ�⸦ ����
			&bytesWritten, // �Լ� ȣ�� �Ϸ� �� ���۵� ���� �������� ũ�⸦ ����Ʈ ������ ��� ���� ������ �ּҸ� ����.
			NULL)) // ReadFile�� ���������� ����� NULL�� �ִ´ٰ� �˾Ƶд�.
		{
			_fputts(_T("Unable to write!\n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(message, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}
	}

	CloseHandle(hMailSlot);

	return 0;
}