#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>																// ����� ���� ���ڿ� �迭
char *result[9] = { "high card", "one pair", "two pair", "triple", "straight", "flush", "full house", "four card", "straight flush"};
char *prtn[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
char *prtd[4] = { "C", "D", "H", "S" };
char *prtp[5] = { "Black", "White", "Blue", "Green", "Red" };

typedef struct																	// �÷��̾� ������ ���� ����ü
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
		printf("1. ����1\n2. ����2\n = ");
		if( scanf("%d", &menu) == EOF )	return;									// EOF �Է½� ����
		fflush(stdin);

		switch(menu){
			case 1: poker();	break;											// 1�� ���� ȣ��
			case 2: seven();	break;											// 2�� ���� ȣ��
			default: printf("�߸��� �Է��Դϴ�.\n\n"); break;					// 1,2 ���� �Է½� ���� �޽��� ���
		}
	}
}

void poker(){																	// ���� 1�� ���� �Լ�
	int i, j, temp;
	char card[10];
	Player player[2];

	printf("Black�� White�� ī�� �и� �Է��Ͻÿ�.\n");
	for( i=0; i<10; i++ ){
		if( scanf("%s",card) == EOF )	return;
		
		if( strlen(card) != 2 || (temp = chk(card)) == -1 ){					// �Է��� ī�尡 �´��� Ȯ��
			printf("�ùٸ� ī�带 �Է��ϼ���.\n\n");
			fflush(stdin);
			return;
		}
		for( j=0; j<i; j++ )													// �ߺ� �Էµ� ī�尡 �ִ��� Ȯ��
			if( player[j/5].card[j%5] == temp ){
				printf("�ߺ��� ī�带 �Է��Ͽ����ϴ�.\n\n");
				fflush(stdin);	
				return;
			}

		player[i/5].card[i%5] = temp;											// ���� ������ �÷��̾�� ī�� �Է�
	}

	rule(&player[0],5);															// �÷��̾��� �и� Ȯ��
	rule(&player[1],5);

	printf("\t-> Black = %s %s, White = %s %s (%s)\n\n", prtn[player[0].result%13], result[player[0].result/13], prtn[player[1].result%13], result[player[1].result/13], player[0].result == player[1].result ? "Tie" : (player[0].result>player[1].result ? "Black Wins" : "White Wins"));
}																				// ��� ���

void seven(){																	// ���� 2�� ���� �Լ�
	int deck[52], i, temp, temp2;
	Player player[5];
	srand((unsigned)time(NULL));
	
	for( i=0; i<52; i++ ) deck[i] = i;											// ī�� ���� �����ϰ� ����
	for( i=0; i<52; i++ ){
		temp2 = rand()%52;
		temp = deck[temp2];
		deck[temp2] = deck[i];
		deck[i] = temp;
	}

	for( i=0; i<35; i++ )	player[i%5].card[i/5]=deck[i];						// �÷��̾�鿡�� ī�带 ������ ��
	for( i=0, temp=0, temp2=0; i<5; i++ ){										// �÷��̾��� �и� Ȯ��
		rule(&player[i],7);
		if( player[i].result > player[temp].result )			temp = i;
		else if( player[i].result == player[temp].result )		temp2 = i;
	}

	for( i=0; i<35; i++ ){														// �÷��̾ ���� ī�带 ���
		if( i%7 == 0 )	printf("%s : ", prtp[i/7]);
		printf("%s%s ", prtn[player[i/7].card[i%7]%13], prtd[player[i/7].card[i%7]/13] );
		if( i%7 == 6 )	printf("(%s %s)\n", prtn[player[i/7].result%13], result[player[i/7].result/13] );
	}
	if( temp2 != 0 && player[temp2].result == player[temp].result )	printf("\t%s, %s Tie\n\n", prtp[temp], prtp[temp2] );
	else printf("\tWinner = %s\n\n", prtp[temp]);								// ���� ���� ���
}

void rule(Player *player, int n)												// �÷��̾��� �и� Ȯ���ϴ� �Լ�
{
	int i, j, k, temp, count_num[13]={0}, count_dgn[4]={0};

	for( i=0; i<n-1; i++ ){														// �÷��̾��� �и� ������� ����
		for( j=i+1, k=i; j<n; j++ )
			if( player->card[k] > player->card[j] )		k = j;
		
		temp = player->card[k];
		player->card[k] = player->card[i];
		player->card[i] = temp;
	}

	for( i=0; i<n; i++ ){														// ī�� ������ �ִ� �� count �ϴ� �ݺ���
		if( i <= n-5 && player->card[i] == player->card[i+4] - 4 )	{	player->result = player->card[i+4]%13 + 104;	return;	}
		else{																	// ��Ƽ�� �ִ��� Ȯ���ϴ� ���ǹ�
			if( (count_num[player->card[i]%13]+=1) == 4 )			{	player->result = player->card[i]%13 + 91;		return;	}
			if( (count_dgn[player->card[i]/13]+=1) == 5 )			{	player->result = player->card[i]%13 + 65;		return;	}
		}																		// ��ī�� �ִ��� Ȯ���ϴ� ���ǹ�
	}																			// �÷��� �ִ��� Ȯ���ϴ� ���ǹ�

	for( i=12, player->result = -1; i>=0; i-- )									// count�� �� Ȯ��
	{
		if( count_num[i] > 0 )
		{
			if( i>=4 && count_num[i-1]>0 && count_num[i-2]>0 && count_num[i-3]>0 && count_num[i-4]>0 )	{	player->result = i + 52;	return;	}
			else if( count_num[i] == 3 )										// ��Ʈ����Ʈ �ִ��� Ȯ���ϴ� ���ǹ�
				switch( player->result/13 ){									// Ʈ������ ���
					case 3 : return;											// ������ Ʈ���� �־����� �ƿ�
					case 2 :
					case 1 : player->result = i + 78;	return;					// �� ������ Ǯ�Ͽ콺
					default : player->result = i + 39;							// �ƹ��͵� �ƴϸ� �׳� Ʈ����
				}
			else if( count_num[i] == 2 )										// ����� ���
				switch( player->result/13 ){
					case 3 : player->result += 39;	return;						// Ʈ������ ������ Ǯ�Ͽ콺
					case 2 : return;											// ������ ���� �־����� �ƿ�
					case 1 : player->result += 13;	break;						// ������ ���� �־����� �����
					case 0 : player->result = i + 13;							// �ƹ��͵� �ƴϸ� �׳� �����
				}
			else if( player->result == -1 )		player->result = i;				// �ƹ� �е� ���� �� ž ī�� ����
		}
	}
}

int chk(char *card){															// �Է¹��� ī�带 Ȯ���ϴ� �Լ�
	int num=-1, i;
	card[0] = toupper(card[0]), card[1] = toupper(card[1]);						// �ҹ��ڸ� �빮�ڷ� ġȯ

	for( i=0; i<13; i++ )	if( strncmp( &card[0], prtn[i], 1 ) == 0 ){	num = i;	break; }
	if( num == -1 )	return -1;													// 2~A �� 0~12�� ġȯ ���� ��� ����(-1)
	for( i=0; i<4; i++ )	if( strncmp( &card[1], prtd[i], 1 ) == 0 )	return num + 13*i;
	return -1;																	// C~S �� (0~3)*13�� ġȯ�Ͽ� ��ȯ, ������ ����(-1)
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.9.28