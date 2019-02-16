//
// Created by emred on 13.12.2018.
//

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H
using namespace std;
#include <list>
#include <cmath>
#include <vector>
#include <queue>
#include "Pair.h"
#include <iostream>
class Graph {
public:
int M;
int N;
long** table ;
long** resultTable;
long*** adjList;
void findResult(int m1, int n1, int m2, int n2);
void addHeight(int y, int x, long h);
void fillAdjList();
Graph(int m, int n);
~Graph();
};


#endif //PROJECT4_GRAPH_H
