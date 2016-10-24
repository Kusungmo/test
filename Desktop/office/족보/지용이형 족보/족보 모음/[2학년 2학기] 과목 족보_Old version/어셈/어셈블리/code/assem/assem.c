 /* �����ڵ� 
000000111000
000100111100
001001010001
001100101101
010001111101
010100000000
110000000011
-100000000000
*/

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
typedef struct { //��ɾ� ����
	unsigned short opcode:4;
	unsigned short operand:8;
}inc;

inc memory[256]; //�� �޸�
short r1,r2,r3,r4; //��������
inc mbr; 
char pc1[4];
int pc,mar;

//---�Լ�����
void inc_print(inc);
void decode(inc);
void two (int);

//---����----------------------------------------
void main(){
	int add, opco, oper, i;
	char ad[4], opc[4], ope[4];
	char menu, inter;
	printf("		  ��������������������������������������������\n");
	printf("		  ��        ��Assembly Team Project��       ��\n");
	printf("		  ��      ���� : �ӿ���, ������, ������     ��\n");
	printf("		  ��������������������������������������������\n");
	
	while(1){
		printf("\n  ��������������������������\n");
		printf("  ��     �� M E N U ��    ��\n");
		printf("  �� a : �޸𸮿� ����    ��\n");
		printf("  �� p : PC�� �Է�        ��\n");
		printf("  �� c : ����             ��\n");
		printf("  �� i : ���ͷ�Ʈ         ��\n");
		printf("  �� e : ����             ��\n");
		printf("  ��������������������������\n\n");
		
		printf("  * �����ϼ��� : "); //�޴����� ���߿�....
		scanf("%c", &menu);
		switch(menu){
		case 'a': // �޸𸮹����� �Է� 
			while(1){
				printf("  - [address][opcode][operand] : ");
				
				// 2������ �Է¹ޱ� ����  
				fflush(stdin);
				for(i=0; i<4; i++)
					scanf("%c", &ad[i]);
				for(i=0; i<4; i++)
					scanf("%c", &opc[i]);
				for(i=0; i<4; i++)
					scanf("%c", &ope[i]);
				
				// 2���� ���·� �Է¹����� 10������ �ٲٱ� 
				add = 8*(ad[0]-48) + 4*(ad[1]-48) + 2*(ad[2]-48) + 1*(ad[3]-48);
				opco =  8*(opc[0]-48) + 4*(opc[1]-48) + 2*(opc[2]-48) + 1*(opc[3]-48);
				oper = 8*(ope[0]-48) + 4*(ope[1]-48) + 2*(ope[2]-48) + 1*(ope[3]-48);
				
				// �Է°��� ������ �ƴ϶�� �ش������ opcode,operand ����
				if(add>=0 && opco>=0 && oper>=0){
					memory[add].opcode=opco;
					memory[add].operand=oper; 
					continue;
				}
				break; // �Է°��� ������ ���� (�Ѱ���..)
			}
			break;
			
		case 'p': // pc�� �Է� 
			printf("  - Input PC : ");
			// 2������ �Է¹ޱ� ����
			fflush(stdin);
			for(i=0; i<4; i++)
				scanf("%c", &pc1[i]);
			// 2���� ���·� �Է¹����� 10������ �ٲٱ� 
			pc = 8*(pc1[0]-48) + 4*(pc1[1]-48) + 2*(pc1[2]-48) + 1*(pc1[3]-48);
			break;
			
		case 'c': // ���� 
			printf("\n  - PC = "); two(pc); printf("\n");
			mar=pc; // mar�� pc���� �־���
			printf("  - MAR <- "); two(pc); printf("\n");
			
			// �ش������ opcode,operand�� mbr�� ����
			mbr.opcode=memory[pc].opcode;
			mbr.operand=memory[pc].operand;
			printf("  - MBR <- "); inc_print(mbr);
			decode(mbr); // ��ɾ� �ص�
			break;
			
		case 'i': // ���ͷ�Ʈ 
			printf( " ����������������\n");
			printf("     !!!���ͷ�Ʈ ����!!! \n") ;
			printf("   ���ͷ�Ʈ �����Ϸ��� r�Է�\n");

			while(1){
				scanf("%c", &inter);
				if(inter=='r')
					break; 	
				printf("     --interrupt mode--");

				fflush(stdin); 
			}
			printf("     !!!���ͷ�Ʈ ����!!! \n");
			printf(" ���������������� \n");
			break;
			
		case 'e': // ���α׷� ����
			printf("  - ���α׷��� �����մϴ�. ByeBye~\n");
			exit(1);
			break;
			
		default:
			printf("�ȹٷ� �Է��ϼ�!");
			
		}//switch
		fflush(stdin);
	}//while
	
}//main
//------10������ 2������ ���------------
void two (int dec){
	// �Է¹��� 10�������� 2�� ���� �������� �迭�� ����
	int i;
	int a[4] ;
	
	a[3] = dec % 2 ;
	dec = dec / 2 ;
	a[2] = dec % 2 ; 
	dec = dec / 2 ; 
	a[1] = dec % 2 ; 
	a[0] = dec / 2   ;
	// ���
	for ( i = 0 ; i < 4 ; i ++ )
		printf ("%d", a[i] ) ;
}
//----��mbr ������ ���-------------------
void inc_print(inc i){
	// �Է¹��� structure�ȿ��ִ� 10�������� 2�� ���� �������� �迭�� ����
	int j;
	int a[4], b[4] ;
	
	a[3] = i.opcode % 2 ;
	i.opcode = i.opcode / 2 ;
	a[2] =  i.opcode % 2 ; 
	i.opcode =  i.opcode / 2 ; 
	a[1] =  i.opcode % 2 ; 
	a[0] =  i.opcode / 2   ;
	
	b[3] = i.operand % 2 ;
	i.operand = i.operand / 2 ;
	b[2] =  i.operand % 2 ; 
	i.operand =  i.operand / 2 ; 
	b[1] =  i.operand % 2 ; 
	b[0] =  i.operand / 2   ;
	
	for ( j = 0 ; j < 4 ; j ++ )
		printf ("%d", a[j] ) ;
	printf (" ") ; 
	for ( j = 0 ; j < 4 ; j ++ )
		printf ("%d", b[j] ) ;
	printf ("\n") ;
} 

