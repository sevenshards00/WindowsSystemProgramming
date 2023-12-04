/*
* Windows System Programming - ��� ������Ʈ(CMD Prompt) ������Ʈ
* ���ϸ�: CMDPrompt.cpp
* ���� ����: 0.3
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����: 2023-12-03
* ���� ����: echo, start ��ɾ� �߰�
* ���� ���� ����: ��� ������Ʈ ��� �߰�(���α׷� ����)
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

// ����� �������� ���� �� ����

// ���� ó���� ���� �������� ���ڿ� ����
TCHAR ERROR_CMD[] = _T("'%s'�� ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");
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

// �Լ� �����
int CmdProcessing(int);
int CmdReadTokenize(void);
TCHAR* StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[])
{
	// �����ڵ� ��� �ѱ� �Է��� �ޱ� ���� locale ó��
	_tsetlocale(LC_ALL, _T("Korean"));

	// �Է¹��� ������ ���� 2���� ū �����
	// ��, CMDPrompt start�� ��� argc�� 2�� �ȴ�.
	// argv[0]�� ���α׷���(==CMDPrompt.exe), argv[1](==start)�� ��ɾ �ȴ�.
	// �ڿ� ���ڰ� �� �ִٸ� 2���� ū ��Ȳ
	if (argc > 2)
	{
		for(int i=1; i<argc;i++)
			_tcscpy(cmdTokenList[i - 1], argv[i]); // ���� �������� ���α׷����� �� �ʿ䰡 �����Ƿ� ������ ���� ó��
		CmdProcessing(argc - 1); // ���α׷����� ������ �ǹǷ� ���� ī��Ʈ�� -1�� �� ��
	}

	DWORD isExit;
	while (1)
	{
		int tokenNum = CmdReadTokenize();

		if (tokenNum == 0) // �ƹ��� �Է��� ���ٸ� (EnterŰ�� ������ ���)
			continue; // ��� �ݺ�

		isExit = CmdProcessing(tokenNum); // �ֿܼ��� �Է¹��� ��ɾ ó��
		if (isExit == TRUE) // exit �Է¿� ���� TRUE�� ��ȯ�Ǿ��ٸ�
		{
			_fputts(_T("��ɾ� ó���� �����մϴ�.\n"), stdout); // ���α׷� ����
			break;
		}
	}
	return 0;
}

/*
* �Լ�: int CmdReadTokenize(void)
* ���: CmdProcessing�� �ִ� �Է¹��� ��ɾ ��ū���� �ɰ��� ������ ������ �Լ��� �и�.
* ������ CmdProcessing�� ��ɾ��� �Է°� ��ɾ��� ó���� ���ÿ� �����߾���.
* ���⼭�� �Է¹��� ��¾ ��ū���� �ɰ��� ������ ����
*/

int CmdReadTokenize(void)
{
	TCHAR* token; // �Է� ���� ���ڿ��� ������ ��ū���� ������ ������ ����

	_fputts(_T("Best command prompt>> "), stdout);
	// gets �迭 �Լ��� C++14���� �����Ǿ���
	// ���� ������ BOF �߻��� ������ �� �����Ƿ�
	// ���� _getts�� �����Ǿ���
	// �Ʒ��� �ڵ�� ��ü
	_fgetts(cmdString, STR_LEN, stdin);

	// cmdString���� ���� ��ɾ ��ū���� �ɰ���.
	// �����ڴ� ������ ������ �͵��� �������� �Ѵ�.
	token = _tcstok(cmdString, seps);
	int tokenNum = 0;

	// ��ū���� �ɰ��� ����
	// StrLower �Լ��� ���� ��ҹ��� ������ ���� �ʰ� �Ѵ�.
	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum; // ��ū�� ����(�� ���ڿ��� ����) ��ȯ
}

/*
* �Լ�: int CmdProcessing(int tokenNum)
* ���: CmdReadTokenize�� ���� �Է¹��� ��ɾ ó���ϴ� �Լ�.
* ������ ���¿��� �Է��� void������ �Է°����� tokenNum�� �޵��� ����
* exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷��� ����� �̾���.
*/

