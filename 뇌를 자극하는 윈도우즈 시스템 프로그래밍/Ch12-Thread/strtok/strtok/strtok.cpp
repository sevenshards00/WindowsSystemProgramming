/*
* Windows System Programming - �������� ������ �Ҹ�
* ���ϸ�: strtok.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-07
* ���� ���� �ۼ� ����:
* ���� ����: ���ڿ��� ��ū���� ������ strtok_s ��� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// ���ڿ� ���� �� ������ ���� �̾ �ۼ��ص� �ϳ��� ���ڿ��� �ȴ�.
	TCHAR string[] =
		TEXT("Hey, get a life!")
		TEXT("You don't even have two pennies to rub together.");
	// strtok_s�� ���ؼ� �и��� ���� ���� ���ڿ��� ���� ����
	TCHAR* context = NULL;

	// ��ū(token)���� �ɰ��� ���� ����(������, Separator)�� ����.
	TCHAR seps[] = TEXT(" ,.!");

	// ��ū �и� ����, ���ڿ� ���� �� ù ��° ��ū ��ȯ
	// �׷��� ù token���� Hey�� ����.
	TCHAR* token = _tcstok_s(string, seps, &context);

	// �ݺ����� ���� ��ū�� ��� ���
	while(token != NULL)
	{
		_tprintf(TEXT("%s\n"), token);
		token = _tcstok_s(NULL, seps, &context);
	}

	return 0;
}