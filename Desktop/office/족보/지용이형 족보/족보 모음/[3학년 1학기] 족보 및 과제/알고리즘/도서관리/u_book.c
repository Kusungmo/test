
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc()�Լ� ���

//������ ���� ����ü ����
typedef struct 
        {
	 char b_name[30];
	 char b_number[30];
	 char auther[30];
	 int b_empty;
	 
	 } Book;

//ȸ���� ���� ����ü ����
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
       printf("\n\n\n\t\t�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�\n");
       printf("\n\t\t\t���α׷��� : �������� ���α׷�\n");
       printf("\t\t\t\n");
       printf("\t\t\t\n");
	   printf("\t\t\t\n");
	   printf("\t\t\t\n");
       printf("\t\t\t�ߺ�Ź �帳�ϴ�~ \n\n");
       printf("\t\t�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�\n");
	   printf("\n\n\t\t\t�ƹ�Ű�� ��������");
       getchar();
       }


/****************************/
/*        main_menu         */
/****************************/
void main_menu()
     {
      system("cls");
      fflush(stdin);//�Է� ���ۿ� �ִ� ��Ʈ���� �����ϰ� ����.
      printf("\n\n\n\n");
      printf("\t\t\t------------------------------------\n");
      printf("\t\t\t1.������\n");
      printf("\t\t\t2.å����\n");
      printf("\t\t\t3.�뿩����\n");
      printf("\t\t\t4.����\n");
      printf("\t\t\t------------------------------------\n");
      printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
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
	     default : printf("\t\t\t�߸������Ͽ����ϴ�!!!\n");
			main_menu();
              }
      }

/*****************************************/
/*                                       */
/*             ȸ�� ����                 */
/*                                       */
/*****************************************/

void client_menu()
     {
      
      system("cls");
      fflush(stdin);
      
	  printf("\n\n\n\n");
      printf("\t\t\t------------------------------------\n");
	  
	  printf("\t\t\t1.ȸ�� ����ϱ�\n");
      printf("\t\t\t2.ȸ�� ã��\n");
      printf("\t\t\t3.ȸ�� ���� \n");
      printf("\t\t\t4.ȸ�� ����\n");
      printf("\t\t\t5.���θ޴���....\n");
      printf("\t\t\t------------------------------------\n\n");
      printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
      //���ϴ� �޴��� ���ù���
	  scanf("%d",&num);
      
	  switch(num)
            {
	     case 1 : c_insert();//ȸ�� ��� �Լ�  ȣ�� 
                        break;
	     case 2 : c_search();//ȸ�� ã��  �Լ� ȣ�� 
                        break;
	     case 3 : c_delete();//ȸ�� �����  �Լ� ȣ��
                        break;
	     case 4 : c_update();//ȸ�� ���� �Լ� ȣ��
                        break;
	     case 5 : main_menu();//ȸ��  �޴��Լ� ȣ��
                        break;
	     default : printf("�߸������Ͽ����ϴ�!!!\n");
			 //1~5�� ���ڰ� �ƴҰ�� �ٽ� ȸ������ �޴��� ���ư�
					client_menu();
              }
      }

/************************************/
/*             ȸ��  ���           */
/************************************/

