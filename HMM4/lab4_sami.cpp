#include <iostream>
#include <fstream>
#include <stdlib.h> // atof
#include <stdio.h> // printf, fgets
#include <sstream> // stringstream

using namespace std;

int main(){
    std::ifstream infile; 
    infile.open("sample_00.in");
    
    if(infile.is_open()){
        std::string line;
        getline(infile, line);
        std::stringstream smurf(line);
        
        std::cout << line << std::endl;
        
        int m,n;
        smurf >> m >> n;
        std::cout << m << "x" << n;
        
        double **A = new double *[m]; 
        /*
         * **A is pointers on pointers
         * new double *[m], we create multiple pointers 
         * which we reference with [m], i.e.
         * [1],[2],[3] are all different pointers
         *
         * for-loop below allocates memory to respective
         * pointer location
         * */

        for (int i = 0; i < m; ++i) {
            A[i] = new double[n];
        }
        
        for (int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
               smurf >> A[i][j];
            }
        }
    }
    else{
        std::cout << "Fail not open" << std::endl;
    }
}
