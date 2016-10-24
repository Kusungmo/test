
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc()함수 사용

//도서에 대한 구조체 선언
typedef struct 
        {
	 char b_name[30];
	 char b_number[30];
	 char auther[30];
	 int b_empty;
	 
	 } Book;

//회원에 대한 구조체 선언
typedef struct
	{
	 char name[30];
	 char number[30];
	 char address[30];
	 char list[30];
	 int empty;
	 } Client;

FILE *fp;
Book *bp,*bp1;
Client *cp,*cp1;

int i,num;
char yes_no;
char tmp_number[5];
int is_client(char number[5]);

void intro();
void main_menu();
void client_menu();
void book_menu();
void give_take_menu();
void give_take();
void c_insert();
void insert();
void c_search();
void search();
void c_delete();
void delete();
void c_update();
void update();
void give();
void take();

/*******************************/
/* main                        */
/*******************************/
main()
    {
     intro();
     while(1)
          {
	       main_menu();
           }
     }
/********************************/
/*         intro                */
/********************************/
void intro()
      {
       
       system("cls");
       printf("\n\n\n\t\t★★★★★★★★★★★★★★★★★★★★★★★★★\n");
       printf("\n\t\t\t프로그램명 : 도서관리 프로그램\n");
       printf("\t\t\t\n");
       printf("\t\t\t\n");
	   printf("\t\t\t\n");
	   printf("\t\t\t\n");
       printf("\t\t\t잘부탁 드립니다~ \n\n");
       printf("\t\t★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	   printf("\n\n\t\t\t아무키나 누르세요");
       getchar();
       }


/****************************/
/*        main_menu         */
/****************************/
void main_menu()
     {
      system("cls");
      fflush(stdin);//입력 버퍼에 있는 스트림을 깨끗하게 비운다.
      printf("\n\n\n\n");
      printf("\t\t\t------------------------------------\n");
      printf("\t\t\t1.고객관리\n");
      printf("\t\t\t2.책관리\n");
      printf("\t\t\t3.대여관리\n");
      printf("\t\t\t4.종료\n");
      printf("\t\t\t------------------------------------\n");
      printf("\t\t\t원하는 번호를 선택하세요:");
      scanf("%d",&num);
      switch(num)
            {
	     case 1 : client_menu();
                        break;
	     case 2 : book_menu();
                        break;
	     case 3 : give_take_menu();
			break;
	     case 4 : exit(1);
                        break;
	     default : printf("\t\t\t잘못선택하였습니다!!!\n");
			main_menu();
              }
      }

/*****************************************/
/*                                       */
/*             회원 관리                 */
/*                                       */
/*****************************************/

void client_menu()
     {
      
      system("cls");
      fflush(stdin);
      
	  printf("\n\n\n\n");
      printf("\t\t\t------------------------------------\n");
	  
	  printf("\t\t\t1.회원 등록하기\n");
      printf("\t\t\t2.회원 찾기\n");
      printf("\t\t\t3.회원 삭제 \n");
      printf("\t\t\t4.회원 수정\n");
      printf("\t\t\t5.메인메뉴로....\n");
      printf("\t\t\t------------------------------------\n\n");
      printf("\t\t\t원하는 번호를 선택하세요:");
      //원하는 메뉴를 선택받음
	  scanf("%d",&num);
      
	  switch(num)
            {
	     case 1 : c_insert();//회원 등록 함수  호출 
                        break;
	     case 2 : c_search();//회원 찾기  함수 호출 
                        break;
	     case 3 : c_delete();//회원 지우기  함수 호출
                        break;
	     case 4 : c_update();//회원 수정 함수 호출
                        break;
	     case 5 : main_menu();//회원  메뉴함수 호출
                        break;
	     default : printf("잘못선택하였습니다!!!\n");
			 //1~5의 숫자가 아닐경우 다시 회원관리 메뉴로 돌아감
					client_menu();
              }
      }

/************************************/
/*             회원  등록           */
/************************************/

void c_insert()
     {
		//calloc:메모리 블럭을 client 용량의 1개을 확보후 0으로 초기화함 
		cp = (Client *)calloc(1,sizeof(Client));
		cp1 = (Client *)calloc(1,sizeof(Client));
	  
		//system:도스에 있는 명령어 실행
		//화면을 지움
		system("cls");

		fflush(stdin);
      
		printf("\n\n\n\t\t회원 이름 :");
		gets(cp->name);//name에 입력받은 것을 cp에 저장
		printf("\n\t\t회원 번호 :");
		gets(cp->number);//number에 입력받은 것을 cp에 저장
		printf("\n\t\t회원 주소 :");
		gets(cp->address);//address에 입력받은 것을 cp에 저장
		cp->empty = 1;//empty cp에 1저장,자료가 있다는 것을 확인하기 위해 
		fp = fopen("c_data.txt","a+");//c_data.txt화일을 읽기및 쓰기위해 추가하거나 생성한다
		printf("\t\t등록되었습니다.\n");
		printf("\t\t아무키나 누르세요");
		getchar();
		rewind(fp);//화일의 시작점으로 fp에 있는 화일 포인터를 이동한다.
		
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력
		//null이 아닐경우 반복 
		while(fread(cp1,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp가 지적하는 화일포인터에 현재위치를 i에 저장
				if( cp1->empty == 0)
					{
						fclose(fp);//fp로 지정한 화일을 닫는다
						fp = fopen("c_data.txt","r+");//읽기와 쓰기를 위해 'c_data.txt'를 염  
						//화일의선두에서 i-sizeof(Client) 만큼의 새 위치로 fp에 따른 화일 포인터 이동
						fseek(fp,i-sizeof(Client),SEEK_SET);
						fwrite(cp,sizeof(Client),1,fp);//1만큼 데이타를 fp화일에 기입
						fclose(fp);//fp로 지정한 화일을 닫는다
						return;
					}
			}
		fclose(fp);//fp로 지정한 화일을 닫는다
		fp = fopen("c_data.txt","a+");//읽기와 쓰기를 위해 'c_data.txt'생성 
		fwrite(cp,sizeof(Client),1,fp);//1만큼 데이타를 fp화일에 기입
		fclose(fp);//fp로 지정한 화일을 닫는다
      }

/**********************************/
/*            회원  찾기          */
/**********************************/
void c_search()
     {
		//system:도스에 있는 명령어 실행
		//화면을 지움
        system("cls");
        fflush(stdin);
       
	    printf("\n\n\n\t\t회원 번호를 입력하세요:");
        gets(tmp_number);//회원번호입력받음 
        fp = fopen("c_data.txt","r");//읽기 위해 'c_data.txt'를 염 
        //calloc:메모리 블럭 client 1개을 확보후 0으로 초기화함 
		cp=(Client *)calloc(1,sizeof(Client));
       	
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력
		//null이 아닐경우 반복 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				if(strcmp(cp->number,tmp_number) == 0)//number와 tmp_number를 비교하여 같을경우 실행 
					{
						if(cp->empty == 0)
						break;
						printf("\n\t\t--------------------------------------\n");
						printf("\t\t회원을 찾았습니다~~~~~~~~!");
						printf("\n\t\t--------------------------------------\n");
						printf("\t\t회원 이름 : %s\n",cp->name);
						printf("\t\t회원 번호 : %s\n",cp->number);
						printf("\t\t회원 주소 : %s",cp->address);
						printf("\n\t\t--------------------------------------\n");
						fclose(fp);//fp로 지정한 화일을 닫는다
						printf("\t\t아무키나 누르세요");
						getchar();
						return;
					 }
			}
       fclose(fp);//fp로 지정한 화일을 닫는다
       printf("\n\t\t%s회원은 없는 회원입니다........ !\n",tmp_number);
       printf("\n\t\t아무키나 누르세요");
	   getchar();
       }

/*******************************************/
/*           회원  지우기                  */
/*******************************************/

void c_delete()
     {
		char yes_no;
       //system:도스에 있는 명령어 실행
		//화면을 지움
		system("cls");
		fflush(stdin);
     
	   //삭제할 회원을 찾음
		printf("\n\n\n");
		printf("\t\t\t회원 번호를 입력하세요 :");
		gets(tmp_number);//회원 번호입력받음 
		fp=fopen("c_data.txt","r+");//읽기와 쓰기를 위해"c_data.txt"를 염
		//calloc:메모리 블럭 client 1개을 확보후 0으로 초기화함 
		cp=(Client *)calloc(1,sizeof(Client));
        
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력
		//null이 아닐경우 반복 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp가지정하는 화일 포인터의 현재 위치를 i에 저장
				if(strcmp(cp->number,tmp_number) == 0)//number와 tmp_number를 비교하여 같을경우 실행 
					{
						if(cp->empty == 0)
						break;
					    printf("\n\t\t----------------------------------\n");
						printf("\t\t회원을 찾았습니다~~~~!");
					    printf("\n\t\t----------------------------------\n");
						printf("\t\t회원 이름 : %s\n",cp->name);
						printf("\t\t회원 번호 : %s\n",cp->number);
						printf("\t\t회원 주소 : %s",cp->address);
					    printf("\n\t\t----------------------------------\n");
						printf("\t\t아무키나 누르세요");
						getchar();
						fclose(fp);
		  
						//회원 삭제 yes/no
						printf("\t\t회원을 삭제하겠습니까?(y/n)");
						scanf("%c",&yes_no);
		  
						if(yes_no == 'y') 	
							{
								fp = fopen("c_data.txt","r+");//읽고쓰기를 위해 'c_data.txt'를 염
								//화일의선두에서 i-sizeof(Client) 만큼의 새 위치로 fp에 따른 화일 포인터 이동
								fseek(fp,i - sizeof(Client),SEEK_SET);
								cp->empty = 0;
								fwrite(cp,sizeof(Client),1,fp);//1만큼 데이타를 fp화일에 기입
								fclose(fp);//fp로 지정한 화일을 닫는다
							 }
						return;
					}
		      }
       
		fclose(fp);//fp로 지정한 화일을 닫는다
		//회원을 찾지 못했을 경우
		printf("\n\n\t\t%s회원은 없는 회원입니다......",tmp_number);
		printf("\t\t아무키나 누르세요");
		getchar();
       }
