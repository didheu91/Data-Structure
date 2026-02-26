// Queue.c
#include <stdio.h>
#define MAX 100

// 구조체 -----------------------------------------
// data배열, 맨 앞 데이터 front, 맨 뒤 데이터 rear로 구성
typedef struct{
    int data[MAX];
    int front;
    int rear;
} Queue;

// 함수 -------------------------------------------
// 큐 초기화 (front 0, rear -1)
void InitQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}
// 공백 검사 (안 비었으면 0, 비었으면 1)
int IsEmpty(Queue *q) {
    return q->rear == -1;
}
// 가득 찼는지 (가득 차지 않았으면 0, 가득 찼으면 1)
int IsFull(Queue *q) {
    return q->front == MAX-1;
}
// 데이터 삽입 (가득 찼으면 오버플로우, 아니면 rear값 증가와 rear위치에 데이터 삽입)
void EnQueue(Queue *q, int data) {
    if(IsFull(q)) {
        printf("Overflow\n");
        return;
    }
    q->data[++q->rear] = data;
}
// 데이터 삭제,반환 (비었으면 언더플로우, 아니면 front 데이터 출력 후 front 증가)
void DeQueue(Queue *q) {
    if(IsEmpty(q)) {
        printf("Underflow\n");
        return;
    }
    printf("[DeQueue] %d\n", q->data[q->front++]);
}
// 맨 앞 데이터 출력 (공백 검사)
void PrintFront(Queue *q) {
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    printf("[Front] %d\n", q->data[q->front]);
}
// 맨 뒤 데이터 출력 (공백 검사)
void PrintRear(Queue *q) {
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    printf("[Rear] %d\n", q->data[q->rear]);
}
// 모든 데이터 출력 (공백 검사)
void PrintQueue(Queue *q) {
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    printf("[Queue]");
    for(int i=q->front; i<=q->rear; i++) {
        printf(" %d", q->data[i]);
    }
    printf("\n");
}

// 메인 -------------------------------------------
int main() {
    Queue q;
    InitQueue(&q);

    EnQueue(&q, 10);
    EnQueue(&q, 20);
    EnQueue(&q, 30);

    PrintFront(&q);
    PrintRear(&q);

    DeQueue(&q);
    PrintQueue(&q);

    return 0;
}