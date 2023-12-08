/*
* Windows System Programming - ���μ��� �� ���(Inter-Process Communication, IPC)
* ���ϸ�: MailSender2_Child.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-05
* ���� ���� �ۼ� ����:
* ���� ����: ���Ͻ���(MailSlot) �ڵ��� ��� Ȯ�ο� ���� - �ڽ� ���μ���
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; // mailslot �ڵ�
	TCHAR message[50];
	DWORD bytesWritten; // �� ����Ʈ�� �о��°� Ȯ��
	
	// �ڵ��� ��� �κ�
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Inheritable Handle: %d\n"), hMailSlot);

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
			_gettchar();
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