// CircleList.c
#include <stdio.h>
#include <stdlib.h>

// 구조체 ------------------------------------------
typedef struct Node {
	int data;
	struct Node *next; // 다음 노드의 주소를 가리키는 포인터
} Node;

// 함수 --------------------------------------------
// 새 노드 생성 함수
Node* CreateNode(int data) { //값을 받으면 그 값을 가진 노드를 만든다
    Node* newNode = (Node*)malloc(sizeof(Node));
    // newNode가 주소를 받음
    if (newNode == NULL) { //newNode가 주소값을 받지 못했다면
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode -> data = data;
    //newNode가 가리키는 곳에 있는 노드의 멤버 data에 매개변수 data의 값을 저장한다
    newNode -> next = NULL;
    return newNode;
}
// 맨 앞에 노드 삽입
void InsertFront(Node **h, int data) {
	Node *newNode = CreateNode(data);
	// 맨 앞이 NULL인 경우
	if (*h==NULL) {
		*h = newNode;
		// 원형 관계 만들어주기
		newNode->next = newNode;
		return;
	}
	// 빈 리스트가 아닌 경우
	// 맨 앞에 노드 삽입 + 맨 뒤를 새로운 Head와 연결
	// 맨 뒤에 노드 찾기
	Node *last = *h;
	while(last->next!=*h) {
		last = last->next;
	}
	newNode->next = *h; // 맨 앞 데이터 삽입
	last->next = newNode; // 마지막 노드와 연결
	*h = newNode; // h가 새로운 Head를 가리키게 함
}
// 맨 뒤에 노드 삽입
void InsertEnd(Node **h, int data) {
	// 리스트가 비었는지 확인하기
	if(*h==NULL) {
		// 비었으면 InsertFront
		InsertFront(h, data);
		return;
	}		
	// 리스트가 비지 않았으면 맨 끝에 노드 삽입
	Node *newNode = CreateNode(data);
	// 맨 끝 노드 찾기
	Node *last = *h;
	while(last->next!=*h) {
		last = last->next;
	}
	last->next = newNode;
	newNode->next = *h; // Head와 연결
}
// 데이터를 기준으로 노드 삽입
void InsertAfterValue(Node **h, int data, int target) {
	// 빈 리스트 일 경우
	if(*h==NULL) {
		printf("Empty!\n");
		return;
	}
	// target 찾기
	Node *temp = *h;
	while(1) {
		if(temp->data==target) {
			// 찾음!
			Node *newNode = CreateNode(data);
			newNode->next = temp->next;
			temp->next = newNode;
			return;
		}
		// 못 찾음. 이동
		temp = temp->next;
		if(temp==*h) {
			// temp가 h에 도착 = 한 바퀴를 돔 = 못 찾음
			printf("Not Find Target\n");
			return;
		}
	}
}
// 특정 노드 삭제
void Delete(Node **h, int target) {
	// 빈 리스트인 경우
	if(*h==NULL) {
		printf("Empty!\n");
		return;
	}
	Node *temp = *h;
	// 삭제 대상이 head인 경우
	if(temp->data==target) {
		//노드가 1개 뿐인 경우 *h는 NULL
		if(temp->next==*h) {
			free(temp);
			*h = NULL;
			return;
		}
		// 아닐 경우, last로 마지막 노드 찾아서 새로운 head와 연결	
		Node *last = temp;
		while(last->next!=*h) {
			last = last->next;
		}
		*h = temp->next;
		free(temp);
		last->next = *h;
		return;
	}
	// 일반적인 삭제. prev 필요
	Node *prev = temp;
	temp = temp->next;
	while(temp!=*h) {
		if(temp->data==target) {
			// 찾음!
			prev->next = temp->next;
			free(temp);
			return;
		}
		// 못 찾음. 이동
		prev = temp;
		temp = temp->next;		
	}
	// temp가 h이 됨 = 한 바퀴 돔 = 찾는 값이 없음
	printf("Target Not Find\n");
}
// 리스트 출력
void PrintList(Node *h) {
    Node *temp = h;
    // 비었으면 끝
    if(temp==NULL) {
        printf("Empty!\n");
        return;
    }
    // 뭐라도 하나 있으니 출력
    while(1) {
        printf("%d -> ", temp->data);
        temp = temp->next;
        if(temp == h)   break;
    }
    printf("End\n");
}
// 메모리 해제
void FreeList(Node **h) {
    if(*h==NULL) {
        printf("Empty!\n");
        return;
    }
    Node *temp = *h;
    Node *nextNode;
    
    printf("[Free List]\n");
    // 첫 노드를 제외하고 순회.
    // 다 돌았다는 기준을 head를 사용해야 하기 때문
    while(temp->next!=*h) {
        nextNode = temp->next;
        temp->next = nextNode->next;
        free(nextNode);
        // temp는 그대로 두면서 temp->next만 계속 변경하여 메모리를 해제하는 방식
    } 
    free(*h);
    *h = NULL;
}

// 메인 --------------------------------------------
int main() {
	Node *head = NULL;
    InsertFront(&head, 10);
    InsertFront(&head, 20);
    InsertFront(&head, 30);
    InsertFront(&head, 40);
    PrintList(head);

    InsertEnd(&head, 100);
    InsertEnd(&head, 200);
    InsertEnd(&head, 300);
    InsertEnd(&head, 400);
    PrintList(head);

    InsertAfterValue(&head, 1000, 40);
    InsertAfterValue(&head, 2000, 100);
    InsertAfterValue(&head, 3000, 400);
	PrintList(head);

    Delete(&head, 1000);
    Delete(&head, 2000);
    Delete(&head, 3000);
    Delete(&head, 111); // 없는 값
    PrintList(head);

    FreeList(&head);
    PrintList(head);
}
