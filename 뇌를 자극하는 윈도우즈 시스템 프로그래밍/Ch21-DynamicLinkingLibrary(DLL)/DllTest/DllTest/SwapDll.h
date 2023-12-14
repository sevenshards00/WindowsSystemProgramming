/*
* Windows System Programming - Dynamic Linking Library (DLL)
* 파일명: SwapDll.h
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 동적 라이브러리 기본 예제
* 이전 버전 내용:
*/

__declspec(dllimport)
void swap(int* v1, int* v2);