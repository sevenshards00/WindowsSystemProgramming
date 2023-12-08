/*
* Windows System Programming - ���μ��� ���� ����
* ���ϸ�: Calculator2.cpp
* ���� ����: 0.1
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-12-04
* ���� ���� �ۼ� ����:
* ���� ����: ������ �ۼ��ߴ� ���� ���α׷��� ������ �ذ�
* ���� ���� ����:
*/

// ���� scanf�� �ƴ� _tscanf_s�� _fgetts�� �ͼ������߰ڴ�.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// ������ ���� ���� �� ����
enum { DIV = 1, MUL, ADD, MIN, ELSE, EXIT };

// �޴� ��� �Լ� �� ��Ģ���� ���� �Լ� ����
DWORD ShowMenu();
void Divide(double, double);
void Multiple(double, double);
void Add(double, double);
void Min(double, double);

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, }; // STARTUPINFO ����ü�� 0���� �ʱ�ȭ
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION ����ü ����

	si.cb = sizeof(si); // STARTUPINFO ����ü�� ũ�� �ʱ�ȭ
	TCHAR command[] = _T("calc.exe"); // ���μ��� ���� �� ������ ����

	// ���� ���͸� ����(���� ���ô� �ƴ�, �̷����� ���� ������η� ���°� ����)
	// �׸��� ���� �̷��� �� �ʿ䵵 ���� ���� 2��° ���ڷ� �����ϸ� ǥ�� �˻� ��θ� ���ؼ� ã�� ��.
	// �׷��� �ּ�ó���ϰ� �����غ��� �Ȱ��� ����Ǵ� ���� Ȯ�� ������
	SetCurrentDirectory(_T("C:\\WINDOWS\\system32"));

	DWORD sel;
	double num1, num2;
	while (true)
	{
		sel = ShowMenu();
		if (sel == EXIT)
			return 0;

		if (sel != ELSE)
		{
			_fputts(_T("Input Num1, Num2: "), stdout);
			_tscanf(_T("%lf %lf"), &num1, &num2);
		}

		switch (sel)
		{
		case DIV:
			Divide(num1, num2);
			break;
		case MUL:
			Multiple(num1, num2);
			break;
		case ADD:
			Add(num1, num2);
			break;
		case MIN:
			Min(num1, num2);
			break;
		case ELSE:
			ZeroMemory(&pi, sizeof(pi)); // ����ü ������ 0���� �ʱ�ȭ�ϴµ� ����ϴ� �Լ�.
			CreateProcess(
				NULL, command, NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);

			// �� �κ��� �߰��Ǿ�� �Ѵ�.
			// �� �κ��� ������ �Ź� Calc.exe�� ����� ������ Ŀ�� ������Ʈ�� �Ҹ���� �ʰ� �����ȴ�.
			// ���⸦ �����ϴ��� Usage Count�� 0�� �ƴϱ� ������ Ŀ�� ������Ʈ�� �Ҹ���� �ʰ� �����Ǵ� ��.
			// �׷��� �Ϲ������� ���μ��� ������ �䱸�ϰ� ������ �Ǹ� �ٷ� �ڵ��� ��ȯ�Ͽ� Usage Count�� 1 ���ҽ�Ų��.
			CloseHandle(pi.hProcess);
			// ���� ������ ���� ������ �ƴ����� ���μ��� Ŀ�� ������Ʈ�� ���������� �����嵵 Ŀ�� ������Ʈ�� �ִ�.
			// �׷��� ������ ������ ���ϰ� �ǹǷ� �Ȱ��� ó���Ѵ�.
			CloseHandle(pi.hThread);
			break;
		}
	}
	return 0;
}

DWORD ShowMenu()
{
	DWORD sel;

	_fputts(_T("-----Menu-----\n"), stdout);
	_fputts(_T("num 1: Divide\n"), stdout);
	_fputts(_T("num 2: Multiple\n"), stdout);
	_fputts(_T("num 3: Add\n"), stdout);
	_fputts(_T("num 4: Minus\n"), stdout);
	_fputts(_T("num 5: Any other operations.\n"), stdout);
	_fputts(_T("num 6: Exit\n"), stdout);
	_fputts(_T("Select Num >> "), stdout);
	_tscanf(_T("%d"), &sel);

	return sel;
}

void Divide(double a, double b)
{
	_tprintf(_T("%lf / %lf = %lf\n\n"), a, b, a / b);
}

void Multiple(double a, double b)
{
	_tprintf(_T("%lf * %lf = %lf\n\n"), a, b, a * b);
}

void Add(double a, double b)
{
	_tprintf(_T("%lf + %lf = %lf\n\n"), a, b, a + b);
}

void Min(double a, double b)
{
	_tprintf(_T("%lf - %lf = %lf\n\n"), a, b, a - b);
}