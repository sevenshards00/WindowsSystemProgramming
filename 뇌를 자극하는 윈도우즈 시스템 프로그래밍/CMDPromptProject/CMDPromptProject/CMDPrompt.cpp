/*
* Windows System Programming - 명령 프롬프트(CMD Prompt) 프로젝트
* 파일명: CMDPrompt.cpp
* 파일 버전: 0.2
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자: 2023-12-02
* 버전 내용: 명령 프롬프트 기능 추가(프로그램 실행)
* 이전 버전 내용: 명령 프롬프트의 골격 작성
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <locale.h> // 한글 입력 처리를 위해 삽입한 헤더파일

#define STR_LEN 256
#define CMD_TOKEN_NUM 10
#define DIR_LEN MAX_PATH+1

// 오류 처리를 위한 전역변수 문자열 선언
TCHAR ERROR_CMD[] = _T("'%s'는 실행할 수 있는 프로그램이 아닙니다.\n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

int _tmain()
{
	// 유니코드 기반 한글 입력을 받기 위한 locale 처리
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit;
	while (1)
	{
		isExit = CmdProcessing(); // 콘솔에서 입력받은 명령어를 처리
		if (isExit == TRUE) // exit 입력에 대해 TRUE가 반환되었다면
		{
			_fputts(_T("명령어 처리를 종료합니다.\n"), stdout); // 프로그램 종료
			break;
		}
	}
	return 0;
}

TCHAR cmdString[STR_LEN];
// 이 부분에 대한 정리를 안해서 개념이 헷갈렸었다.
// 명령어는 하나만 들어오는 것이 아니라 실행할 프로그램 뒤에 옵션이 붙는 경우들이 있다.
// 그런 것들을 고려해서 2차원 배열의 형태로 만든 것.
// 그래서 cmdTokenList[0]은 실행할 파일의 이름이 되는 것이다.
// main에서의 argv로 생각하면 argv[1]이 여기서는 cmdTokenList[0]인 것이다.
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
// 받아들인 명령어를 토큰으로 쪼갤 때 사용할 구분 기준
// 공백문자(' '), 콤마(','), 탭('\t'), 개행('\n')
TCHAR seps[] = _T(" ,\t\n:");

/*
* 함수: TCHAR int CmdProcessing(void)
* 기능: 명령어를 입력받아서 해당 명령어에 지정되어 있는 기능을 수행.
* exit가 입력되면 TRUE를 반환하고 이는 프로그램의 종료로 이어짐.
*/

int CmdProcessing(void)
{
	_fputts(_T("Best command prompt>> "), stdout);
	// gets 계열 함수는 C++14부터 삭제되었음
	// 삭제 이유는 BOF 발생을 유도할 수 있으므로
	// 따라서 _getts도 삭제되었음
	// 아래의 코드로 대체
	_fgetts(cmdString, STR_LEN, stdin);

	// cmdString으로 들어온 명령어를 토큰으로 쪼갠다.
	// 구분자는 위에서 정의한 것들을 기준으로 한다.
	TCHAR* token = _tcstok(cmdString, seps);
	int tokenNum = 0;

	// 토큰으로 쪼개는 과정
	// StrLower 함수를 통해 대소문자 구분을 하지 않게 한다.
	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	// exit를 입력받았을 때
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("추가되는 명령어 1")))
	{
		
	}
	else if (!_tcscmp(cmdTokenList[0], _T("추가되는 명령어 2")))
	{

	}
	else
	{
		STARTUPINFO si = { 0, }; // STARTUPINFO 구조체를 0으로 초기화
		PROCESS_INFORMATION pi; // PROCESS_INFORMATION 구조체
		BOOL state; // 프로세스 생성 성공 여부를 확인하기 위해 사용한 변수

		si.cb = sizeof(si); // STARTUPINFO 구조체의 크기 초기화

		state = CreateProcess(
			NULL, cmdTokenList[0], NULL, NULL,
			TRUE, NULL,	NULL, NULL, &si, &pi
		);

		if (state == 0) // 프로세스 생성이 실패했다면
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		
	}

	return 0;
}

/*
* 함수: TCHAR* StrLower(TCHAR* pStr)
* 기능: 문자열 내에 존재하는 모든 대문자를 소문자로 변경한다.
* 반환 값은 변경된 문자열의 포인터를 반환.
*/

TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	// NULL문자를 읽어들일 때까지 반복
	while (*pStr)
	{
		// 대문자라면
		if (_istupper(*pStr))
			*pStr = _tolower(*pStr); // 소문자로 변경
		pStr++;
	}

	return ret;
}