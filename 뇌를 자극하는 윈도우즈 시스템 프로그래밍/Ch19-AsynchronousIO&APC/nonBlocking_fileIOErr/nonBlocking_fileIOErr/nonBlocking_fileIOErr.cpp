/*
* Windows System Programming - 비동기 I/O와 APC
* 파일명: nonBlocking_fileIOErr.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 비동기 파일 I/O 오류가 있는 예제 - 파일 위치 정보 고려 안했을 때
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

TCHAR strData1[] = TEXT("Nobody was farther off base than the pundits who said \n");
TCHAR strData2[] = TEXT("Royal Liverpool was outdated and not worthy of hosting ~ \n");
TCHAR strData3[] = TEXT("for the first time since 1967. The Hoylake track ~ \n");
TCHAR strData4[] = TEXT("Here's the solution to modern golf technology -- firm, \n");
TCHAR strData5[] = TEXT("fast fairways, penal bunkers, firm greens and, with any ~\n");

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

	OVERLAPPED overlappedInstOne;
	memset(&overlappedInstOne, 0, sizeof(overlappedInstOne));
	overlappedInstOne.hEvent = (HANDLE)"First I/O";
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstTwo, 0, sizeof(overlappedInstTwo));
	overlappedInstTwo.hEvent = (HANDLE)"Second I/O";
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstTwo, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstThree;
	memset(&overlappedInstThree, 0, sizeof(overlappedInstThree));
	overlappedInstThree.hEvent = (HANDLE)"Third I/O";
	WriteFileEx(hFile, strData3, sizeof(strData3), &overlappedInstThree, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstFour;
	memset(&overlappedInstFour, 0, sizeof(overlappedInstFour));
	overlappedInstFour.hEvent = (HANDLE)"Fourth I/O";
	WriteFileEx(hFile, strData4, sizeof(strData4), &overlappedInstFour, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstFive;
	memset(&overlappedInstFive, 0, sizeof(overlappedInstFive));
	overlappedInstFive.hEvent = (HANDLE)"Fifth I/O";
	WriteFileEx(hFile, strData5, sizeof(strData5), &overlappedInstFive, FileIOCompletionRoutine);

	SleepEx(INFINITE, TRUE);

	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransferred, LPOVERLAPPED overlapped)
{
	_tprintf(TEXT("**********File write result**********\n"));
	_tprintf(TEXT("Error code: %u\n"), errorCode);
	_tprintf(TEXT("Transferred bytes len: %u\n"), numOfBytesTransferred);
	_tprintf(TEXT("The other info: %s\n"), (TCHAR*)overlapped->hEvent); // 강제 형 변환을 해도 출력이 생각처럼 안나옴, 유니코드 기반 호환이 완전히 안된다고 판단
}