void c_insert()
     {
		//calloc:�޸� ���� client �뷮�� 1���� Ȯ���� 0���� �ʱ�ȭ�� 
		cp = (Client *)calloc(1,sizeof(Client));
		cp1 = (Client *)calloc(1,sizeof(Client));
	  
		//system:������ �ִ� ��ɾ� ����
		//ȭ���� ����
		system("cls");

		fflush(stdin);
      
		printf("\n\n\n\t\tȸ�� �̸� :");
		gets(cp->name);//name�� �Է¹��� ���� cp�� ����
		printf("\n\t\tȸ�� ��ȣ :");
		gets(cp->number);//number�� �Է¹��� ���� cp�� ����
		printf("\n\t\tȸ�� �ּ� :");
		gets(cp->address);//address�� �Է¹��� ���� cp�� ����
		cp->empty = 1;//empty cp�� 1����,�ڷᰡ �ִٴ� ���� Ȯ���ϱ� ���� 
		fp = fopen("c_data.txt","a+");//c_data.txtȭ���� �б�� �������� �߰��ϰų� �����Ѵ�
		printf("\t\t��ϵǾ����ϴ�.\n");
		printf("\t\t�ƹ�Ű�� ��������");
		getchar();
		rewind(fp);//ȭ���� ���������� fp�� �ִ� ȭ�� �����͸� �̵��Ѵ�.
		
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ���
		//null�� �ƴҰ�� �ݺ� 
		while(fread(cp1,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp�� �����ϴ� ȭ�������Ϳ� ������ġ�� i�� ����
				if( cp1->empty == 0)
					{
						fclose(fp);//fp�� ������ ȭ���� �ݴ´�
						fp = fopen("c_data.txt","r+");//�б�� ���⸦ ���� 'c_data.txt'�� ��  
						//ȭ���Ǽ��ο��� i-sizeof(Client) ��ŭ�� �� ��ġ�� fp�� ���� ȭ�� ������ �̵�
						fseek(fp,i-sizeof(Client),SEEK_SET);
						fwrite(cp,sizeof(Client),1,fp);//1��ŭ ����Ÿ�� fpȭ�Ͽ� ����
						fclose(fp);//fp�� ������ ȭ���� �ݴ´�
						return;
					}
			}
		fclose(fp);//fp�� ������ ȭ���� �ݴ´�
		fp = fopen("c_data.txt","a+");//�б�� ���⸦ ���� 'c_data.txt'���� 
		fwrite(cp,sizeof(Client),1,fp);//1��ŭ ����Ÿ�� fpȭ�Ͽ� ����
		fclose(fp);//fp�� ������ ȭ���� �ݴ´�
      }

/**********************************/
/*            ȸ��  ã��          */
/**********************************/
void c_search()
     {
		//system:������ �ִ� ��ɾ� ����
		//ȭ���� ����
        system("cls");
        fflush(stdin);
       
	    printf("\n\n\n\t\tȸ�� ��ȣ�� �Է��ϼ���:");
        gets(tmp_number);//ȸ����ȣ�Է¹��� 
        fp = fopen("c_data.txt","r");//�б� ���� 'c_data.txt'�� �� 
        //calloc:�޸� �� client 1���� Ȯ���� 0���� �ʱ�ȭ�� 
		cp=(Client *)calloc(1,sizeof(Client));
       	
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ���
		//null�� �ƴҰ�� �ݺ� 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				if(strcmp(cp->number,tmp_number) == 0)//number�� tmp_number�� ���Ͽ� ������� ���� 
					{
						if(cp->empty == 0)
						break;
						printf("\n\t\t--------------------------------------\n");
						printf("\t\tȸ���� ã�ҽ��ϴ�~~~~~~~~!");
						printf("\n\t\t--------------------------------------\n");
						printf("\t\tȸ�� �̸� : %s\n",cp->name);
						printf("\t\tȸ�� ��ȣ : %s\n",cp->number);
						printf("\t\tȸ�� �ּ� : %s",cp->address);
						printf("\n\t\t--------------------------------------\n");
						fclose(fp);//fp�� ������ ȭ���� �ݴ´�
						printf("\t\t�ƹ�Ű�� ��������");
						getchar();
						return;
					 }
			}
       fclose(fp);//fp�� ������ ȭ���� �ݴ´�
       printf("\n\t\t%sȸ���� ���� ȸ���Դϴ�........ !\n",tmp_number);
       printf("\n\t\t�ƹ�Ű�� ��������");
	   getchar();
       }

/*******************************************/
/*           ȸ��  �����                  */
/*******************************************/

