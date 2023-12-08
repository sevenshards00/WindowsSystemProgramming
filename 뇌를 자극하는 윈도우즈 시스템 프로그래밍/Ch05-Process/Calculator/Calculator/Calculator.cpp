/*
* Windows System Programming - 프로세스 생성 예제
* 파일명: Calculator.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자:
* 버전 내용: 프로세스를 생성하는 간단한 예제(2) - 계산기 프로그램
* 이전 버전 내용:
*/

// 이제 scanf가 아닌 _tscanf_s나 _fgetts에 익숙해져야겠다.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 열거형 변수 선언 및 정의
enum { DIV = 1, MUL, ADD, MIN, ELSE, EXIT };

// 메뉴 출력 함수 및 사칙연산 관련 함수 선언
DWORD ShowMenu();
void Divide(double, double);
void Multiple(double, double);
void Add(double, double);
void Min(double, double);

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, }; // STARTUPINFO 구조체를 0으로 초기화
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION 구조체 생성
	
	si.cb = sizeof(si); // STARTUPINFO 구조체의 크기 초기화
	TCHAR command[] = _T("calc.exe"); // 프로세스 생성 시 전달할 인자
	
	// 현재 디렉터리 지정(좋은 예시는 아님, 이럴때는 차라리 완전경로로 쓰는게 나음)
	// 그리고 굳이 이렇게 줄 필요도 없는 것이 2번째 인자로 전달하면 표준 검색 경로를 통해서 찾게 됨.
	// 그래서 주석처리하고 실행해보면 똑같이 실행되는 것을 확인 가능함
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
			ZeroMemory(&pi, sizeof(pi)); // 구조체 변수를 0으로 초기화하는데 사용하는 함수.
			CreateProcess(
				NULL, command, NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);
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