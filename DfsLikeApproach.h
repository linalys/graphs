//
// Created by USER on 16-May-20.
//
#include<iostream>
#include <vector>

using namespace std;
const int D = 20;

class DfsLikeApproach {
public:
    // finalDFS[] stores the final solution
    int finalDfs[D+1];
    int currentDfs[D+1];
    DfsLikeApproach(int vert, int info[D][D]){

        //Passes data from the file to the array to be used
        int graph[D][D];
        for(int i = 0;i<D; i++){
            finalDfs[i] = 0;
            currentDfs[i] = 0;
            for(int j = 0; j<vert; j++){
                graph[i][j] = 0;
            }
        }
        for(int i = 0;i<vert; i++){
            for(int j = 0; j<vert; j++){
                graph[i][j] = info[i][j];
            }
        }

        // Boolean array to check if a node
        // has been visited or not
        vector<bool> v(vert);
        for (int i = 0; i < vert; i++)
            v[i] = false;

        // Mark 0th node as visited
        v[0] = true;
        int ans = INT_MAX;

        // Find the minimum weight Hamiltonian Cycle
        minHam(graph, v, 0, vert, 1, 0, ans);

        // ans is the minimum weight Hamiltonian Cycle
        cout<<"Entering DFS"<<endl;
        cout<<"Minimum cost : "<< ans<< endl;
        cout<<"Path Taken : ";

        for (int i=0; i<=vert; i++)
            cout<<finalDfs[i]<< "   ";
    };
    void minHam(int graph[D][D], vector<bool> &v, int currPos, int vert, int count, int cost, int& ans){
        currentDfs[count-1] = currPos;

        //If last node is reached and it has a link to the starting node, keeps the minimum value out of the total cost of traversal and "ans"
        //Then, returns to check for more possible values
        if (count == vert && graph[currPos][0]) {
            if((cost + graph[currPos][0]) < ans){
                ans = cost + graph[currPos][0];
                for(int i = 0; i<vert; i++){
                    finalDfs[i] = currentDfs[i];
                }
            }
            return;
        }

        //Loop that checks all the possible vertices that can be visited from current position in DFS manner. If there is no viable path
        //between current position and next vertex, it is ignored.
        for (int i = 0; i < vert; i++) {
            if (!v[i] && graph[currPos][i]) {
                // Mark as visited
                v[i] = true;
                minHam(graph, v, i, vert, count + 1,cost + graph[currPos][i], ans);

                // Mark ith node as unvisited
                v[i] = false;
            }
        }
    };
};


