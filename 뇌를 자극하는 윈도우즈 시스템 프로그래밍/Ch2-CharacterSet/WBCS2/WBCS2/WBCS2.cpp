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

#include <iostream>
#include <cstring>

int main()
{
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	wprintf(L"Array Size: %d\n", size);
	wprintf(L"String Length: %d\n", len);

	return 0;
}