void c_delete()
     {
		char yes_no;
       //system:������ �ִ� ��ɾ� ����
		//ȭ���� ����
		system("cls");
		fflush(stdin);
     
	   //������ ȸ���� ã��
		printf("\n\n\n");
		printf("\t\t\tȸ�� ��ȣ�� �Է��ϼ��� :");
		gets(tmp_number);//ȸ�� ��ȣ�Է¹��� 
		fp=fopen("c_data.txt","r+");//�б�� ���⸦ ����"c_data.txt"�� ��
		//calloc:�޸� �� client 1���� Ȯ���� 0���� �ʱ�ȭ�� 
		cp=(Client *)calloc(1,sizeof(Client));
        
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ���
		//null�� �ƴҰ�� �ݺ� 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp�������ϴ� ȭ�� �������� ���� ��ġ�� i�� ����
				if(strcmp(cp->number,tmp_number) == 0)//number�� tmp_number�� ���Ͽ� ������� ���� 
					{
						if(cp->empty == 0)
						break;
					    printf("\n\t\t----------------------------------\n");
						printf("\t\tȸ���� ã�ҽ��ϴ�~~~~!");
					    printf("\n\t\t----------------------------------\n");
						printf("\t\tȸ�� �̸� : %s\n",cp->name);
						printf("\t\tȸ�� ��ȣ : %s\n",cp->number);
						printf("\t\tȸ�� �ּ� : %s",cp->address);
					    printf("\n\t\t----------------------------------\n");
						printf("\t\t�ƹ�Ű�� ��������");
						getchar();
						fclose(fp);
		  
						//ȸ�� ���� yes/no
						printf("\t\tȸ���� �����ϰڽ��ϱ�?(y/n)");
						scanf("%c",&yes_no);
		  
						if(yes_no == 'y') 	
							{
								fp = fopen("c_data.txt","r+");//�а��⸦ ���� 'c_data.txt'�� ��
								//ȭ���Ǽ��ο��� i-sizeof(Client) ��ŭ�� �� ��ġ�� fp�� ���� ȭ�� ������ �̵�
								fseek(fp,i - sizeof(Client),SEEK_SET);
								cp->empty = 0;
								fwrite(cp,sizeof(Client),1,fp);//1��ŭ ����Ÿ�� fpȭ�Ͽ� ����
								fclose(fp);//fp�� ������ ȭ���� �ݴ´�
							 }
						return;
					}
		      }
       
		fclose(fp);//fp�� ������ ȭ���� �ݴ´�
		//ȸ���� ã�� ������ ���
		printf("\n\n\t\t%sȸ���� ���� ȸ���Դϴ�......",tmp_number);
		printf("\t\t�ƹ�Ű�� ��������");
		getchar();
       }
