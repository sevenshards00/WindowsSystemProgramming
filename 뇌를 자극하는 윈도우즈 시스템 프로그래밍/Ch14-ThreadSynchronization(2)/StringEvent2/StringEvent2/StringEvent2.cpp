/*
* Windows System Programming - ������ ����ȭ ���(2)
* ���ϸ�: StringEvent2.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-08
* ���� ���� �ۼ� ����:
* ���� ����: �̺�Ʈ ��� ����ȭ ��� - Manual-Reset ��带 Ȱ���� Event ��� ����ȭ ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

// ������ �����忡�� ����� �Լ� ����
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

// main ������, �������� ����
int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	// Event ����
	hEvent = CreateEvent(
		NULL, // ����(���) �Ӽ�, ������� �����Ƿ� NULL
		TRUE, // manual-reset mode��, FALSE�� �ָ� auto-reset mode
		FALSE, // Non-Signaled ���·� ����
		NULL // �̸� ����, ���⼭�� �Ⱦ��Ƿ� NULl
	);

	if (hEvent == NULL) // �̺�Ʈ ���� ���� ��
	{
		_tprintf(TEXT("Event object Creation Error\n"));
		return -1;
	}

	// ������ ����, �Һ���1
	hThread[0] = (HANDLE)_beginthreadex(
		NULL, // ����(���) �Ӽ�, ������� �����Ƿ� NULL
		0, // �������� ���� ũ��, 0���� �� ��� ����Ʈ��(1M)
		OutputThreadFunction, // �����忡�� ������ �Լ�
		NULL, // �Լ��� ������ ����
		0, // ������ ���ÿ� ����, �������ڸ��� �������� �������� CREATE_SUSPENDED �Ӽ�
		(unsigned*)&dwThreadID[0] // �������� ID�� ������ ������ �ּҰ� ����
	);

	// ������ ����, �Һ���2
	hThread[1] = (HANDLE)_beginthreadex(
		NULL, // ����(���) �Ӽ�, ������� �����Ƿ� NULL
		0, // �������� ���� ũ��, 0���� �� ��� ����Ʈ��(1M)
		CountThreadFunction, // �����忡�� ������ �Լ�
		NULL, // �Լ��� ������ ����
		0, // ������ ���ÿ� ����, �������ڸ��� �������� �������� CREATE_SUSPENDED �Ӽ�
		(unsigned*)&dwThreadID[1] // �������� ID�� ������ ������ �ּҰ� ����
	);

	if (hThread[0] == NULL || hThread[1] == NULL) // ������ ���� ���� ��
	{
		_tprintf(TEXT("Thread object Creation Error\n"));
		return -1;
	}


	// ���ڿ��� �Է¹޴´�. (main ������ == ������)
	_fputts(TEXT("Insert string: "), stdout);
	_fgetts(string, 30, stdin);

	// �̺�Ʈ�� Signaled ���·� ����
	SetEvent(hEvent);

	WaitForMultipleObjects(
		2,
		hThread,
		TRUE,
		INFINITE
	);
	CloseHandle(hEvent);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	// Event�� Signaled ���°� �� ������ ������� ���ŷ�� ���°� �ȴ�.
	WaitForSingleObject(hEvent, INFINITE);
	// �׸��� ���� Event�� manual-reset ���� ����
	// WaitForSingleObject �Լ� ȣ�� ���Ŀ��� ��� Signaled ���¸� �����ϰ� ��
	// ���⼭�� ���� ���¸� ������ �ʿ䰡 �����Ƿ� ������ �ʾ����� ������ ������ �ִ� ���� ����
	// Signaled ������ Event�� Non-Signaled�� ����
	// ResetEvent(hEvent);

	// Event�� Signaled ���°� �Ǹ� �Ʒ��� ������ ����

	_fputts(TEXT("Output String: "), stdout);
	_fputts(string, stdout);

	// �Ӱ� ������ ���� ���� �̺�Ʈ�� �ٽ� Signaled ���·� ����
	// SetEvent(hEvent);

	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	// Event�� Signaled ���°� �� ������ ������� ���ŷ�� ���°� �ȴ�.
	WaitForSingleObject(hEvent, INFINITE);
	// �׸��� ���� Event�� manual-reset ���� ����
	// WaitForSingleObject �Լ� ȣ�� ���Ŀ��� ��� Signaled ���¸� �����ϰ� ��
	// ���⼭�� ���� ���¸� ������ �ʿ䰡 �����Ƿ� ������ �ʾ����� ������ ������ �ִ� ���� ����
	// Signaled ������ Event�� Non-Signaled�� ����
	// ResetEvent(hEvent);

	// Event�� Signaled ���°� �Ǹ� �Ʒ��� ������ ����

	_tprintf(TEXT("Output String Length: %lld\n"), _tcslen(string)-1);

	// �Ӱ� ������ ���� ���� �̺�Ʈ�� �ٽ� Signaled ���·� ����
	// SetEvent(hEvent);

	return 0;
}