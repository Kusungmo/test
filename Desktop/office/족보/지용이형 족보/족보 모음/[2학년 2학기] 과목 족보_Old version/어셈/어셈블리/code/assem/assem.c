 /* 샘플코드 
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
typedef struct { //명령어 구조
	unsigned short opcode:4;
	unsigned short operand:8;
}inc;

inc memory[256]; //총 메모리
short r1,r2,r3,r4; //레지스터
inc mbr; 
char pc1[4];
int pc,mar;

//---함수원형
void inc_print(inc);
void decode(inc);
void two (int);

//---메인----------------------------------------
void main(){
	int add, opco, oper, i;
	char ad[4], opc[4], ope[4];
	char menu, inter;
	printf("		  ┏━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("		  ┃        。Assembly Team Project。       ┃\n");
	printf("		  ┃      팀원 : 임영신, 김은미, 강정희     ┃\n");
	printf("		  ┗━━━━━━━━━━━━━━━━━━━━┛\n");
	
	while(1){
		printf("\n  ┌───────────┐\n");
		printf("  │     【 M E N U 】    │\n");
		printf("  │ a : 메모리에 저장    │\n");
		printf("  │ p : PC값 입력        │\n");
		printf("  │ c : 실행             │\n");
		printf("  │ i : 인터럽트         │\n");
		printf("  │ e : 종료             │\n");
		printf("  └───────────┘\n\n");
		
		printf("  * 선택하세요 : "); //메뉴얼은 나중에....
		scanf("%c", &menu);
		switch(menu){
		case 'a': // 메모리번지에 입력 
			while(1){
				printf("  - [address][opcode][operand] : ");
				
				// 2진수로 입력받기 위해  
				fflush(stdin);
				for(i=0; i<4; i++)
					scanf("%c", &ad[i]);
				for(i=0; i<4; i++)
					scanf("%c", &opc[i]);
				for(i=0; i<4; i++)
					scanf("%c", &ope[i]);
				
				// 2진수 형태로 입력받은걸 10진수로 바꾸기 
				add = 8*(ad[0]-48) + 4*(ad[1]-48) + 2*(ad[2]-48) + 1*(ad[3]-48);
				opco =  8*(opc[0]-48) + 4*(opc[1]-48) + 2*(opc[2]-48) + 1*(opc[3]-48);
				oper = 8*(ope[0]-48) + 4*(ope[1]-48) + 2*(ope[2]-48) + 1*(ope[3]-48);
				
				// 입력값이 음수가 아니라면 해당번지에 opcode,operand 저장
				if(add>=0 && opco>=0 && oper>=0){
					memory[add].opcode=opco;
					memory[add].operand=oper; 
					continue;
				}
				break; // 입력값이 음수면 종료 (한개라도..)
			}
			break;
			
		case 'p': // pc값 입력 
			printf("  - Input PC : ");
			// 2진수로 입력받기 위해
			fflush(stdin);
			for(i=0; i<4; i++)
				scanf("%c", &pc1[i]);
			// 2진수 형태로 입력받은걸 10진수로 바꾸기 
			pc = 8*(pc1[0]-48) + 4*(pc1[1]-48) + 2*(pc1[2]-48) + 1*(pc1[3]-48);
			break;
			
		case 'c': // 실행 
			printf("\n  - PC = "); two(pc); printf("\n");
			mar=pc; // mar에 pc값을 넣어줌
			printf("  - MAR <- "); two(pc); printf("\n");
			
			// 해당번지의 opcode,operand를 mbr에 저장
			mbr.opcode=memory[pc].opcode;
			mbr.operand=memory[pc].operand;
			printf("  - MBR <- "); inc_print(mbr);
			decode(mbr); // 명령어 해독
			break;
			
		case 'i': // 인터럽트 
			printf( " ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼\n");
			printf("     !!!인터럽트 실행!!! \n") ;
			printf("   인터럽트 종료하려면 r입력\n");

			while(1){
				scanf("%c", &inter);
				if(inter=='r')
					break; 	
				printf("     --interrupt mode--");

				fflush(stdin); 
			}
			printf("     !!!인터럽트 종료!!! \n");
			printf(" ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ \n");
			break;
			
		case 'e': // 프로그램 종료
			printf("  - 프로그램을 종료합니다. ByeBye~\n");
			exit(1);
			break;
			
		default:
			printf("똑바로 입력하셈!");
			
		}//switch
		fflush(stdin);
	}//while
	
}//main
//------10진수를 2진수로 출력------------
void two (int dec){
	// 입력받은 10진수값을 2로 나눈 나머지를 배열에 저장
	int i;
	int a[4] ;
	
	a[3] = dec % 2 ;
	dec = dec / 2 ;
	a[2] = dec % 2 ; 
	dec = dec / 2 ; 
	a[1] = dec % 2 ; 
	a[0] = dec / 2   ;
	// 출력
	for ( i = 0 ; i < 4 ; i ++ )
		printf ("%d", a[i] ) ;
}
//----ㅡmbr 이진수 출력-------------------
void inc_print(inc i){
	// 입력받은 structure안에있는 10진수값을 2로 나눈 나머지를 배열에 저장
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

//---디코드-------------------------------------
void decode(inc mbr) {

	printf("\n   ━━━━━━━━━━ \n");
	printf("   。Decoder Execution 。 \n");
	printf("   ━━━━━━━━━━ \n");
	r2=mbr.opcode; // mbr의 opcode를 r2에 저장
	r3=mbr.operand; // mbr의 operand를 r3에 저장
	switch(r2){ 
	case 0: // 명령어 HALT
		if(r3==0){ //r3가 0이면 종료
			printf("       ≪ END ≫\n");
			pc=14;
			exit(1);
		}
		break;
	case 1: // 명령어 LOAD
		printf("        ≪ LOAD ≫ \n");
		r1=memory[r3].operand; // r3의 operand를 r1에 저장
		printf("  - R1 <==memory["); two(r3); printf("]\n");
		pc++; // pc값 증가
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 2: // 명령어 STOR
		printf("        ≪ STORD ≫ \n");
		memory[r3].operand=r1; // r1의 값을 r3의 operand에 저장
		printf("  - memory["); two(r3); printf("] <-- R1\n");
		pc++; // pc값 증가
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 3: // 명령어 ADD
		printf("        ≪ ADD ≫  \n");
		printf("  - ALU에 의해서 덧셈 연산\n");
		r1+=memory[r3].operand; // r1의 값에 r3의 operand의 값을 더한후 r1에 저장
		printf("  - R1 = R1 + memory["); two(r3); printf("] \n");
		pc++;// pc값 증가
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 4: // 명령어 SUBT
		printf("        ≪ SUB ≫ \n");
		printf("  - ALU에 의해서 연산\n");
		r1 -= memory[r3].operand; // r1의 값에 r3의 operand의 값을 뺀후 r1에 저장
		printf("  - R1 = R1 - memory["); two(r3); printf("] \n");
		pc++;// pc값 증가
		printf("  - PC +1 \n");
		printf("\n") ;
		break;
	case 5: // 명령어 JL
		printf("        ≪ JL ≫ \n");
		if(r1<10){ //r1의 값이 10 보다 작다면
			pc=r3; // pc값을 r3로 
			printf("  - PC = "); two(r3); printf("\n");
		}
		else{
			pc++;// pc값 증가
			printf("  - PC +1 \n");
		}
		printf("\n") ;
		break;
	case 6: // 명령어 JMP
		printf("        ≪ JMP ≫ \n");
		pc=r3; // pc값을 r3로. 무조건 분기
		printf("  - PC = "); two(r3); printf("\n");
		printf("\n") ;
		break;
	case 7: // 명령어 PRINT
		printf("        ≪ PRINT ≫ \n");
		printf ("  - ") ;
		two(r3); printf("번지 = "); two(memory[r3].operand);
		pc++;// pc값 증가
		printf("\n  - PC +1 \n");
		printf("\n") ;
		break;
	default:
		printf("        ≪  잘못된 opcode 입니다. ≫ \n");
		printf("\n") ;		
	}//switch
	
}





