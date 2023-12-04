/*
* Windows System Programming - 커널 오브젝트와 핸들
* 파일명: KernelObjShare.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: 커널 오브젝트는 여러 프로세스에서 접근 가능함을 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("Operation2.exe");

	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		0, NULL, NULL, &si, &pi);

	// 타이밍이라는 변수를 둔다.
	DWORD timing = 0;

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); // Busy Waiting

		_fputts(_T("Parent\n"), stdout);

		// Busy waiting을 하는 사이에 증가한다.
		timing += 1;
		if (timing == 2) // 2가 되면
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS); // 우선순위를 낮춘다.
	}
	return 0;
}