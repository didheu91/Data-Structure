// BFS.c
// 인접행렬, 그래프를 이용한 문제
#include <stdio.h>
#define MAX 5
// 전역변수 ---------------------------------------------
int graph[MAX][MAX] = { {0,1,1,0,0},
                        {1,0,1,0,0},
                        {1,1,0,1,0},
                        {0,0,1,0,0},
                        {0,0,0,0,0} };
int visit[MAX] = {0}; // 방문한 노드 중복 방문 방지
int queue[1000];
int front = 0, rear = -1;

// 함수 ---------------------------------------------------
int BFS(int start){
    int cnt = 0;
    visit[start] = 1; 
    queue[++rear] = start; // queue[0] = 2; queue에 2를 집어넣음

    while(front<=rear){ // front가 rear보다 커진다 == queue가 비었다
        int target = queue[front++]; // front를 증가 시킨다 == queue에서 하나 뺀다 
        cnt++;

        // target과 연관된 노드 모두 찾기
        for(int i=0;i<MAX;i++){
            if(graph[target][i] == 1 && visit[i] == 0){
                // 나랑 연결되어있고, 방문한 적 없음
                queue[++rear] = i; // 큐에 넣음
                visit[i] = 1; //방문했다 표시
            }
        }
    }
    return cnt;
}

// 메인 -----------------------------------------------
int main(){
    printf("Link: %d\n", BFS(2));
}
