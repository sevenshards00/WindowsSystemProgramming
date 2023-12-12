/*
* Windows System Programming - ���� I/O�� ���͸� ��Ʈ��
* ���ϸ�: UNICODE_BASE_FILE_IO.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-12
* ���� ���� �ۼ� ����:
* ���� ����: �����ڵ� ����� ���� ����� ����(1)
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt");
	TCHAR fileData[] = TEXT("Test String");

	HANDLE hFile = CreateFile(
		fileName, // ����(Open)�� ���� �̸��� ����
		GENERIC_WRITE, // �б�/���� ��带 ����. ���⼭�� ���� ���. or(|) �������� ���� ����
		FILE_SHARE_WRITE, // ������ ���� ��带 ����
		0, // ����(���) �Ӽ� ����
		CREATE_ALWAYS, // ������ ���� �Ǵ� ���� �� ����ϴ� ����
		FILE_ATTRIBUTE_NORMAL, // ������ Ư�� ���� ����. �Ϲ� �����̶�� FILE_ATTRIBUTE_NORMAL�� ��������� ���
		0 // ������ �����ϴ� ���ϰ� ������ Ư���� ������ �� ������ ���� �� ����ϴ� ����. �Ϲ������� NULL ����.
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Creation Failed\n"));
		return -1;
	}

	DWORD numOfByteWritten = 0;
	WriteFile(
		hFile, // �����͸� ������ ������ �ڵ��� ����
		fileData, // �����͸� �����ϰ� �ִ� ������ �ּҸ� ����
		sizeof(fileData), // ���Ͽ� �����ϰ��� �ϴ� ������ ũ�⸦ ����Ʈ ������ ����
		&numOfByteWritten, // ������ ����� ������ ũ�⸦ ��� ���� ������ �ּ� ����
		NULL // OverLapped ����, �񵿱� I/O�� ����
	);

	_tprintf(TEXT("Written data size: %u\n"), numOfByteWritten);
	CloseHandle(hFile);

	return 0;
}