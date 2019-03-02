
//Celem dzialania programu jest przeanalizowanie tekstowego pliku wejsciowego, znalezienie najkrotszej drogi z domu do sklepu poprzez uzycie kolejki priorytetowej w formie kopca oraz algorytmu Dijkstry, a nastepnie wydruk odleglosci, czasu oraz sciezki do pliku wyjsciowego
//Struktura pliku: numer budynku, czy jest to sklep ( 1 - tak, 0 - nie), liczba sasiadow, numer sasiada, odleglosc

//The purpose of this program is to analyze text input file, find the shortest route to the shop from home using the priority queue in the structure of heap and Dijkstra algorithm and print results in output file ( wyniki.txt)
//Structure of the input file: number of the building, is it a shop ( 1-yes, 0 - no), number of the neigbouring building, number of the neighbouring building, distance to this building, ...

#include "pch.h"
#include "global.h" 
#include "list.h"


int ReadFile( Vertex** vertex, FILE* fin );
void PrintResults( Vertex* node, int nSize );
void PrintWays( FILE* fout, Vertex* pVertex, int nSize );
int AllocAddLines( Vertex** vertex, int nCurrSize );

#define REALLOC 3
#define RESULTS "wyniki.txt"



int main( int argc, char** argv )
{
	if( argc != 2 )
	{
		printf( "Podaj jako drugi argument nazwê pliku!\n" );
		return 0;
	}

	FILE* fin = fopen( argv[1], "r" );
	if( !fin )
	{
		perror( "Nie znaleziono pliku!\n" );
		return 0;
	}


	Vertex* pVertex = NULL; //tablica przechowujaca struktury bedace wierzcholkami grafu


	int amountOfReadedPlace = ReadFile( &pVertex, fin );
	if( !amountOfReadedPlace )
	{
		perror( "Nie przeczytano zadnych danych \n" );
		return 0;
	}



	int* visited = ( int* ) calloc( amountOfReadedPlace, sizeof( int ) );

	if( !visited )
	{
		perror( "ERROR: BAD MEMORY ALLOCATION \n" );
		return 0;
	}

	DFS( pVertex, 0, visited );

	

	PrintResults(pVertex, amountOfReadedPlace );
	FreeMemory( pVertex, amountOfReadedPlace );

	return 0;
}




int ReadFile( Vertex** vertex, FILE* fin )
{
	int amountOfReadedPlace = 0;
	char c;

	while( !feof( fin ) ) // dopoki nie koniec pliku
	{
	
			if( !( amountOfReadedPlace%REALLOC )&&  !AllocAddLines( vertex, amountOfReadedPlace ) ) //realokuje tablice struktur co 3 linijki pliku wsadowego
			{
				perror( "Nie udalo sie zaalokowac dodatkowej pamieci" );
				return -1;
			}
		

		Vertex* pVertex = &( ( *vertex )[amountOfReadedPlace] );//wskaznik na wierzcholek o ktorym sczytujemy info

		fscanf( fin, "%d %d %d", &pVertex->numberOfHome, &pVertex->isItShop, &pVertex->amountOfNeighbours );
		// wpisanie numberu, czy to sklep oraz liczby sasiadow
		ListItem* tmp = CreateList(); // stworzenie pustej listy
	
		while( !feof( fin ) && ( ( c = fgetc( fin ) ) != '\n' ) ) // dopoki nie koniec pliku oraz jesli nie znak nowej linii - wpisywanie w tej petli pozostalych informacji o wierzcholku
			if( c >= '0' && c <= '9' )
			{
				ungetc( c, fin );
				LISTINFO* pItem = CreateElement( 0, 0, 0 );
				fscanf( fin, "%d", &pItem->numberOfHome );
				fscanf( fin, "%lf", &pItem->distance );
				pItem->time = 0;// liczenie nastepuje w dfs
				tmp->pInfo->distance = 0;
				tmp->pInfo->numberOfHome = amountOfReadedPlace;
				tmp->pInfo->time = 0;
				//te trzy linijki sa konieczne, bo w tmp ustawia sie na pInfo pierwsze zawsze 0 - lista z glowa, wiec w wartosci glowy ustawiam po prostu wartosci dla danego wiercholka
				Insert( tmp, pItem ); // umiejscowienie  elementu pItem na poczatku listy

			}
		pVertex->listOfNeighbours = tmp;
		amountOfReadedPlace++; // po sczytaniu zwiekszamy liczbe przeczytanych wierzcholkow
	}

	fclose( fin );
	return amountOfReadedPlace;
}

