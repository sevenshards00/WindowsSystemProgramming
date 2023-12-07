/*
* Windows System Programming - �����ٸ� �˰���� �켱����
* ���ϸ�: ABOVE_NORMAL_PRIORITY_CLASS.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-07
* ���� ���� �ۼ� ����:
* ���� ����: �켱������ ������ �����ٸ� �˰����� ����Ǵ� ���� Ȯ���ϴ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// �켱���� NORMAL_PRIORITY_CLASS�� �ο��� �ڽ� ���μ���
	STARTUPINFO si_Normal = { 0, };
	PROCESS_INFORMATION pi_Normal = { 0, };
	TCHAR cmdNormal[] = _T("NORMAL_PRIORITY_CLASS.exe");

	// �켱���� BELOW_NORMAL_PRIORITY_CLASS�� �ο��� �ڽ� ���μ���
	STARTUPINFO si_Below = { 0, };
	PROCESS_INFORMATION pi_Below = { 0, };
	TCHAR cmdBelow[] = _T("BELOW_NORMAL_PRIORITY_CLASS.exe");

	si_Normal.cb = sizeof(si_Normal);
	si_Below.cb = sizeof(si_Below);

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);


	// �ڽ� ���μ��� ����
	CreateProcess(
		NULL,cmdNormal, NULL, NULL, TRUE,
		0, NULL, NULL, &si_Normal, &pi_Normal);

	CreateProcess(
		NULL, cmdBelow, NULL, NULL, TRUE,
		0, NULL, NULL, &si_Below, &pi_Below);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		//Sleep(10);

		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}