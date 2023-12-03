/*
* Windows System Programming - ��� ������Ʈ(CMD Prompt) ������Ʈ
* ���ϸ�: CMDPrompt.cpp
* ���� ����: 0.2
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-03
* ���� ���� �ۼ� ����: 2023-12-02
* ���� ����: ��� ������Ʈ ��� �߰�(���α׷� ����)
* ���� ���� ����: ��� ������Ʈ�� ��� �ۼ�
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <locale.h> // �ѱ� �Է� ó���� ���� ������ �������

#define STR_LEN 256
#define CMD_TOKEN_NUM 10
#define DIR_LEN MAX_PATH+1

// ���� ó���� ���� �������� ���ڿ� ����
TCHAR ERROR_CMD[] = _T("'%s'�� ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

int _tmain()
{
	// �����ڵ� ��� �ѱ� �Է��� �ޱ� ���� locale ó��
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit;
	while (1)
	{
		isExit = CmdProcessing(); // �ֿܼ��� �Է¹��� ��ɾ ó��
		if (isExit == TRUE) // exit �Է¿� ���� TRUE�� ��ȯ�Ǿ��ٸ�
		{
			_fputts(_T("��ɾ� ó���� �����մϴ�.\n"), stdout); // ���α׷� ����
			break;
		}
	}
	return 0;
}

TCHAR cmdString[STR_LEN];
// �� �κп� ���� ������ ���ؼ� ������ �򰥷Ⱦ���.
// ��ɾ�� �ϳ��� ������ ���� �ƴ϶� ������ ���α׷� �ڿ� �ɼ��� �ٴ� ������ �ִ�.
// �׷� �͵��� ����ؼ� 2���� �迭�� ���·� ���� ��.
// �׷��� cmdTokenList[0]�� ������ ������ �̸��� �Ǵ� ���̴�.
// main������ argv�� �����ϸ� argv[1]�� ���⼭�� cmdTokenList[0]�� ���̴�.
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
// �޾Ƶ��� ��ɾ ��ū���� �ɰ� �� ����� ���� ����
// ���鹮��(' '), �޸�(','), ��('\t'), ����('\n')
TCHAR seps[] = _T(" ,\t\n:");

/*
* �Լ�: TCHAR int CmdProcessing(void)
* ���: ��ɾ �Է¹޾Ƽ� �ش� ��ɾ �����Ǿ� �ִ� ����� ����.
* exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷��� ����� �̾���.
*/

int CmdProcessing(void)
{
	_fputts(_T("Best command prompt>> "), stdout);
	// gets �迭 �Լ��� C++14���� �����Ǿ���
	// ���� ������ BOF �߻��� ������ �� �����Ƿ�
	// ���� _getts�� �����Ǿ���
	// �Ʒ��� �ڵ�� ��ü
	_fgetts(cmdString, STR_LEN, stdin);

	// cmdString���� ���� ��ɾ ��ū���� �ɰ���.
	// �����ڴ� ������ ������ �͵��� �������� �Ѵ�.
	TCHAR* token = _tcstok(cmdString, seps);
	int tokenNum = 0;

	// ��ū���� �ɰ��� ����
	// StrLower �Լ��� ���� ��ҹ��� ������ ���� �ʰ� �Ѵ�.
	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	// exit�� �Է¹޾��� ��
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("�߰��Ǵ� ��ɾ� 1")))
	{
		
	}
	else if (!_tcscmp(cmdTokenList[0], _T("�߰��Ǵ� ��ɾ� 2")))
	{

	}
	else
	{
		STARTUPINFO si = { 0, }; // STARTUPINFO ����ü�� 0���� �ʱ�ȭ
		PROCESS_INFORMATION pi; // PROCESS_INFORMATION ����ü
		BOOL state; // ���μ��� ���� ���� ���θ� Ȯ���ϱ� ���� ����� ����

		si.cb = sizeof(si); // STARTUPINFO ����ü�� ũ�� �ʱ�ȭ

		state = CreateProcess(
			NULL, cmdTokenList[0], NULL, NULL,
			TRUE, NULL,	NULL, NULL, &si, &pi
		);

		if (state == 0) // ���μ��� ������ �����ߴٸ�
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		
	}

	return 0;
}

/*
* �Լ�: TCHAR* StrLower(TCHAR* pStr)
* ���: ���ڿ� ���� �����ϴ� ��� �빮�ڸ� �ҹ��ڷ� �����Ѵ�.
* ��ȯ ���� ����� ���ڿ��� �����͸� ��ȯ.
*/

TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	// NULL���ڸ� �о���� ������ �ݺ�
	while (*pStr)
	{
		// �빮�ڶ��
		if (_istupper(*pStr))
			*pStr = _tolower(*pStr); // �ҹ��ڷ� ����
		pStr++;
	}

	return ret;
}