/********************************************/
/*                ȸ��  ����                */
/********************************************/
void c_update()
      {
        //system:������ �ִ� ��ɾ� ����
		//ȭ���� ����
		system("cls");
		fflush(stdin);

		printf("\n\n\n\t\tȸ�� ��ȣ�� �Է��ϼ��� :");
		gets(tmp_number);
       
		fp = fopen("c_data.txt","r+");//�а� ���⸦ ���� 'c_data.txt'�� ��  
		//calloc:�޸� �� client 1���� Ȯ���� 0���� �ʱ�ȭ�� 
		cp = (Client *)calloc(1,sizeof(Client));
        
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ���
		//null�� �ƴҰ�� �ݺ� 
		while(fread(cp,sizeof(Client),1,fp) != NULL)
			{
				i = ftell(fp);//fp�������ϴ� ȭ�� �������� ���� ��ġ�� i�� ����
				if(strcmp(cp->number,tmp_number) == 0)//number�� tmp_number�� ���Ͽ� ������� ���� 
					{
						 if(cp->empty == 0)
						 break;
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\tȸ���� ã�ҽ��ϴ�!");
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\tȸ�� �̸� : %s\n",cp->name);
						 printf("\t\tȸ�� ��ȣ : %s\n",cp->number);
						 printf("\t\tȸ�� �ּ� : %s",cp->address);
						 printf("\n\t\t-------------------------------------\n");
						 printf("\t\t�ƹ�Ű�� ��������");
						 getchar();
						{	
							int a;
							//ȸ���׸��� ������ �׸��� 
							printf("\n\t\t---------------------------------------------");
							printf("\n\t\t������ �׸��� �����ϼ���\n");
							printf("\t\t----------------------------------------------\n");
							printf("\t\t1.ȸ�� �̸� \t2.ȸ�� ��ȣ \t3.ȸ�� �ּ� ");
							printf("\n\t\t---------------------------------------------\n");
							
							scanf("\t\t\t%d",&a);
							fflush(stdin);
							switch(a)
								{
									case  1: 
										printf("\n\t\t���ο� ȸ�� �̸��� �Է��ϼ��� :");
										gets(cp->name);//���ο� �̸��� ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
									case  2:
										printf("\n\t���ο� ȸ�� ��ȣ�� �Է��ϼ��� :");
										gets(cp->number);//���ο� ��ȣ�� ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
									case 3:
										printf("\n\t���ο� ȸ�� �ּҸ� �Է��ϼ��� :");
										gets(cp->address);//���ο� �ּ��� ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
								}	

						 }

						fclose(fp);//fp�� ������ ȭ���� �ݴ´�
						fp = fopen("c_data.txt","r+");//�а� ���⸦ ���� 'c_data.txt'�� �� 
						//ȭ���Ǽ��ο��� i-sizeof(Client) ��ŭ�� �� ��ġ�� fp�� ���� ȭ�� ������ �̵�
						fseek(fp,i - sizeof(Client),0);
						fwrite(cp,sizeof(Client),1,fp);//1��ŭ ����Ÿ�� fpȭ�Ͽ� ����
						fclose(fp);//fp�� ������ ȭ���� �ݴ´�
						printf("\n\t\t�ƹ�Ű�� ��������");
						getchar();
						 return;
					}
              }
			fclose(fp);//fp�� ������ ȭ���� �ݴ´�
			printf("\n\n\t\t%sȸ���� ���� ȸ���Դϴ�......",tmp_number);
			printf("\n\t\t�ƹ�Ű�� ��������");
			getchar();
       }


/*****************************************/
/*                                       */
/*             å   ����                 */
/*                                       */
/*****************************************/

void book_menu()
     {
		// system ���� ��� ����
		// ȭ���� ����
		system("cls"); 
		fflush(stdin);
		printf("\n\n\n\n");
		printf("\t\t\t------------------------------------\n");
		printf("\t\t\t1.å����ϱ�\n");
		printf("\t\t\t2.åã��\n");
		printf("\t\t\t3.å�����\n");
		printf("\t\t\t4.å����\n");
		printf("\t\t\t5.���θ޴�\n");
		printf("\t\t\t------------------------------------\n");
		printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
		scanf("%d",&num); // ���� �Է�
		switch(num)
            {
				case 1 : insert(); // num�� 1�� �� insert()�Լ��� 
                        break;  //�����
				case 2 : search();
                        break;
				case 3 : delete();
                        break;
				case 4 : update();
                        break;
				case 5 : main_menu();
                        break;
				default : printf("�߸������Ͽ����ϴ�!!!\n"); /*1~5���� ���� �ƴϸ� ���*/
						book_menu(); /*book_menu()�Լ��� �̵�*/
              }
      }

/*****************************************/
/*             å ����ϱ�               */
/*****************************************/

