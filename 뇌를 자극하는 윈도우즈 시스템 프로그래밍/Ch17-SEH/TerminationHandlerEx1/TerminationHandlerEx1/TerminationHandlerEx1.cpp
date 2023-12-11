/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: TerminationHandlerEx1.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ���� �ڵ鷯�� Ȱ�� ����(1)
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int ReadStringAndWrite(void);

int _tmain(int argc, TCHAR* argv[])
{
	int state = 0;

	while (1)
	{
		state = ReadStringAndWrite();
		if (state == -1)
		{
			_tprintf(TEXT("Some Exception Occurred!\n"));
			break;
		}

		if (state == 0)
		{
			_tprintf(TEXT("Jobs Done!\n"));
			break;
		}
	}

	return 0;
}

int ReadStringAndWrite(void)
{
	FILE* fPtr = NULL;
	TCHAR* strBufPtr = NULL;

	__try
	{
		// ���� ����
		fPtr = _tfopen(TEXT("string.dat"), TEXT("a+t"));
		if (fPtr == NULL)
			return -1;

		DWORD strLen = 0;
		_tprintf(TEXT("Input String Length(0 to exit): "));
		_tscanf(TEXT("%d"), &strLen);

		if (strLen == 0)
			return 0;

		// �Է¹��� ���ڿ��� �����ϱ� ���� �޸� ���� �Ҵ�
		strBufPtr = (TCHAR*)malloc(sizeof(TCHAR) * strLen + 1);
		if (strBufPtr == NULL)
			return -1;

		_tprintf(TEXT("Input String:"));
		_tscanf(TEXT("%s"), strBufPtr);


		_ftprintf(fPtr, TEXT("%s\n"), strBufPtr);
	}
	__finally
	{
		// ���� �߻� �� �����ߴ� ������ �ݴ´�
		if (fPtr != NULL)
			fclose(fPtr);

		// ���� �߻� �� �Ҵ��� �޸𸮸� �����Ѵ�
		if (strBufPtr != NULL)
			free(strBufPtr);
	}

	return 1;
}