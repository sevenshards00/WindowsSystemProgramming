/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: MBCS2.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-01
* ���� ���� �ۼ� ����:
* ���� ����: MBCS�� WBCS�� �⺻���� ����
* ���� ���� ����:
*/

#include <iostream>
using std::cout;


int main()
{
	char str[] = "�ѱ��Դϴ�";
	int i;

	for (i = 0; i < 5; i++)
		fputc(str[i], stdout);
		// c++�� ���ٸ�
		// cout << str[i];

	fputs("\n", stdout);

	for (i = 0; i < 10; i++)
		fputc(str[i], stdout);
		// c++�� ���ٸ�
		// cout << str[i];

	fputs("\n", stdout);
	return 0;
}