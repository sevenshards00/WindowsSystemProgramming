/*
* Windows System Programming - Ŀ�� ������Ʈ�� �ڵ�
* ���ϸ�: KernelObjProb2.cpp
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
	DWORD n = 0;
	while (n < 100)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy waiting

		_fputts(_T("KernelObjProb2.exe\n"), stdout);
		n++;
	}

	return 0;
}