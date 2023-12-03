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
	PROCESS_INFORMATION pi; // PROCESS_INFORMATION 구조체
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
	
	TCHAR command[] = _T("AdderProcess.exe 10 20"); // CreateProcess의 두 번째 인자로 전달할 문자열
	TCHAR cDir[DIR_LEN]; // 현재 디렉터리 경로를 저장할 배열
	BOOL state; // 프로세스 생성 성공 여부를 확인하기 위해 사용한 변수

	GetCurrentDirectory(DIR_LEN, cDir); // 현재 디렉터리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("D:\\WinSystem")); // 현재 디렉터리를 지정하는 함수.

	GetCurrentDirectory(DIR_LEN, cDir); // 현재 디렉터리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess(
		// 첫 번째 인자를 NULL로 전달하면 두 번째 인자를 통해서 생성하려는 프로세스의 이름 정보까지 함께 전달 가능
		// 첫 번째 인자로 실행파일의 이름을 전달하는 경우에는 '현재 디렉터리'를 기준으로 실행파일을 찾음
		NULL, 
		// 두 번째 인자로 실행파일의 이름을 전달하는 경우에는 '표준 검색경로' 순서대로 실행파일을 찾아서 프로세스를 생성
		// 추가로 유니코드 버전에서는 _T("AdderProcess.exe 10 20");를 바로 넣으면 런타임 오류가 난다.
		// CreateProcess 함수는 내부적으로 문자열에 변경을 가하기 때문.
		// 함수 호출이 끝날 때는 변경된 문자열을 다시 원래 상태로 돌려놓기 때문에 변경이 되는 것을 인지하기 어려움
		// 그래서 전달인자의 문자열은 반드시 '변수'형태로 전달할 것.
		command, 
		NULL, NULL, TRUE,
		// 특성을 결정하는 인자로, 새로운 콘솔창을 띄울 때 쓰는 전달 인자.
		// 만약 0을 전달한다면 부모 프로세스의 콘솔 윈도우를 자식 프로세스가 공유한다.
		CREATE_NEW_CONSOLE,
		// STARTUPINFO 구조체와 PROCESS_INFORMATION 구조체를 인자로 전달.
		// PROCESS_INFORMAION구조체는 새로 생성되는 프로세스 관련 정보를 얻기 위해 사용.
		NULL, NULL, &si, &pi 
	);

	if (state != 0) // 프로세스 생성이 성공했다면
		_fputts(_T("Creation Success! \n"), stdout);
	else // 실패했다면
		_fputts(_T("Creation Error! \n"), stdout);

	return 0;
}