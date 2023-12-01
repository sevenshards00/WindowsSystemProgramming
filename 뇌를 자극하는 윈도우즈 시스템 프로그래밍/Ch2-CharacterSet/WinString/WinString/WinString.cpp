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
#include <windows.h>

int wmain(int argc, wchar_t* argv[])
{
	// ������ ���� å�̶� ������ C++���� �Ʒ��� �ڵ�� �Ұ���
	// 
	// LPSTR str1 = "SBCS Style String 1";
	// LPWSTR str2 = L"WBCS Styple String 1";
	// 
	// ���� C++�� ���ڿ� ���ͷ��� char*�� �ƴ� const char*�� ó���ϱ� ����
	LPCSTR str1 = "SBCS Style String 1";
	LPCWSTR str2 = L"WBCS Styple String 1";

	CHAR arr1[] = "SBCS Style String 2";
	WCHAR arr2[] = L"WBCS Style String 2";

	LPCSTR cStr = arr1;
	LPCWSTR wStr = arr2;

	printf("%s\n", str1);
	printf("%s\n", arr1);

	wprintf(L"%s\n", str2);
	wprintf(L"%s\n", arr2);



	return 0;
}