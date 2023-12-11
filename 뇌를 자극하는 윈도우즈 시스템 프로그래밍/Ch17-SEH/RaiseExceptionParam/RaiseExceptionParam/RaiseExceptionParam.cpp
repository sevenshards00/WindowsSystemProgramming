/*
* Windows System Programming - ������ ����ó��(Structured Exception Handling, SEH)
* ���ϸ�: RaiseExceptionParam.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-11
* ���� ���� �ۼ� ����:
* ���� ����: RaiseException �Լ��� 3, 4��° ���� ���� GetExceptionInformation()�� ���� ������ �� ������ ��� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// �����(������) ���� ����
#define STATUS_DEFAULT_USER_DEFINED_EXPT ((DWORD) 0xE0000008L)

void SoftwareException();
DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr);

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(TEXT("End of the _tmain\n"));

	return 0;
}

void SoftwareException()
{
	CONST TCHAR* exptString[] = {
		TEXT("Exception String One"),
		TEXT("Exception String Two"),
		TEXT("Exception String Three")
	};

	__try
	{
		RaiseException(
			STATUS_DEFAULT_USER_DEFINED_EXPT, // �߻� ��ų ������ ����
			0, // ���� �߻� ������ ���� ��Ŀ� ������ �� �� �����ϴ� ����
			3, // �߰� ������ ����, ���ٸ� NULL
			(ULONG_PTR*)exptString // �߰� ������ �����ϱ� ���� ����, ���ٸ� NULL
		);
		_tprintf(TEXT("Working!\n"));
	}
	// ���� ������ �ڸ����� �Լ��� �͵� �ȴ�.
	// ��, ��ȯ���� �������� ���� ǥ�����ϰ�.
	__except (FilterFunction(GetExceptionInformation())) 
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(TEXT("Recv: exception code : 0x%X\n"), exptType);
	}
}

DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr)
{
	PEXCEPTION_RECORD exptRecord = exptPtr->ExceptionRecord;

	switch (exptRecord->ExceptionCode)
	{
	case STATUS_DEFAULT_USER_DEFINED_EXPT:
		_tprintf(TEXT("Exception code: 0x%X\n"), exptRecord->ExceptionCode);
		_tprintf(TEXT("Exception flags: %d\n"), exptRecord->ExceptionFlags);
		_tprintf(TEXT("Exception param num: %d\n"), exptRecord->NumberParameters);
		_tprintf(TEXT("String One: %s\n"), exptRecord->ExceptionInformation[0]);
		_tprintf(TEXT("String Two: %s\n"), exptRecord->ExceptionInformation[1]);
		_tprintf(TEXT("String Three: %s\n"), exptRecord->ExceptionInformation[2]);
		break;
	default:
		break;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}