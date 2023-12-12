/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: FileTimeInformation.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 파일의 시간 정보를 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt"); // 확인할 파일 이름

	// 파일의 시간 정보를 담을 버퍼
	TCHAR fileCreateTimeInfo[STRING_LEN]; // 생성 시간
	TCHAR fileAccessTimeInfo[STRING_LEN]; // 파일에 마지막으로 접근한 시간
	TCHAR fileWriteTimeInfo[STRING_LEN]; // 파일에 마지막으로 데이터를 갱신(덮어 쓰기 포함)한 시간

	// 파일의 시간 정보를 담을 FILETIME 구조체(시간 정보를 나타내는 8바이트(DWORD * 2) 자료형) 선언
	FILETIME ftCreate, ftAccess, ftWrite;

	// FILETIME 구조체의 시간은 UTC를 기준으로 설정, 시스템의 기준 시각으로 맞추기 위해 변수 지정
	SYSTEMTIME stCreateUTC, stCreateLocal;
	SYSTEMTIME stAccessUTC, stAccessLocal;
	SYSTEMTIME stWriteUTC, stWriteLocal;

	HANDLE hFile = CreateFile(
		fileName, // 개방(Open)할 파일 이름을 지정
		GENERIC_READ, // 읽기/쓰기 모드를 지정. 여기서는 읽기 모드. or(|) 연산으로 결합 가능
		FILE_SHARE_READ, // 파일의 공유 모드를 지정
		0, // 보안(상속) 속성 지정
		OPEN_EXISTING, // 파일이 생성 또는 읽을 때 사용하는 인자
		FILE_ATTRIBUTE_NORMAL, // 파일의 특성 정보 지정. 일반 파일이라면 FILE_ATTRIBUTE_NORMAL을 통상적으로 사용
		0 // 기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들 때 사용하는 인자. 일반적으로 NULL 전달.
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Creation Failed\n"));
		return -1;
	}

	// 파일의 시간 정보 추출
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
	{
		// 시간 정보 추출 실패 시
		_tprintf(TEXT("GetFileTime Function call fault\n"));
		return FALSE;
	}

	// 추출한 시간 정보를 변환
	// 추출한 시간 정보를 SYSTEMTIME 구조체에 옮긴다.
	// 그리고 SYSTEMTIME 구조체에 있는 정보를 현재 시스템(Local) 기준으로 바꾸는 과정
	FileTimeToSystemTime(&ftCreate, &stCreateUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stCreateUTC, &stCreateLocal);

	FileTimeToSystemTime(&ftAccess, &stAccessUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stAccessUTC, &stAccessLocal);

	FileTimeToSystemTime(&ftWrite, &stWriteUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stWriteUTC, &stWriteLocal);

	// 시간 정보 출력
	// sprintf 함수 -> strcat과 유사하나, 형식에 맞춰서 문자열을 연결해준다.
	// 첫 번째 인자에는 저장할 버퍼(배열)을 지정.
	// 여기서는 _s가 붙은 것을 사용했는데, 두 번째 인자에는 버퍼의 크기(길이)를 지정
	// 무심코 sizeof(버퍼이름)을 넣으면 예제 기준으로는 200이 잡힌다.
	// 그래서 TCHAR만큼 나눠야 100이 나옴.
	_stprintf_s(fileCreateTimeInfo, sizeof(fileCreateTimeInfo)/sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stCreateLocal.wMonth, stCreateLocal.wDay, stCreateLocal.wYear,
		stCreateLocal.wHour, stCreateLocal.wMinute, stCreateLocal.wSecond);

	_stprintf_s(fileAccessTimeInfo, sizeof(fileAccessTimeInfo) / sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stAccessLocal.wMonth, stAccessLocal.wDay, stAccessLocal.wYear,
		stAccessLocal.wHour, stAccessLocal.wMinute, stAccessLocal.wSecond);

	_stprintf_s(fileWriteTimeInfo, sizeof(fileWriteTimeInfo) / sizeof(TCHAR), TEXT("%02d/ %02d / %02d \t %02d:%02d:%02d"),
		stWriteLocal.wMonth, stWriteLocal.wDay, stWriteLocal.wYear,
		stWriteLocal.wHour, stWriteLocal.wMinute, stWriteLocal.wSecond);

	_tprintf(TEXT("File Created Time: %s\n"), fileCreateTimeInfo);
	_tprintf(TEXT("File Accessed Time: %s\n"), fileAccessTimeInfo);
	_tprintf(TEXT("File Written Time: %s\n"), fileWriteTimeInfo);

	CloseHandle(hFile);

	return 0;
}