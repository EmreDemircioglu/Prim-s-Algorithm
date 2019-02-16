//
// Created by emred on 13.12.2018.
//

#include "Pair.h"

Pair::Pair(int a, int b, long cost) {
    this->row=a;
    this->cost=cost;
    this->column=b;
}
bool Pairptrs::operator()(const Pair *first, const Pair *second) {
    return first->cost>=second->cost;
}