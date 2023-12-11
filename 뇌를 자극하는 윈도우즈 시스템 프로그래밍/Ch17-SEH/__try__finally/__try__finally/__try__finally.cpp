/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: __try__finally.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: �⺻���� ���� �ڵ鷯 ����
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	int a, b;
	// __try ~ __finally (���� �ϳ��� �̷��)
	// try ���
	// ���ܹ߻� ���� ���� + ����ó�� ���� ������ġ(�󸶳� �ǳʶ� ���ΰ�)�� ���
	// try ��Ͽ��� ���������� �Ǵ� ��ǥ���� ��Ȳ = return, continue, break, goto, "���ܻ�Ȳ"
	__try
	{
		_tprintf(TEXT("Input Num to Divide [ a / b ]: "));
		_tscanf(TEXT("%d / %d"), &a, &b);

		if (b == 0)
			return -1;
	}
	// finally ���
	// try ����� �� ���̶� �����ϰ� �Ǹ� �ݵ�� finally ����� ����
	// finally ����� ����� �� return���� ���� ��ȯ�Ǵ� ���� �����Ϸ��� ����� �ӽú����� ����
	// �׸��� finally ����� �����ϰ� �� �ڿ� return�� ����ȴ�
	__finally
	{
		_tprintf(TEXT("__finally blocked\n"));
	}

	_tprintf(TEXT("result: %d\n"), a / b);

	return 0;
}