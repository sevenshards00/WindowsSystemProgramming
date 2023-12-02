/*
* Windows System Programming - 64비트 기반 프로그래밍
* 파일명: PolymorphicType2.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-02
* 이전 버전 작성 일자:
* 버전 내용: Windows의 Polymorphic 자료형에 대한 이해
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 메모리 공간상 거리 차이를 계산하기 위한 함수 (x64, 64비트)
UINT_PTR CalcDistance(UINT_PTR a, UINT_PTR b)
{
	// 32비트라면
	//return a-b;
	return b - a;
}

int _tmain()
{
	INT val1 = 10;
	INT val2 = 20;
	
	_tprintf(_T("Distance: %u \n"), CalcDistance((UINT_PTR)&val1, (UINT_PTR)&val2));

	return 0;
}