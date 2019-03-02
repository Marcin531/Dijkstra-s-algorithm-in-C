#include "global.h"
#include "PQueue.h"


void DFS( Vertex* vertex, int indexOfVertex, int* visited ) // przechodzi graf - liczenie czasow do sasiadow
{
	visited[indexOfVertex] = 1;  //oznaczenie, ze bylo sie/ jest w tym wierzcholku
	ListItem* pList = vertex[indexOfVertex].listOfNeighbours;  //wybranie sasiada
	while( pList )		// dopoki jest jakis sasiad
	{
		pList->pInfo->time = pList->pInfo->distance / SPEED; // obliczenie czasu do danego sasiada 
		if( !visited[pList->pInfo->numberOfHome] ) // jezeli nie jest odwiedzony
			DFS( vertex, pList->pInfo->numberOfHome, visited ); //wchodze DFS w kolejne wierzcholki
		pList = pList->pNext;// przesuwa sie do kolejnego sasiada
	}

}


double Dijkstra( Vertex* vertex, int nSize, int start )
{
	PQueue* pQueue = PQInit( nSize ); // inizjalizacja kolejki priorytetowej - odwrocony priorytet!
	if( !pQueue )
	{
		perror( "Nie udalo sie zainicjalizowac kolejki priorytetowej" );
		return -1;
	}


	double* cTab = ( double* ) calloc( 1, nSize * sizeof( double ) ); //inicjalizuje kosztow dojscia c - cost - minimalne koszty dojscia
	int* pTab = ( int* ) calloc( nSize, sizeof( int ) ); //inicjalizuje tablica poprzednikow na sciezce od wierzcholka v
	if( !pTab || !cTab )
	{
		perror( "ERROR: BAD MEMORY ALLOCATION\n" );
		return -1;
	}


	

	for( int i = 0; i < nSize; i++ ) //wypelnia tablice kosztow wartosciami maksymalnymi
	{
		cTab[i] = INT_MAX; // //ustawienie kosztu dojscia na nieskonczonosc
		pTab[i] = -1; //tablica do tworzenia drogi
	}

	vertex[start].way = pTab;

	PQEnqueue( pQueue, start, 0 );
	cTab[start] = 0; // bo dla poczatkowego jest 0 odleglosc
	double len = 0; // odleglosc do najblizszego sklepu 

	while( !( PQIsEmpty( pQueue ) ) )
	{
		int k = PQDequeue( pQueue );// sciagniecie sasiada z kolejki
		if( vertex[k].isItShop ) // jesli jest sklepem to nie potrzeba szukac drogi 
		{
			vertex[start].nearestShop = k; // jesli wejdzie w tego ifa to k jest sklepem o najmniejszej odleglosci -> bo kolejka priorytetowa
			PQRelease( &pQueue );
			len = cTab[k];
			break;
		}

		else
		{
			ListItem* neighbourList = vertex[k].listOfNeighbours; //lista sasiadow 
			while( neighbourList )
			{
				int neighbour = neighbourList->pInfo->numberOfHome;// ustawienie  na sasiada

				if( cTab[k] + neighbourList->pInfo->distance < cTab[neighbour] ) // sprawdzam, czy jego dystans jest mniejszy niz koszt tablicy/ suumaryczny z dojsciem do niego
					//cTab[k] - droga do sasiada, ktorego sciagnieto z kolejki od wierzcholka neigbourList
				{
					cTab[neighbour] = cTab[k] + neighbourList->pInfo->distance;
					vertex[start].way[neighbour] = k; // poprzednik, z ktorego do kolejnego wierzcholk
					PQEnqueue( pQueue, neighbour, cTab[neighbour] ); //cTab[neigbour] - priorytet rowny drodze do tego sasiada
				}
				neighbourList = neighbourList->pNext; // wskazanie na nastepnego sasiada
			}
		}
	}
	free(cTab);
	return len;
}


void FreeMemory( Vertex* vertex, int nSize )
{
	for( int i = 0; i < nSize; i++ )
	{
		FreeList( vertex[i].listOfNeighbours );
		free( vertex[i].way );
	}
	free( vertex );
	vertex = NULL;
}
