/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: Set_Get_FileAttributes.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 파일의 특성 정보 참조 및 변경하는 예제
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = TEXT("data.txt"); // 확인할 파일 이름

	_tprintf(TEXT("Original file attributes\n"));
	DWORD attrib = GetFileAttributes(fileName);
	ShowAttributes(attrib);
	
	// OR 연산(|)을 통해 파일의 속성을 변경
	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	// 변경된 속성을 적용
	SetFileAttributes(fileName, attrib);

	_tprintf(TEXT("Changed file attributes\n"));
	attrib = GetFileAttributes(fileName);
	ShowAttributes(attrib);

	return 0;
}

void ShowAttributes(DWORD attrib)
{
	// AND(&) 연산을 통해 파일의 속성을 비교한다.
	// 일반 파일이라면 다른 특성이 없는 파일을 뜻한다.
	// OS에서는 기본적으로 파일을 FILE_ATTRIBUTE_NORMAL로 생성해도 FILE_ATTRIBUTE_ARCHIVE 속성을 부여한다.
	// 그래서 아래 속성은 나오지 않는다.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
		_tprintf(TEXT("FILE_ATTRIBUTE_NORMAL OR FILE_ATTRIBUTE_ARCHIVE\n"));
	else
	{
		// 읽기 전용 속성이 있을 경우
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(TEXT("FILE_ATTRIBUTE_READONLY\n"));
		// 숨김 파일 속성이 있을 경우
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(TEXT("FILE_ATTRIBUTE_HIDDEN\n"));
	}
		
	_tprintf(TEXT("\n"));
}