/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: MBCS1.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-01
* ���� ���� �ۼ� ����:
* ���� ����: MBCS�� WBCS�� �⺻���� ����
* ���� ���� ����:
*/

#include <iostream>
#include <cstring>
using std::cout;


int main()
{
	char str[] = "ABC�ѱ�";
	int size = sizeof(str);
	int len = strlen(str);

	cout << "�迭�� ũ��: " << size << '\n';
	cout << "���ڿ� ����: " << len << '\n';

	return 0;
}