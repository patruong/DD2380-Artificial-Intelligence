#include <iostream>
#include <fstream>
#include <stdlib.h> // atof
#include <stdio.h> // printf, fgets
#include <sstream> // stringstream

using namespace std;

int main(){

    ifstream infile; 
    infile.open("sample_00.in");
    
    if(infile.is_open()){
        std::string line;
        getline(infile, line);
        std::stringstream smurf(line);

        int n, m;
        int i, j;
        smurf >> m >> n;
        cout << m << "x" << n << endl;
        double **A = new double*[n];
        //double **A[m][n];
        for (i = 0; i < n; ++i) {
            A[i] = new double[m];
            for (j = 0; j < n; ++j) {
                 infile >> A[i][j];
            }  
        }

        for (i = 0; i < n; ++i){
            for (j = 0; j < m; ++j){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }

    }
    else{
        cout << "Fail not open" << endl;
    }

}

