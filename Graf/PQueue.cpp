#include "PQueue.h"

void UpdateDown( PQueue*, int l, int p );// uaktoalnienie warunku stogu
void UpdateUP( PQueue*, int l, int p );


PQueue* PQInit( int PQSize )
{
	PQueue* queue = ( PQueue* ) calloc( 1, sizeof( PQueue ) );

	queue->PQItem = ( PQItem* ) calloc( PQSize, sizeof( PQItem ) );

	if( !( queue && queue->PQItem ) )
		perror( "Nie udalo sie utworzyc kolejki" );

	queue->PQCurrentSize = 0;
	queue->PQSize = PQSize;
	return queue;
}

int PQIsEmpty( PQueue* queue )
{
	return !( queue->PQCurrentSize );
}

void PQEnqueue( PQueue* queue, int nKey, double nPrior )
{
	if( queue->PQCurrentSize == queue->PQSize ) //sprawdzam, czy osiagnieto max rozmiar
	{
		printf( "Nie mozna dodac elementu " );
		return;
	}
	queue->PQItem[queue->PQCurrentSize].nKey = nKey;
	queue->PQItem[queue->PQCurrentSize].nPrior = nPrior;
	//queue->PQCurrentSize++;
	UpdateUP( queue, 0, queue->PQCurrentSize++ ); // update a potem zwiekszenie aktualnego rozmiaru o 1
}

int PQDequeue( PQueue* queue )
{
	if( PQIsEmpty( queue ) )
	{
		printf( "Kolejka jest pusta! \n" );
		return -1;
	}
	int temp = queue->PQItem->nKey;

	queue->PQItem->nKey = queue->PQItem[queue->PQCurrentSize - 1].nKey; // ostatni elementu zamieniony z pierwszym
	queue->PQItem->nPrior = queue->PQItem[queue->PQCurrentSize - 1].nPrior;// ostatni element zamienony z pierwszym

	queue->PQItem[queue->PQCurrentSize - 1].nKey = 0;
	queue->PQItem[queue->PQCurrentSize - 1].nPrior = 0;
	queue->PQCurrentSize--;

	UpdateDown( queue, 0, queue->PQCurrentSize - 1 ); // zamiana jak w kopcu 

	return temp;

}

void PQClearQueue( PQueue* queue )
{
	while( !PQIsEmpty( queue ) )
	{
		queue->PQItem[queue->PQCurrentSize - 1].nKey = 0;
		queue->PQItem[queue->PQCurrentSize - 1].nPrior = 0;
		queue->PQCurrentSize--;
	}
}

void PQRelease( PQueue** queue )
{
	PQClearQueue( *queue );
	( *queue )->PQSize = 0;
	free( ( *queue )->PQItem );
	queue = NULL;
}

void PQPrint( PQueue* queue )
{
	if( !PQIsEmpty( queue ) )
	{
		for( int i = 0; i < queue->PQCurrentSize; i++ )
			printf( "%d: %d - %lf\n", i, queue->PQItem[i].nKey, queue->PQItem[i].nPrior );
		printf( "Rozmiar: %d\n", queue->PQCurrentSize );
	}
	else
		printf( "Kolejka jest pusta" );

}


void UpdateDown( PQueue* queue, int l, int p )
{
	if( l == p ) return;
	int i = l;
	int j = 2 * i + 1;
	PQItem tmp = queue->PQItem[i];

	while( j <= p )
	{
		if( j < p )
			if( queue->PQItem[j].nPrior >= queue->PQItem[j + 1].nPrior ) // zmienione w stosunku do pq
				j++;

		if( queue->PQItem[i].nPrior > tmp.nPrior ) break;// zmiana w stosunku do pq

		queue->PQItem[i] = queue->PQItem[j];
		i = j;
		j = 2 * i + 1;
	}
	queue->PQItem[i] = tmp;
}



void UpdateUP( PQueue* queue, int l, int p )
{
	if( l == p ) return;
	int j = p;
	int i = ( j - 1 ) / 2;
	PQItem tmp = queue->PQItem[j];

	while( ( j > 0 ) && ( queue->PQItem[i].nPrior >= tmp.nPrior ) ) // zmienione w stosunku do pq
	{

		queue->PQItem[j] = queue->PQItem[i];
		j = i;
		i = ( j - 1 ) / 2;

	}

	queue->PQItem[j] = tmp;
}