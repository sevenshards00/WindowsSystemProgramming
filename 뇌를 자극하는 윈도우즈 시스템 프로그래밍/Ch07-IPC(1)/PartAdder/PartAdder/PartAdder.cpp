/*
* Windows System Programming - Ŀ�� ������Ʈ�� ����(State)
* ���ϸ�: PartAdder.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: Ŀ�� ������Ʈ�� ����(State)�� ���� �ڵ�(Exit Code)�� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 3)
		return 1;

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start; i <= end; i++)
		total += i;

	return total;
}