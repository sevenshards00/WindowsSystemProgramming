/*
* Windows System Programming - Ŀ�� ������Ʈ�� �ڵ�
* ���ϸ�: OperationStateChild.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: CloseHandle �Լ��� ���μ��� �����ڵ� ����
* ���� ���� ����:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>

int main(int argc, TCHAR* argv[])
{
	float num1, num2;
	_fputts(_T("Return Value Test\n"), stdout);
	_tscanf(_T("%f %f"), &num1, &num2);

	if (num2 == 0)
		exit(-1); // �Ǵ� return -1;

	_tprintf(_T("Operation Result: %f\n"), num1 / num2);
	
	return 1;
}