/********************************************/
/*                회원  수정                */
/********************************************/
void c_update()
      {
        //system:도스에 있는 명령어 실행
		//화면을 지움
		system("cls");
		fflush(stdin);

		printf("\n\n\n\t\t회원 번호를 입력하세요 :");
		gets(tmp_number);
       
		fp = fopen("c_data.txt","r+");//읽고 쓰기를 위해 'c_data.txt'를 염  
		//calloc:메모리 블럭 client 1개을 확보후 0으로 초기화함 
		cp = (Client *)calloc(1,sizeof(Client));
        
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력
		//null이 아닐경우 반복 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp가지정하는 화일 포인터의 현재 위치를 i에 저장
				if(strcmp(cp->number,tmp_number) == 0)//number와 tmp_number를 비교하여 같을경우 실행 
					{
						 if(cp->empty == 0)
						 break;
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\t회원을 찾았습니다!");
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\t회원 이름 : %s\n",cp->name);
						 printf("\t\t회원 번호 : %s\n",cp->number);
						 printf("\t\t회원 주소 : %s",cp->address);
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\t아무키나 누르세요");
						 getchar();
						{	
							int a;
							//회원항목중 주정할 항목선택 
							printf("\n\t\t---------------------------------------------");
							printf("\n\t\t수정할 항목을 선택하세요\n");
							printf("\t\t----------------------------------------------\n");
							printf("\t\t1.회원 이름 \t2.회원 번호 \t3.회원 주소 ");
							printf("\n\t\t---------------------------------------------\n");
							
							scanf("\t\t\t%d",&a);
							fflush(stdin);
							switch(a)
								{
									case  1: 
										printf("\n\t\t새로운 회원 이름을 입력하세요 :");
										gets(cp->name);//새로운 이름을 저장
										printf("\t\t수정되었습니다.");
										break;
									case  2:
										printf("\n\t새로운 회원 번호를 입력하세요 :");
										gets(cp->number);//새로운 번호을 저장
										printf("\t\t수정되었습니다.");
										break;
									case 3:
										printf("\n\t새로운 회원 주소를 입력하세요 :");
										gets(cp->address);//새로운 주소을 저장
										printf("\t\t수정되었습니다.");
										break;
								}	

						 }

						fclose(fp);//fp로 지정한 화일을 닫는다
						fp = fopen("c_data.txt","r+");//읽고 쓰기를 위해 'c_data.txt'를 염 
						//화일의선두에서 i-sizeof(Client) 만큼의 새 위치로 fp에 따른 화일 포인터 이동
						fseek(fp,i - sizeof(Client),0);
						fwrite(cp,sizeof(Client),1,fp);//1만큼 데이타를 fp화일에 기입
						fclose(fp);//fp로 지정한 화일을 닫는다
						printf("\n\t\t아무키나 누르세요");
						getchar();
						 return;
					}
              }
			fclose(fp);//fp로 지정한 화일을 닫는다
			printf("\n\n\t\t%s회원은 없는 회원입니다......",tmp_number);
			printf("\n\t\t아무키나 누르세요");
			getchar();
       }


