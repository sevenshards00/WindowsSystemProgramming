/*
* Windows System Programming - ���μ��� ���� ����
* ���ϸ�: CreateProcess.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-03
* ���� ���� �ۼ� ����:
* ���� ����: ���μ����� �����ϴ� ������ ���� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1 // ���͸� ����� �ִ� ���̸� ��ũ�η� ����

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, }; // STARTUPINFO ����ü�� 0���� �ʱ�ȭ
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION ����ü
	TCHAR npTitle[] = _T("New Process!"); // ���ο� ���μ����� �ܼ� �������� Ÿ��Ʋ�� ����� ���ڿ�
	
	// STARTUPINFO ����ü�� ��� ���� �ʱ�ȭ
	si.cb = sizeof(si); // ����ü ������ ũ��, ���������� ����ϴ� ���� ũ��.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE; // �ݿ��ϰ��� �ϴ� ����� ���� ���� ����
	si.dwX = 100; // �ܼ��� ��ġ (X��)
	si.dwY = 200; // �ܼ��� ��ġ (Y��)
	si.dwXSize = 300; // �ܼ��� ũ��(X��)
	si.dwYSize = 200; // �ܼ��� ũ��(Y��)
	/*
	* C++ 11 ���ķ� char* �� const char* �� ����Ű�� ���� �Ұ�����.
	* ��� C������ ���ڿ��� char*�� ����Ű�� ���� �ƴ϶� const char*�� ����Ű�� ���� ����.
	* ���� ���ڿ� ���ͷ��� const char*�̹Ƿ� å�� �ִ� ���� �ڵ�� �״�� ��� �Ұ���
	* si.lpTitle = _T("New Process!");
	* _T("New Process!")�� const wchar_t* �ε�, lpTitle�� ���� LPWSTR(wchar_t*)�̴�.
	* �׷��� ���� ���ο� ���μ����� �ܼ� �������� Ÿ��Ʋ�� ����� ���ڿ��� �迭�� �־���.
	*/ 
	si.lpTitle = npTitle; // ���ο� ���μ����� �ܼ� â���� �� Ÿ��Ʋ �� ����
	
	TCHAR command[] = _T("AdderProcess.exe 10 20"); // CreateProcess�� �� ��° ���ڷ� ������ ���ڿ�
	TCHAR cDir[DIR_LEN]; // ���� ���͸� ��θ� ������ �迭
	BOOL state; // ���μ��� ���� ���� ���θ� Ȯ���ϱ� ���� ����� ����

	GetCurrentDirectory(DIR_LEN, cDir); // ���� ���͸� Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("D:\\WinSystem")); // ���� ���͸��� �����ϴ� �Լ�.

	GetCurrentDirectory(DIR_LEN, cDir); // ���� ���͸� Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess(
		// ù ��° ���ڸ� NULL�� �����ϸ� �� ��° ���ڸ� ���ؼ� �����Ϸ��� ���μ����� �̸� �������� �Բ� ���� ����
		// ù ��° ���ڷ� ���������� �̸��� �����ϴ� ��쿡�� '���� ���͸�'�� �������� ���������� ã��
		NULL, 
		// �� ��° ���ڷ� ���������� �̸��� �����ϴ� ��쿡�� 'ǥ�� �˻����' ������� ���������� ã�Ƽ� ���μ����� ����
		// �߰��� �����ڵ� ���������� _T("AdderProcess.exe 10 20");�� �ٷ� ������ ��Ÿ�� ������ ����.
		// CreateProcess �Լ��� ���������� ���ڿ��� ������ ���ϱ� ����.
		// �Լ� ȣ���� ���� ���� ����� ���ڿ��� �ٽ� ���� ���·� �������� ������ ������ �Ǵ� ���� �����ϱ� �����
		// �׷��� ���������� ���ڿ��� �ݵ�� '����'���·� ������ ��.
		command, 
		NULL, NULL, TRUE,
		// Ư���� �����ϴ� ���ڷ�, ���ο� �ܼ�â�� ��� �� ���� ���� ����.
		// ���� 0�� �����Ѵٸ� �θ� ���μ����� �ܼ� �����츦 �ڽ� ���μ����� �����Ѵ�.
		CREATE_NEW_CONSOLE,
		// STARTUPINFO ����ü�� PROCESS_INFORMATION ����ü�� ���ڷ� ����.
		// PROCESS_INFORMAION����ü�� ���� �����Ǵ� ���μ��� ���� ������ ��� ���� ���.
		NULL, NULL, &si, &pi 
	);

	if (state != 0) // ���μ��� ������ �����ߴٸ�
		_fputts(_T("Creation Success! \n"), stdout);
	else // �����ߴٸ�
		_fputts(_T("Creation Error! \n"), stdout);

	return 0;
}