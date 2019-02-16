//
// Created by emred on 13.12.2018.
//

#include "Graph.h"
Graph::Graph(int m, int n) {
    this->M=m;
    this->N=n;
    this->table=new long*[m];
    this->resultTable=new long*[m];
    this->adjList=new long**[m];
    for (int i = 0; i < m ; ++i) {
        table[i]=new long[n];
        resultTable[i]=new long[n];
        adjList[i]=new long*[n];
        for (int j = 0; j <n ; ++j) {
            adjList[i][j]=new long[4];
        }
    }
}
Graph::~Graph() {
    for (int i = 0; i < M; ++i) {
        delete[] table[i];
        delete[] resultTable[i];
        for (int j = 0; j < N; ++j) {
            delete[] adjList[i][j];
        }
        delete[] adjList[i];
    }
    delete[] table;
    delete[] resultTable;
    delete[] adjList;
}
void Graph::addHeight(int y, int x, long h) { table[y][x]=h;}
void Graph::fillAdjList() {
    for(int i=0;i<M;++i){
        for (int j = 0; j < N; ++j) {
            if(j==0){
                adjList[i][j][3]=-1;
                adjList[i][j][1]=abs(table[i][j+1]-table[i][j]);
                if(i==0){
                    adjList[i][j][0]=-1;
                    adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                }else if(i==M-1){
                    adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                    adjList[i][j][2]=-1;
                }else{
                    adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                    adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                }

            }else if(j==N-1){
                adjList[i][j][1]=-1;
                adjList[i][j][3]=abs(table[i][j-1]-table[i][j]);
                if(i==0){
                    adjList[i][j][0]=-1;
                    adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                }else if(i==M-1){
                    adjList[i][j][2]=-1;
                    adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                } else{
                    adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                    adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                }
            }else if(i==0){
                adjList[i][j][0]=-1;
                adjList[i][j][1]=abs(table[i][j+1]-table[i][j]);
                adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                adjList[i][j][3]=abs(table[i][j-1]-table[i][j]);
            }else if(i==M-1){
                adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                adjList[i][j][1]=abs(table[i][j+1]-table[i][j]);
                adjList[i][j][2]=-1;
                adjList[i][j][3]=abs(table[i][j-1]-table[i][j]);
            }else{
                adjList[i][j][0]=abs(table[i-1][j]-table[i][j]);
                adjList[i][j][1]=abs(table[i][j+1]-table[i][j]);
                adjList[i][j][2]=abs(table[i+1][j]-table[i][j]);
                adjList[i][j][3]=abs(table[i][j-1]-table[i][j]);
            }
        }
    }

}
void Graph::findResult(int m1, int n1, int m2, int n2) {

    long** cost=new long*[M];
    bool** known=new bool*[M];
    for (int k = 0; k < M; ++k) {
        cost[k]=new long[N];
        known[k]=new bool[N];
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            resultTable[i][j]=-1;
            cost[i][j]= 1000000001;
            known[i][j]=false;
        }
    }

    priority_queue<Pair*,vector<Pair*>,Pairptrs> abcd;
    cost[m1][n1]=0;
    resultTable[m1][n1]=0;
    abcd.push(new Pair(m1,n1,cost[m1][n1]));
    while(!abcd.empty()){
        Pair* temp=abcd.top();
        abcd.pop();
        if(!known[temp->row][temp->column]){
            known[temp->row][temp->column]=true;
            if(adjList[temp->row][temp->column][0]!=-1){
                if(!known[temp->row-1][temp->column]){
                    if(adjList[temp->row][temp->column][0]<=cost[temp->row-1][temp->column]){
                        cost[temp->row-1][temp->column]=adjList[temp->row][temp->column][0];
                        abcd.push(new Pair(temp->row-1,temp->column,cost[temp->row-1][temp->column]));
                        if(cost[temp->row-1][temp->column]>=resultTable[temp->row][temp->column]){
                            if(resultTable[temp->row-1][temp->column]==-1||resultTable[temp->row-1][temp->column]>cost[temp->row-1][temp->column]) {
                                resultTable[temp->row - 1][temp->column] = cost[temp->row - 1][temp->column];
                            }
                        }else{
                            if(resultTable[temp->row-1][temp->column]==-1||resultTable[temp->row-1][temp->column]>resultTable[temp->row][temp->column]) {
                                resultTable[temp->row - 1][temp->column] = resultTable[temp->row][temp->column];
                            }
                        }
                    }
                }
            }
            if(adjList[temp->row][temp->column][1]!=-1){
                if(!known[temp->row][temp->column+1]){
                    if(adjList[temp->row][temp->column][1]<=cost[temp->row][temp->column+1]){
                        cost[temp->row][temp->column+1]=adjList[temp->row][temp->column][1];
                        abcd.push(new Pair(temp->row,temp->column+1,cost[temp->row][temp->column+1]));
                        if(cost[temp->row][temp->column+1]>=resultTable[temp->row][temp->column]){
                            if(resultTable[temp->row][temp->column+1]==-1||resultTable[temp->row][temp->column+1]>cost[temp->row][temp->column+1]) {
                                resultTable[temp->row][temp->column+1]=cost[temp->row][temp->column+1];
                            }

                        }else{
                            if(resultTable[temp->row][temp->column+1]==-1||resultTable[temp->row][temp->column+1]>resultTable[temp->row][temp->column]) {
                                resultTable[temp->row ][temp->column+1] = resultTable[temp->row][temp->column];
                            }
                        }
                    }
                }
            }
            if(adjList[temp->row][temp->column][2]!=-1){
                if(!known[temp->row+1][temp->column]){
                    if(adjList[temp->row][temp->column][2]<=cost[temp->row+1][temp->column]){
                        cost[temp->row+1][temp->column]=adjList[temp->row][temp->column][2];
                        abcd.push(new Pair(temp->row+1,temp->column,cost[temp->row+1][temp->column]));
                        if(cost[temp->row+1][temp->column]>=resultTable[temp->row][temp->column]){
                            if(resultTable[temp->row+1][temp->column]==-1||resultTable[temp->row+1][temp->column]>cost[temp->row+1][temp->column]) {
                                resultTable[temp->row + 1][temp->column] = cost[temp->row + 1][temp->column];
                            }
                        }else{
                            if(resultTable[temp->row+1][temp->column]==-1||resultTable[temp->row+1][temp->column]>resultTable[temp->row][temp->column]) {
                                resultTable[temp->row + 1][temp->column] = resultTable[temp->row][temp->column];
                            }
                        }
                    }
                }
            }
            if(adjList[temp->row][temp->column][3]!=-1){
                if(!known[temp->row][temp->column-1]){
                    if(adjList[temp->row][temp->column][3]<=cost[temp->row][temp->column-1]){
                        cost[temp->row][temp->column-1]=adjList[temp->row][temp->column][3];
                        abcd.push(new Pair(temp->row,temp->column-1,cost[temp->row][temp->column-1]));
                        if(cost[temp->row][temp->column-1]>=resultTable[temp->row][temp->column]){
                            if(resultTable[temp->row][temp->column-1]==-1||resultTable[temp->row][temp->column-1]>cost[temp->row][temp->column-1]) {
                                resultTable[temp->row][temp->column-1]=cost[temp->row][temp->column-1];
                            }
                        }else{
                            if(resultTable[temp->row][temp->column-1]==-1||resultTable[temp->row][temp->column-1]>resultTable[temp->row][temp->column]) {
                                resultTable[temp->row ][temp->column-1] = resultTable[temp->row][temp->column];
                            }
                        }
                    }
                }
            }
        }
        if(known[m2][n2]){

            break;
        }

    }

    for (int i = 0; i < M; ++i) {
        delete[] cost[i];
        delete[] known[i];

    }

    delete[] cost;
    delete[] known;
}