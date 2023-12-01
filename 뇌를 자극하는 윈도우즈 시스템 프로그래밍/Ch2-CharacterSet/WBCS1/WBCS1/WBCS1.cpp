/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: WBCS1.cpp
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
	wchar_t str_w[] = L"ABC"; // WBCS (Wide Byte Character Set)
	char str_s[] = "ABC"; // SBCS (Single Byte Character Set)
	int size_w = sizeof(str_w);
	int size_s = sizeof(str_s);
	int len_w = wcslen(str_w); // strlen�� �ƴ϶� wcslen
	int len_s = strlen(str_s);

	cout << "WBCS �迭�� ũ��: " << size_w << '\n';
	cout << "WBCS ���ڿ� ����: " << len_w << '\n';
	cout << "SBCS �迭�� ũ��: " << size_s << '\n';
	cout << "WBCS ���ڿ� ����: " << len_s << '\n';

	return 0;
}