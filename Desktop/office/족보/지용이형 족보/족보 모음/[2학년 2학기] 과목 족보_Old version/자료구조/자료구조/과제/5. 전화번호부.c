#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node {										// ��ȭ��ȣ ����ü
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
		printf( "��    �� : " );
		scanf( "%c", &menu );								// �޴� �Է�

		switch( menu ) {
			case 'I' :	case 'i' :							// Insert
				printf( "��    �� : " );
				scanf( "%s", name );
				printf( "��ȭ��ȣ : " );
				scanf( "%s", phone );
				Insert( &root, name, phone );
				printf("\n");
				break;
			case 'B' :	case 'b' :							// Bulk Insert
				Bulkinsert( &root );
				printf("\n");
				break;
			case 'D' :	case 'd' :							// Delete
				printf( "��    �� : " );
				scanf( "%s", name );
				Delete( &root, name );
				printf("\n");
				break;
			case 'S' :	case 's' :							// Search
				printf( "��    �� : " );
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
				printf( "Ʈ���� depth : %d\n", maxl );
				printf( "Ʈ�� ��� �� : %d\n", sumn );
				printf( "��� �˻� �� : %f\n\n", sumn? (double)suml/sumn : 0 );
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
	node *temp = (node *)malloc(sizeof(node));				// ���ο� ��� ����
	strcpy( temp->name, name );
	strcpy( temp->phone, phone );
	temp->left = temp->right = NULL;

	if( !*root ) {	*root = temp;	return;	}				// ��Ʈ�� ����ִ� ���

	while( ptr ) {
		if( strcmp( ptr->name, name ) == 0 ) {				// �ߺ��� �̸��� ���
			printf( "[%s] �ߺ��� �̸� �Դϴ�.\n", name );
			return;
		} else if( strcmp( ptr->name, name ) > 0 ) {		// ������ ������ ����
			if( !ptr->left )	{	ptr->left = temp;	return;	}
			else				{	ptr = ptr->left;	}
		} else if( strcmp( ptr->name, name ) < 0 ) {		// ������ ������ ����
			if( !ptr->right )	{	ptr->right = temp;	return;	}
			else				{	ptr = ptr->right;	}
		}
	}
	printf( "�����͸� ã�� �� �����ϴ�.\n" );
}

void Bulkinsert( node **root ) {							// Bulk Insert
	char name[10], phone[14], *token, buf[30];
	FILE *file = fopen("data.txt", "r+t");					// ���� ����

	if( !file ) {											// ������ �� ���� ���
		printf("������ �� �� �����ϴ�.\n\n");
		return;
	}

	while( !feof(file) ) {									// ���� ������ �˻�
		fflush(stdin);
		if( !fgets( buf, 30, file ) )	break;

		token = strtok( buf, " \t\n" );						// ������ �б�
		strcpy( name, token );
		token = strtok( NULL, " \t\n" );
		strcpy( phone, token );

		Insert( root, name, phone );						// ��� ����
	}

	fclose( file );
}

void Delete( node **root, char name[] ) {					// Delete
	node *ptr = *root, *temp;

	while( ptr ) {
		if( strcmp( ptr->name, name ) == 0 ) {				// ���� �����͸� ã������
			if( !ptr->left && !ptr->right ) {				// ���� ����� ���
				if( ptr == *root ) {		*root = NULL;
				}else {
					if( temp->left == ptr )	temp->left = NULL;
					else					temp->right = NULL;
				}
				free(ptr);
				return;
			} else if( !ptr->left ) {	temp = ptr->right;	// ������ �� ����� ���
			} else if( !ptr->right ) {	temp = ptr->left;	// ������ �� ����� ���
			} else {										// �ڽ��� �Ѵ� ���� ���
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
		} else if ( strcmp( ptr->name, name ) > 0 ) {		// �������� �̵�
			temp = ptr;
			ptr = ptr->left;
		} else if ( strcmp( ptr->name, name ) < 0 ) {		// �������� �̵�
			temp = ptr;
			ptr = ptr->right;
		}
	}
	printf( "�ش� ��ȭ��ȣ�� �����ϴ�.\n" );
}

void Search( node *root, char name[] ) {					// Search
	while( root )
		if( strcmp( root->name, name ) == 0 ) {
			printf( "��ȭ��ȣ : %s\n\n", root->phone );
			return;
		}
		else if( strcmp( root->name, name ) > 0 )	root = root->left;
		else if( strcmp( root->name, name ) < 0 )	root = root->right;
	printf( "�ش� ��ȭ��ȣ�� �����ϴ�.\n\n" );
}

void Print( node *root, int *count ) {						// Print
	if( root ) {
		Print( root->left, count );

		if( *count%20 == 0 )	getch();
		printf( "��    �� : %s\n", root->name );
		printf( "��ȭ��ȣ : %s\n\n", root->phone );
		*count += 1;

		Print( root->right, count );
	}
}

void sTatus( node *root, int *suml, int *sumn, int *maxl, int level ) {
	if( root ) {											// sTstus
		*suml += level;										// ���� �հ� ���
		*sumn += 1;											// ��� ���� ���
		if( *maxl < level ) *maxl = level;					// Ʈ�� ���� ���

		sTatus( root->left, suml, sumn, maxl, level+1 );
		sTatus( root->right, suml, sumn, maxl, level+1 );
	}
}

void eXit( node *root ) {									// eXit
	if( root ) {											// ������ �Ҵ�� ��� ����
		eXit( root->left );
		eXit( root->right );

		free(root);
	}
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.11.18