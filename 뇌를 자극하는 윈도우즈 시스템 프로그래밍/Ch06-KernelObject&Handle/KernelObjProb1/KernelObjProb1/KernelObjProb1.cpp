/*
* Windows System Programming - Ŀ�� ������Ʈ�� �ڵ�
* ���ϸ�: KernelObjProb1.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: CloseHandle �Լ� ��� ����
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

	TCHAR command[] = _T("KernelObjProb2.exe");
	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		0, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);

	return 0;
}