// LinkedList.c
#include <stdio.h>
#include <stdlib.h>

// 구조체 -------------------------------------------
typedef struct Node {
	int data;
	struct Node *next; // 다음 노드의 주소를 가리키는 포인터
} Node;

// 함수 ---------------------------------------------
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
void InsertFront(Node** head, int data) {
    Node* newNode = CreateNode(data); // 새 노드 생성
    newNode->next = *head;
    *head = newNode;
}  
// 맨 뒤에 노드 삽입
void InsertEnd(Node** head, int data) {
    Node* newNode = CreateNode(data);
    Node *temp = *head;

    // 리스트가 비어있으면 바로 삽입
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
// 중간에 노드 삽입
void InsertMid(Node**head, int data, int position) {
    if (position == 0) {
        InsertFront(head, data); // head는 이미 이중 포인터이므로 그대로 전달
        return;
    }

    Node* temp = *head;
    for (int i = 0; i < position - 1; i++) {
        temp = temp -> next;
    }

    if (temp == NULL) {
        printf("리스트 길이를 초과\n");
        return;
    }

    Node* newNode = CreateNode(data);
    newNode -> next = temp -> next;
    // 새로운 노드는 temp가 가리키던 곳을 가리키고
    temp -> next = newNode;
    // temp는 새로운 노드를 가리키게 된다
}
// 노드 삭제
void DeleteNode(Node** head, int target) {
    Node* temp = *head;
    Node* prev = NULL;

    if (temp == NULL) {
        printf("Empty!\n");
        return;
    }
    // 삭제할 노드가 맨 앞에 있을 때
    else if (temp -> data == target) {
        *head = temp -> next; // head가 가리키는 곳을 두번째 노드로 바꿈
        free(temp); //삭제
        return;
    }

    else { // target을 찾을 때까지 이동
        while (1) {
            if (temp == NULL) {
                printf("Can't Find Target : %d\n", target);
                return;
            }
            else if(temp -> data == target) {
                prev -> next = temp -> next;
                // 앞의 노드의 next에 temp 다음 노드의 주소를 저장
                free(temp);
                return;
            }
            else { // target을 찾을 때까지 계속 이동
                prev = temp;
                temp = temp -> next;
            }
        }
    }
}
// 노드 검색
void SearchNode(Node* head, int target) {
    int position = 0;
    Node* temp = head;

    while (temp != NULL) {
        if (temp -> data == target) {
            printf("%d is at position %d.\n", target, position);
            return;
        }
        temp = temp -> next;
        position++;
    }
    printf("Can't Find Target : %d\n", target);
}
// 리스트 출력
void PrintList(Node *h) {
	Node *temp = h;
    if (temp == NULL) {
        printf("Empty!\n");
        return;
    }
	printf("[List] ");
	while(1) {
		if(temp==NULL) { 
			printf(" End\n");
			return;
		}
		else {
			printf("%d -> ", temp->data);
			temp = temp->next;
		}
	}
}
// 메모리 해제
void FreeList(Node **h) {
    if(*h==NULL) {
        printf("Empty!\n");
        return;
    }
    Node *temp = *h;
    Node *next;
    
    printf("[Free List]\n");
    while(temp!=NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    } 
    *h = NULL;
}

// 메인 ---------------------------------------------
int main(){
	Node *head = NULL;
	
	// 맨 앞에 삽입 
    InsertFront(&head,20);
    InsertFront(&head,10);
    InsertFront(&head,100);
    PrintList(head);
  
    // 맨 뒤에 삽입
    InsertEnd(&head, 200);
    InsertEnd(&head, 300);
    PrintList(head);
    
    // 중간에 삽입
    InsertMid(&head,3,0);
    PrintList(head);
    
    //중간지우기
    DeleteNode(&head,10);
    PrintList(head);

    // 맨앞지우기
    DeleteNode(&head,3);
    PrintList(head);

    //맨뒤지우기
    DeleteNode(&head,300);
    PrintList(head);
        
    //이상한거 지우기
    DeleteNode(&head,999);
    PrintList(head);
    
    // 검색하기 > 300, 20, 777
    SearchNode(head, 300);
    SearchNode(head, 20);
    SearchNode(head, 777); 
    
    // 메모리 해제
    FreeList(&head);
    PrintList(head);
}
