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

// �޸� ������ �Ÿ� ���̸� ����ϱ� ���� �Լ� (x64, 64��Ʈ)
UINT64 CalcDistance(UINT64 a, UINT64 b)
{
	return b - a;
}

// �޸� ������ �Ÿ� ���̸� ����ϱ� ���� �Լ� (x86, 32��Ʈ)
UINT CalcDistance(UINT a, UINT b)
{
	return a - b;
}

int _tmain()
{
	INT val1 = 10;
	INT val2 = 20;

	// x86, 32��Ʈ ȯ��
	_tprintf(_T("Position %u, %u \n"), (UINT)&val1, (UINT)&val2);
	_tprintf(_T("Distance: %u \n"), CalcDistance((UINT)&val1, (UINT)&val2));

	// x64, 64��Ʈ ȯ��
	_tprintf(_T("Position %llu, %llu \n"), (UINT64)&val1, (UINT64)&val2);
	_tprintf(_T("Distance: %llu \n"), CalcDistance((UINT64)&val1, (UINT64)&val2));

	return 0;
}