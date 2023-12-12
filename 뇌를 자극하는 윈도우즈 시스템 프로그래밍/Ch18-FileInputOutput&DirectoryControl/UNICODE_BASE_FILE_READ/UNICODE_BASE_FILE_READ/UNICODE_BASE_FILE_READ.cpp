/*
* Windows System Programming - ���� I/O�� ���͸� ��Ʈ��
* ���ϸ�: UNICODE_BASE_FILE_READ.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-12
* ���� ���� �ۼ� ����:
* ���� ����: �����ڵ� ����� ���� ����� ����(2)
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt");
	TCHAR fileData[STRING_LEN];

	HANDLE hFile = CreateFile(
		fileName, // ����(Open)�� ���� �̸��� ����
		GENERIC_READ, // �б�/���� ��带 ����. ���⼭�� �б� ���. or(|) �������� ���� ����
		FILE_SHARE_READ, // ������ ���� ��带 ����
		0, // ����(���) �Ӽ� ����
		OPEN_EXISTING, // ������ ���� �Ǵ� ���� �� ����ϴ� ����
		FILE_ATTRIBUTE_NORMAL, // ������ Ư�� ���� ����. �Ϲ� �����̶�� FILE_ATTRIBUTE_NORMAL�� ��������� ���
		0 // ������ �����ϴ� ���ϰ� ������ Ư���� ������ �� ������ ���� �� ����ϴ� ����. �Ϲ������� NULL ����.
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Creation Failed\n"));
		return -1;
	}

	DWORD numOfByteRead = 0;
	ReadFile(
		hFile, // �����͸� ������ ������ �ڵ��� ����
		fileData, // �����͸� �����ϰ� �ִ� ������ �ּҸ� ����
		sizeof(fileData), // ���Ͽ� �����ϰ��� �ϴ� ������ ũ�⸦ ����Ʈ ������ ����
		&numOfByteRead, // ������ ����� ������ ũ�⸦ ��� ���� ������ �ּ� ����
		NULL // OverLapped ����, �񵿱� I/O�� ����
	);

	fileData[numOfByteRead / sizeof(TCHAR)] = '\0'; // ���ڿ��� �о���̱� ���� �������� �� ���� �Է�

	_tprintf(TEXT("Read data size: %u\n"), numOfByteRead);
	_tprintf(TEXT("Read String: %s\n"), fileData);
	CloseHandle(hFile);

	return 0;
}