/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: MailReceiver.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-04
* 이전 버전 작성 일자:
* 버전 내용: 메일슬롯(MailSlot)의 사용 예제 - Receiver
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// 사용할 메일슬롯의 주소
// \\computerName\mailslot\[path]name
// 아래의 주소는 \\.\mailslot\mailbox라고 쓴 것과 같다.
// 여기서 '.'이 의미하는 것은 로컬 컴퓨터, 즉 내 컴퓨터를 뜻한다.
// 루프백인 127.0.0.1과 같다고 보면 된다.
#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; // mailslot 핸들
	TCHAR messageBox[50];
	DWORD bytesRead; // 몇 바이트나 읽었는가 확인

	// mailslot 생성
	hMailSlot = CreateMailslot(
		SLOT_NAME, // 메일 슬롯의 이름, 즉 주소를 지정하는 것
		0, // 메일 슬롯의 버퍼 크기 지정, 0을 전달하면 시스템이 허용하는 최대 크기로 지정
		MAILSLOT_WAIT_FOREVER, // 메일슬롯을 통해 읽어들일 데이터가 채워질 때까지 기다리는 블로킹(Blocking) 타임아웃 설정
		NULL // 보안 속성 지정시 사용, 정확히는 핸들의 상속과 관련이 있음.
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n\n"), stdout);
		return 1;
	}

	// Message 수신
	_fputts(_T("******** Message ********\n"), stdout);
	while (1)
	{
		// ReadFile 함수를 통해 메일슬롯으로 전달된 데이터를 읽는다.
		// 원래 파일로부터 데이터를 읽어들일 때 사용하는 함수인데, 여기서는 메일슬롯으로부터 데이터를 읽는다.
		if(!ReadFile(hMailSlot, // 메일슬롯의 핸들은 인자로 전달. 파일이라면 파일의 핸들을 인자로 전달한다.
			messageBox, // 읽어 들인 데이터를 저장할 버퍼를 지정
			sizeof(TCHAR) * 50, // 읽어들일 데이터의 최대 크기를 지정 
			&bytesRead, // 실제로 읽어들인 데이터 크기를 바이트 단위로 저장하기 위한 변수의 주소를 지정
			NULL)) // 여기는 현재 언급하기 어려우므로 NULL을 전달한다고 이해
		{
			_fputts(_T("Unable to read!\n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(messageBox, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}

		messageBox[bytesRead / sizeof(TCHAR)] = 0; // 마지막에 NULL 문자 삽입
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot);

	return 0;
}