/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: MailSender2_Child.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 메일슬롯(MailSlot) 핸들의 상속 확인용 예제 - 자식 프로세스
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; // mailslot 핸들
	TCHAR message[50];
	DWORD bytesWritten; // 몇 바이트나 읽었는가 확인
	
	// 핸들을 얻는 부분
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Inheritable Handle: %d\n"), hMailSlot);

	// Message 송신
	while (1)
	{
		// 문자열을 입력받는다.
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		// WriteFile 함수를 통해 메일슬롯으로 데이터를 전송한다.
		if (!WriteFile(hMailSlot, // 데이터를 저장할 파일을 지정한다. 여기서는 데이터를 메일슬롯에 저장한다(보낸다).
			message, // 전송할 데이터가 저장되어 있는 버퍼를 지정한다.
			_tcslen(message) * sizeof(TCHAR), // 전송할 데이터 크기를 지정
			&bytesWritten, // 함수 호출 완료 후 전송된 실제 데이터의 크기를 바이트 단위로 얻기 위한 변수의 주소를 지정.
			NULL)) // ReadFile과 마찬가지로 현재는 NULL을 넣는다고만 알아둔다.
		{
			_fputts(_T("Unable to write!\n"), stdout);
			_gettchar();
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(message, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}
	}

	CloseHandle(hMailSlot);

	return 0;
}