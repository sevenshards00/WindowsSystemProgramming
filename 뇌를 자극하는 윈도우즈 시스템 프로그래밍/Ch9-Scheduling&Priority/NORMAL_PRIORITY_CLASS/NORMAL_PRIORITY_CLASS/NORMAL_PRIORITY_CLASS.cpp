/*
* Windows System Programming - �����ٸ� �˰���� �켱����
* ���ϸ�: NORMAL_PRIORITY_CLASS.cpp
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
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		//Sleep(10);

		_fputts(_T("NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}