void PrintResults( Vertex* pVertex, int nSize )
{
	FILE* fout = NULL;
	if( !( fout = fopen( RESULTS, "wt" ) ) ) // RESULTS- nazwa pliku wyjsciowego, jesli nie ma tego pliku to go tworzy
	{
		fputs( RESULTS, fout );
	}

	for( int i = 0; i < nSize; i++ )
	{
		pVertex[i].distanceToShop = Dijkstra( pVertex, nSize, i); // szukanie najkrotszej drogi 
		pVertex[i].time = pVertex[i].distanceToShop/SPEED;
		if( !( pVertex[i].isItShop ) )
		{
			int minutes = (int)( pVertex[i].time * 60 ); // minuty
			int seconds = (int)(( pVertex[i].time * 60 - minutes ) * 60); // sekundy
			fprintf( fout, "\nDla danego wierzcholka o indeksie %d, odleglosc do najblizszego sklepu wynosi: %.1lf, pokonasz ja w czasie %d minut i %d sekund.\nJest to sklep o indeksie: %d. \n", i, pVertex[i].distanceToShop, minutes, seconds, pVertex[i].nearestShop );
		}
		else
			fprintf( fout, "\nSKLEP o indeksie: %d. \n", i );

	}
	
	PrintWays( fout, pVertex, nSize );
	fclose( fout );
}

void PrintWays( FILE* fout, Vertex* pVertex, int nSize )
{
	for( int i = 0; i < nSize; i++ )
	{
		if( !( pVertex[i].isItShop ) )
		{
			int* route = ( int* ) calloc( nSize, sizeof( int ) );
			if( !route )
			{
				perror( "BAD MEMORY ALLOCATION" );		
			}

			int tmp = pVertex[i].nearestShop;
			int p = 1;
			route[0] = tmp; // konieczne jest wczesniejszy przyporzadkowanie
			while( p < nSize && route[p - 1] != i )// kopiowanie tablicy z odpowiednich pol
			{
				route[p] = tmp;
				tmp = pVertex[i].way[tmp]; 
				p++;
			}


			for( int k = 0; k < p / 2; k++ )			//odwraca tablice zwierajaca droge
			{
				int temp = route[p - k - 1];
				route[p - k - 1] = route[k];
				route[k] = temp;
			}
			pVertex[i].way = route; // przypisanie

			fprintf( fout, "\n" );

			fprintf( fout, "\n Sciezka dla domu nr: %d\n", i );
			int m = 0;
			while( pVertex[i].way[m] != pVertex[i].nearestShop )
				fprintf( fout, "%d -> ", pVertex[i].way[m++] );
			fprintf( fout, "%d ", pVertex[i].way[m] );
		}
	}
}





int AllocAddLines( Vertex** vertex, int nCurrSize )
{
	Vertex* tmp = ( Vertex* ) realloc( *vertex, sizeof( Vertex )*( nCurrSize + REALLOC ) ); //tablica przechowujaca wezly struktury
	if( !tmp )
	{
		perror( "ERROR: BAD MEMORY ALLOCATION" );
		return 0;
	}
	*vertex = tmp;
	memset( ( *vertex + nCurrSize ), 0, sizeof( Vertex ) * REALLOC ); //wyplenienie zerami jeszcze nie zapelnionych elementow tablicy
	return REALLOC;
}