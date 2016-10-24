#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {														// 이벤트 리스트를 구성할 구조체
	double time;
	double duration;
	int type;
	struct _Node *next;
}Node;

typedef struct _Queue {														// 대기열 큐를 구성할 구조체
	Node *front;
	Node *rear;
	int num;
	int total;
	int users;
}Queue;

void generate(Node **, double, double, int);
void arrive(Node **, Queue *, double, int);
void depart(Node **, Queue *, double, int);
double waitTime=0;

void main() {
	int n, i;
	double inTime, timer, min, max;
	Node *evlist = NULL;
	Queue *q;
	srand((unsigned)time(NULL));

	printf("직원의 수 : ");													// 설정 값 입력
	scanf("%d", &n);
	printf("시간 편차 : ");
	scanf("%lf", &inTime);
	printf("최소 시간 : ");
	scanf("%lf", &min);
	printf("최대 시간 : ");
	scanf("%lf", &max);

	if( n <= 0 || (inTime*=60) <= 0 || (min*=60) <= 0 || (max*=60) <=0 || (max-=min) < 0 ) {
		printf("잘못된 설정 입니다.\n");
		return;
	}

	q = (Queue*)calloc(n,sizeof(Queue));									// 입력한 값 만큼 대기열 큐 생성
	timer = inTime;

	do {
		if( timer <= 28800 && (int)(timer)%(int)(inTime) == 0 )				// 새로운 손님 이벤트 생성
			generate(&evlist, timer, (max? (double)(rand()%(int)(max)) + min : min), -1);
		if( evlist->type == -1 )											// 새로운 손님 이벤트를 대기열 큐로 할당
			arrive(&evlist, q, timer, n);
		timer += 1;
		if( evlist->type >= 0 && evlist->time <= timer )					// 할당된 이벤트가 끝날때 대기열 큐 삭제
			depart(&evlist, q, timer, n);
	} while( evlist );

	printf(" 은행 평균 대기 시간 : %f\n", waitTime>0? (waitTime/60)/(int)(28800/inTime) : 0.0 );
	for( i=0; i<n; i++ )													// 결과 값 출력
		printf("Q[%2d] 평균 대기 인원 : %f\n", i+1, q[i].total>0? (double)q[i].total/q[i].users: 0.0 );
	free(q);
}

void generate(Node **evlist, double timer, double duration, int type) {		// 새로운 이벤트 생성하는 함수
	Node *newnode = (Node*)malloc(sizeof(Node)), *temp = *evlist;			// 새로운 노드 생성
	newnode->time = timer;													
	newnode->duration = duration;
	newnode->type = type;

	if( !*evlist || type == -1 ) {											// 새로운 손님 이벤트이거나 첫 이벤트일때
		newnode->next = temp;
		*evlist = newnode;
	} else {																// 대기열 큐에 할당된 이벤트 일때
		for( ; temp->next && temp->next->time < timer; temp = temp->next );
		newnode->next = temp->next;
		temp->next = newnode;
	}
}

void arrive(Node **evlist, Queue *q, double timer, int n) {					// 대기열 큐에 할당하는 함수
	int i, min=0;
	Node *temp;

	for( i=1; i<n; i++ )													// 손님이 적은 대기열 검색
		if( q[i].num < q[min].num )
			min = i;

	temp = *evlist;															// 이벤트 리스트에서 리스트 삭제
	*evlist = (*evlist)->next;
	temp->next = NULL;

	if(q[min].front == NULL) {												// 첫 리스트일때 이벤트 생성
		q[min].front = temp;
		generate(evlist, timer+temp->duration, temp->duration, min);
	} else																	// 처음이 아닌경우 뒤에 대기
		q[min].rear->next = temp;

	q[min].rear = temp;
	q[min].total += (++q[min].num);											// 출력을 위한 카운터
	q[min].users ++;
}

void depart(Node **evlist, Queue *q, double timer, int n) {					// 대기열 큐에 삭제하는 함수
	Node *temp = q[(*evlist)->type].front;									// 대기열 큐의 데이터 삭제
	waitTime += ((*evlist)->time - q[(*evlist)->type].front->time);
	q[(*evlist)->type].num --;
	q[(*evlist)->type].front = q[(*evlist)->type].front->next;
	free(temp);

	if( q[(*evlist)->type].front )											// 다음 대기자가 있을때 이벤트 생성
		generate(evlist, (*evlist)->time+q[(*evlist)->type].front->duration, q[(*evlist)->type].front->duration, (*evlist)->type);

	temp = *evlist;															// 대기열 리스트 데이터 삭제
	*evlist = (*evlist)->next;
	free(temp);
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.10.27