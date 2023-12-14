/*
* Windows System Programming - 메모리 관리(Virtual Memory, Heap, MMF)
* 파일명: LINKED_HEAP.cpp
* 파일 버전: 0.1
* 작성자: Sevenshards
* 작성 일자: 2023-12-14
* 이전 버전 작성 일자:
* 버전 내용: 힙을 사용한 연결 리스트 예제(MBCS 기반)
* 이전 버전 내용:
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

typedef int ListElementDataType; // 리스트의 데이터 타입

typedef struct _node
{
	ListElementDataType data;
	struct _node* next;
} Node;

Node* head;
Node* tail;

HANDLE hHeap = 0;

// 힙 초기화
void InitListHeap()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	UINT pageSize = sysInfo.dwPageSize;

	hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);
}

// 리스트 초기화 (head, tail 모두 더미노드 기반)
void InitList()
{
	InitListHeap(); // 동적 힙 기반에서만 호출.

	// C 기준 head = (Node*)malloc(sizeof(Node));
	head = (Node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(Node));
	// C 기준 tail = (Node*)malloc(sizeof(Node));
	tail = (Node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(Node));

	head->next = tail;
	tail->next = tail;
}

// 노드 제거
int DeleteNode(int data)
{
	Node* cur = head; // 무조건 시작은 head부터 (LFirst)
	Node* curNext = cur->next; // 현재 노드의 다음 위치

	// 제거할 데이터를 찾거나 tail이 아닐때까지
	while (curNext->data != data && curNext != tail)
	{
		cur = cur->next;
		curNext = cur->next;
	}

	if (curNext != tail)
	{
		// 현재 노드가 가리키는 next를 현재 위치 다음 노드로
		cur->next = curNext->next;
		// C 기준 free(curNext);
		HeapFree(hHeap, HEAP_NO_SERIALIZE, curNext);
		return 1; // 제거 성공 시 1
	}
	else
		return 0; // 제거하지 못했을 경우 0
}

// 노드 삽입 (단, 정렬해서 삽입)
void OrderedInsert(int data)
{
	Node* cur = head;
	Node* curNext = cur->next;

	Node* newNode;

	// 오름차순 정렬
	while (curNext->data <= data && curNext != tail)
	{
		cur = cur->next;
		curNext = cur->next;
	}

	// C기준 newNode = (Node*)malloc(sizeof(Node));
	newNode = (Node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(Node));
	newNode->data = data;
	cur->next = newNode;
	newNode->next = curNext;
}

// 리스트에 저장된 모든 데이터 출력
void PrintAllList()
{
	Node* startNode = head->next;
	while (startNode != tail)
	{
		printf("%-4d", startNode->data);
		startNode = startNode->next;
	}
	_tprintf(TEXT("\n\n"));
}

// 리스트에 저장된 모든 데이터 삭제
void DeleteAll()
{
	/*
	Node* cur = head->next;
	Node* delNode;
	while (cur != tail)
	{
		delNode = cur;
		cur = cur->next;
		free(delNode);
	}
	*/
	// 위와 같이 구현해도 되지만 힙은 한 방에 날리는 것이 가능하다
	HeapDestroy(hHeap); // 싹 다 날리고
	InitList(); // 다시 초기화하면 된다 (성능 향상, 에러 발생율 낮음)
}

int _tmain(int argc, TCHAR* argv[])
{
	InitList();

	printf("Input 1, 2, 3\n");
	OrderedInsert(1);
	OrderedInsert(2);
	OrderedInsert(3);
	PrintAllList();

	printf("Input 4, 5, 6\n");
	OrderedInsert(4);
	OrderedInsert(5);
	OrderedInsert(6);
	PrintAllList();
	
	printf("Delete 2, 5\n");
	DeleteNode(2);
	DeleteNode(5);
	PrintAllList();

	printf("Flush List\n\n");
	DeleteAll();

	printf("Input 6, 5, 4\n");
	OrderedInsert(6);
	OrderedInsert(5);
	OrderedInsert(4);
	PrintAllList();

	printf("Input 3, 2, 1\n");
	OrderedInsert(3);
	OrderedInsert(2);
	OrderedInsert(1);
	PrintAllList();

	printf("Flush List\n\n");
	DeleteAll();

	printf("Input 1, 3, 5\n");
	OrderedInsert(1);
	OrderedInsert(3);
	OrderedInsert(5);
	PrintAllList();

	printf("Input 2, 4, 6\n");
	OrderedInsert(2);
	OrderedInsert(4);
	OrderedInsert(6);
	PrintAllList();

	return 0;
}