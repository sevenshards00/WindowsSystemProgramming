/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: RaiseException.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: ����Ʈ���� ����(����� ���� ����) ���� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SoftwareException();

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	DWORD DefinedException = 0x00;

	// �ɰ���(31, 30�� ��Ʈ. 11�� ������ ��� �ɰ��� ����)
	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	// MS���� ������ ���� �Ǵ� ����� ���� ���� (29�� ��Ʈ, 1�� ��� ����� ���� ����)
	DefinedException |= 0x01 << 29;

	// ����(Reserved)�� ��Ʈ, �ݵ�� 0�̾�� �ϸ� ���� �� �κ��� �ȳ־ ��
	DefinedException |= 0x00 << 28;

	// ���� �߻� ȯ�� ����(16~27)
	DefinedException |= 0x00 << 16;

	// ���� ������ �����ϱ� ���� �ڵ� (0~15, ������ ������ ����)
	DefinedException |= 0x08;

	__try
	{
		_tprintf(TEXT("Send: exception code: 0x%X \n"), DefinedException);
		RaiseException(
			DefinedException, // �߻� ��ų ������ ����
			0, // ���� �߻� ������ ���� ��Ŀ� ������ �� �� �����ϴ� ����
			NULL, // �߰� ������ ����, ���ٸ� NULL
			NULL // �߰� ������ �����ϱ� ���� ����, ���ٸ� NULL
		);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(TEXT("Recv: exception code : 0x%X\n"), exptType);
	}
}