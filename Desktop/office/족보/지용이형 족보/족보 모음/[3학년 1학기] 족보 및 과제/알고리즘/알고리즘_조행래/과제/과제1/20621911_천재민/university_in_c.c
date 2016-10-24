#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
	int id;
	char name[20];
	int age;
	double grade;
}student;

int dump_input(char *);
int search(int);
int update(int);

int main()
{
	int id;
	int menu = 100;	//�޴����ú���
	char file_name[50];

	while(menu){
		printf("1. dump input\n");
		printf("2. search\n");
		printf("3. update\n");
		printf("4. exit\n");

		printf("Choose Menu : ");
		scanf("%d",&menu);

		if(menu == 1)
		{
			printf("Enter the filename! ");
			scanf("%s", &file_name);
			dump_input(file_name);
		}
		else if(menu == 2)
		{
			while(1)
			{
				printf("ã�� �л��� �й��� �Է� : ");
				scanf("%d", &id);
				fflush(stdin);	//�Է¹��� ����

				if(id == -1)
					break;

				if(search(id) == 0)
					printf("ã�� �й��� �����ϴ�!\n");
			}
		}
		else if(menu == 3)
		{
			while(1)
			{
				printf("ã�� �л��� �й��� �Է� : ");
				scanf("%d", &id);

				if(id == -1)
					break;

				if(update(id) == 0)
					printf("�� �й��� �������� �ʽ��ϴ�.\n");
			}
		}
		else if(menu == 4)
			break;
		else
			continue;
	}
  return 0;
}

int dump_input(char *file_name)
{
	FILE *txt_file, *dat_file;
	student buf;

	if((txt_file = fopen(file_name, "rt")) == NULL)
		return -1;

	if((dat_file = fopen("student.dat", "wb+")) == NULL){
		fclose(txt_file);
		return -2;
	}

	while(fscanf(txt_file, "%d %s %d %lf", &buf.id, &buf.name, &buf.age, &buf.grade) != EOF){
		fseek(dat_file, ((buf.id-1)*sizeof(student)), SEEK_SET);
		fwrite(&buf, sizeof(student), 1, dat_file);
	}
	fclose(txt_file);
	fclose(dat_file);
	return 0;
}

int search(int id)
{
	FILE *fp = fopen("student.dat", "rb");
	student buf;

	if(fp == NULL){
		printf("File Open error!!\n");
		exit(1);
	}

	fseek(fp, (id-1)*sizeof(student), SEEK_SET);
	fread(&buf, sizeof(student), 1, fp);
	if(!(buf.id))
		return 0;
	printf("�й� : %d, �̸� : %s, ���� : %d, ���� : %.2f\n", buf.id, buf.name, buf.age, buf.grade);
	fclose(fp);
	return -1;
}

int update(int id)
{
	FILE *fp = fopen("student.dat", "rb+");
	student buf;
	char name[20];
	int age;
	double grade;

	if(fp == NULL){
		printf("File Open error!!\n");
		exit(1);
	}

	fseek(fp, (id-1)*sizeof(student), SEEK_SET);
	fread(&buf, sizeof(student), 1, fp);

	if(!(buf.id))
		return 0;
	printf("�й� : %d, �̸� : %s, ���� : %d, ���� : %.2f\n", buf.id, buf.name, buf.age, buf.grade);
	printf("������ �̸��� �Է��ϼ��� : ");
	scanf("%s", &name);
	printf("������ ���̸� �Է��ϼ��� : ");
	scanf("%d", &age);
	printf("������ ������ �Է��ϼ��� : ");
	scanf("%lf", &grade);
	sscanf(name, "%s", &buf.name);	//strcpy��� ���
	buf.age = age;
	buf.grade = grade;
	fseek(fp, ((buf.id-1)*sizeof(student)), SEEK_SET);
	fwrite(&buf, sizeof(student), 1,fp);

	fclose(fp);
	return -1;
}
