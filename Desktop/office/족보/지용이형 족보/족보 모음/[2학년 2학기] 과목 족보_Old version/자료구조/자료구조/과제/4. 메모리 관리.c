#include <stdio.h>
#include <stdlib.h>

typedef struct _Segment {													// 남은 메모리를 저장할 구조체
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
	printf("최대 메모리 : ");
	scanf("%d", &seg->size);												// 최대 메모리 입력
	if( seg->size < 0 ) {
		printf("잘못된 메모리 할당 입니다.\n");
		return;
	}

	while(1) {
		fflush(stdin);
		addr=-2;
		printf("시작주소, 크기 : ");										// 메모리 제어 요청
		scanf("%d %d", &addr, &size);

		if( addr == -1 && size == -1 )		endSegment(seg);				// 남은 메모리 출력 후 종료
		if( addr == -1 && size > 0 )		assignment(seg, size);			// 메모리를 할당
		else if( addr >= 0 && size > 0 )	withdrawal(seg, addr, size);	// 메모리를 반환
		else								printf("잘못된 값입니다.\n");	// 잘못된 값 입력시
	}
}

void assignment(Segment *seg, int size) {									// 메모리 할당 함수
	Segment *temp=seg;

	for( ; seg; seg = seg->next )											// 가장 적당한 사이즈를 찾음
		if( temp->size < size || (seg->size >= size && seg->size < temp->size) )
			temp = seg;

	if( temp->size < size ) {												// 적당한 사이즈가 없는 경우
		printf("남은 공간이 부족합니다.\n");
		return;
	}

	if( temp->size == size && temp->next ) {								// 사이즈가 딱 맞아서 없애야 하는 경우
		seg = temp->next;
		temp->addr = seg->addr;
		temp->size = seg->size;
		temp->next = seg->next;
		free(seg);
		return;
	}
	temp->addr += size;														// 메모리가 남을 경우
	temp->size -= size;
}

void withdrawal(Segment *seg, int addr, int size) {							// 메모리 반환 함수
	Segment *temp=NULL;

	for( ; seg; seg = seg->next )
		if( addr+size < seg->addr ){										// 새로운 메모리를 생성 해야 하는 경우
			temp = (Segment*)malloc(sizeof(Segment));
			temp->addr = seg->addr;
			temp->size = seg->size;
			temp->next = seg->next;
			seg->addr = addr;
			seg->size = size;
			seg->next = temp;
			return;
		}
		else if( addr+size == seg->addr ) {									// 기존 메모리 앞에 붙어야 하는 경우
			seg->addr -= size;
			seg->size += size;
			return;
		}
		else if( seg->addr+seg->size > addr ) break;						// 할당되지 않은 지역인 경우
		else if( seg->next && addr == seg->addr + seg->size )				// 기존 메모리 뒤에 붙어야 하는 경우
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
	printf("할당되지 않은 지역입니다\n");
}

void endSegment(Segment *seg){												// 남은 메모리를 출력한 후 종료하는 함수
	int count = 1;
	Segment *temp;

	while( seg ) {
		if( seg->size > 0 ) {
			printf("\n세그먼트 %d\n", count++);
			printf("시작 : %d\n", seg->addr);
			printf("크기 : %d\n", seg->size);
		}
		temp = seg;
		seg = seg->next;
		free(temp);
	}

	exit(0);
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.10.26