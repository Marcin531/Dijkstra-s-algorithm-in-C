#pragma once
#ifndef PQUEUE_H
#define PQUEUE_H

#include "global.h"

typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct tagPQueue
{
	PQItem* PQItem;
	int PQSize;
	int PQCurrentSize;
	//pQueue//kolejka realizowana w postaci stogu//tablica w odpowiedniej funkcji ktora bedzie inicjalizowac te kolejke
	//int //PQSize // rozmiar kolejki priorytetowej
	//PQCurrentSize //aktualna ilosc elementow w kolejce - jednoczesnie indeks elementu to tablicy gdzie trzeba wstawic nowy element
	// po wstawieniu nalezy uaktualnic kopiec od dolu do gory
}PQueue;


PQueue* PQInit( int );	  //na bazie parametru okreslajacego maksymalny rozmiar kolejki ma stworzyc te kolejke
	// tworzy strukture PQueue dynamiczne, dla pQueue(pola) przydziela dynamicznie pamiec, przekazuje wartossc PQSize, ustawia
	//PQCurrentSize na zero
int PQIsEmpty( PQueue* );//zwraca wartosc 1 gdy jest pusta- zwraca po prostu PQCurrentSize 
void PQEnqueue( PQueue*, int nKey, double nPrior );//wkłada element do kolejki priorytetowej o kluczu nKey i priorytecie nPrior
int PQDequeue( PQueue* ); // wyciaga z kolejki pierwszy element ktory ma najwyzszy (lub najnizszy- u nas najnizszy)
	//piorytet
void PQClearQueue( PQueue* );//ma wyczyscic kolejke, ale cała kolejka zostaje
void PQRelease( PQueue** );//  całkowicie usuwa kolejkę, ale zwraca w parametrze we/wy NULLL
//void PQPrint( PQueue* );//drukuje w inorder

#endif