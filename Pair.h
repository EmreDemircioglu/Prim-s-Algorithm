//
// Created by emred on 13.12.2018.
//

#ifndef PROJECT4_PAIR_H
#define PROJECT4_PAIR_H


class Pair {

public:
    int row;
    int column;
    int cost;
    Pair(int a,int b,long cost);

};
struct Pairptrs{
    //comparison function for Pair pointers
    bool operator()(const Pair* first,const Pair* second);

};


#endif //PROJECT4_PAIR_H
