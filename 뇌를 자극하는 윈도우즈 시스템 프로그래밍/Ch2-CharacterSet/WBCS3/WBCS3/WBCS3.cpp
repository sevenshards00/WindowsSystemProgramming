/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: WBCS2.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-01
* ���� ���� �ۼ� ����:
* ���� ����: MBCS�� WBCS�� �⺻���� ����
* ���� ���� ����:
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < argc; i++)
		fputws(argv[i], stdout); // ���⿡�� ������ ���� �߻�, ������ Ÿ���� ��ġ���� ����

	return 0;
}