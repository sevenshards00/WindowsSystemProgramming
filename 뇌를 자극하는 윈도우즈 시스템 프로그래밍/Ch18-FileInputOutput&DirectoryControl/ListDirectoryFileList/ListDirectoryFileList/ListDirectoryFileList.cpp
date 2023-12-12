/*
* Windows System Programming - 파일 I/O와 디렉터리 컨트롤
* 파일명: ListDirectoryFileList.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-12
* 이전 버전 작성 일자:
* 버전 내용: 디렉터리 내에 존재하는 파일 리스트 출력
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR DirSpec[MAX_PATH];

	_tprintf(TEXT("Insert target Directory: "));
	_tscanf_s(TEXT("%s"), DirSpec, _countof(DirSpec));
	_tcsncat_s(DirSpec, TEXT("\\*"), 3);
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("Invalid File Value\n"));
		return -1;
	}
	else
	{
		_tprintf(TEXT("First file name is %s\n"), FindFileData.cFileName);
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			_tprintf(TEXT("Next file name is %s\n"), FindFileData.cFileName);
		}
		FindClose(hFind);
	}
	return 0;
}