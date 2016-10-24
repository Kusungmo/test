
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BLOCK_CAPACITY 0.7

struct record{
	int serial;
	char name[40];
	char category[80];
	char company[40];
	int year;
	unsigned int price;
	int qty;
};


struct block{
	struct record data[23];
	long next;
	long prev;
	long data_count;
	char fill[36];
};


int display_menu();
int dump_input();
void block_display();
void sort_record();
void search_record();
void insert_record();
void delete_record();
// record sort 관련 함수
int sum(int* data, int cnt);
int max_record(struct record *data, int mode, int block_num);
//qsort compare function
int sort_name(const void *pBlockItem1,
			  const void *pBlockItem2);
int sort_serial(const void *pBlockItem1, 
				const void *pBlockItem2);
int sort_qty(const void *pBlockItem1, 
			 const void *pBlockItem2);
int sort_price(const void *pBlockItem1, 
			   const void *pBlockItem2);
int sort_year(const void *pBlockItem1, 
			  const void *pBlockItem2);
int sort_category(const void *pBlockItem1, 
				  const void *pBlockItem2);
int search_category(char* keyword, char* src);




int main()
{
	int exit = FALSE;	
	int block_num;
	while(exit == FALSE)
	{
		switch(display_menu())
		{
		case 1:
			dump_input();
			break;
		case 2:
			sort_record();
			break;
		case 3:
			search_record();
			break;
		case 4:
			insert_record();
			break;
		case 5:
			delete_record();
			break;
		case 6:
			block_display();
			break;
		case 7:
			exit = TRUE;
			break;
		default:
			printf("wrong input!!\n");
			fflush(stdin);
		}
		system("pause");
		system("cls");
	}							
	
}


int display_menu()
{
	int menu_sw;
	printf("G-Market\n");
	printf("=======Menu=======\n");
	printf("1 : dump input\n");
	printf("2 : sort\n");
	printf("3 : search\n");
	printf("4 : insert\n");
	printf("5 : delete\n");
	printf("6 : block display\n");
	printf("7 : exit\n>");
	scanf("%d",&menu_sw);
	return menu_sw;
}

int dump_input()
{
	FILE *dump, *input;
	char *file_folder[80], buf[80];
	int block_count=0, block_num=0, i;
	struct block a;

	printf("=======Dump Input=======\n");
	printf("file name? ");
	scanf("%s",file_folder);
	//dump file open
	dump = fopen(file_folder,"rt");	
	if(!dump)
	{
		printf("dump file open error!\n");
		return -1;
	}
	//input file open
	input = fopen("input.bin","wb");
	if(!input)
	{
		printf("input file open error!\n");
		return -1;
	}
	//dump start
	while(!feof(dump))
	{		
		for(i=0; i<(23*BLOCK_CAPACITY); i++)
		{

			if(fgets(buf,80,dump) == EOF)
				break;
			a.data[i].serial = atoi(buf);		//serial

			fgets(buf,80,dump);			
			strtok(buf,"\n");
			strcpy(a.data[i].name, buf);		//name

			fgets(buf,80,dump);
			strtok(buf,"\n");
			strcpy(a.data[i].category, buf);	//category

			fgets(buf,80,dump);
			strtok(buf,"\n");
			strcpy(a.data[i].company, buf);		//company

			fgets(buf,80,dump);
			strtok(buf,"\n");
			a.data[i].year = atoi(buf);			//year

			fgets(buf,80,dump);
			a.data[i].price = atoi(buf);		//price

			fgets(buf,80,dump);
			a.data[i].qty = atoi(buf);			//qty
			if(feof(dump))
				break;
		}
		a.data_count = i;
		a.prev = sizeof(struct block)*block_count;
		block_count++;
		a.next = sizeof(struct block)*block_count;

		fwrite(&a,sizeof(a),1,input);	
		++block_num;
	}
	fwrite(&block_num,sizeof(block_num),1,input);
	printf("dump input is complete!\n");	
	printf("block number : %d\n",block_num);
	fcloseall();
	return block_num;
}


void search_record()
{
	FILE * input;
	int i, j, sw=0, wrong=FALSE, category_search = FALSE;
	int block_count, keyword_cnt=0, match;
	struct record keyword={-1,"","","",-1,-1,-1};
	struct block a;
	char key[80]="0";	
	for(i=0; i<3; i++)
	{
		printf("=======search=======\n");
		printf("1 : serial\n");
		printf("2 : name\n");
		printf("3 : category\n");
		printf("4 : company\n");
		printf("5 : year\n");
		printf("6 : price\n");
		printf("7 : qty\n");
		printf("0 : end\n");
		printf("field? >");
		scanf("%d", &sw);
		if(sw<0 || sw>7)
		{
			printf("wrong input!\n");			
			fflush(stdin);
			return;
		}
		if(!sw)
			break;
		printf("value : ");
		scanf("%s", key);	
		keyword_cnt++;
		switch(sw)
		{		
		case 1:
			keyword.serial = atoi(key);
			if(keyword.serial < 0)
				wrong = TRUE;			
			break;
		case 2:
			strcpy(keyword.name, key);
			if(strlen(keyword.name)>40)
				wrong = TRUE;
			break;
		case 3:					
			strcat(keyword.category, key);
			strcat(keyword.category, ",");
			category_search++;			
			if(strlen(keyword.name)>80)
				wrong = TRUE;
			break;
		case 4:
			strcpy(keyword.company, key);
			if(strlen(keyword.name)>40)
				wrong = TRUE;
			break;
		case 5:
			keyword.year = atoi(key);
			if(keyword.serial < 0)
				wrong = TRUE;
			break;
		case 6:
			keyword.price = atoi(key);
			if(keyword.serial < 0)
				wrong = TRUE;
			break;
		case 7:
			keyword.qty = atoi(key);
			if(keyword.serial < 0)
				wrong = TRUE;
			break;		
		}
		if(wrong)
		{
			printf("wrong input!\n");			
			keyword_cnt--;
			fflush(stdin);
			return;
		}

	}

	input = fopen("input.bin","rb");	
	if(!input)
	{
		printf("dump file open error!\n");
		return -1;
	}
	fseek(input,-sizeof(block_count),SEEK_END);
	fread(&block_count,sizeof(block_count),1,input);
	fseek(input, 0, SEEK_SET);
	for(i=0; i<block_count; i++)
	{
		fread(&a, sizeof(a), 1, input);
		for(j=0; j<a.data_count; j++)
		{
			match = 0;			
			if(keyword.serial>-1 && keyword.serial == a.data[j].serial)
				match++;
			if(keyword.name!="" && !strcmp(keyword.name, a.data[j].name))
				match++;
			if(keyword.category!="")
				match+=search_category(keyword.category, a.data[j].category);
			if(keyword.company!="" && !strcmp(keyword.company, a.data[j].company))
				match++;
			if(keyword.year>-1 && keyword.year == a.data[j].year)
				match++;
			if(keyword.price>-1 && keyword.price == a.data[j].price)
				match++;
			if(keyword.qty>-1 && keyword.qty == a.data[j].qty)
				match++;
			if(match == keyword_cnt)
			{
				printf("serial : %d\n",a.data[j].serial);
				printf("name : %s\n",a.data[j].name);
				printf("category : %s\n",a.data[j].category);
				printf("company : %s\n",a.data[j].company);
				printf("year : %d\n",a.data[j].year);
				printf("price : %d\n",a.data[j].price);
				printf("qty : %d\n",a.data[j].qty);
				printf("------------------------------------------------\n");
			}

		}
	}
}
