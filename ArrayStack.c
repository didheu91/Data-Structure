// ArrayStack.c
#include <stdio.h>
#define MAX 100

// 구조체 ---------------------------------------------
typedef struct{
    int data[MAX];
    int top; // 맨 위 데이터의 인덱스
} Stack;

// 함수 -----------------------------------------------
// 스택 초기화
void InitStack(Stack *s) {
    s->top = -1;
}
// 스택이 비어있는지
int IsEmpty(Stack *s) {
    // 비었으면 1, 비지 않았으면 0
    return s->top == -1;
}
// 스택이 가득 찼는지
int IsFull(Stack *s) {
    // 가득 찼으면 1, 아니면 0
    return s->top == MAX-1;
}
// 삽입
void Push(Stack *s, int data) {
    if(IsFull(s)) {
        printf("Overflow\n");
        return;
    }
    s->data[++(s->top)] = data;
    // top 증가, top 위치에 새 data 삽입
}
// 삭제
void Pop(Stack *s) {
    if(IsEmpty(s)) {
        printf("Underflow\n");
        return;
    }
    printf("[Pop] %d\n", s->data[s->top]);
    s->top--;
}
// 맨 위의 데이터 출력
void PrintTop(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty\n");
        return;
    }
    printf("[Top] %d\n", s->data[s->top]);
}
// 맨 아래의 데이터 출력
void PrintBottom(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty\n");
        return;
    }
    printf("[Bottom] %d\n", s->data[0]);
}
// 모든 데이터 출력
void PrintStack(Stack *s) {
    if(IsEmpty(s)) {
        printf("Empty\n");
        return;
    }
    printf("[Stack]");
    for(int i=s->top; i>=0; i--) {
        printf(" %d", s->data[i]);
    }
    printf("\n");
}
// 메인 -----------------------------------------------
int main() {
    Stack s;
    InitStack(&s);

    Push(&s, 10);
    Push(&s, 20);
    Push(&s, 30);

    PrintTop(&s);
    PrintBottom(&s);

    Pop(&s);
    
    PrintStack(&s);

    return 0;
}