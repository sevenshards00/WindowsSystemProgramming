/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: GetFileSize.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 파일의 크기 정보를 확인하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName1[] = TEXT("data.txt"); // 확인할 파일 이름
	TCHAR fileName2[] = TEXT("D:\\半沢直樹\\S1\\Hanzawa.Naoki.1080p.HDTV.x264.AAC-MED\\Hanzawa.Naoki.Ep01.1080p.HDTV.x264.AAC-MED.mkv"); // 확인할 파일 이름

	HANDLE hFile1 = CreateFile(
		fileName1, // 개방(Open)할 파일 이름을 지정
		GENERIC_READ, // 읽기/쓰기 모드를 지정. 여기서는 읽기 모드. or(|) 연산으로 결합 가능
		FILE_SHARE_READ, // 파일의 공유 모드를 지정
		0, // 보안(상속) 속성 지정
		OPEN_EXISTING, // 파일이 생성 또는 읽을 때 사용하는 인자
		FILE_ATTRIBUTE_NORMAL, // 파일의 특성 정보 지정. 일반 파일이라면 FILE_ATTRIBUTE_NORMAL을 통상적으로 사용
		0 // 기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들 때 사용하는 인자. 일반적으로 NULL 전달.
	);

	HANDLE hFile2 = CreateFile(
		fileName2, // 개방(Open)할 파일 이름을 지정
		GENERIC_READ, // 읽기/쓰기 모드를 지정. 여기서는 읽기 모드. or(|) 연산으로 결합 가능
		FILE_SHARE_READ, // 파일의 공유 모드를 지정
		0, // 보안(상속) 속성 지정
		OPEN_EXISTING, // 파일이 생성 또는 읽을 때 사용하는 인자
		FILE_ATTRIBUTE_NORMAL, // 파일의 특성 정보 지정. 일반 파일이라면 FILE_ATTRIBUTE_NORMAL을 통상적으로 사용
		0 // 기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들 때 사용하는 인자. 일반적으로 NULL 전달.
	);

	if (hFile1 == INVALID_HANDLE_VALUE && hFile2 == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("File Creation Failed\n"));
		return -1;
	}

	// 32비트 환경 기준
	// 파일 하나가 4GB 미만일 경우 (2^2 * 2^10 * 2^10 * 2^10)
	// 4byte(32bit)만 가지고 표현이 가능 (0~2^32-1)
	// 파일이 4GB 이상일 경우 상위 4바이트 정보가 GetFileSize의 2번째 인자로 전달
	DWORD high4ByteFileSize = 0; // 사실상 NULL, 4GB 이상이면 여기에 상위 4바이트 정보가 전달된다
	DWORD low4ByteFileSize = GetFileSize(hFile1, &high4ByteFileSize); // 4GB 미만의 경우 GetFileSize

	_tprintf(TEXT("High 4byte file size: %u byte\n"), high4ByteFileSize);
	_tprintf(TEXT("Low 4byte file size: %u byte\n"), low4ByteFileSize);

	// 64비트 환경 기준
	// 파일 하나가 4GB 이상일 경우
	// 4byte(32bit)만 가지고는 표현이 불가능
	// LARGE_INTER는 8byte 공용체(Union)
	// 4GB 이상이면 8byte(64bit)를 사용하여 LowPart + HighPart까지 사용 (0~2^64-1)
	// 4GB 미만까지는 LowPart, 4GB 이상부터는 HighPart를 사용
	// 그래서 전체 용량은 QuadPart를 보면 알 수 있음
	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFile2, &fileSize); // 4GB 이상일 경우 GetFileSizeEx
	_tprintf(TEXT("Total file size: %llu byte\n"), fileSize.QuadPart);

	CloseHandle(hFile1);
	CloseHandle(hFile2);

	return 0;
}