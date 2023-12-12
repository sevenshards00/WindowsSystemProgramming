/*
* Windows System Programming - ���� I/O�� ���͸� ��Ʈ��
* ���ϸ�: Set_Get_FileAttributes.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-12
* ���� ���� �ۼ� ����:
* ���� ����: ������ Ư�� ���� ���� �� �����ϴ� ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt"); // Ȯ���� ���� �̸�

	_tprintf(TEXT("Original file attributes\n"));
	DWORD attrib = GetFileAttributes(fileName);
	ShowAttributes(attrib);
	
	// OR ����(|)�� ���� ������ �Ӽ��� ����
	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	// ����� �Ӽ��� ����
	SetFileAttributes(fileName, attrib);

	_tprintf(TEXT("Changed file attributes\n"));
	attrib = GetFileAttributes(fileName);
	ShowAttributes(attrib);

	return 0;
}

void ShowAttributes(DWORD attrib)
{
	// AND(&) ������ ���� ������ �Ӽ��� ���Ѵ�.
	// �Ϲ� �����̶�� �ٸ� Ư���� ���� ������ ���Ѵ�.
	// OS������ �⺻������ ������ FILE_ATTRIBUTE_NORMAL�� �����ص� FILE_ATTRIBUTE_ARCHIVE �Ӽ��� �ο��Ѵ�.
	// �׷��� �Ʒ� �Ӽ��� ������ �ʴ´�.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
		_tprintf(TEXT("FILE_ATTRIBUTE_NORMAL OR FILE_ATTRIBUTE_ARCHIVE\n"));
	else
	{
		// �б� ���� �Ӽ��� ���� ���
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(TEXT("FILE_ATTRIBUTE_READONLY\n"));
		// ���� ���� �Ӽ��� ���� ���
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(TEXT("FILE_ATTRIBUTE_HIDDEN\n"));
	}
		
	_tprintf(TEXT("\n"));
}