/*
* Windows System Programming - ���� ��(Character Set)
* ���ϸ�: MBCS_WBCS1.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-01
* ���� ���� �ۼ� ����:
* ���� ����: MBCS�� WBCS�� �⺻���� ����
* ���� ���� ����:
*/

// warning �޽����� ���´�
// �⺻������ .NET �����Ϸ������� �ش� ��ũ�θ� �⺻���� �������ֱ� ����.
#define UNICODE
#define _UNICODE

// MBCS ������� �������ϰڴٸ� �Ʒ��� �����ڷ� ���ǵ� ��ũ�θ� ��ȿȭ�ϸ� �ȴ�.
// #undef UNICODE
// #undef _UNICODE

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int wmain()
{
	TCHAR str[] = _T("1234567");
	int size = sizeof(str);
	printf("string length: %d\n", size);

	return 0;
}