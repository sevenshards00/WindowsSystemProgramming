/*
* Windows System Programming - 프로세스 간 통신(Inter-Process Communication, IPC)
* 파일명: MailSender2_Parent.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-05
* 이전 버전 작성 일자:
* 버전 내용: 메일슬롯(MailSlot) 핸들의 상속 확인용 예제 - 부모 프로세스
* 이전 버전 내용:
*/

#define _CRT_SECURE_NO_WARNINGS

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
	TCHAR message[50];
	DWORD bytesWritten; // 몇 바이트나 읽었는가 확인

	SECURITY_ATTRIBUTES sa; // 보안 속성(상속과 관련된 속성) 구조체 정의
	sa.nLength = sizeof(sa); // 구조체의 크기
	sa.lpSecurityDescriptor = NULL; // 상속 관점에서는 의미가 없음
	sa.bInheritHandle = TRUE; // 상속 여부를 결정 짓는 요소. TRUE로 설정해야 상속이 된다.

	// mailslot에 메시지를 전달하기 위한 데이터 스트림 생성
	hMailSlot = CreateFile(
		SLOT_NAME, // 메일 슬롯의 주소, 즉 해당 주소의 메일슬롯을 개방한다.
		GENERIC_WRITE, // 쓰기 모드
		FILE_SHARE_READ, // 파일의 공유 방식, 여기서는 동시 읽기 접근 가능
		&sa, // 보안 속성 지정, 핸들 상속과 관련있는 부분. 여기서는 상속을 위해 정의한 sa 사용
		OPEN_EXISTING, // 기존의 파일을 개방. 없다면 함수 호출 실패. Receiver에 의해 메일슬롯이 생성되어 있는 상황.
		FILE_ATTRIBUTE_NORMAL, // 파일의 속성. 별다른 특성이 없는 보통 파일. 일반적으로 이걸 쓴다고 보면 됨.
		NULL // 기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들때 사용되는 전달 인자. 일반적으로 NULL 사용.
	); // 함수 호출이 성공하면 파일의 핸들이 반환됨.

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot stream!\n"), stdout);
		return 1;
	}

	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot); // 현재 상속할 핸들 출력
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt")); // 파일을 개방. 텍스트 모드로 작성
	_ftprintf(file, _T("%d"), hMailSlot); // 핸들을 파일에 기록
	fclose(file); // 스트림 해제

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSender2_Child.exe");

	// 핸들을 상속한 프로세스 생성
	CreateProcess(NULL, command, NULL, NULL,
		TRUE, // 핸들 테이블을 상속하겠다
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi);

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