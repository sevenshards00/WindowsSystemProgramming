/*
* Windows System Programming - 프로세스 생성 예제
* 파일명: CreateProcess.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자:
* 버전 내용: 프로세스를 생성하는 간단한 예제 구현
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1 // 디렉터리 경로의 최대 길이를 매크로로 선언

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, }; // STARTUPINFO 구조체를 0으로 초기화
	PROCESS_INFORMATION pi;
	TCHAR npTitle[] = _T("New Process!"); // 새로운 프로세스의 콘솔 윈도우의 타이틀에 사용할 문자열
	
	// STARTUPINFO 구조체의 멤버 변수 초기화
	si.cb = sizeof(si); // 구조체 변수의 크기, 형식적으로 사용하는 것이 크다.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE; // 반영하고자 하는 멤버에 대한 정보 설정
	si.dwX = 100; // 콘솔의 위치 (X축)
	si.dwY = 200; // 콘솔의 위치 (Y축)
	si.dwXSize = 300; // 콘솔의 크기(X축)
	si.dwYSize = 200; // 콘솔의 크기(Y축)
	/*
	* C++ 11 이후로 char* 로 const char* 를 가리키는 것을 불가능함.
	* 사실 C에서도 문자열은 char*로 가리키는 것이 아니라 const char*로 가리키는 것이 맞음.
	* 따라서 문자열 리터럴은 const char*이므로 책에 있는 예제 코드는 그대로 사용 불가능
	* si.lpTitle = _T("New Process!");
	* _T("New Process!")는 const wchar_t* 인데, lpTitle의 형은 LPWSTR(wchar_t*)이다.
	* 그래서 위에 새로운 프로세스의 콘솔 윈도우의 타이틀에 사용할 문자열을 배열에 넣었다.
	*/ 
	si.lpTitle = npTitle; // 새로운 프로세스의 콘솔 창에서 쓸 타이틀 바 제목
	
	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir); // 현재 디렉터리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("D:\\WinSystem"));

	GetCurrentDirectory(DIR_LEN, cDir); // 현재 디렉터리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess(
		NULL,
		command,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi
	);

	if (state != 0)
		_fputts(_T("Creation Success! \n"), stdout);
	else
		_fputts(_T("Creation Error! \n"), stdout);

	return 0;
}