/*
* Windows System Programming - 64비트 기반 프로그래밍
* 파일명: PolymorphicType1.cpp
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
UINT64 CalcDistance(UINT64 a, UINT64 b)
{
	return b - a;
}

// 메모리 공간상 거리 차이를 계산하기 위한 함수 (x86, 32비트)
UINT CalcDistance(UINT a, UINT b)
{
	return a - b;
}

int _tmain()
{
	INT val1 = 10;
	INT val2 = 20;

	// x86, 32비트 환경
	_tprintf(_T("Position %u, %u \n"), (UINT)&val1, (UINT)&val2);
	_tprintf(_T("Distance: %u \n"), CalcDistance((UINT)&val1, (UINT)&val2));

	// x64, 64비트 환경
	_tprintf(_T("Position %llu, %llu \n"), (UINT64)&val1, (UINT64)&val2);
	_tprintf(_T("Distance: %llu \n"), CalcDistance((UINT64)&val1, (UINT64)&val2));

	return 0;
}