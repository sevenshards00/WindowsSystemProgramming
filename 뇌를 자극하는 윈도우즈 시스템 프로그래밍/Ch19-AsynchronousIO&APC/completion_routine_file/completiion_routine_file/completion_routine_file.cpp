/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: completion_routine_file.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 파일 기반의 확장 I/O 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

TCHAR strData[] =
TEXT("Nobody was farther off base than the pundits who said \n")
TEXT("Royal Liverpool was outdated and not worthy of hosting ~ \n")
TEXT("for the first time since 1967. The Hoylake track ~ \n")
TEXT("Here's the solution to modern golf technology -- firm, \n")
TEXT("fast firways, penal bunkers, firm greens and, with any ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = (TEXT("data.txt"));
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File creation fault!\n"));
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;
	WriteFileEx(hFile, strData, sizeof(strData), & overlappedInst, FileIOCompletionRoutine);

	SleepEx(INFINITE, TRUE);

	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransferred, LPOVERLAPPED overlapped)
{
	_tprintf(TEXT("**********File write result**********\n"));
	_tprintf(TEXT("Error code: %u\n"), errorCode);
	_tprintf(TEXT("Transferred bytes len: %u\n"), numOfBytesTransferred);
	_tprintf(TEXT("The other info: %u\n"), (DWORD)overlapped->hEvent);
}