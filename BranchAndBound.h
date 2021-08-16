#ifndef UNTITLED8_BRANCHANDBOUND_H
#define UNTITLED8_BRANCHANDBOUND_H
const int N = 20;

class BranchAndBound{
public:
    BranchAndBound(int vert, int [][N]);
    void copyToFinal(int, int []);
    int firstMin(int, int [][N], int);
    int secondMin(int, int [][N], int);
    void recursion(int, int [][N], int, int, int, int[]);
    void begin(int, int [][N]);
};


#endif //UNTITLED8_BRANCHANDBOUND_H