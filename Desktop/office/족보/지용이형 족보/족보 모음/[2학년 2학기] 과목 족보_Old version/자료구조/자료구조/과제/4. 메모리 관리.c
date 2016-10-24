#include <stdio.h>
#include <stdlib.h>

typedef struct _Segment {													// ���� �޸𸮸� ������ ����ü
	int addr;
	int size;
	struct _Segment *next;
}Segment;

void assignment(Segment *, int);
void withdrawal(Segment *, int, int);
void endSegment(Segment *);

void main() {
	Segment *seg = (Segment*)malloc(sizeof(Segment));
	int addr, size;

	seg->addr=0;
	seg->next=NULL;
	printf("�ִ� �޸� : ");
	scanf("%d", &seg->size);												// �ִ� �޸� �Է�
	if( seg->size < 0 ) {
		printf("�߸��� �޸� �Ҵ� �Դϴ�.\n");
		return;
	}

	while(1) {
		fflush(stdin);
		addr=-2;
		printf("�����ּ�, ũ�� : ");										// �޸� ���� ��û
		scanf("%d %d", &addr, &size);

		if( addr == -1 && size == -1 )		endSegment(seg);				// ���� �޸� ��� �� ����
		if( addr == -1 && size > 0 )		assignment(seg, size);			// �޸𸮸� �Ҵ�
		else if( addr >= 0 && size > 0 )	withdrawal(seg, addr, size);	// �޸𸮸� ��ȯ
		else								printf("�߸��� ���Դϴ�.\n");	// �߸��� �� �Է½�
	}
}

void assignment(Segment *seg, int size) {									// �޸� �Ҵ� �Լ�
	Segment *temp=seg;

	for( ; seg; seg = seg->next )											// ���� ������ ����� ã��
		if( temp->size < size || (seg->size >= size && seg->size < temp->size) )
			temp = seg;

	if( temp->size < size ) {												// ������ ����� ���� ���
		printf("���� ������ �����մϴ�.\n");
		return;
	}

	if( temp->size == size && temp->next ) {								// ����� �� �¾Ƽ� ���־� �ϴ� ���
		seg = temp->next;
		temp->addr = seg->addr;
		temp->size = seg->size;
		temp->next = seg->next;
		free(seg);
		return;
	}
	temp->addr += size;														// �޸𸮰� ���� ���
	temp->size -= size;
}

void withdrawal(Segment *seg, int addr, int size) {							// �޸� ��ȯ �Լ�
	Segment *temp=NULL;

	for( ; seg; seg = seg->next )
		if( addr+size < seg->addr ){										// ���ο� �޸𸮸� ���� �ؾ� �ϴ� ���
			temp = (Segment*)malloc(sizeof(Segment));
			temp->addr = seg->addr;
			temp->size = seg->size;
			temp->next = seg->next;
			seg->addr = addr;
			seg->size = size;
			seg->next = temp;
			return;
		}
		else if( addr+size == seg->addr ) {									// ���� �޸� �տ� �پ�� �ϴ� ���
			seg->addr -= size;
			seg->size += size;
			return;
		}
		else if( seg->addr+seg->size > addr ) break;						// �Ҵ���� ���� ������ ���
		else if( seg->next && addr == seg->addr + seg->size )				// ���� �޸� �ڿ� �پ�� �ϴ� ���
			if( addr+size < seg->next->addr ) {
				seg->size += size;
				return;
			}
			else if( addr+size == seg->next->addr ) {
				temp = seg->next;
				seg->size += (temp->size+size);
				seg->next = temp->next;
				free(temp);
				return;
			}
	printf("�Ҵ���� ���� �����Դϴ�\n");
}

void endSegment(Segment *seg){												// ���� �޸𸮸� ����� �� �����ϴ� �Լ�
	int count = 1;
	Segment *temp;

	while( seg ) {
		if( seg->size > 0 ) {
			printf("\n���׸�Ʈ %d\n", count++);
			printf("���� : %d\n", seg->addr);
			printf("ũ�� : %d\n", seg->size);
		}
		temp = seg;
		seg = seg->next;
		free(temp);
	}

	exit(0);
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.10.26