#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
char *strp[5] = { "Black", "White", "Blue", "Green", "Red" };					// 출력을 위한 문자열 배열
char *strd[4] = { "C", "H", "D", "S" };
char *strn[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
char *strr[13] = { "Top", "One Pair", "Two Pair", "Triple", "Straight", "Back Straght", "Mountain", "Flush", "Full House", "Four Card", "Straight Flush", "Back Straight Flush", "Royal Straight Flush"};

typedef struct																	// 플레이어 정보를 넣을 구조체
{
	int result;
	int card[7];
}Player;

void poker();
void seven();
void rule(Player *, int );
int chk(char *);

void main()
{
	while(1)
	{
		int menu = 0;
		printf("1. 숙제1\n2. 숙제2\n = ");
		if( scanf("%d", &menu) == EOF )	return;									// EOF 입력시 종료
		fflush(stdin);

		switch(menu)
		{
			case 1: poker();	break;											// 1번 과제 호출
			case 2: seven();	break;											// 2번 과제 호출
			default: printf("잘못된 입력입니다.\n\n"); break;					// 1,2 외의 입력시 오류 메시지 출력
		}
	}
}

void poker()																	// 과제 1번 실행 함수
{
	int i, j, temp;
	char card[10];
	Player player[2];

	printf("Black과 White의 카드 패를 입력하시오.\n");
	for( i=0; i<10; i++ ){
		if( scanf("%s",card) == EOF )	return;
		
		if( strlen(card) != 2 || (temp = chk(card)) == -1 )						// 입력이 카드가 맞는지 확인
		{
			printf("올바른 카드를 입력하세요.\n\n");
			fflush(stdin);
			return;
		}

		for( j=0; j<i; j++ )													// 중복 입력된 카드가 있는지 확인
			if( player[j/5].card[j%5] == temp )
			{
				printf("중복된 카드를 입력하였습니다.\n\n");
				fflush(stdin);	
				return;
			}

		player[i/5].card[i%5] = temp;											// 오류 없을시 플레이어에게 카드 입력
	}

	rule(&player[0],5);															// 플레이어의 패를 확인
	rule(&player[1],5);

	printf("\t-> Black = %s %s, White = %s %s ", strn[player[0].result%64/4], strr[player[0].result/64], strn[player[1].result%64/4], strr[player[1].result/64]);
	printf("(%s)\n\n", player[0].result/4 == player[1].result/4 ? "Tie" : (player[0].result>player[1].result ? "Black Wins" : "White Wins" ));
}																				// 결과 출력

void seven()																	// 과제 2번 실행 함수
{
	int deck[52], i, j, temp;
	Player player[5];
	srand((unsigned)time(NULL));
	
	for( i=0, temp=0; i<52; deck[i++] = i+temp )								// 카드 덱 생성
		if( i%13 == 0 )	temp++;

	for( i=0; i<52; i++ )														// 카드 덱 셔플
	{
		temp = deck[j = rand()%52];
		deck[j] = deck[i];
		deck[i] = temp;
	}

	for( i=0; i<35; i++ )	player[i%5].card[i/5]=deck[i];						// 플레이어들에게 카드를 7장씩 나누어 줌

	for( i=0, temp=0; i<5; i++ )												// 플레이어의 패를 확인
	{
		rule( &player[i], 7 );
		if( player[i].result > player[temp].result )	temp = i;
	}

	for( i=0; i<35; i++ )														// 플레이어가 가진 카드를 출력
	{
		if( i%7 == 0 )	printf("%s : ", strp[i/7]);
		printf("%s%s ", strn[player[i/7].card[i%7]%14-1], strd[player[i/7].card[i%7]/14] );
		if( i%7 == 6 )	printf("(%s%s %s)\n", strn[player[i/7].result%64/4], strd[player[i/7].result%4], strr[player[i/7].result/64] );
	}
	printf("\tWinner = %s\n\n", strp[temp]);									// 게임 승자 출력
}

void rule(Player *player, int n)												// 플레이어의 패를 확인하는 함수
{
	int i, j, k, temp = n, card[11], count_num[14] = {0}, count_dgn[4] = {0};

	for( i = 0; i < temp; card[i] = player->card[i], i++ )						// 플레이어 카드 복사
		if( player->card[i]%14 == 13 )	card[n++] = player->card[i]-13;

	for( i = 0; i < n; i++ )													// 플레이어의 패를 순서대로 정렬
	{
		for( j=i+1, k=i; j<n; j++ )
			if( card[k] > card[j] )		k = j;

		temp = card[k];
		card[k] = card[i];
		card[i] = temp;
	}

	for( i = n-1, player->result = -1; i >= 0; i-- )							// 카드 가지고 있는 것 count 하는 반복문
	{
		if( i >= 4 && card[i]%14 >= 4 && card[i] == card[i-4] + 4 )
			if( card[i]%14 == 13 )					{	player->result = 64*12 + 4*12 + card[i]/14;	return; }
			else if( card[i]%14 == 4 )				{	player->result = 64*11 + 4*12 + card[i]/14; return; }
			else									{	player->result = 64*10 + 4*(card[i]%14-1) + card[i]/14;	return;	}
		else if( card[i]%14 != 0 )												// 스티플 있는지 확인하는 조건문
		{
			if( (count_num[card[i]%14]+=1) == 4 )	{	player->result = 64*9 + 4*(card[i]%14-1) + 3;		return;	}
			if( (count_dgn[card[i]/14]+=1) == 5 )
				for( j=n-1; j>=i; j-- )
					if( card[i]/14 == card[j]/14 )	{	player->result = 64*7 + 4*(card[j]%14-1) + card[j]/14;		return;	}
		}																		// 포카드 있는지 확인하는 조건문
	}																			// 플러시 있는지 확인하는 조건문
	count_num[0] = count_num[13];

	for( i = 13, temp = 0; i >= 0; i-- )										// count된 값 확인
	{
		if( count_num[i] > 0 )
		{
			if( i>=4 && count_num[i-1]>0 && count_num[i-2]>0 && count_num[i-3]>0 && count_num[i-4]>0 )
				if( i == 13 )						{	player->result = 64*6 + 4*12; break;	}
				else if( i == 4 )					{	player->result = 64*5 + 4*12; break;	}
				else								{	player->result = 64*4 + 4*(i-1); break;	}
			else if( count_num[i] == 3 )										// 스트레이트 있는지 확인하는 조건문
				if( temp == 3 )		break;										// 트리플일 경우
				else if( temp > 0 )	{	player->result = 64*8 + 4*(i-1); break;	}
				else								player->result = 64*3 + 4*(i-1), temp = 3;
			else if( count_num[i] == 2 )										// 페어인 경우
				if( temp == 3 )		{	player->result += 64*5;	break;	}
				else if( temp == 2 )	break;
				else if( temp == 1 )	player->result += 64, temp = 2;
				else								player->result = 64 + 4*(i-1), temp = 1;
			else if( player->result == -1 )			player->result = 4*(i-1);	// 아무 패도 없을 때 탑 카드 지정
		}
	}

	for( i = n-1, temp = player->result%64/4+1; i >= 0; i-- )					// 탑 카드의 무늬 찾는 부분
		if( temp == card[i]%14 )					{	player->result += card[i]/14;	return;	}
}

int chk( char *card )															// 입력받은 카드를 확인하는 함수
{
	int num=-1, i;
	card[0] = toupper(card[0]), card[1] = toupper(card[1]);						// 소문자를 대문자로 치환

	for( i=0; i<13; i++ )	if( card[0] == *strn[i] ){	num = i+1;	break; }
	if( num == -1 )	return -1;													// 2~A 를 0~12로 치환 없을 경우 에러(-1)

	for( i=0; i<4; i++ )	if( card[1] == *strd[i] )	return num + 14*i;
	return -1;																	// C~S 를 (0~3)*13로 치환하여 반환, 없으면 에러(-1)
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.9.28