//---���ڵ�-------------------------------------
void decode(inc mbr) {

	printf("\n   �������������������� \n");
	printf("   ��Decoder Execution �� \n");
	printf("   �������������������� \n");
	r2=mbr.opcode; // mbr�� opcode�� r2�� ����
	r3=mbr.operand; // mbr�� operand�� r3�� ����
	switch(r2){ 
	case 0: // ��ɾ� HALT
		if(r3==0){ //r3�� 0�̸� ����
			printf("       �� END ��\n");
			pc=14;
			exit(1);
		}
		break;
	case 1: // ��ɾ� LOAD
		printf("        �� LOAD �� \n");
		r1=memory[r3].operand; // r3�� operand�� r1�� ����
		printf("  - R1 <==memory["); two(r3); printf("]\n");
		pc++; // pc�� ����
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 2: // ��ɾ� STOR
		printf("        �� STORD �� \n");
		memory[r3].operand=r1; // r1�� ���� r3�� operand�� ����
		printf("  - memory["); two(r3); printf("] <-- R1\n");
		pc++; // pc�� ����
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 3: // ��ɾ� ADD
		printf("        �� ADD ��  \n");
		printf("  - ALU�� ���ؼ� ���� ����\n");
		r1+=memory[r3].operand; // r1�� ���� r3�� operand�� ���� ������ r1�� ����
		printf("  - R1 = R1 + memory["); two(r3); printf("] \n");
		pc++;// pc�� ����
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 4: // ��ɾ� SUBT
		printf("        �� SUB �� \n");
		printf("  - ALU�� ���ؼ� ����\n");
		r1 -= memory[r3].operand; // r1�� ���� r3�� operand�� ���� ���� r1�� ����
		printf("  - R1 = R1 - memory["); two(r3); printf("] \n");
		pc++;// pc�� ����
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 5: // ��ɾ� JL
		printf("        �� JL �� \n");
		if(r1<10){ //r1�� ���� 10 ���� �۴ٸ�
			pc=r3; // pc���� r3�� 
			printf("  - PC = "); two(r3); printf("\n");
		}
		else{
			pc++;// pc�� ����
			printf("  - PC +1 \n");
		}
		printf("\n") ;
		break;
	case 6: // ��ɾ� JMP
		printf("        �� JMP �� \n");
		pc=r3; // pc���� r3��. ������ �б�
		printf("  - PC = "); two(r3); printf("\n");
		printf("\n") ;
		break;
	case 7: // ��ɾ� PRINT
		printf("        �� PRINT �� \n");
		printf ("  - ") ;
		two(r3); printf("���� = "); two(memory[r3].operand);
		pc++;// pc�� ����
		printf("\n  - PC +1 \n");
		printf("\n") ;
		break;
	default:
		printf("        ��  �߸��� opcode �Դϴ�. �� \n");
		printf("\n") ;		
	}//switch
	
}





