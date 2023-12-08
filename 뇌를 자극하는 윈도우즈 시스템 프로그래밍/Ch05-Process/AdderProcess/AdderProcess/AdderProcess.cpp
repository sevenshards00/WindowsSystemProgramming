/*
* Windows System Programming - 프로세스 생성 예제
* 파일명: AdderProcess.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-03
* 이전 버전 작성 일자:
* 버전 내용: 프로세스를 생성하는 간단한 예제 구현
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD val1, val2;
	// _ttoi는 MBCS 기반이면 atoi, 유니코드 기반이면 _wtoi를 호출
	// 동시지원을 위해 지원하는 함수.
	val1 = _ttoi(argv[1]);
	val2 = _ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d\n"), val1, val2, val1 + val2);

	// getchar와 마찬가지로 MBCS 기반이면 getchar, 유니코드 기반이면 getwchar 함수를 호출
	// 동시 지원을 위해 지원하는 함수.
	// 프로그램의 실행을 잠시 멈추기 위해서 사용
	_gettchar();
	return 0;
}