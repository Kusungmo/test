#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
char *strp[5] = { "Black", "White", "Blue", "Green", "Red" };					// ����� ���� ���ڿ� �迭
char *strd[4] = { "C", "H", "D", "S" };
char *strn[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
char *strr[13] = { "Top", "One Pair", "Two Pair", "Triple", "Straight", "Back Straght", "Mountain", "Flush", "Full House", "Four Card", "Straight Flush", "Back Straight Flush", "Royal Straight Flush"};

typedef struct																	// �÷��̾� ������ ���� ����ü
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
		printf("1. ����1\n2. ����2\n = ");
		if( scanf("%d", &menu) == EOF )	return;									// EOF �Է½� ����
		fflush(stdin);

		switch(menu)
		{
			case 1: poker();	break;											// 1�� ���� ȣ��
			case 2: seven();	break;											// 2�� ���� ȣ��
			default: printf("�߸��� �Է��Դϴ�.\n\n"); break;					// 1,2 ���� �Է½� ���� �޽��� ���
		}
	}
}

void poker()																	// ���� 1�� ���� �Լ�
{
	int i, j, temp;
	char card[10];
	Player player[2];

	printf("Black�� White�� ī�� �и� �Է��Ͻÿ�.\n");
	for( i=0; i<10; i++ ){
		if( scanf("%s",card) == EOF )	return;
		
		if( strlen(card) != 2 || (temp = chk(card)) == -1 )						// �Է��� ī�尡 �´��� Ȯ��
		{
			printf("�ùٸ� ī�带 �Է��ϼ���.\n\n");
			fflush(stdin);
			return;
		}

		for( j=0; j<i; j++ )													// �ߺ� �Էµ� ī�尡 �ִ��� Ȯ��
			if( player[j/5].card[j%5] == temp )
			{
				printf("�ߺ��� ī�带 �Է��Ͽ����ϴ�.\n\n");
				fflush(stdin);	
				return;
			}

		player[i/5].card[i%5] = temp;											// ���� ������ �÷��̾�� ī�� �Է�
	}

	rule(&player[0],5);															// �÷��̾��� �и� Ȯ��
	rule(&player[1],5);

	printf("\t-> Black = %s %s, White = %s %s ", strn[player[0].result%64/4], strr[player[0].result/64], strn[player[1].result%64/4], strr[player[1].result/64]);
	printf("(%s)\n\n", player[0].result/4 == player[1].result/4 ? "Tie" : (player[0].result>player[1].result ? "Black Wins" : "White Wins" ));
}																				// ��� ���

void seven()																	// ���� 2�� ���� �Լ�
{
	int deck[52], i, j, temp;
	Player player[5];
	srand((unsigned)time(NULL));
	
	for( i=0, temp=0; i<52; deck[i++] = i+temp )								// ī�� �� ����
		if( i%13 == 0 )	temp++;

	for( i=0; i<52; i++ )														// ī�� �� ����
	{
		temp = deck[j = rand()%52];
		deck[j] = deck[i];
		deck[i] = temp;
	}

	for( i=0; i<35; i++ )	player[i%5].card[i/5]=deck[i];						// �÷��̾�鿡�� ī�带 7�徿 ������ ��

	for( i=0, temp=0; i<5; i++ )												// �÷��̾��� �и� Ȯ��
	{
		rule( &player[i], 7 );
		if( player[i].result > player[temp].result )	temp = i;
	}

	for( i=0; i<35; i++ )														// �÷��̾ ���� ī�带 ���
	{
		if( i%7 == 0 )	printf("%s : ", strp[i/7]);
		printf("%s%s ", strn[player[i/7].card[i%7]%14-1], strd[player[i/7].card[i%7]/14] );
		if( i%7 == 6 )	printf("(%s%s %s)\n", strn[player[i/7].result%64/4], strd[player[i/7].result%4], strr[player[i/7].result/64] );
	}
	printf("\tWinner = %s\n\n", strp[temp]);									// ���� ���� ���
}

