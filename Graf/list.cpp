#include"list.h"
#include "global.h"



ListItem* CreateList()
{
	ListItem* p = ( ListItem * ) calloc( 1, sizeof( ListItem ) ); // dwa callocki
	LISTINFO* n = ( LISTINFO* ) calloc( 1, sizeof( LISTINFO ) );
	if( p && n )
	{

		p->pInfo = n;
		p->pNext = NULL;
		return p;

	}
	printf( "Nie udalo sie utworzyc listy" );
	return NULL;
}

void InsertFront( ListItem* pList, LISTINFO* pInfo )
{
	Insert( pList, pInfo );
}

void Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	//calloc na stworzenie elementu
	
	ListItem* p = ( ListItem* ) calloc( 1, sizeof( ListItem ) );
	if( p )
	{
		p->pNext = pAfter->pNext;
		p->pInfo = pInfo;
		pAfter->pNext = p;
	}
	else
		perror( "Nie mozna wlozyc elementu" );
}

ListItem* Front( ListItem* pList )
{
	return pList->pNext;
}


void Remove( ListItem* pAfter )
{
	//{//!!!!!pAfter???
	if( pAfter->pNext )
	{
		ListItem* p = pAfter->pNext;
		pAfter->pNext = p->pNext;
		free( p );
		// free 
	}
	else
		perror( "Nie mozna usunac elementu" );
}

void RemoveFront( ListItem* pList )
{
	Remove( pList );
}



void FreeList( ListItem* pList )
{
	while( !isEmpty( pList ) )
	{
		RemoveFront( pList );
	}
}

int isEmpty( ListItem* pList )
{
	return !( pList->pNext );
}

LISTINFO* CreateElement( int numberOfHome, double distance, double time )
{
	LISTINFO* n = ( LISTINFO* ) malloc( sizeof( LISTINFO ) );
	if( n )
	{
		n->numberOfHome = numberOfHome ;
		n->distance = distance ;
		n->time = time;
		return n;
	}
	else
		perror( "Nie udalo sie utworzyc elementu" );
	return 0;
}