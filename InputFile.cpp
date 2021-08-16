//Libraries
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
//Classes
#include "InputFile.h"
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "DfsLikeApproach.h"
//Maximum capacity of array lists
#define N 20

using namespace std;
//Used for timing the alorythms
using namespace std::chrono;

InputFile::InputFile() {
    //Creates a 20*20 array to store the incoming data from the text file, initializes with 0
    int info[N][N];
    for(int i = 0;i<N; i++){
        for(int j = 0; j<N; j++){
            info[i][j] = 0;
        }
    }
    cout<<"Opening file"<<endl;
    //Opens file, reds it line by line
    std::ifstream file("C:\\Users\\USER\\CLionProjects\\Graphs\\test.txt");
    if (file.is_open()) {
        std::string line;
        int v = 0, vertex = 0;
        int l = 0;
        //For each line reads every number and places it into the right cell in the array list
        while ( getline(file, line)) {
            istringstream iss( line );
            int number;
            while( iss >> number ){
                info[l][v] = number;
                cout<<info[l][v]<<"    ";
                v++;
            }
            l++;
            //Stores the number of the vertices to pass it on as a parameter when calling the algorithms
            if(vertex==0){
                vertex = v;
            }
            v = 0;
        cout<<endl;
        }

        file.close();
        cout<<"---------------------------------------------------"<<endl;
        //Starts the chronometer, then calls the first class. When process is finished, stops the timer and prints the result
        auto start = high_resolution_clock::now();
        BranchAndBound bab(vertex, info);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // To get the value of duration it uses the count() member function on the duration object
        cout << endl<<"The duration of Branch and Bound : "<<duration.count() << " microseconds";
        cout<<endl<<"---------------------------------------------------"<<endl;
        //Starts the chronometer, then calls the second class. When process is finished, stops the timer and prints the result
        start = high_resolution_clock::now();
        BruteForce bf(vertex, info);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << endl<<"The duration of Branch and Bound : "<<duration.count() << " microseconds";
        cout<<endl<<"---------------------------------------------------"<<endl;
        //Starts the chronometer, then calls the third class. When process is finished, stops the timer and prints the result
        start = high_resolution_clock::now();
        DfsLikeApproach dfs(vertex, info);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << endl<<"The duration of Branch and Bound : "<<duration.count() << " microseconds";

    }else{
        cout<<"Could not open file";
    }


}