void rule(Player *player, int n)												// �÷��̾��� �и� Ȯ���ϴ� �Լ�
{
	int i, j, k, temp = n, card[11], count_num[14] = {0}, count_dgn[4] = {0};

	for( i = 0; i < temp; card[i] = player->card[i], i++ )						// �÷��̾� ī�� ����
		if( player->card[i]%14 == 13 )	card[n++] = player->card[i]-13;

	for( i = 0; i < n; i++ )													// �÷��̾��� �и� ������� ����
	{
		for( j=i+1, k=i; j<n; j++ )
			if( card[k] > card[j] )		k = j;

		temp = card[k];
		card[k] = card[i];
		card[i] = temp;
	}

	for( i = n-1, player->result = -1; i >= 0; i-- )							// ī�� ������ �ִ� �� count �ϴ� �ݺ���
	{
		if( i >= 4 && card[i]%14 >= 4 && card[i] == card[i-4] + 4 )
			if( card[i]%14 == 13 )					{	player->result = 64*12 + 4*12 + card[i]/14;	return; }
			else if( card[i]%14 == 4 )				{	player->result = 64*11 + 4*12 + card[i]/14; return; }
			else									{	player->result = 64*10 + 4*(card[i]%14-1) + card[i]/14;	return;	}
		else if( card[i]%14 != 0 )												// ��Ƽ�� �ִ��� Ȯ���ϴ� ���ǹ�
		{
			if( (count_num[card[i]%14]+=1) == 4 )	{	player->result = 64*9 + 4*(card[i]%14-1) + 3;		return;	}
			if( (count_dgn[card[i]/14]+=1) == 5 )
				for( j=n-1; j>=i; j-- )
					if( card[i]/14 == card[j]/14 )	{	player->result = 64*7 + 4*(card[j]%14-1) + card[j]/14;		return;	}
		}																		// ��ī�� �ִ��� Ȯ���ϴ� ���ǹ�
	}																			// �÷��� �ִ��� Ȯ���ϴ� ���ǹ�
	count_num[0] = count_num[13];

	for( i = 13, temp = 0; i >= 0; i-- )										// count�� �� Ȯ��
	{
		if( count_num[i] > 0 )
		{
			if( i>=4 && count_num[i-1]>0 && count_num[i-2]>0 && count_num[i-3]>0 && count_num[i-4]>0 )
				if( i == 13 )						{	player->result = 64*6 + 4*12; break;	}
				else if( i == 4 )					{	player->result = 64*5 + 4*12; break;	}
				else								{	player->result = 64*4 + 4*(i-1); break;	}
			else if( count_num[i] == 3 )										// ��Ʈ����Ʈ �ִ��� Ȯ���ϴ� ���ǹ�
				if( temp == 3 )		break;										// Ʈ������ ���
				else if( temp > 0 )	{	player->result = 64*8 + 4*(i-1); break;	}
				else								player->result = 64*3 + 4*(i-1), temp = 3;
			else if( count_num[i] == 2 )										// ����� ���
				if( temp == 3 )		{	player->result += 64*5;	break;	}
				else if( temp == 2 )	break;
				else if( temp == 1 )	player->result += 64, temp = 2;
				else								player->result = 64 + 4*(i-1), temp = 1;
			else if( player->result == -1 )			player->result = 4*(i-1);	// �ƹ� �е� ���� �� ž ī�� ����
		}
	}

	for( i = n-1, temp = player->result%64/4+1; i >= 0; i-- )					// ž ī���� ���� ã�� �κ�
		if( temp == card[i]%14 )					{	player->result += card[i]/14;	return;	}
}

int chk( char *card )															// �Է¹��� ī�带 Ȯ���ϴ� �Լ�
{
	int num=-1, i;
	card[0] = toupper(card[0]), card[1] = toupper(card[1]);						// �ҹ��ڸ� �빮�ڷ� ġȯ

	for( i=0; i<13; i++ )	if( card[0] == *strn[i] ){	num = i+1;	break; }
	if( num == -1 )	return -1;													// 2~A �� 0~12�� ġȯ ���� ��� ����(-1)

	for( i=0; i<4; i++ )	if( card[1] == *strd[i] )	return num + 14*i;
	return -1;																	// C~S �� (0~3)*13�� ġȯ�Ͽ� ��ȯ, ������ ����(-1)
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.9.28