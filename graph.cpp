#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "heap.h" 
#include "util.h"

pVERTEX V;



//n=total number of nodes, A = array of nodes, s=source vetex, t=distance
pVERTEX dijkstra(int n, pNODE* A, int s, int t, int flag) {
	//something missing part
	pVERTEX V = (pVERTEX)calloc(n + 1, sizeof(VERTEX)); //final product written in here
	HEAP* heap =  heapInit(n);
	pNODE node;
	pELEMENT element;
	int v, pos; 
	float w; //weight = w should be float ?
	int u;

	//Initialize
	heapInit(n);

	for (int i = 1; i <= n; i++) {
		V[i].color = 0;
		V[i].pi = NULL;
	}

	V[s].dist = 0;
	V[s].color = 1;

	pELEMENT source = (pELEMENT)calloc(1, sizeof(ELEMENT));
	source->vertex = s;
	source->key = V[s].dist;

	HeapInsert(heap, source, V, flag);

	//Dijkstra
	while (heap->size != 0) {

		//u = ExtractMin(heap);
		u = DeleteMin(heap, V, flag)->vertex;
		V[u].color = 2;

		if (u == t) {
			heapFree(heap);
			break;
		}


		node = A[u];
		while (node) {
			v = node->v;
			w = node->w;

			if (V[v].color == 0) {
				V[v].dist = V[u].dist + w;
				V[v].pi = u;
				V[v].color = 1;
				//printf("V[%d].color to 1\n", v);
				V[v].pos = heap->size + 1;
				element = (ELEMENT*)malloc(sizeof(ELEMENT));
				element->vertex = v;
				element->key = V[v].dist;
				//Insert(heap, element);
				HeapInsert(heap, element, V, flag);

				//if (flag == 1) {
				////print insertion information
				//printf("Inserted V[%d], dist=%12.6f\n", v, V[v].dist);
				//}
			}
			else if (V[v].dist > V[u].dist + w) {
				//if (flag == 1) {
				////print insertion information
				//printf("Decrease key of vertex %d, from %12.6f to %12.6f\n", v, V[v].dist, V[u].dist + w);
				//}
				V[v].dist = V[u].dist + w;
				V[v].pi = u;
				pos = V[v].pos;
				DecreaseKey(heap, pos, V[v].dist, V, flag);
			}
			node = node->next;
		}
    }
	/*if (flag == 1) {
		for (v = 1; v <= n; v++) {
			if (V[v].color == 0) {
				printf("V[%7d].dist=	infinity, ", v);
			}
			else {
				printf("V[%7d].dist=%12.6f, ", v, V[v].dist);
			}
			printf("V[%7d].pi=%d, ", v, V[v].pi);
			printf("V[%7d].pos=%d\n", v, V[v].pos);
		}
	}*/

	return 0;
}

int printPath(int n, pNODE* A, int source, int destination, int s, int t, int flag) {
	pVERTEX V = dijkstra(n, A, source, destination, 0);
	int* path = new int[n];
	int count, j = 0;

	if (V[t].color == 0) {
		if (destination < 1 || destination > n || t == destination) {
			printf("No %d-%d path exists.\n", s, t);
			return 0;
		}
		else {
			printf("No %d-%d path has been computed.\n", s, t);
			return 0;
		}
	}

	path[0] = t;
	count++;
	int v = t;

	while (v != s) {
		if (V[v].color != 0) {
			if (V[v].color != 2) {
				j = 1;
			}
			v = V[v].pi;
			path[count] = v;
			count++;
		}
		else {
			if (v == t) {
				printf("No %d-%d path exists.\n", s, t);
				return 0;
			}
			else {
				printf("No %d-%d has been computed.\n", s, t);
				return 0;
			}
		}
		if (V[v].color != 2) {
			j = 1;
		}
	}
	if (j == 0) {
		printf("Shortest path: <");
	}
	else {
		printf("Path not known to be shortest: <");
	}

	for (int i = count - 1; i > 0; i--) {
		printf("%d, ", path[i]);
	}
	printf("%d>\n", path[0]);
	printf("The path weight is: %12.4f\n", V[t].dist);

	delete V;

	return 1;
}