void insert()
     {
		//calloc:�޸� ���� bp �뷮�� 1���� Ȯ���� 0���� �ʱ�ȭ��//
		bp = (Book *)calloc(1,sizeof(Book));
		bp1 = (Book *)calloc(1,sizeof(Book));
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\tå���� :");
		gets(bp->b_name); // b_name�� �Է� ���� ���� bp�� ���� //
		printf("\n\t\t\tå��ȣ :");
		gets(bp->b_number); // b_number�� �Է� ���� ���� bp�� ����  //
		printf("\n\t\t\tå���� :");
		gets(bp->auther); // b_auther�� �Է� ���� ���� bp�� ���� //
		bp->b_empty = 1; //empty bp�� 1 ���� //
		fp = fopen("data.txt","a+"); // data.txt�� �߰��ؼ� ���� �̿� ���� �ּҸ� fp�� �޴´� //
		rewind(fp); // ȭ���� ���������� fp�� �ִ� ȭ�� �����͸� �̵��Ѵ� //
		
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� bp1���� ���//
		//null�� �ƴҰ�� �ݺ� //
		while(fread(bp1,sizeof(Book),1,fp) != NULL)
			{
				i = ftell(fp); //fp�� �����ϴ� ȭ�� �������� ��ġ i�� ���� //
				if( bp1->b_empty == 0) // bp�� �� b_empty ���� 0�̶��  //
					{
						fclose(fp); //ȭ�� ����� ȭ�� ������ fp�� �ݴ´� //
						fp = fopen("data.txt","r+"); // data.txt�� �б� �������� ���� �̿� ���� �ּҸ� fp�� �޴´� //
						fseek(fp,i-sizeof(Book),0);//ó������ ���� i-client�� ũ�� ��ŭ �ǳ� �ڴ�
						fwrite(bp,sizeof(Book),1,fp); //1��ŭ ����Ÿ�� fpȭ�Ͽ� ����//
						fclose(fp);
						return;
					}
			}
		fclose(fp);
		fp = fopen("data.txt","a+"); 
		fwrite(bp,sizeof(Book),1,fp);
		fclose(fp); //ȭ�� ����� ȭ�� ������ fp�� �ݴ´� //
      }

/*****************************************/
/*             å     ã��               */
/*****************************************/

void search()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\tå��ȣ�� �Է��ϼ���:");
		gets(tmp_number); // å��ȣ�� �Է� // 
		fp = fopen("data.txt","r"); 
		bp=(Book *)calloc(1,sizeof(Book));
       
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ��� //
	   //null�� �ƴҰ�� �ݺ� //
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				if(strcmp(bp->b_number,tmp_number) == 0) //number�� tmp_number�� ���Ͽ� ������� ����//
					{
						if(bp->b_empty == 0)//bp���� �ֳ� ���� ��
						break;
						printf("\t\t\tã�ҽ��ϴ�!\n");
						printf("\t\t\tå���� : %s\n",bp->b_name);
						printf("\t\t\tå��ȣ : %s\n",bp->b_number);
						printf("\t\t\tå���� : %s\n",bp->auther);
						fclose(fp);
						printf("\t\t\t�ƹ�Ű�� ��������");
						getchar();
						return;
					 }
			}
		fclose(fp);
		printf("\t\t\tã�� ���Ͽ����ϴ�!!\n");
		printf("\t\t\t�ƹ�Ű�� ��������");
		getchar();
     }

/*****************************************/
/*             å �����                 */
/*****************************************/

void delete()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\tå��ȣ�� �Է��ϼ��� :");
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
						printf("\t\t\tã�ҽ��ϴ�!\n");
						printf("\t\t\tå���� : %s\n",bp->b_name);
						printf("\t\t\tå��ȣ : %s\n",bp->b_number);
						printf("\t\t\tå���� : %s\n",bp->auther);
						printf("\t\t\t�ƹ�Ű�� ��������");
						getchar();
						fclose(fp);
						printf("\n\t\t\t�����ϰڽ��ϱ�?(y/n)"); //å ���� (y/n) //
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
		printf("\t\t\tã�����Ͽ����ϴ�");
		printf("\t\t\t�ƹ�Ű�� ��������");
		getchar();
    }
/*****************************************/
/*             å �����ϱ�               */
/*****************************************/

