#include <iostream>
using namespace std;
#include <fstream>
#include "Graph.h"
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    int y;
    infile >> y;
    int x;
    infile >> x;
    Graph prim(y,x);
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
        long temp;
        infile >> temp;
        prim.addHeight(i,j,temp);
        }
    }
    prim.fillAdjList();
    int q;
    infile >> q;
    ofstream myfile;
    myfile.open (argv[2]);
    for (int k = 0; k < q; ++k) {
        int y1; int x1; int y2; int x2;
        infile >> y1;
        infile >> x1;
        infile >> y2;
        infile >> x2;
        prim.findResult(y1-1,x1-1,y2-1,x2-1);
        myfile << prim.resultTable[y2-1][x2-1] << endl;
    }
    myfile.close();

    return 0;
}