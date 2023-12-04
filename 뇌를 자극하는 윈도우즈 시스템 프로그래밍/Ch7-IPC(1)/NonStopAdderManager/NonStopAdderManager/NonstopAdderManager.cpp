/*
* Windows System Programming - 커널 오브젝트의 상태(State)
* 파일명: NonstopAdderManager.cpp
* 파일 버전: 0.2
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: 커널 오브젝트의 상태(State)를 확인하는 방식으로 문제를 해결한 코드
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1 = { 0, };
	PROCESS_INFORMATION pi2 = { 0, };

	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE,
		0, NULL, NULL, &si1, &pi1);
	CreateProcess(NULL, command2, NULL, NULL, TRUE,
		0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);


	// 자식 프로세스가 진짜로 종료될 때까지 블로킹 상태로 대기.
	// 다시 말해서 non-signaled 상태에서 signaled 상태가 되었을 때의 커널 오브젝트 상태를 보겠다는 것.
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	// 연산 결과에 해당하는 종료코드를 반환하고 종료할 것이라는 가정을 가지고 진행
	// 하지만 실제 결과는 STILL_ACTIVE였기 때문에 55가 아닌 518이라는 결과값이 나옴
	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)
		return -1;

	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("Total: %d\n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}