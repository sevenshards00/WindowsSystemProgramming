/*
* Windows System Programming - 64��Ʈ ��� ���α׷���
* ���ϸ�: PolymorphicType2.cpp
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
UINT_PTR CalcDistance(UINT_PTR a, UINT_PTR b)
{
	// 32��Ʈ���
	//return a-b;
	return b - a;
}

int _tmain()
{
	INT val1 = 10;
	INT val2 = 20;
	
	_tprintf(_T("Distance: %u \n"), CalcDistance((UINT_PTR)&val1, (UINT_PTR)&val2));

	return 0;
}