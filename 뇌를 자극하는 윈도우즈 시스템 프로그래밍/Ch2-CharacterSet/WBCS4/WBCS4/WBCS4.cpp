/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: WBCS4.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-01
* ���� ���� �ۼ� ����:
* ���� ����: MBCS�� WBCS�� �⺻���� ����
* ���� ���� ����:
*/

#include <iostream>

// main�� �ƴ϶� wmain
// ���޵Ǵ� ���ڿ��� �����ڵ� ������� �����ϰڴٴ� �ǹ�
// char* argv[] -> wchar_t* argv[]�� ����
int wmain(int argc, wchar_t* argv[]) 
{
	// 1���� �����ϹǷ� �������� ���� ����
	for (int i = 1; i < argc; i++)
	{
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}

	return 0;
}