/*****************************************/
/*                                       */
/*             책   관리                 */
/*                                       */
/*****************************************/

void book_menu()
     {
		// system 도스 명령 실행
		// 화면을 지움
		system("cls"); 
		fflush(stdin);
		printf("\n\n\n\n");
		printf("\t\t\t------------------------------------\n");
		printf("\t\t\t1.책등록하기\n");
		printf("\t\t\t2.책찾기\n");
		printf("\t\t\t3.책지우기\n");
		printf("\t\t\t4.책수정\n");
		printf("\t\t\t5.메인메뉴\n");
		printf("\t\t\t------------------------------------\n");
		printf("\t\t\t원하는 번호를 선택하세요:");
		scanf("%d",&num); // 숫자 입력
		switch(num)
            {
				case 1 : insert(); // num이 1일 때 insert()함수로 
                        break;  //멈춰라
				case 2 : search();
                        break;
				case 3 : delete();
                        break;
				case 4 : update();
                        break;
				case 5 : main_menu();
                        break;
				default : printf("잘못선택하였습니다!!!\n"); /*1~5사이 숫자 아니면 출력*/
						book_menu(); /*book_menu()함수로 이동*/
              }
      }

/*****************************************/
/*             책 등록하기               */
/*****************************************/

void insert()
     {
		//calloc:메모리 블럭을 bp 용량의 1개을 확보후 0으로 초기화함//
		bp = (Book *)calloc(1,sizeof(Book));
		bp1 = (Book *)calloc(1,sizeof(Book));
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\t책제목 :");
		gets(bp->b_name); // b_name에 입력 받은 것을 bp에 저장 //
		printf("\n\t\t\t책번호 :");
		gets(bp->b_number); // b_number에 입력 받은 것을 bp에 저장  //
		printf("\n\t\t\t책저자 :");
		gets(bp->auther); // b_auther에 입력 받은 것을 bp에 저장 //
		bp->b_empty = 1; //empty bp에 1 저장 //
		fp = fopen("data.txt","a+"); // data.txt를 추가해서 열고 이에 대한 주소를 fp로 받는다 //
		rewind(fp); // 화일의 시작점으로 fp에 있는 화일 포인터를 이동한다 //
		
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 bp1으로 출력//
		//null이 아닐경우 반복 //
		while(fread(bp1,sizeof(Book),1,fp) != NULL)
			{
				i = ftell(fp); //fp가 지적하는 화일 포인터의 위치 i에 저장 //
				if( bp1->b_empty == 0) // bp에 들어갈 b_empty 값이 0이라면  //
					{
						fclose(fp); //화일 종료시 화일 포인터 fp를 닫는다 //
						fp = fopen("data.txt","r+"); // data.txt를 읽기 전용으로 열고 이에 대한 주소를 fp로 받는다 //
						fseek(fp,i-sizeof(Book),0);//처음에서 부터 i-client의 크기 만큼 건너 뛴다
						fwrite(bp,sizeof(Book),1,fp); //1만큼 데이타를 fp화일에 기입//
						fclose(fp);
						return;
					}
			}
		fclose(fp);
		fp = fopen("data.txt","a+"); 
		fwrite(bp,sizeof(Book),1,fp);
		fclose(fp); //화일 종료시 화일 포인터 fp를 닫는다 //
      }

