/*
* Windows System Programming - Ŀ�� ������Ʈ�� �ڵ�
* ���ϸ�: OperationStateParent.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: CloseHandle �Լ��� ���μ��� �����ڵ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int main(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	DWORD state;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	TCHAR title[] = _T("OperationStateChild.exe");
	si.lpTitle = title;

	TCHAR command[] = _T("OperationStateChild.exe");

	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	for (DWORD i = 0; i < 10000; i++)
		for (DWORD i = 0; i < 10000; i++); // busy waiting, �ڽ� ���μ����� ���Ḧ ��ٸ�
	
	// WaitForSingleObject(pi.hProcess, INFINITE);
	// �� �Լ��� ����� ��쿡�� �ڽ� ���μ����� ���� �ڵ带 ���������� ��ٸ���.
	// ���� busy waiting�� �������� ���� �����Ƿ� �̰� ����ؼ� Ȯ���ϴ� ���� ����

	// �ڽ� ���μ����� ���� �ڵ带 �ޱ� ���� ����� �Լ�
	GetExitCodeProcess(pi.hProcess, &state);

	if (state == STILL_ACTIVE)
		_tprintf(_T("STILL_ACTIVE\n\n"));
	else
		_tprintf(_T("state: %d\n\n"), state);

	// CloseHandle(pi.hProcess);
	// Ŀ�� ������Ʈ�� Usage Count�� 1 ���ҽ�Ű�� ���.
	// ������ ���μ����� �Ҹ�Ǵ� ���� Ŀ�� ������Ʈ�� Usage Count�� 0�� �Ǿ��� ��.
	// �׸��� ���μ����� ��쿡�� ���μ����� ����Ǵ� �������� Usage Count�� 1 �����Ѵ�.


	return 0;
}