void update()
      {
		system("cls");
		fflush(stdin);
		printf("\n\n\n\t\t\tå��ȣ�� �Է��ϼ��� :");
		gets(tmp_number); //å��ȣ �Է�//
		fp = fopen("data.txt","r+");
		bp = (Book *)calloc(1,sizeof(Book));
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				i = ftell(fp);
				if(strcmp(bp->b_number,tmp_number) == 0)
					{
						if(bp->b_empty == 0)
						break;
						printf("\t\t\tã�ҽ��ϴ�!\n");
						printf("\t\t\tå���� : %s\n",bp->b_name);
						printf("\t\t\tå��ȣ : %s\n",bp->b_number);
						printf("\t\t\tå���� : %s\n",bp->auther);
						printf("\t\t\t�ƹ�Ű�� ��������");
						getchar();
						{	
							int a;
							//�����׸��� ������ �׸��� 
							printf("\n\t\t\t---------------------------------------------");
							printf("\n\t\t\t������ �׸��� �����ϼ���\n");
							printf("\t\t\t----------------------------------------------\n");
							printf("\t\t\t1.å ����\t2.å ��ȣ \t3.å ����");
							printf("\n\t\t\t---------------------------------------------\n");
							
							scanf("\t\t\t%d",&a);
							fflush(stdin);
							switch(a)
								{
									case  1: 
										printf("\n\t\t���ο� å������ �Է��ϼ��� :");
										gets(bp->b_name);//���ο� å������ ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
									case  2:
										printf("\n\t���ο� å��ȣ�� �Է��ϼ��� :");
										gets(bp->b_number);//���ο� å ��ȣ�� ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
									case 3:
										printf("\n\t���ο� å���ڸ� �Է��ϼ��� :");
										gets(bp->auther);//���ο� å ���ڸ� ����
										printf("\t\t�����Ǿ����ϴ�.");
										break;
								}	

						 }
						
						fclose(fp);
						 fp = fopen("data.txt","r+");
						fseek(fp,i - sizeof(Book),0);
						fwrite(bp,sizeof(Book),1,fp);
						fclose(fp);
						printf("\n\t\t�ƹ�Ű�� ��������");
						getchar();
						 return;
					}
			 }
		fclose(fp);
		printf("\t\t\tã�����Ͽ����ϴ�\n");
		printf("\t\t\t�ƹ�Ű�� ��������");
		getchar();
      }



