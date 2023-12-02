/*
* Windows System Programming - 64��Ʈ ��� ���α׷���
* ���ϸ�: PolymorphicType1.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-02
* ���� ���� �ۼ� ����:
* ���� ����: Windows�� Polymorphic �ڷ����� ���� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// �޸� ������ �Ÿ� ���̸� ����ϱ� ���� �Լ�
UINT64 CalcDistance(UINT64 a, UINT64 b)
{
	return b - a;
}

int _tmain()
{
	INT val1 = 10;
	INT val2 = 20;

	_tprintf(_T("Position %llu, %llu \n"), (UINT64)&val1, (UINT64)&val2);
	_tprintf(_T("Distance: %llu \n"), CalcDistance((UINT64)&val1, (UINT64)&val2));

	return 0;
}