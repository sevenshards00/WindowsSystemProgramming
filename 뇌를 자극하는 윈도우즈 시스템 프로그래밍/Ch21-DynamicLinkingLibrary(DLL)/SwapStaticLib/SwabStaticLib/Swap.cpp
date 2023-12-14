/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: Swap.h
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 정적 라이브러리 기본 예제
* 이전 버전 내용:
*/

#include "pch.h"

void swap(int* v1, int* v2)
{
	int temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}