/***********************************/
/*                                 */
/*            �뿩����             */
/*                                 */
/***********************************/
void give_take_menu()
{		int j;	
		system("cls");
		fflush(stdin);	
		printf("\n\n\n\t\t------------------------");
		printf("\n\t\t1.�뿩\n\t\t2.�ݳ�\n\t\t3.���θ޴�\n");
		printf("\t\t--------------------------");
		printf("\n\t\t�Է��ϼ��� : ");
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
		system("cls");		//������ɾ��� cls�� ��������ش�
		fflush(stdin);		//�Է� ���ۿ� �ִ� ��Ʈ���� �����ϰ� ����.
		printf("\n\n\n\t\t\t����ȣ�� �Է��ϼ��� : ");
		gets(tmp_number);		//�� ��ȣ �Է�//
		j = is_client(tmp_number);		//is_client�Լ� ���� �� �� �� ���� j�� ���� 
		if(j == 0)		//0���� ���ϵ��� ��� ����
          {
				printf("\n\t\t\tȸ���� �ƴմϴ�...Ȯ���� �ٽ� �õ����ּ���");
				printf("\t\t\t�ƹ�Ű�� ��������");
				getchar();
				return;		//�� �Լ��� �θ� ������ ����
           }
		if(j == 1)		
			{   
				int j;
				fp = fopen("c_data.txt","r+");		//c_data.txt ȭ���� �а� ���� ���� ���ϴ�.
				cp = (Client *)calloc(1,sizeof(Client));		//cp���� 1���� client ������ŭ �Ҵ� �ް� �� ������ �ʱ�ȭ ��ŵ�ϴ�
				while(fread(cp,sizeof(Client),1,fp) != NULL)		//���� fp���� client�� ����*1�� �������� cp�� ����Ű�� ���� ������ ���� 0�� �ƴ϶�� ����
				{
					i=ftell(fp);		//fp�� ���� ��ġ�� ���� �� i�� ����
					if(strcmp(cp->number,tmp_number) == 0)		//number�� tmp_number �� �ؼ� ���ٸ� ����
					{
						if(cp->empty == 0)		//cp�� ���� ���ٸ� �����
						break;
						printf("\n\t\tã�ҽ��ϴ�!\n");		
						printf("\t\t���̸� : %s\n",cp->name);		
						printf("\t\t����ȣ : %s\n",cp->number);
						printf("\t\t���ּ� : %s\n",cp->address);
						printf("\t\t�뿩å : %s\n",cp->list);
						printf("\t\t�뿩�Ͻ÷��� �ƹ�Ű�� ��������\n");
						getchar();		//�����ϳ� �ƹ��ų� ������
						
					    give();
								
						fclose(fp);		//ȭ�� �ݱ�
						fp = fopen("c_data.txt","r+");		//�а� ���� ���� c_data.txt�� �����
						fseek(fp,i - sizeof(Client),0);		//ó������ ���� i-client�� ũ�� ��ŭ �ǳ� �ڴ�
						fwrite(cp,sizeof(Client),1,fp);		//cp�� ����Ű�� ������ �����ͷ� ���� client�� ������ �������� fp�� �����Ѵ�.		
						fclose(fp);
						return;
					}	
              }
			fclose(fp);		//number�� tmp_number �� �ؼ� ���� �ʾ����� ����
			printf("\t\tã�����Ͽ����ϴ�\n");	
			
			printf("\n\t\t�ƹ�Ű�� ��������");
			getchar();
       }

       }

int is_client(char tmp_number[5])
  {
        system("cls");
		fflush(stdin);
		fp = fopen("c_data.txt","r");		//c_data.txt�� �б� ���� ����
		bp=(Client *)calloc(1,sizeof(Client));		//cp�� 1���� client ��ŭ�� ������ �Ҵ� �ް� �� ������ �ʱ�ȭ ��Ŵ				
		while(fread(cp,sizeof(Client),1,fp) != NULL)		//���� fp���� client�� ����*1�� �������� cp�� ����Ű�� ���� ������ ���� 0�� �ƴ϶�� ����
			{
				if(strcmp(cp->number,tmp_number) == 0)		//number�� cp�� ������ �Ͱ� tmp_number�� �� ���ٸ� ��
					{
						if(cp->empty == 0)		//cp�� ���� ���ٸ� �������Ͷ�		
						break;
						fclose(fp);		//ȭ�� �ݱ�
						return 1;		//1���� �����϶�(�θ� ������) 
					}
			}
       fclose(fp);		
       return 0;		//0�� �����϶�
   }
void give()
{
		fflush(stdin);
		printf("\t\t�뿩å ��ȣ�� �Է����ּ���:");
		gets(tmp_number); // å��ȣ�� �Է� // 
		fp = fopen("data.txt","r"); 
		bp=(Book *)calloc(1,sizeof(Book));
       
		//�־��� fpȭ�Ϸ� ���� 1��ŭ�� ����Ÿ�� �о� cp1���� ��� //
	   //null�� �ƴҰ�� �ݺ� //
		while(fread(bp,sizeof(Book),1,fp) != NULL)
			{
				if(strcmp(bp->b_number,tmp_number) == 0) //number�� tmp_number�� ���Ͽ� ������� ����//
					{
						if(bp->b_empty == 0)//bp���� �ֳ� ���� ��
						break;
						printf("\t\tã�ҽ��ϴ�!\n");
						printf("\t\tå���� : %s\n",bp->b_name);
						printf("\t\tå��ȣ : %s\n",bp->b_number);
						printf("\t\tå���� : %s\n",bp->auther);
						
						fclose(fp);
						printf("\n\t\t�뿩�Ͻðڽ��ϱ�?(y/n)"); 
						scanf("%c",&yes_no); 
						if(yes_no == 'y') 
							 {
								fp = fopen("c_data.txt","r+");
								strcpy(cp->list,tmp_number);
								
								fclose(fp);
								}
						printf("\n\t\t�뿩�� �Ǿ����ϴ�\n");
						printf("\t\t�ƹ�Ű�� ��������");
						getchar();
						return;
					 }
			}
		fclose(fp);
		printf("\t\t\tã�� ���Ͽ����ϴ�!!\n");
		printf("\t\t\t�ƹ�Ű�� ��������");
		getchar();
     }
