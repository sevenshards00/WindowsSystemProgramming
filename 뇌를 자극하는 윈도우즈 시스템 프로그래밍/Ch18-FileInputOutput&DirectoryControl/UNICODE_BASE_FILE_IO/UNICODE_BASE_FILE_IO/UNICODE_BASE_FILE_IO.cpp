/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: UNICODE_BASE_FILE_IO.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 유니코드 기반의 파일 입출력 예제(1)
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt");
	TCHAR fileData[] = TEXT("Test String");

	HANDLE hFile = CreateFile(
		fileName, // 개방(Open)할 파일 이름을 지정
		GENERIC_WRITE, // 읽기/쓰기 모드를 지정. 여기서는 쓰기 모드. or(|) 연산으로 결합 가능
		FILE_SHARE_WRITE, // 파일의 공유 모드를 지정
		0, // 보안(상속) 속성 지정
		CREATE_ALWAYS, // 파일이 생성 또는 읽을 때 사용하는 인자
		FILE_ATTRIBUTE_NORMAL, // 파일의 특성 정보 지정. 일반 파일이라면 FILE_ATTRIBUTE_NORMAL을 통상적으로 사용
		0 // 기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들 때 사용하는 인자. 일반적으로 NULL 전달.
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Creation Failed\n"));
		return -1;
	}

	DWORD numOfByteWritten = 0;
	WriteFile(
		hFile, // 데이터를 저장할 파일의 핸들을 지정
		fileData, // 데이터를 저장하고 있는 버퍼의 주소를 지정
		sizeof(fileData), // 파일에 저장하고자 하는 데이터 크기를 바이트 단위로 지정
		&numOfByteWritten, // 실제로 저장된 데이터 크기를 얻기 위한 변수의 주소 지정
		NULL // OverLapped 관련, 비동기 I/O와 관련
	);

	_tprintf(TEXT("Written data size: %u\n"), numOfByteWritten);
	CloseHandle(hFile);

	return 0;
}