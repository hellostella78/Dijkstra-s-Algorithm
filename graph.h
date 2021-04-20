//#pragma once
//#pragma warning (disable:4996)
#ifndef _graph_h
#define _graph_h 1

#include <stdio.h>

typedef struct TAG_VERTEX {
	int color; /*color of vertex: in {0, 1, 2} */
	int pi;	   /*predecessor of vertex: in {1, 2, ..., n} */
	float dist;/*current distance from source vertex */
	int pos;   /*position in the heap array */
	char* name;/*name of the POI represented by this vertex */
}VERTEX;

typedef VERTEX *pVERTEX;
/*
v[1], v[2],...,v[n] form an array of n structs of type VERTEX
v[i] represetns vertex i
v[i].color is the color of vertex i
v[i].pi is either 0 or the predecessor of vertex i
v[i].dist is the current value of the source to i distance
v[i].name is not used at this moment
*/

typedef struct TAG_NODE {
	int u;  /*start vertex u... Reduadant safe guard*/
	int v;  /*end vertex v*/
	float w;/*weight of edge (u, v)*/
	TAG_NODE* next; /*pointer to next node*/
}NODE;

typedef NODE* pNODE; 

/*
A[1], A[2],...,A[n] form an array of n pointers of type pNODE
A[i] is the adjacency list of vertex i
*/

//int n = number of vertices, A = array of nod, int s = 
//int dijkstra(int n, pNODE* A, int s, int t, int f_i, int f_d, int f_u, int f_p);
pVERTEX dijkstra(int n, pNODE* A, int s, int t, int flag);

int printPath(int n, pNODE* A, int source, int deestination, int s, int t, int flag);
#endif