void take()
{	int j;
		system("cls");		//������ɾ��� cls�� ��������ش�
		fflush(stdin);		//�Է� ���ۿ� �ִ� ��Ʈ���� �����ϰ� ����.
		printf("\n\n\n\t\t\t����ȣ�� �Է��ϼ��� : ");
		gets(tmp_number);		//�� ��ȣ �Է�//
		j = is_client(tmp_number);		//is_client�Լ� ���� �� �� �� ���� j�� ���� 
		if(j == 0)		//0���� ���ϵ��� ��� ����
          {
				printf("\n\t\t\tȸ���� �ƴմϴ�...Ȯ���� �ٽ� �õ����ּ���");
				printf("\t\t\t�ƹ�Ű�� ��������");
				getchar();
				return;		//�� �Լ��� �θ� ������ ����
           }
		if(j == 1)		
			{   
				int j;
				fp = fopen("c_data.txt","r+");		//c_data.txt ȭ���� �а� ���� ���� ���ϴ�.
				cp = (Client *)calloc(1,sizeof(Client));		//cp���� 1���� client ������ŭ �Ҵ� �ް� �� ������ �ʱ�ȭ ��ŵ�ϴ�
				while(fread(cp,sizeof(Client),1,fp) != NULL)		//���� fp���� client�� ����*1�� �������� cp�� ����Ű�� ���� ������ ���� 0�� �ƴ϶�� ����
				{
					i=ftell(fp);		//fp�� ���� ��ġ�� ���� �� i�� ����
					if(strcmp(cp->number,tmp_number) == 0)		//number�� tmp_number �� �ؼ� ���ٸ� ����
					{
						if(cp->empty == 0)		//cp�� ���� ���ٸ� �����
						break;
						printf("\n\t\tã�ҽ��ϴ�!\n");		
						printf("\t\t���̸� : %s\n",cp->name);		
						printf("\t\t����ȣ : %s\n",cp->number);
						printf("\t\t���ּ� : %s\n",cp->address);
						printf("\t\t�뿩å : %s\n",cp->list);
						printf("\t\t�ݳ��� ���� �ƹ��ų� ��������\n");
						getchar();		//�����ϳ� �ƹ��ų� ������
						printf("\t\t�ݳ��Ͻ÷��� �׳� enter�� ġ����\n"); 
					    gets(cp->list);
						fclose(fp);		//ȭ�� �ݱ�
						fp = fopen("c_data.txt","r+");		//�а� ���� ���� c_data.txt�� �����
						fseek(fp,i - sizeof(Client),0);		//ó������ ���� i-client�� ũ�� ��ŭ �ǳ� �ڴ�
						fwrite(cp,sizeof(Client),1,fp);		//cp�� ����Ű�� ������ �����ͷ� ���� client�� ������ �������� fp�� �����Ѵ�.		
						fclose(fp);
						return;
					}	
              }
			fclose(fp);		//number�� tmp_number �� �ؼ� ���� �ʾ����� ����
			printf("\t\tã�����Ͽ����ϴ�\n");	
			
			printf("\n\t\t�ƹ�Ű�� ��������");
			getchar();
       }

       }