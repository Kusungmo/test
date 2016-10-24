#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {														// �̺�Ʈ ����Ʈ�� ������ ����ü
	double time;
	double duration;
	int type;
	struct _Node *next;
}Node;

typedef struct _Queue {														// ��⿭ ť�� ������ ����ü
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

	printf("������ �� : ");													// ���� �� �Է�
	scanf("%d", &n);
	printf("�ð� ���� : ");
	scanf("%lf", &inTime);
	printf("�ּ� �ð� : ");
	scanf("%lf", &min);
	printf("�ִ� �ð� : ");
	scanf("%lf", &max);

	if( n <= 0 || (inTime*=60) <= 0 || (min*=60) <= 0 || (max*=60) <=0 || (max-=min) < 0 ) {
		printf("�߸��� ���� �Դϴ�.\n");
		return;
	}

	q = (Queue*)calloc(n,sizeof(Queue));									// �Է��� �� ��ŭ ��⿭ ť ����
	timer = inTime;

	do {
		if( timer <= 28800 && (int)(timer)%(int)(inTime) == 0 )				// ���ο� �մ� �̺�Ʈ ����
			generate(&evlist, timer, (max? (double)(rand()%(int)(max)) + min : min), -1);
		if( evlist->type == -1 )											// ���ο� �մ� �̺�Ʈ�� ��⿭ ť�� �Ҵ�
			arrive(&evlist, q, timer, n);
		timer += 1;
		if( evlist->type >= 0 && evlist->time <= timer )					// �Ҵ�� �̺�Ʈ�� ������ ��⿭ ť ����
			depart(&evlist, q, timer, n);
	} while( evlist );

	printf(" ���� ��� ��� �ð� : %f\n", waitTime>0? (waitTime/60)/(int)(28800/inTime) : 0.0 );
	for( i=0; i<n; i++ )													// ��� �� ���
		printf("Q[%2d] ��� ��� �ο� : %f\n", i+1, q[i].total>0? (double)q[i].total/q[i].users: 0.0 );
	free(q);
}

void generate(Node **evlist, double timer, double duration, int type) {		// ���ο� �̺�Ʈ �����ϴ� �Լ�
	Node *newnode = (Node*)malloc(sizeof(Node)), *temp = *evlist;			// ���ο� ��� ����
	newnode->time = timer;													
	newnode->duration = duration;
	newnode->type = type;

	if( !*evlist || type == -1 ) {											// ���ο� �մ� �̺�Ʈ�̰ų� ù �̺�Ʈ�϶�
		newnode->next = temp;
		*evlist = newnode;
	} else {																// ��⿭ ť�� �Ҵ�� �̺�Ʈ �϶�
		for( ; temp->next && temp->next->time < timer; temp = temp->next );
		newnode->next = temp->next;
		temp->next = newnode;
	}
}

void arrive(Node **evlist, Queue *q, double timer, int n) {					// ��⿭ ť�� �Ҵ��ϴ� �Լ�
	int i, min=0;
	Node *temp;

	for( i=1; i<n; i++ )													// �մ��� ���� ��⿭ �˻�
		if( q[i].num < q[min].num )
			min = i;

	temp = *evlist;															// �̺�Ʈ ����Ʈ���� ����Ʈ ����
	*evlist = (*evlist)->next;
	temp->next = NULL;

	if(q[min].front == NULL) {												// ù ����Ʈ�϶� �̺�Ʈ ����
		q[min].front = temp;
		generate(evlist, timer+temp->duration, temp->duration, min);
	} else																	// ó���� �ƴѰ�� �ڿ� ���
		q[min].rear->next = temp;

	q[min].rear = temp;
	q[min].total += (++q[min].num);											// ����� ���� ī����
	q[min].users ++;
}

void depart(Node **evlist, Queue *q, double timer, int n) {					// ��⿭ ť�� �����ϴ� �Լ�
	Node *temp = q[(*evlist)->type].front;									// ��⿭ ť�� ������ ����
	waitTime += ((*evlist)->time - q[(*evlist)->type].front->time);
	q[(*evlist)->type].num --;
	q[(*evlist)->type].front = q[(*evlist)->type].front->next;
	free(temp);

	if( q[(*evlist)->type].front )											// ���� ����ڰ� ������ �̺�Ʈ ����
		generate(evlist, (*evlist)->time+q[(*evlist)->type].front->duration, q[(*evlist)->type].front->duration, (*evlist)->type);

	temp = *evlist;															// ��⿭ ����Ʈ ������ ����
	*evlist = (*evlist)->next;
	free(temp);
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.10.27