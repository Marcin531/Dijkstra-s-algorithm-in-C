#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H


#include <stdlib.h>
#include "list.h"
#include "PQueue.h"
#include <stdio.h>
#include <memory.h>

#define PLACES 27
#define SPEED 5		//km/h
							//odleglosci pomiedzy wezlami sa podane w kilometrach
typedef struct 
{
	ListItem* listOfNeighbours;
	int numberOfHome; // numer wezla
	int isItShop; // czy to sklep 1 - tak 0 - nie
	int amountOfNeighbours; //liczba sasiadow
	double distanceToShop; // dystans
	double time; // czas w godzinach
	int* way; 
	int nearestShop; //indeks najblizszego sklepu 
}Vertex;

double Dijkstra( Vertex* vertex, int nSize, int start);
void FreeMemory( Vertex* vertex, int nSize );
void DFS( Vertex* vertex, int v, int* visited );



#endif