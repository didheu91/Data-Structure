// BinarySearchTree.c
#define CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

// 전역변수 ---------------------------------------
int target;
int count = 0;
int foundOrder = 0;
int flag = 0;
// 구조체 --------------------------------------1-----
typedef struct Node {
    int data;
    // Tree니까 next가 아니라 left와 right가 있음
    struct Node *left;
    struct Node *right;
} Node;

// 함수 ---------------------------------------------
// 노드 생성
Node *CreateNode(int data) {
    // 노드 구조체 포인터 함수
    // 주소를 알려주는 함수
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode; // 주소 반환
}
// 타겟 찾기
void FindTarget(Node *root) {
    count++;
    printf("%d ", root->data);
    if (root->data == target) {
        foundOrder = count;
        flag = 1;
    }
}
// 횟수 출력
void PrintCount() {
    if (flag == 1) {
        printf("Found at step %d\n", foundOrder);
    } else {
        printf("Target not found\n");
    }
}
// 전역변수 초기회
void ResetCount() {
    count = 0;
    foundOrder = 0;
    flag = 0;
}
// 전위 순회
void SearchPre(Node *root) {
    // 빈 트리면 종료
    if(root == NULL)    return;
    FindTarget(root);
    SearchPre(root->left);
    SearchPre(root->right);
}
// 중위 순회
void SearchIn(Node *root) {
    if(root == NULL)    return;
    SearchIn(root->left);
    FindTarget(root);
    SearchIn(root->right);
}
// 후위 순회
void SearchPost(Node *root) {
    if(root == NULL)    return;
    SearchPost(root->left);
    SearchPost(root->right);
    FindTarget(root);
}
// BST 이진 탐색 트리
void InsertBST(Node **root, int data) {
    // 비어있으면 삽입
    if(*root == NULL) {
        *root = CreateNode(data);
        return;
    }
    // 현재 노드의 데이터보다 값이 크면 right
    if(data > (*root)->data)
        InsertBST(&(*root)->right, data);
    // 현재 노드의 데이터보다 값이 작으면 left
    else if(data < (*root)->data)
        InsertBST(&(*root)->left, data);
    // 중복
    else    printf("Duplicate!\n");    
}
// 메모리 해제
void FreeTree(Node *root) {
    if(root == NULL)    return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

// 메인 ---------------------------------------------
int main() {
    Node *tree = NULL;
    InsertBST(&tree, 8);    
    InsertBST(&tree, 10);
    InsertBST(&tree, 4);
    InsertBST(&tree, 9);
    InsertBST(&tree, 12);
    InsertBST(&tree, 16);
    InsertBST(&tree, 5);
    InsertBST(&tree, 3);
    InsertBST(&tree, 7);
    InsertBST(&tree, 1);
    InsertBST(&tree, 6);

    printf("(Preorder) Input Target: ");
    scanf("%d", &target);
    SearchPre(tree);
    printf("\n");
    PrintCount();
    ResetCount();  

    printf("(Inorder) Input Target: ");
    scanf("%d", &target);
    SearchIn(tree);
    printf("\n");
    PrintCount();
    ResetCount(); 

    printf("(Postorder) Input Target: ");
    scanf("%d", &target);
    SearchPost(tree);
    printf("\n");
    PrintCount();
    ResetCount(); 

    FreeTree(tree);
    return 0;
}
