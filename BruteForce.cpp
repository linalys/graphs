// CPP program to implement traveling salesman
// problem using naive approach.
#include <bits/stdc++.h>
#include "BruteForce.h"

using namespace std;

//Stores the final solution
int finalBF[V+1];

BruteForce::BruteForce(int vert, int info[V][V]) {
    int graph[V][V];
    for(int i = 0;i<V; i++){
        for(int j = 0; j<vert; j++){
            graph[i][j] = 0;
        }
    }
    //Passes data from the file to the array to be used
    for(int i = 0;i<vert; i++){
        for(int j = 0; j<vert; j++){
            graph[i][j] = info[i][j];
        }
    }
    int s = 0;
    cout<<"Entering BruteForce"<<endl;
    cout<<"Minimum cost : "<< minPath(vert, graph, s)<< endl;
    cout<<"Path Taken : ";
    for (int i=0; i<=vert; i++)
        cout<<finalBF[i]<< "    ";
}

//Copies temporary solution to the final solution
void BruteForce::copyToFinal(int vert, int currPath[])
{
    for (int i=0; i<vert; i++)
        finalBF[i] = currPath[i];
    finalBF[vert] = currPath[0];
}

//Creates recursively all (n-1)! permutations of different paths
int BruteForce::minPath(int vert, int graph[][V], int s)
{
    int testPath[vert];
    //Stores all vertices apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < vert; i++)
        if (i != s)
            vertex.push_back(i);

    //Stores the minimum weight
    int minPath = INT_MAX;
    do {

        //Initializes current path weight
        int currentPathweight = 0;

        testPath[0] = s;
        int v = 1;

        //Computes current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            currentPathweight += graph[k][vertex[i]];
            k = vertex[i];
            testPath[v] = k;
            v++;
        }
        currentPathweight += graph[k][s];

        //If current path weight is less than total minimum, updates it and the final path
        if(currentPathweight< minPath){
            minPath = currentPathweight;
            copyToFinal(vert, testPath);
        }
    } while (next_permutation(vertex.begin(), vertex.end()));

    return minPath;
}

