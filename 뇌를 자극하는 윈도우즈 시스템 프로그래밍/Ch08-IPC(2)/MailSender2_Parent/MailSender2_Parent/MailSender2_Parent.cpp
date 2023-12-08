/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: MailSender2_Parent.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: ���Ͻ���(MailSlot) �ڵ��� ��� Ȯ�ο� ���� - �θ� ���μ���
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

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

	SECURITY_ATTRIBUTES sa; // ���� �Ӽ�(��Ӱ� ���õ� �Ӽ�) ����ü ����
	sa.nLength = sizeof(sa); // ����ü�� ũ��
	sa.lpSecurityDescriptor = NULL; // ��� ���������� �ǹ̰� ����
	sa.bInheritHandle = TRUE; // ��� ���θ� ���� ���� ���. TRUE�� �����ؾ� ����� �ȴ�.

	// mailslot�� �޽����� �����ϱ� ���� ������ ��Ʈ�� ����
	hMailSlot = CreateFile(
		SLOT_NAME, // ���� ������ �ּ�, �� �ش� �ּ��� ���Ͻ����� �����Ѵ�.
		GENERIC_WRITE, // ���� ���
		FILE_SHARE_READ, // ������ ���� ���, ���⼭�� ���� �б� ���� ����
		&sa, // ���� �Ӽ� ����, �ڵ� ��Ӱ� �����ִ� �κ�. ���⼭�� ����� ���� ������ sa ���
		OPEN_EXISTING, // ������ ������ ����. ���ٸ� �Լ� ȣ�� ����. Receiver�� ���� ���Ͻ����� �����Ǿ� �ִ� ��Ȳ.
		FILE_ATTRIBUTE_NORMAL, // ������ �Ӽ�. ���ٸ� Ư���� ���� ���� ����. �Ϲ������� �̰� ���ٰ� ���� ��.
		NULL // ������ �����ϴ� ���ϰ� ������ Ư���� ������ �� ������ ���鶧 ���Ǵ� ���� ����. �Ϲ������� NULL ���.
	); // �Լ� ȣ���� �����ϸ� ������ �ڵ��� ��ȯ��.

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot stream!\n"), stdout);
		return 1;
	}

	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot); // ���� ����� �ڵ� ���
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt")); // ������ ����. �ؽ�Ʈ ���� �ۼ�
	_ftprintf(file, _T("%d"), hMailSlot); // �ڵ��� ���Ͽ� ���
	fclose(file); // ��Ʈ�� ����

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSender2_Child.exe");

	// �ڵ��� ����� ���μ��� ����
	CreateProcess(NULL, command, NULL, NULL,
		TRUE, // �ڵ� ���̺��� ����ϰڴ�
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi);

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