/*****************************************/
/*             책     찾기               */
/*****************************************/

void search()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\t책번호를 입력하세요:");
		gets(tmp_number); // 책번호를 입력 // 
		fp = fopen("data.txt","r"); 
		bp=(Book *)calloc(1,sizeof(Book));
       
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력 //
	   //null이 아닐경우 반복 //
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				if(strcmp(bp->b_number,tmp_number) == 0) //number와 tmp_number를 비교하여 같을경우 실행//
					{
						if(bp->b_empty == 0)//bp값이 있나 없나 봄
						break;
						printf("\t\t\t찾았습니다!\n");
						printf("\t\t\t책제목 : %s\n",bp->b_name);
						printf("\t\t\t책번호 : %s\n",bp->b_number);
						printf("\t\t\t책저자 : %s\n",bp->auther);
						fclose(fp);
						printf("\t\t\t아무키나 누르세요");
						getchar();
						return;
					 }
			}
		fclose(fp);
		printf("\t\t\t찾지 못하였습니다!!\n");
		printf("\t\t\t아무키나 누르세요");
		getchar();
     }

/*****************************************/
/*             책 지우기                 */
/*****************************************/

void delete()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\t책번호를 입력하세요 :");
		gets(tmp_number); 
		fp = fopen("data.txt","r+");
		bp=(Book *)calloc(1,sizeof(Book));
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				i = ftell(fp);
				 if(strcmp(bp->b_number,tmp_number) == 0)
					{
						if(bp->b_empty == 0)
						break;
						printf("\t\t\t찾았습니다!\n");
						printf("\t\t\t책제목 : %s\n",bp->b_name);
						printf("\t\t\t책번호 : %s\n",bp->b_number);
						printf("\t\t\t책저자 : %s\n",bp->auther);
						printf("\t\t\t아무키나 누르세요");
						getchar();
						fclose(fp);
						printf("\n\t\t\t삭제하겠습니까?(y/n)"); //책 삭제 (y/n) //
						scanf("%c",&yes_no); 
						if(yes_no == 'y') 
							 {
								fp = fopen("data.txt","r+");
								fseek(fp,i - sizeof(Book),0);
								bp->b_empty = 0;
								fwrite(bp,sizeof(Book),1,fp);
								fclose(fp);
								}
						return;
				}
	      }
		fclose(fp);
		printf("\t\t\t찾지못하였습니다");
		printf("\t\t\t아무키나 누르세요");
		getchar();
    }
