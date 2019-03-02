#pragma once
#ifndef LIST_H
#define LIST_H

typedef struct
{
	int numberOfHome;
	double distance;
	double time;

}ListInfo;

#define LISTINFO ListInfo


typedef struct tagListItem
{
	LISTINFO* pInfo;
	tagListItem* pNext; // wskaznik na kolejny element

}ListItem;

//glowa w liscie oznacza element wskazujacy na piewrszy element, czyli jego wartosc nKey nie ma znaczenia
void InsertFront( ListItem* pList, LISTINFO* pInfo );   //wstawienie na poczatek
void Insert( ListItem* pAfter, LISTINFO* pInfo );
void Remove( ListItem* pAfter ); // usuniecie elementow o tych wskaznikach- nie ma przeszukiwac listy
void RemoveFront( ListItem* pList );   // odpowiada pop		- usuwa szczytowy element z listy
ListItem* CreateList(); //-worzy pust¹ listê	  ma zrobic pusty element na poczatku- glowe;
ListItem* Front( ListItem* pList );//odpowiednik funkcji top
void FreeList( ListItem* pList );//czysci liste- zostawia tylko glowe
int isEmpty( ListItem* pList );
//void DelList( ListItem* pList );// usuwa cala liste
LISTINFO* CreateElement(  int numberOfHome,double distance, double time );// tworzy element

#endif // !LIST_H