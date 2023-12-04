/*
* Windows System Programming - 명령 프롬프트(CMD Prompt) 프로젝트
* 파일명: CMDPrompt.cpp
* 파일 버전: 0.3
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자: 2023-12-03
* 버전 내용: echo, start 명령어 추가
* 이전 버전 내용: 명령 프롬프트 기능 추가(프로그램 실행)
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

// 사용할 전역변수 선언 및 정의

// 오류 처리를 위한 전역변수 문자열 선언
TCHAR ERROR_CMD[] = _T("'%s'는 실행할 수 있는 프로그램이 아닙니다.\n");
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

// 함수 선언부
int CmdProcessing(int);
int CmdReadTokenize(void);
TCHAR* StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[])
{
	// 유니코드 기반 한글 입력을 받기 위한 locale 처리
	_tsetlocale(LC_ALL, _T("Korean"));

	// 입력받은 인자의 수가 2보다 큰 경우라면
	// 즉, CMDPrompt start의 경우 argc는 2가 된다.
	// argv[0]은 프로그램명(==CMDPrompt.exe), argv[1](==start)은 명령어가 된다.
	// 뒤에 인자가 더 있다면 2보다 큰 상황
	if (argc > 2)
	{
		for(int i=1; i<argc;i++)
			_tcscpy(cmdTokenList[i - 1], argv[i]); // 현재 실행중인 프로그램명은 들어갈 필요가 없으므로 다음과 같이 처리
		CmdProcessing(argc - 1); // 프로그램명은 빠지게 되므로 실제 카운트는 -1을 한 값
	}

	DWORD isExit;
	while (1)
	{
		int tokenNum = CmdReadTokenize();

		if (tokenNum == 0) // 아무런 입력이 없다면 (Enter키만 눌렀을 경우)
			continue; // 계속 반복

		isExit = CmdProcessing(tokenNum); // 콘솔에서 입력받은 명령어를 처리
		if (isExit == TRUE) // exit 입력에 대해 TRUE가 반환되었다면
		{
			_fputts(_T("명령어 처리를 종료합니다.\n"), stdout); // 프로그램 종료
			break;
		}
	}
	return 0;
}

/*
* 함수: int CmdReadTokenize(void)
* 기능: CmdProcessing에 있던 입력받은 명령어를 토큰으로 쪼개는 과정을 별도의 함수로 분리.
* 기존의 CmdProcessing은 명령어의 입력과 명령어의 처리를 동시에 수행했었음.
* 여기서는 입력받은 명력어를 토큰으로 쪼개는 과정을 수행
*/

int CmdReadTokenize(void)
{
	TCHAR* token; // 입력 받은 문자열을 각각의 토큰으로 나눠서 저장할 변수

	_fputts(_T("Best command prompt>> "), stdout);
	// gets 계열 함수는 C++14부터 삭제되었음
	// 삭제 이유는 BOF 발생을 유도할 수 있으므로
	// 따라서 _getts도 삭제되었음
	// 아래의 코드로 대체
	_fgetts(cmdString, STR_LEN, stdin);

	// cmdString으로 들어온 명령어를 토큰으로 쪼갠다.
	// 구분자는 위에서 정의한 것들을 기준으로 한다.
	token = _tcstok(cmdString, seps);
	int tokenNum = 0;

	// 토큰으로 쪼개는 과정
	// StrLower 함수를 통해 대소문자 구분을 하지 않게 한다.
	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum; // 토큰의 갯수(총 문자열의 갯수) 반환
}

/*
* 함수: int CmdProcessing(int tokenNum)
* 기능: CmdReadTokenize에 의해 입력받은 명령어를 처리하는 함수.
* 기존의 형태에서 입력이 void였으나 입력값으로 tokenNum을 받도록 변경
* exit가 입력되면 TRUE를 반환하고 이는 프로그램의 종료로 이어짐.
*/