/*****************************************/
/*             책 수정하기               */
/*****************************************/

void update()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\t책번호를 입력하세요 :");
		gets(tmp_number); //책번호 입력//
		fp = fopen("data.txt","r+");
		bp = (Book *)calloc(1,sizeof(Book));
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				i = ftell(fp);
				if(strcmp(bp->b_number,tmp_number) == 0)
					{
						if(bp->b_empty == 0)
						break;
						printf("\t\t\t찾았습니다!\n");
						printf("\t\t\t책제목 : %s\n",bp->b_name);
						printf("\t\t\t책번호 : %s\n",bp->b_number);
						printf("\t\t\t책저자 : %s\n",bp->auther);
						printf("\t\t\t아무키나 누르세요");
						getchar();
						{	
							int a;
							//도서항목중 수정할 항목선택 
							printf("\n\t\t\t---------------------------------------------");
							printf("\n\t\t\t수정할 항목을 선택하세요\n");
							printf("\t\t\t----------------------------------------------\n");
							printf("\t\t\t1.책 제목\t2.책 번호 \t3.책 저자");
							printf("\n\t\t\t---------------------------------------------\n");
							
							scanf("\t\t\t%d",&a);
							fflush(stdin);
							switch(a)
								{
									case  1: 
										printf("\n\t\t새로운 책제목을 입력하세요 :");
										gets(bp->b_name);//새로운 책제목을 저장
										printf("\t\t수정되었습니다.");
										break;
									case  2:
										printf("\n\t새로운 책번호를 입력하세요 :");
										gets(bp->b_number);//새로운 책 번호를 저장
										printf("\t\t수정되었습니다.");
										break;
									case 3:
										printf("\n\t새로운 책저자를 입력하세요 :");
										gets(bp->auther);//새로운 책 저자를 저장
										printf("\t\t수정되었습니다.");
										break;
								}	

						 }
						
						fclose(fp);
						 fp = fopen("data.txt","r+");
						fseek(fp,i - sizeof(Book),0);
						fwrite(bp,sizeof(Book),1,fp);
						fclose(fp);
						printf("\n\t\t아무키나 누르세요");
						getchar();
						 return;
					}
			 }
		fclose(fp);
		printf("\t\t\t찾지못하였습니다\n");
		printf("\t\t\t아무키나 누르세요");
		getchar();
      }



