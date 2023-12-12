/*
* Windows System Programming - ���� I/O�� ���͸� ��Ʈ��
* ���ϸ�: FileTimeInformation.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-12
* ���� ���� �ۼ� ����:
* ���� ����: ������ �ð� ������ Ȯ���ϴ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt"); // Ȯ���� ���� �̸�

	// ������ �ð� ������ ���� ����
	TCHAR fileCreateTimeInfo[STRING_LEN]; // ���� �ð�
	TCHAR fileAccessTimeInfo[STRING_LEN]; // ���Ͽ� ���������� ������ �ð�
	TCHAR fileWriteTimeInfo[STRING_LEN]; // ���Ͽ� ���������� �����͸� ����(���� ���� ����)�� �ð�

	// ������ �ð� ������ ���� FILETIME ����ü(�ð� ������ ��Ÿ���� 8����Ʈ(DWORD * 2) �ڷ���) ����
	FILETIME ftCreate, ftAccess, ftWrite;

	// FILETIME ����ü�� �ð��� UTC�� �������� ����, �ý����� ���� �ð����� ���߱� ���� ���� ����
	SYSTEMTIME stCreateUTC, stCreateLocal;
	SYSTEMTIME stAccessUTC, stAccessLocal;
	SYSTEMTIME stWriteUTC, stWriteLocal;

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

	// ������ �ð� ���� ����
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
	{
		// �ð� ���� ���� ���� ��
		_tprintf(TEXT("GetFileTime Function call fault\n"));
		return FALSE;
	}

	// ������ �ð� ������ ��ȯ
	// ������ �ð� ������ SYSTEMTIME ����ü�� �ű��.
	// �׸��� SYSTEMTIME ����ü�� �ִ� ������ ���� �ý���(Local) �������� �ٲٴ� ����
	FileTimeToSystemTime(&ftCreate, &stCreateUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stCreateUTC, &stCreateLocal);

	FileTimeToSystemTime(&ftAccess, &stAccessUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stAccessUTC, &stAccessLocal);

	FileTimeToSystemTime(&ftWrite, &stWriteUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stWriteUTC, &stWriteLocal);

	// �ð� ���� ���
	// sprintf �Լ� -> strcat�� �����ϳ�, ���Ŀ� ���缭 ���ڿ��� �������ش�.
	// ù ��° ���ڿ��� ������ ����(�迭)�� ����.
	// ���⼭�� _s�� ���� ���� ����ߴµ�, �� ��° ���ڿ��� ������ ũ��(����)�� ����
	// ������ sizeof(�����̸�)�� ������ ���� �������δ� 200�� ������.
	// �׷��� TCHAR��ŭ ������ 100�� ����.
	_stprintf_s(fileCreateTimeInfo, sizeof(fileCreateTimeInfo)/sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stCreateLocal.wMonth, stCreateLocal.wDay, stCreateLocal.wYear,
		stCreateLocal.wHour, stCreateLocal.wMinute, stCreateLocal.wSecond);

	_stprintf_s(fileAccessTimeInfo, sizeof(fileAccessTimeInfo) / sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stAccessLocal.wMonth, stAccessLocal.wDay, stAccessLocal.wYear,
		stAccessLocal.wHour, stAccessLocal.wMinute, stAccessLocal.wSecond);

	_stprintf_s(fileWriteTimeInfo, sizeof(fileWriteTimeInfo) / sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stWriteLocal.wMonth, stWriteLocal.wDay, stWriteLocal.wYear,
		stWriteLocal.wHour, stWriteLocal.wMinute, stWriteLocal.wSecond);

	_tprintf(TEXT("File Created Time: %s\n"), fileCreateTimeInfo);
	_tprintf(TEXT("File Accessed Time: %s\n"), fileAccessTimeInfo);
	_tprintf(TEXT("File Written Time: %s\n"), fileWriteTimeInfo);

	CloseHandle(hFile);

	return 0;
}