int CmdProcessing(int tokenNum)
{
	// 프로세스 생성에 사용될 변수들
	// 모든 명령어 케이스별로 변수를 지정할 수 없으므로 함수 전체 블록에서 사용할 수 있도록 위치를 이동

	STARTUPINFO si; // STARTUPINFO 구조체
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION 구조체
	BOOL state; // 프로세스 생성 성공 여부를 확인하기 위해 사용한 변수

	// ZeroMemory 함수 - 구조체 변수의 멤버를 0으로 초기화하는데 사용하는 함수
	// 이전에 구조체 '포인터' 변수를 0으로 초기화한다고 잘못 정리해뒀다.
	// 해당 파일 주석은 수정해둘것.
	// 근데 나중에 귀찮으면 그냥 si = {0,}이나 pi= {0,}이 더 편할 수도 있다.
	ZeroMemory(&si, sizeof(si)); // si를 0으로 초기화하는데 사용하는 함수.
	ZeroMemory(&pi, sizeof(pi)); // pi를 0으로 초기화하는데 사용하는 함수.

	si.cb = sizeof(si); // STARTUPINFO 구조체의 크기 초기화
	
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, }; // 명령어 뒤에 추가 옵션이 있는 명령어를 저장할 배열, 0으로 초기화
	TCHAR optString[STR_LEN] = { 0, }; // 추가 옵션이 저장될 배열, 0으로 초기화

	// exit를 입력받았을 때
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	// start를 입력받은 경우
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) 
	{
		// tokenNum이 1 이상이다 -> start 뒤에 추가적인 명령어가 입력됐다.
		if (tokenNum > 1)
		{
			// start(cmdTokenList[0])를 제외한 문자열을 추출한다.
			// 예를 들어 start echo test 123가 입력되었다 치면 start를 제외한 echo test 123을 만든다.
			for (int i = 1; i < tokenNum; i++)
				// 내가 생각했던 방식은 strcat을 이용하여 합치는 방식이었다.
				// 현재 걸리는 부분은 정확히 "echo test 123 "이 된다는 것
				// _tcscat(optString, cmdTokenList[i]);
				// _tcscat(optString, _T(" ")); // 공백 문자

				// 저자가 쓴 부분은 sprintf를 사용했는데, 답을 보기 전까지는 있는지도 몰랐다.
				// 첫 번째 인자로는 저장(출력) 대상, 그리고 두 번째 인자에는 저장될 포맷을 지정한다.
				// printf와 마찬가지로 2번째 인자에서 정해진 포맷의 수만큼 인자를 추가한다.
				// 이 방식을 쓰면 마지막에 공백이 생기지 않으면서 다음의 한 문장으로 끝이 난다.
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);

			// 여기서는 전체 문장을 만들어 준다.
			// 명렁어인 start와 아까 만든 echo test 123을 합치면 된다.
			// 여기서의 start는 이 프로그램 그 자체이므로 "CMDPromptProject.exe"가 된다.
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CMDPromptProject.exe"), optString);
		}
		// 그게 아니라면 start만 입력받은 상황
		else
			// cmdStringWithOptions에 CMDPromptProject.exe 문자열을 저장(출력).
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CMDPromptProject.exe"));
		
		state = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
			TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	// echo를 입력받은 경우
	// 입력 받은 문자열을 그대로 출력하는 명령어다.
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		// echo를 제외한 입력받은 문자열만 출력해야 하므로 optString만 아까처럼 만든다.
		// 예를 들면 echo Hello World!라고 하면 Hello World!만 출력되면 된다.

		for (int i = 1; i < tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		
		// 그대로 화면에 출력하면 끝
		// 별도의 프로세스가 아닌 '명령어'이므로 프로세스를 생성할 필요가 없다.
		_tprintf(_T("%s\n"), optString);
	}
	else // 그 외의 경우
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]); // 입력받은 첫 번째 명령어(또는 프로그램명)을 복사한다.
		
		// 예를 들어 인터넷 익스플로러를 실행할 때, iexplore.exe www.naver.com이라고 하면 바로 네이버로 접속된다.
		// 이와 같은 경우를 처리하기 위해서 뒤에 추가로 붙는 문자열도 처리한다. 
		for (int i = 1; i < tokenNum; i++)
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		
		// 프로세스 생성
		state = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
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