/***********************************/
/*                                 */
/*            대여관리             */
/*                                 */
/***********************************/
void give_take_menu()
{		int j;	
		system("cls");
		fflush(stdin);	
		printf("\n\n\n\t\t------------------------");
		printf("\n\t\t1.대여\n\t\t2.반납\n\t\t3.메인메뉴\n");
		printf("\t\t--------------------------");
		printf("\n\t\t입력하세요 : ");
		scanf("%d",&j);
		switch(j)
		{
		case 1:
			give_take();
			break;
		case 2:
			take();
			break;
		case 3:
			main_menu();
			break;
		}
}
void give_take()
      {
		int j;
		system("cls");		//도스명령어인 cls를 실행시켜준다
		fflush(stdin);		//입력 버퍼에 있는 스트림을 깨끗하게 비운다.
		printf("\n\n\n\t\t\t고객번호를 입력하세요 : ");
		gets(tmp_number);		//고객 번호 입력//
		j = is_client(tmp_number);		//is_client함수 실행 한 후 그 값을 j에 저장 
		if(j == 0)		//0값이 리턴됐을 경우 실행
          {
				printf("\n\t\t\t회원이 아닙니다...확인후 다시 시도해주세요");
				printf("\t\t\t아무키나 누르세요");
				getchar();
				return;		//이 함수를 부른 곳으로 리턴
           }
		if(j == 1)		
			{   
				int j;
				fp = fopen("c_data.txt","r+");		//c_data.txt 화일을 읽고 쓰기 위해 엽니다.
				cp = (Client *)calloc(1,sizeof(Client));		//cp값에 1개의 client 영역만큼 할당 받고 그 영역을 초기화 시킵니다
				while(fread(cp,sizeof(Client),1,fp) != NULL)		//파일 fp에서 client의 영역*1의 기억공간을 cp가 가르키는 곳에 저장한 값이 0이 아니라면 실행
				{
					i=ftell(fp);		//fp의 현재 위치를 읽은 후 i에 저장
					if(strcmp(cp->number,tmp_number) == 0)		//number와 tmp_number 비교 해서 같다면 실행
					{
						if(cp->empty == 0)		//cp에 값이 없다면 멈춰라
						break;
						printf("\n\t\t찾았습니다!\n");		
						printf("\t\t고객이름 : %s\n",cp->name);		
						printf("\t\t고객번호 : %s\n",cp->number);
						printf("\t\t고객주소 : %s\n",cp->address);
						printf("\t\t대여책 : %s\n",cp->list);
						printf("\t\t대여하시려면 아무키나 누르세요\n");
						getchar();		//문자하나 아무거나 눌러라
						
					    give();
								
						fclose(fp);		//화일 닫기
						fp = fopen("c_data.txt","r+");		//읽고 쓰기 위해 c_data.txt를 열어라
						fseek(fp,i - sizeof(Client),0);		//처음에서 부터 i-client의 크기 만큼 건너 뛴다
						fwrite(cp,sizeof(Client),1,fp);		//cp가 가리키는 기억공간 데이터로 부터 client의 영역의 기억공간을 fp에 저장한다.		
						fclose(fp);
						return;
					}	
              }
			fclose(fp);		//number와 tmp_number 비교 해서 같지 않았을때 실행
			printf("\t\t찾지못하였습니다\n");	
			
			printf("\n\t\t아무키나 누르세요");
			getchar();
       }

       }

int is_client(char tmp_number[5])
  {
        system("cls");
		fflush(stdin);
		fp = fopen("c_data.txt","r");		//c_data.txt를 읽기 모드로 연다
		bp=(Client *)calloc(1,sizeof(Client));		//cp에 1개의 client 만큼의 영역을 할당 받고 그 영역을 초기화 시킴				
		while(fread(cp,sizeof(Client),1,fp) != NULL)		//파일 fp에서 client의 영역*1의 기억공간을 cp가 가르키는 곳에 저장한 값이 0이 아니라면 실행
			{
				if(strcmp(cp->number,tmp_number) == 0)		//number를 cp에 저장한 것과 tmp_number를 비교 같다면 참
					{
						if(cp->empty == 0)		//cp의 값이 없다면 빠져나와라		
						break;
						fclose(fp);		//화일 닫기
						return 1;		//1값을 리턴하라(부른 곳으로) 
					}
			}
       fclose(fp);		
       return 0;		//0을 리턴하라
   }
