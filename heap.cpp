#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include "graph.h"

//heap.cpp implements the heap data structure
#pragma warning(disable : 4996)
//Initialize(n) where n is capacity
using namespace std;
//int numberofminheapifycalled = 0;

void heapFree(HEAP* heap) {
	free(heap->H);
	free(heap);
}

int HeapInsert(HEAP* heap, pELEMENT item, pVERTEX V, int flag) {
	if (heap->size >= heap->capacity) {
		printf("Error in HeapInsert: Heap full...\n");
		return 1;
	}
	heap->size++;
	heap->H[heap->size] = item;
	heap->H[heap->size]->pos = heap->size;

	MovingUp(heap, heap->H[heap->size]->pos, V);

	if (flag == 1) {
		printf("Insert vertex %d, key=%12.4f\n", item->vertex, item->key);
	}

	return 0;
}

//void Insert(HEAP* H, ELEMENT* element) {
//	H->size++;          //increase the size of heap
//	int i = H->size;
//	H->H[i] = element; //insert a new element at the end
//
//	float value = element->key; //to call decreasekey
//	DecreaseKey(H, i, value); //sort the tree now with new inserted element
//}

int DecreaseKey(HEAP* heap, int pos, float newkey, pVERTEX V, int flag) {
	

	if (pos < 1 || pos > heap->size || newkey >= heap->H[pos]->key) {
		printf("Error in DecreaseKey\n");
		return 1;
	}
	if (flag == 1) {
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", heap->H[pos]->vertex, heap->H[pos]->key, newkey);
	}
	

	heap->H[pos]->key = newkey;
	MovingUp(heap, pos, V);

	return 0;
}

void MovingUp(HEAP* heap, int pos, pVERTEX V) {

	pELEMENT temp;
	int p = parent(pos);//int parent; parent = pos/2;

	if (pos > 1 && heap->H[pos]->key < heap->H[p]->key) {
		temp = heap->H[pos];
		heap->H[pos] = heap->H[p];
		heap->H[p] = temp;

		/*heap->H[pos]->pos = pos;
		heap->H[parent]->pos = parent;*/
		V[heap->H[pos]->vertex].pos = pos;
		V[heap->H[p]->vertex].pos = p;

		MovingUp(heap, p, V);
	}
}

//void MovingDown(HEAP* heap, int pos, int* flag, int* count_Heapify) {
//	// == MinHeapify
//}

pELEMENT DeleteMin(HEAP* heap, pVERTEX V, int flag) {
	pELEMENT min, last;
	
	if (heap->size <= 0) {
		printf("Error in DeleteMin: heap empty\n");
		return NULL;
	}
	min = heap->H[1];
	last = heap->H[heap->size--];
	heap->H[1] = last;
	V[heap->H[1]->vertex].pos = 1;

	minHeapify(heap, 1, flag);

	V[min->vertex].pos = 0;

	if (flag == 1) {
		printf("Delete vertex %d, key=%12.4f\n", min->vertex, V[min->vertex].dist);
	}
	return min;
}

HEAP* heapInit(int capacity) {

	HEAP* heap;
	heap = (HEAP*)calloc(1, sizeof(HEAP));
	heap->capacity = capacity;
	heap->size = 0;

	// dynamic memory allocation
	heap->H = (pELEMENT*)calloc(capacity + 1, sizeof(pELEMENT));
	return heap;
}
// print the elements 
void heapPrint(HEAP* H) {

	printf("capacity=%d, size=%d\n", H->capacity, H->size);

	for (int j = 1; j <= H->size; j++) {

		float content = (H->H[j])->key;
		if (j != H->size) {
			printf("%f, ", content);
		}
		else {
			printf("%f\n", content);
		}
	}
}

void WriteHeap(HEAP* H) {
	FILE* ofile;

	ofile = fopen("HEAPoutput.txt", "w");
	if (!ofile) {
		printf("Error: cannot open file for writing\n");
	}
	else {
		fprintf(ofile, "%d\n", H->size);
	}

	for (int j = 1; j <= H->size; j++) {
		fprintf(ofile, "%f\n", H->H[j]->key);
	}
	fclose(ofile);
}

//changed from float to int
//float ExtractMin(HEAP* H) {
//	float min;
//
//	if (H->size > 0) {
//		min = (H->H[1])->key; //this is min-heap, so the first index has smallest value
//		(H->H[1])->key = (H->H[H->size])->key; //to extract minimum, put the element in last index on the first replacing the min.
//		(H->size)--; //reduce the size
//		minHeapify(H, 1); //heapify the array
//		
//	}
//	return min;
//}

//void DecreaseKey(HEAP* H, int i, int value) {
//	if (value <= H->H[i]->key) {
//		H->H[i]->key = value;  //decrease the key in certain index
//
//		while (i > 1 && ((H->H[parent(i)]->key) > (H->H[i]->key))) {
//			//heapify the array with new element
//			int temp = (H->H[i])->key; //exchange current element with parent if parent element is bigger than the current one
//			(H->H[i])->key = (H->H[parent(i)])->key;
//			(H->H[parent(i)])->key = temp;
//			i = parent(i);
//		}
//	}
//}

void minHeapify(HEAP* H, int i, int flag) {
	int l = left(i), r = right(i), smallest; //these are all indices
	//numberofminheapifycalled++;

	if (l <= H->size && (H->H[l])->key < (H->H[i])->key) {
		smallest = l;
	}
	else {
		smallest = i;
	}
	if (r <= H->size && (H->H[r])->key < (H->H[smallest])->key) {
		smallest = r;
	}

	if (smallest != i) {
		float temp = (H->H[i])->key;
		(H->H[i])->key = (H->H[smallest])->key;
		(H->H[smallest])->key = temp;

		minHeapify(H, smallest, flag);
	}
}

//void BuildHeap(HEAP* H) {
//	for (int i = (H->size) / 2; i >= 1; i--) {
//		minHeapify(H, i);
//	}
//}

int parent(int i) {
	return i / 2;
}

int left(int i) {
	return 2 * i;
}

int right(int i) {
	return 2 * i + 1;
}


//void howmanyminheapify() {
//	printf("Number of Heapify calls: %d\n", numberofminheapifycalled);
//	resetcounts();
//}
