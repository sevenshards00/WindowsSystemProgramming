/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: OperationStateParent.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: CloseHandle 함수와 프로세스 종료코드 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int main(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	DWORD state;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	TCHAR title[] = _T("OperationStateChild.exe");
	si.lpTitle = title;

	TCHAR command[] = _T("OperationStateChild.exe");

	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	for (DWORD i = 0; i < 10000; i++)
		for (DWORD i = 0; i < 10000; i++); // busy waiting, 자식 프로세스의 종료를 기다림
	
	// WaitForSingleObject(pi.hProcess, INFINITE);
	// 위 함수를 사용할 경우에는 자식 프로세스가 종료 코드를 보낼때까지 기다린다.
	// 위의 busy waiting은 생각보다 빨리 끝나므로 이걸 사용해서 확인하는 것이 나음

	// 자식 프로세스의 종료 코드를 받기 위해 사용한 함수
	GetExitCodeProcess(pi.hProcess, &state);

	if (state == STILL_ACTIVE)
		_tprintf(_T("STILL_ACTIVE\n\n"));
	else
		_tprintf(_T("state: %d\n\n"), state);

	// CloseHandle(pi.hProcess);
	// 커널 오브젝트의 Usage Count를 1 감소시키는 기능.
	// 실제로 프로세스가 소멸되는 것은 커널 오브젝트의 Usage Count가 0이 되었을 때.
	// 그리고 프로세스의 경우에는 프로세스가 종료되는 시점에서 Usage Count가 1 감소한다.


	return 0;
}