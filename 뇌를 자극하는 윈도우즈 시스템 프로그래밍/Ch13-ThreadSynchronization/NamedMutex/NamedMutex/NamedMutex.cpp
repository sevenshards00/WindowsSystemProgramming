/*
* Windows System Programming - ������ ����ȭ ���(1)
* ���ϸ�: NamedMutex.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-08
* ���� ���� �ۼ� ����:
* ���� ����: Ŀ�θ�� ����ȭ ���(3) - NamedMutex ��� ����ȭ ����
* ���� ���� ����:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex; // ���ؽ� ������Ʈ ����
DWORD dwWaitResult; // WaitForSingleObject�� ��ȯ���� �ޱ� ���� ����

//�Ӱ� ����
void ProcessBaseCriticalSection()
{
	// WaitForSingleObject�� ��ȯ���� ���� ����� Ȯ���ϱ� ���� ������ ����
	// Signaled ���¿��� Non-Signaled ���°� �ȴٸ� WAIT_OBJECT_0�� ��ȯ
	// �װ� �ƴ϶�� ���(���ŷ)
	// Ÿ�Ӿƿ��� �����س��Ҵٸ�, Ÿ�Ӿƿ� �ð��� �� ���� �Ŀ��� WAIT_TIMEOUT ��ȯ
	// WAIT_ABANDONED�� ���������� ���ؽ��� ��ȯ�� �̷����� �ʾ��� ��쿡 ��ȯ
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0: // �����尡 ���ؽ��� ������ ���
		_tprintf(TEXT("Thread got mutex\n"));
		break;
	case WAIT_TIMEOUT: // time-out�� �߻��� ���
		_tprintf(TEXT("Time out\n"));
		return;
	case WAIT_ABANDONED: // ���ؽ��� ��ȯ�� �����ϰ� �̷����� ���� ���
		return;
	}

	for (DWORD i = 0; i < 5; i++)
	{
		_tprintf(TEXT("Thread is running: %d\n"), i);
		Sleep(10000);
	}

	ReleaseMutex(hMutex); // Non-Signaled�� �� ���ؽ��� Signaled��
}

int _tmain(int argc, TCHAR* argv[])
{
// ���Ǻ� �������� �����ϴ� �κ�
// 0�̶�� �̸��ִ� ���ؽ�(Named Mutex)�� ����, �ƴ϶�� �̸��ִ� ���ؽ��� �����Ѵ�.
// if 1�� �����ϰ� ���� ��, ���� ���� ���� NamedMutex.exe��
// �׸��� if 0���� ���� �� �����ϰ� ���� ���ϸ��� OpenMutex.exe��
#if 0
	hMutex = CreateMutex(
		NULL,
		FALSE,
		TEXT("NamedMutex")
	);
#else
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS, // ���� ���� ��û, MUTEX_ALL_ACCESS�� �����Ͽ� ���� ������ ��û�Ѵ�.
		FALSE, // ��� ���� ����, ����� ���� �����Ƿ� FALSE
		TEXT("NamedMutex") // ���ؽ��� �̸��� �����Ͽ��ٸ� �ش� �̸��� ���ؽ��� ã�´�. �ִٸ� �ڵ��� ��ȯ�� �ڵ����̺� �ڵ鰪�� �߰��ȴ�.
	);
#endif

	if (hMutex == NULL) // ���ؽ��� ����� �������� �ʾ��� ���
	{
		_tprintf(TEXT("Create Mutex Error: %d\n"), GetLastError());
		return -1;
	}

	// �Ӱ� ������ �Լ� ȣ��
	ProcessBaseCriticalSection();

	// ���ؽ��� �ڵ��� ��ȯ, Usage Count 1����
	CloseHandle(hMutex);
	return 0;
}