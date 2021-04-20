#pragma once
#pragma warning (disable:4996)
#ifndef _heap_h
#define _heap_h 
#include <stdio.h>
#include "graph.h"

typedef struct TAG_ELEMENT {
	int vertex; /*points to vertex v[vertex]*/
	float key;
	int pos; //not in capture but being used in heap.cpp
	
}ELEMENT;

typedef ELEMENT* pELEMENT; /* pELEMENT =ElementT */

typedef struct TAG_HEAP {
	int capacity;  /*max size of the heap*/
	int size;      /*current size of the heap*/
	pELEMENT* H; /*array of pointers to elements*/
}HEAP;

void heapFree(HEAP* heap);

int HeapInsert(HEAP* heap, pELEMENT item, pVERTEX V, int flag);

int DecreaseKey(HEAP* heap, int pos, float newkey, pVERTEX V, int flag);

void MovingUp(HEAP* heap, int pos, pVERTEX V);

//void MovingDown(HEAP* heap, int pos, int* flag, int* count_Heapify);

pELEMENT DeleteMin(HEAP* heap, pVERTEX V, int flag);

HEAP* heapInit(int capacity);

void heapPrint(HEAP* heap);

//void WriteHeap(HEAP* heap);

//void Insert(HEAP* heap, ELEMENT* element);

//float ExtractMin(HEAP* heap);

//void DecreaseKey(HEAP* heap, int i, int value);

void minHeapify(HEAP* heap, int i, int flag);

void BuildHeap(HEAP* heap, int flag);

int parent(int i);
int left(int i);
int right(int i);

//void howmanyminheapify();
//void resetcounts();
#endif