int CmdProcessing(int tokenNum)
{
	// ���μ��� ������ ���� ������
	// ��� ��ɾ� ���̽����� ������ ������ �� �����Ƿ� �Լ� ��ü ��Ͽ��� ����� �� �ֵ��� ��ġ�� �̵�

	STARTUPINFO si; // STARTUPINFO ����ü
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION ����ü
	BOOL state; // ���μ��� ���� ���� ���θ� Ȯ���ϱ� ���� ����� ����

	// ZeroMemory �Լ� - ����ü ������ ����� 0���� �ʱ�ȭ�ϴµ� ����ϴ� �Լ�
	// ������ ����ü '������' ������ 0���� �ʱ�ȭ�Ѵٰ� �߸� �����ص״�.
	// �ش� ���� �ּ��� �����صѰ�.
	// �ٵ� ���߿� �������� �׳� si = {0,}�̳� pi= {0,}�� �� ���� ���� �ִ�.
	ZeroMemory(&si, sizeof(si)); // si�� 0���� �ʱ�ȭ�ϴµ� ����ϴ� �Լ�.
	ZeroMemory(&pi, sizeof(pi)); // pi�� 0���� �ʱ�ȭ�ϴµ� ����ϴ� �Լ�.

	si.cb = sizeof(si); // STARTUPINFO ����ü�� ũ�� �ʱ�ȭ
	
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, }; // ��ɾ� �ڿ� �߰� �ɼ��� �ִ� ��ɾ ������ �迭, 0���� �ʱ�ȭ
	TCHAR optString[STR_LEN] = { 0, }; // �߰� �ɼ��� ����� �迭, 0���� �ʱ�ȭ

	// exit�� �Է¹޾��� ��
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	// start�� �Է¹��� ���
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) 
	{
		// tokenNum�� 1 �̻��̴� -> start �ڿ� �߰����� ��ɾ �Էµƴ�.
		if (tokenNum > 1)
		{
			// start(cmdTokenList[0])�� ������ ���ڿ��� �����Ѵ�.
			// ���� ��� start echo test 123�� �ԷµǾ��� ġ�� start�� ������ echo test 123�� �����.
			for (int i = 1; i < tokenNum; i++)
				// ���� �����ߴ� ����� strcat�� �̿��Ͽ� ��ġ�� ����̾���.
				// ���� �ɸ��� �κ��� ��Ȯ�� "echo test 123 "�� �ȴٴ� ��
				// _tcscat(optString, cmdTokenList[i]);
				// _tcscat(optString, _T(" ")); // ���� ����

				// ���ڰ� �� �κ��� sprintf�� ����ߴµ�, ���� ���� �������� �ִ����� ������.
				// ù ��° ���ڷδ� ����(���) ���, �׸��� �� ��° ���ڿ��� ����� ������ �����Ѵ�.
				// printf�� ���������� 2��° ���ڿ��� ������ ������ ����ŭ ���ڸ� �߰��Ѵ�.
				// �� ����� ���� �������� ������ ������ �����鼭 ������ �� �������� ���� ����.
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);

			// ���⼭�� ��ü ������ ����� �ش�.
			// ������ start�� �Ʊ� ���� echo test 123�� ��ġ�� �ȴ�.
			// ���⼭�� start�� �� ���α׷� �� ��ü�̹Ƿ� "CMDPromptProject.exe"�� �ȴ�.
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CMDPromptProject.exe"), optString);
		}
		// �װ� �ƴ϶�� start�� �Է¹��� ��Ȳ
		else
			// cmdStringWithOptions�� CMDPromptProject.exe ���ڿ��� ����(���).
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CMDPromptProject.exe"));
		
		state = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
			TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	// echo�� �Է¹��� ���
	// �Է� ���� ���ڿ��� �״�� ����ϴ� ��ɾ��.
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		// echo�� ������ �Է¹��� ���ڿ��� ����ؾ� �ϹǷ� optString�� �Ʊ�ó�� �����.
		// ���� ��� echo Hello World!��� �ϸ� Hello World!�� ��µǸ� �ȴ�.

		for (int i = 1; i < tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		
		// �״�� ȭ�鿡 ����ϸ� ��
		// ������ ���μ����� �ƴ� '��ɾ�'�̹Ƿ� ���μ����� ������ �ʿ䰡 ����.
		_tprintf(_T("%s\n"), optString);
	}
	else // �� ���� ���
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]); // �Է¹��� ù ��° ��ɾ�(�Ǵ� ���α׷���)�� �����Ѵ�.
		
		// ���� ��� ���ͳ� �ͽ��÷η��� ������ ��, iexplore.exe www.naver.com�̶�� �ϸ� �ٷ� ���̹��� ���ӵȴ�.
		// �̿� ���� ��츦 ó���ϱ� ���ؼ� �ڿ� �߰��� �ٴ� ���ڿ��� ó���Ѵ�. 
		for (int i = 1; i < tokenNum; i++)
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		
		// ���μ��� ����
		state = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
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