void give()
{
		fflush(stdin);
		printf("\t\t대여책 번호를 입력해주세요:");
		gets(tmp_number); // 책번호를 입력 // 
		fp = fopen("data.txt","r"); 
		bp=(Book *)calloc(1,sizeof(Book));
       
		//주어진 fp화일로 부터 1만큼의 데이타를 읽어 cp1으로 출력 //
	   //null이 아닐경우 반복 //
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				if(strcmp(bp->b_number,tmp_number) == 0) //number와 tmp_number를 비교하여 같을경우 실행//
					{
						if(bp->b_empty == 0)//bp값이 있나 없나 봄
						break;
						printf("\t\t찾았습니다!\n");
						printf("\t\t책제목 : %s\n",bp->b_name);
						printf("\t\t책번호 : %s\n",bp->b_number);
						printf("\t\t책저자 : %s\n",bp->auther);
						
						fclose(fp);
						printf("\n\t\t대여하시겠습니까?(y/n)"); 
						scanf("%c",&yes_no); 
						if(yes_no == 'y') 
							 {
								fp = fopen("c_data.txt","r+");
								strcpy(cp->list,tmp_number);
								
								fclose(fp);
								}
						printf("\n\t\t대여가 되었습니다\n");
						printf("\t\t아무키나 누르세요");
						getchar();
						return;
					 }
			}
		fclose(fp);
		printf("\t\t\t찾지 못하였습니다!!\n");
		printf("\t\t\t아무키나 누르세요");
		getchar();
     }
void take()
{	int j;
		system("cls");		//도스명령어인 cls를 실행시켜준다
		fflush(stdin);		//입력 버퍼에 있는 스트림을 깨끗하게 비운다.
		printf("\n\n\n\t\t\t고객번호를 입력하세요 : ");
		gets(tmp_number);		//고객 번호 입력//
		j = is_client(tmp_number);		//is_client함수 실행 한 후 그 값을 j에 저장 
		if(j == 0)		//0값이 리턴됐을 경우 실행
          {
				printf("\n\t\t\t회원이 아닙니다...확인후 다시 시도해주세요");
				printf("\t\t\t아무키나 누르세요");
				getchar();
				return;		//이 함수를 부른 곳으로 리턴
           }
		if(j == 1)		
			{   
				int j;
				fp = fopen("c_data.txt","r+");		//c_data.txt 화일을 읽고 쓰기 위해 엽니다.
				cp = (Client *)calloc(1,sizeof(Client));		//cp값에 1개의 client 영역만큼 할당 받고 그 영역을 초기화 시킵니다
				while(fread(cp,sizeof(Client),1,fp) != NULL)		//파일 fp에서 client의 영역*1의 기억공간을 cp가 가르키는 곳에 저장한 값이 0이 아니라면 실행
				{
					i=ftell(fp);		//fp의 현재 위치를 읽은 후 i에 저장
					if(strcmp(cp->number,tmp_number) == 0)		//number와 tmp_number 비교 해서 같다면 실행
					{
						if(cp->empty == 0)		//cp에 값이 없다면 멈춰라
						break;
						printf("\n\t\t찾았습니다!\n");		
						printf("\t\t고객이름 : %s\n",cp->name);		
						printf("\t\t고객번호 : %s\n",cp->number);
						printf("\t\t고객주소 : %s\n",cp->address);
						printf("\t\t대여책 : %s\n",cp->list);
						printf("\t\t반납을 위해 아무거나 누르세요\n");
						getchar();		//문자하나 아무거나 눌러라
						printf("\t\t반납하시려면 그냥 enter를 치세요\n"); 
					    gets(cp->list);
						fclose(fp);		//화일 닫기
						fp = fopen("c_data.txt","r+");		//읽고 쓰기 위해 c_data.txt를 열어라
						fseek(fp,i - sizeof(Client),0);		//처음에서 부터 i-client의 크기 만큼 건너 뛴다
						fwrite(cp,sizeof(Client),1,fp);		//cp가 가리키는 기억공간 데이터로 부터 client의 영역의 기억공간을 fp에 저장한다.		
						fclose(fp);
						return;
					}	
              }
			fclose(fp);		//number와 tmp_number 비교 해서 같지 않았을때 실행
			printf("\t\t찾지못하였습니다\n");	
			
			printf("\n\t\t아무키나 누르세요");
			getchar();
       }

       }