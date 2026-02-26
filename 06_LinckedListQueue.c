// LinkedListQueue.c
#include <stdio.h>
#include <stdlib.h>

// 구조체 -----------------------------------------
// 노드 구조체
typedef struct Node {
    int data;
    struct Node *next;
} Node;
// 큐 구조체
typedef struct {
    Node *front;
    Node *rear;
    int size;
} Queue;

// 함수 -------------------------------------------
// 공백 검사 (1 빔, 0 안빔)
int IsEmpty(Queue *q) {
    return q->size==0;
}
// 데이터 삽입
void EnQueue(Queue *q, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    // 안전장치
    if(newNode==NULL) {
        printf("Memory Error\n");
        exit(1);
    }
    // newNode 세팅
    newNode->data = data;
    newNode->next = NULL;
    // 큐가 비었을 경우 front도 세팅
    if(IsEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    }
    // 큐가 비지 않았을 경우
    else {
        q->rear->next = newNode;
        q->rear = newNode; // rear 이동
    }
    // 사이즈 증가
    q->size++;
}
// 데이터 추출
void DeQueue(Queue *q) {
    // 공백이면 Underflow
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    // temp 필요
    Node *temp = q->front;
    // front 이동
    q->front = q->front->next;
    // 사이즈 감소
    q->size--;
    printf("[DeQueue] %d\n", temp->data);
    free(temp);

    // 만약 큐의 모든 데이터를 뺀다면 rear도 반드시 NULL을 해줘야 함
    if(q->front==NULL)
        q->rear = NULL;
}
// 큐 출력
void PrintQueue(Queue *q) {
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    printf("[Queue]");
    Node *temp = q->front;
    for(int i=0; i<q->size; i++) {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
// 검색
void Search(Queue *q, int target) {
    // 공백 검사
    if(IsEmpty(q)) {
        printf("Empty\n");
    }
    Node *temp = q->front;
    // size만큼
    for(int i=0; i<q->size; i++) {
        if(temp->data==target) {
            printf("[Search] %d is at %d\n", target, i);
            return;
        }
        temp = temp->next;
    }
    printf("Can't Find Target\n");
}
// 메모리 초기화
void FreeQueue(Queue *q) {
    // 공백 검사
    if(IsEmpty(q)) {
        printf("Empty\n");
        return;
    }
    printf("=== Free ===\n");
    // temp 필요
    Node *temp;
    for(int i=0; i<q->size; i++) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    q->size = 0;
}

// 메인 -------------------------------------------
int main() {
    Queue q = {NULL, NULL, 0};

    int ary[] = {10,20,30,40,50,60,70,80,90,100};
    int size = sizeof(ary)/sizeof(ary[0]);
    for(int i=0;i<size;i++)
        EnQueue(&q, ary[i]);
    PrintQueue(&q);

    for(int i=0; i<3; i++)
        DeQueue(&q);
    PrintQueue(&q);

    Search(&q, 70);
    
    FreeQueue(&q);
    PrintQueue(&q);
}
