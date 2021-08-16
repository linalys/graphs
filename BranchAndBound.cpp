#include <bits/stdc++.h>
#include "BranchAndBound.h"
using namespace std;

// finalBAB[] stores the final solution
int finalBAB[N+1];
// visited[] keeps track of the already visited nodes in a particular path
bool visited[N];
// Stores the final minimum weight of shortest tour.
int finalRes = INT_MAX;


BranchAndBound::BranchAndBound(int vert, int info[N][N]) {
    //Passes data from the file to the array to be used
    int adj[N][N];
    for(int i = 0;i<vert; i++){
        for(int j = 0; j<vert; j++){
            adj[i][j] = info[i][j];
        }
    }

    begin(vert, adj);
    cout<<"Entering BranchAndBound"<<endl;
    printf("Minimum cost : %d\n", finalRes);
    printf("Path Taken : ");
    for (int i=0; i<=vert; i++)
        cout<<finalBAB[i]<<"    ";

}

// Starts the process by doing calculations for the first vertex, and calls the recursive function to fill the currPath[]
void BranchAndBound::begin(int vert, int adj[N][N])
{
    int currPath[N+1];
    // Calculate initial lower bound for the root node using the formula 1/2 * (sum of first min + second min) for all edges.
    // Also initialize the curr_path and visited array
    int currBound = 0;
    memset(currPath, -1, sizeof(currPath));
    memset(visited, 0, sizeof(currPath));

    // Computes initial bound
    for (int i=0; i<vert; i++)
        currBound += (firstMin(vert, adj, i) +
                      secondMin(vert, adj, i));

    currBound = (currBound&1)? currBound/2 + 1 : currBound/2;

    // Sets vertex 0 as start, places it in the current solution
    visited[0] = true;
    currPath[0] = 0;

    // Call to recursive function for currWeight equal to 0 and level 1
    recursion(vert, adj, currBound, 0, 1, currPath);
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//		 space tree
// curr_path[] -> where the solution is being stored which
//			 would later be copied to final_path[]
//Checks if the algorithm has ended with viable solution,
void BranchAndBound::recursion(int vert, int adj[N][N], int currBound, int currWeight,
                               int level, int currPath[])
{
    //Checks if all nodes have been covered
    if (level==vert)
    {
        //Checks if there is an edge from last vertex in path back to the first vertex
        if (adj[currPath[level-1]][currPath[0]] != 0)
        {
            int currRes = currWeight + adj[currPath[level-1]][currPath[0]];
            // Updates final result and final path if current result is better.
            if (currRes < finalRes)
            {
                copyToFinal(vert, currPath);
                finalRes = currRes;
            }
        }
        return;
    }

    //For any other level iterate for all vertices to build the search space tree recursively
    for (int i=0; i<vert; i++)
    {
        // Checks vertices to find new paths ( not diagonal entry in adjacency matrix and not visited already)
        if (adj[currPath[level-1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = currBound;
            currWeight += adj[currPath[level-1]][i];

            if (level==1)
                currBound -= ((firstMin(vert, adj, currPath[level-1]) +
                                firstMin(vert, adj, i))/2);
            else
                currBound -= ((secondMin(vert, adj, currPath[level-1]) +
                                firstMin(vert, adj, i))/2);

            //At this point the actual lower bound is currWeight + currBound
            //If current lower bound < finalRes, the node is explored further
            if (currBound + currWeight < finalRes)
            {
                currPath[level] = i;
                visited[i] = true;

                //Calls recursion for the next level
                recursion(vert, adj, currBound, currWeight, level+1,
                          currPath);
            }

            //Removes any changes that happened during the procedure
            currWeight -= adj[currPath[level-1]][i];
            currBound = temp;

            //Resets the visited array
            memset(visited, false, sizeof(visited));
            for (int j=0; j<=level-1; j++)
                visited[currPath[j]] = true;
        }
    }
}

//Copies the temporary solution to the final solution
void BranchAndBound::copyToFinal(int vert, int currPath[])
{
    for (int i=0; i<vert; i++)
        finalBAB[i] = currPath[i];
    finalBAB[vert] = currPath[0];
}

//Finds the minimum edge cost having an end at the vertex i
int BranchAndBound::firstMin(int vert, int adj[N][N], int i)
{
    int min = INT_MAX;
    for (int k=0; k<vert; k++)
        if (adj[i][k]<min && i != k)
            min = adj[i][k];
    return min;
}

// Finds the second minimum edge cost having an end at the vertex i
int BranchAndBound::secondMin(int vert, int adj[N][N], int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<vert; j++)
    {
        if (i == j)
            continue;
        if (adj[i][j] <= first)
        {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second &&
                 adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}
