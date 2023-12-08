/*
* Windows System Programming - ���μ��� ���� ����
* ���ϸ�: AdderProcess.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-03
* ���� ���� �ۼ� ����:
* ���� ����: ���μ����� �����ϴ� ������ ���� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD val1, val2;
	// _ttoi�� MBCS ����̸� atoi, �����ڵ� ����̸� _wtoi�� ȣ��
	// ���������� ���� �����ϴ� �Լ�.
	val1 = _ttoi(argv[1]);
	val2 = _ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d\n"), val1, val2, val1 + val2);

	// getchar�� ���������� MBCS ����̸� getchar, �����ڵ� ����̸� getwchar �Լ��� ȣ��
	// ���� ������ ���� �����ϴ� �Լ�.
	// ���α׷��� ������ ��� ���߱� ���ؼ� ���
	_gettchar();
	return 0;
}