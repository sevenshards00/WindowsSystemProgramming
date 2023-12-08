/*
* Windows System Programming - Ŀ�� ������Ʈ�� �ڵ�
* ���ϸ�: KernelObjShare.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: Ŀ�� ������Ʈ�� ���� ���μ������� ���� �������� Ȯ���ϴ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("Operation2.exe");

	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		0, NULL, NULL, &si, &pi);

	// Ÿ�̹��̶�� ������ �д�.
	DWORD timing = 0;

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		_fputts(_T("Parent\n"), stdout);

		// Busy waiting�� �ϴ� ���̿� �����Ѵ�.
		timing += 1;
		if (timing == 2) // 2�� �Ǹ�
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS); // �켱������ �����.
	}
	return 0;
}