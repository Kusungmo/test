#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>																// 출력을 위한 문자열 배열
char *result[9] = { "high card", "one pair", "two pair", "triple", "straight", "flush", "full house", "four card", "straight flush"};
char *prtn[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
char *prtd[4] = { "C", "D", "H", "S" };
char *prtp[5] = { "Black", "White", "Blue", "Green", "Red" };

typedef struct																	// 플레이어 정보를 넣을 구조체
{
	int result;
	int card[7];
}Player;

void poker();
void seven();
void rule(Player *, int );
int chk(char *);

void main(){
	while(1){
		int menu = 0;
		printf("1. 숙제1\n2. 숙제2\n = ");
		if( scanf("%d", &menu) == EOF )	return;									// EOF 입력시 종료
		fflush(stdin);

		switch(menu){
			case 1: poker();	break;											// 1번 과제 호출
			case 2: seven();	break;											// 2번 과제 호출
			default: printf("잘못된 입력입니다.\n\n"); break;					// 1,2 외의 입력시 오류 메시지 출력
		}
	}
}

void poker(){																	// 과제 1번 실행 함수
	int i, j, temp;
	char card[10];
	Player player[2];

	printf("Black과 White의 카드 패를 입력하시오.\n");
	for( i=0; i<10; i++ ){
		if( scanf("%s",card) == EOF )	return;
		
		if( strlen(card) != 2 || (temp = chk(card)) == -1 ){					// 입력이 카드가 맞는지 확인
			printf("올바른 카드를 입력하세요.\n\n");
			fflush(stdin);
			return;
		}
		for( j=0; j<i; j++ )													// 중복 입력된 카드가 있는지 확인
			if( player[j/5].card[j%5] == temp ){
				printf("중복된 카드를 입력하였습니다.\n\n");
				fflush(stdin);	
				return;
			}

		player[i/5].card[i%5] = temp;											// 오류 없을시 플레이어에게 카드 입력
	}

	rule(&player[0],5);															// 플레이어의 패를 확인
	rule(&player[1],5);

	printf("\t-> Black = %s %s, White = %s %s (%s)\n\n", prtn[player[0].result%13], result[player[0].result/13], prtn[player[1].result%13], result[player[1].result/13], player[0].result == player[1].result ? "Tie" : (player[0].result>player[1].result ? "Black Wins" : "White Wins"));
}																				// 결과 출력

void seven(){																	// 과제 2번 실행 함수
	int deck[52], i, temp, temp2;
	Player player[5];
	srand((unsigned)time(NULL));
	
	for( i=0; i<52; i++ ) deck[i] = i;											// 카드 덱을 생성하고 셔플
	for( i=0; i<52; i++ ){
		temp2 = rand()%52;
		temp = deck[temp2];
		deck[temp2] = deck[i];
		deck[i] = temp;
	}

	for( i=0; i<35; i++ )	player[i%5].card[i/5]=deck[i];						// 플레이어들에게 카드를 나누어 줌
	for( i=0, temp=0, temp2=0; i<5; i++ ){										// 플레이어의 패를 확인
		rule(&player[i],7);
		if( player[i].result > player[temp].result )			temp = i;
		else if( player[i].result == player[temp].result )		temp2 = i;
	}

	for( i=0; i<35; i++ ){														// 플레이어가 가진 카드를 출력
		if( i%7 == 0 )	printf("%s : ", prtp[i/7]);
		printf("%s%s ", prtn[player[i/7].card[i%7]%13], prtd[player[i/7].card[i%7]/13] );
		if( i%7 == 6 )	printf("(%s %s)\n", prtn[player[i/7].result%13], result[player[i/7].result/13] );
	}
	if( temp2 != 0 && player[temp2].result == player[temp].result )	printf("\t%s, %s Tie\n\n", prtp[temp], prtp[temp2] );
	else printf("\tWinner = %s\n\n", prtp[temp]);								// 게임 승자 출력
}

void rule(Player *player, int n)												// 플레이어의 패를 확인하는 함수
{
	int i, j, k, temp, count_num[13]={0}, count_dgn[4]={0};

	for( i=0; i<n-1; i++ ){														// 플레이어의 패를 순서대로 정렬
		for( j=i+1, k=i; j<n; j++ )
			if( player->card[k] > player->card[j] )		k = j;
		
		temp = player->card[k];
		player->card[k] = player->card[i];
		player->card[i] = temp;
	}

	for( i=0; i<n; i++ ){														// 카드 가지고 있는 것 count 하는 반복문
		if( i <= n-5 && player->card[i] == player->card[i+4] - 4 )	{	player->result = player->card[i+4]%13 + 104;	return;	}
		else{																	// 스티플 있는지 확인하는 조건문
			if( (count_num[player->card[i]%13]+=1) == 4 )			{	player->result = player->card[i]%13 + 91;		return;	}
			if( (count_dgn[player->card[i]/13]+=1) == 5 )			{	player->result = player->card[i]%13 + 65;		return;	}
		}																		// 포카드 있는지 확인하는 조건문
	}																			// 플러시 있는지 확인하는 조건문

	for( i=12, player->result = -1; i>=0; i-- )									// count된 값 확인
	{
		if( count_num[i] > 0 )
		{
			if( i>=4 && count_num[i-1]>0 && count_num[i-2]>0 && count_num[i-3]>0 && count_num[i-4]>0 )	{	player->result = i + 52;	return;	}
			else if( count_num[i] == 3 )										// 스트레이트 있는지 확인하는 조건문
				switch( player->result/13 ){									// 트리플일 경우
					case 3 : return;											// 이전에 트리플 있었으면 아웃
					case 2 :
					case 1 : player->result = i + 78;	return;					// 페어가 있으면 풀하우스
					default : player->result = i + 39;							// 아무것도 아니면 그냥 트리플
				}
			else if( count_num[i] == 2 )										// 페어인 경우
				switch( player->result/13 ){
					case 3 : player->result += 39;	return;						// 트리플이 있으면 풀하우스
					case 2 : return;											// 이전에 투페어가 있었으면 아웃
					case 1 : player->result += 13;	break;						// 이전에 원페어가 있었으면 투페어
					case 0 : player->result = i + 13;							// 아무것도 아니면 그냥 원페어
				}
			else if( player->result == -1 )		player->result = i;				// 아무 패도 없을 때 탑 카드 지정
		}
	}
}

int chk(char *card){															// 입력받은 카드를 확인하는 함수
	int num=-1, i;
	card[0] = toupper(card[0]), card[1] = toupper(card[1]);						// 소문자를 대문자로 치환

	for( i=0; i<13; i++ )	if( strncmp( &card[0], prtn[i], 1 ) == 0 ){	num = i;	break; }
	if( num == -1 )	return -1;													// 2~A 를 0~12로 치환 없을 경우 에러(-1)
	for( i=0; i<4; i++ )	if( strncmp( &card[1], prtd[i], 1 ) == 0 )	return num + 13*i;
	return -1;																	// C~S 를 (0~3)*13로 치환하여 반환, 없으면 에러(-1)
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.9.28