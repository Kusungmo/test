#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node {										// 전화번호 구조체
	char name[10];
	char phone[14];
	struct _node *left;
	struct _node *right;
}node;

void Insert( node **, char [], char [] );
void Bulkinsert( node ** );
void Delete( node **, char [] );
void Search( node *, char [] );
void Print( node *, int * );
void sTatus( node *, int *, int *, int *, int );
void eXit( node * );

void main() {
	node *root = NULL;
	char menu, name[10], phone[14];
	int suml, sumn, maxl, count;

	while(1) {
		fflush( stdin );
		printf( "메    뉴 : " );
		scanf( "%c", &menu );								// 메뉴 입력

		switch( menu ) {
			case 'I' :	case 'i' :							// Insert
				printf( "이    름 : " );
				scanf( "%s", name );
				printf( "전화번호 : " );
				scanf( "%s", phone );
				Insert( &root, name, phone );
				printf("\n");
				break;
			case 'B' :	case 'b' :							// Bulk Insert
				Bulkinsert( &root );
				printf("\n");
				break;
			case 'D' :	case 'd' :							// Delete
				printf( "이    름 : " );
				scanf( "%s", name );
				Delete( &root, name );
				printf("\n");
				break;
			case 'S' :	case 's' :							// Search
				printf( "이    름 : " );
				scanf( "%s", name );
				Search( root, name );
				break;
			case 'P' :	case 'p' :							// Print
				count = 1;
				Print( root, &count );
				break;
			case 'T' :	case 't' :							// sTatus
				suml = sumn = maxl = 0;
				sTatus( root, &suml, &sumn, &maxl, 1 );
				printf( "트리의 depth : %d\n", maxl );
				printf( "트리 노드 수 : %d\n", sumn );
				printf( "평균 검색 수 : %f\n\n", sumn? (double)suml/sumn : 0 );
				break;
			case 'X' :	case 'x' :							// eXit
				eXit( root );
				return;
			default :
				printf( "Insert, Bulk insert, Delete, Search, Print, sTatus, eXit\n\n" );
		}
	}
}

void Insert( node **root, char name[], char phone[] ) {		// Insert
	node *ptr = *root;
	node *temp = (node *)malloc(sizeof(node));				// 새로운 노드 생성
	strcpy( temp->name, name );
	strcpy( temp->phone, phone );
	temp->left = temp->right = NULL;

	if( !*root ) {	*root = temp;	return;	}				// 루트가 비어있는 경우

	while( ptr ) {
		if( strcmp( ptr->name, name ) == 0 ) {				// 중복된 이름인 경우
			printf( "[%s] 중복된 이름 입니다.\n", name );
			return;
		} else if( strcmp( ptr->name, name ) > 0 ) {		// 좌측에 데이터 삽입
			if( !ptr->left )	{	ptr->left = temp;	return;	}
			else				{	ptr = ptr->left;	}
		} else if( strcmp( ptr->name, name ) < 0 ) {		// 우측에 데이터 삽입
			if( !ptr->right )	{	ptr->right = temp;	return;	}
			else				{	ptr = ptr->right;	}
		}
	}
	printf( "데이터를 찾을 수 없습니다.\n" );
}

void Bulkinsert( node **root ) {							// Bulk Insert
	char name[10], phone[14], *token, buf[30];
	FILE *file = fopen("data.txt", "r+t");					// 파일 오픈

	if( !file ) {											// 파일을 못 읽은 경우
		printf("파일을 열 수 없습니다.\n\n");
		return;
	}

	while( !feof(file) ) {									// 파일 끝까지 검색
		fflush(stdin);
		if( !fgets( buf, 30, file ) )	break;

		token = strtok( buf, " \t\n" );						// 데이터 읽기
		strcpy( name, token );
		token = strtok( NULL, " \t\n" );
		strcpy( phone, token );

		Insert( root, name, phone );						// 노드 삽입
	}

	fclose( file );
}

void Delete( node **root, char name[] ) {					// Delete
	node *ptr = *root, *temp;

	while( ptr ) {
		if( strcmp( ptr->name, name ) == 0 ) {				// 지울 데이터를 찾았을때
			if( !ptr->left && !ptr->right ) {				// 리프 노드인 경우
				if( ptr == *root ) {		*root = NULL;
				}else {
					if( temp->left == ptr )	temp->left = NULL;
					else					temp->right = NULL;
				}
				free(ptr);
				return;
			} else if( !ptr->left ) {	temp = ptr->right;	// 우측이 빈 노드인 경우
			} else if( !ptr->right ) {	temp = ptr->left;	// 좌측이 빈 노드인 경우
			} else {										// 자식이 둘다 있을 경우
				for( temp = ptr->left; temp->right; temp = temp->right );
				strcpy( ptr->name, temp->name );
				strcpy( ptr->phone, ptr->phone );

				if( temp == ptr->left ) {
					ptr->left = NULL;
					free(temp);
					return;
				}

				if( !temp->left ) {
					for( ptr = ptr->left; ptr->right == temp; ptr = ptr->right );
					ptr->right = NULL;
					free(temp);
					return;
				}

				ptr = temp;
				temp = temp->left;
			}
			strcpy( ptr->name, temp->name );
			strcpy( ptr->phone, temp->phone );
			ptr->left = temp->left;
			ptr->right = temp->right;
			free(temp);
			return;
		} else if ( strcmp( ptr->name, name ) > 0 ) {		// 좌측으로 이동
			temp = ptr;
			ptr = ptr->left;
		} else if ( strcmp( ptr->name, name ) < 0 ) {		// 우측으로 이동
			temp = ptr;
			ptr = ptr->right;
		}
	}
	printf( "해당 전화번호가 없습니다.\n" );
}

void Search( node *root, char name[] ) {					// Search
	while( root )
		if( strcmp( root->name, name ) == 0 ) {
			printf( "전화번호 : %s\n\n", root->phone );
			return;
		}
		else if( strcmp( root->name, name ) > 0 )	root = root->left;
		else if( strcmp( root->name, name ) < 0 )	root = root->right;
	printf( "해당 전화번호가 없습니다.\n\n" );
}

void Print( node *root, int *count ) {						// Print
	if( root ) {
		Print( root->left, count );

		if( *count%20 == 0 )	getch();
		printf( "이    름 : %s\n", root->name );
		printf( "전화번호 : %s\n\n", root->phone );
		*count += 1;

		Print( root->right, count );
	}
}

void sTatus( node *root, int *suml, int *sumn, int *maxl, int level ) {
	if( root ) {											// sTstus
		*suml += level;										// 레벨 합계 계산
		*sumn += 1;											// 노드 갯수 계산
		if( *maxl < level ) *maxl = level;					// 트리 깊이 계산

		sTatus( root->left, suml, sumn, maxl, level+1 );
		sTatus( root->right, suml, sumn, maxl, level+1 );
	}
}

void eXit( node *root ) {									// eXit
	if( root ) {											// 종료전 할당된 노드 해제
		eXit( root->left );
		eXit( root->right );

		free(root);
	}
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.11.18