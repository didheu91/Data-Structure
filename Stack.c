// Stack.c
#include <stdio.h>
#include <stdlib.h>

// 구조체 ------------------------------------------
// 노드 구조체
typedef struct Node {
    int data;
    struct Node *next;
} Node;
// 스택 구조체
typedef struct Stack {
    Node *top;
} Stack;

// 함수 --------------------------------------------
// 스택 초기화
void InitStack(Stack *s) {
    s->top = NULL;
}
// 공백 검사
int IsEmpty(Stack *s) {
    return s->top == NULL; // 1이면 NULL
}
// 데이터 삽입
void Push(Stack *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    // 연결리스트는 길이의 제한이 없어서
    // 가득 찼는지는 확인 필요 없음
    newNode->data = value;
    newNode->next = s->top; // 기존의 top과 새로운 top을 연결
    s->top = newNode;
}
// 데이터 삭제, 반환
void Pop(Stack *s) {
    // 공백이면 Underflow
    if(IsEmpty(s)) {
        printf("Underflow\n");
        exit(1);
    }
    // 아니면 top 바꾸고 예전 top 삭제
    Node *temp = s->top;
    s->top = temp->next; // top 바꾸기
    printf("[Pop] %d\n", temp->data);
    free(temp);
}
// 맨 위의 데이터 출력
void PrintTop(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty!\n");
        exit(1);
    }
    printf("[Top] %d\n", s->top->data);
}
// 맨 아래의 데이터 출력
void PrintBottom(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty!\n");
        exit(1);
    }
    // 이동
    Node *temp = s->top;
    while(temp->next!=NULL)
        temp = temp->next;
    // 반복문이 끝나고 Bottom을 찾음
    printf("[Bottom] %d\n", temp->data);
}
// 모든 데이터 출력
void PrintStack(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty!\n");
        exit(1);
    }
    printf("[Stack]");
    // top부터 NULL이 나올 때까지
    Node *temp = s->top;
    while(temp!=NULL) {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
// 메모리 해제
void FreeStack(Stack *s) {
    printf("=== Free ===\n");
    while(!IsEmpty(s)) {
        // IsEmpty는 NULL이 아니면 0이 반환됨
        // !0 == 1
        // NULL이 되면 1이 반환되고 !1 == 0
        // 반복문 종료
        Pop(s);
    } 
    printf("=== End ===\n");
}

// 메인 --------------------------------------------
int main() {
    Stack s;
    InitStack(&s);

    Push(&s, 10);
    Push(&s, 20);
    Push(&s, 30);

    PrintTop(&s);
    PrintBottom(&s);

    Pop(&s);
    PrintTop(&s);

    printf("[Empty] %d\n", IsEmpty(&s));

    PrintStack(&s);

    FreeStack(&s);
    PrintStack(&s);

    return 0;
}