#include <iostream>
#include <fstream> // fstream
#include <sstream> // stringstream

using namespace std;

double **matCalc(double **A, double **B, int m, int n, int p, int q);

int main(){
    std::istream &infile = std::cin;
    if(infile){
        
        std::string A_str;
        std::string B_str;
        std::string pi_str;

        getline(infile, A_str);
        getline(infile, B_str);
        getline(infile, pi_str);

        std::stringstream A_obj(A_str);
        std::stringstream B_obj(B_str);
        std::stringstream pi_obj(pi_str);

        int m,n; // A
        int p,q; // B
        int r,s; // pi
        int i,j; // iterators

        A_obj >> m >> n;
        B_obj >> p >> q;
        pi_obj >> r >> s;
        
        
        // Fill A
        double **A = new double *[m];
        for (i = 0; i < m; ++i){
            A[i] = new double[n];
        }
        for (i = 0; i < m; ++i){
            for (j = 0; j < n; ++j){
                A_obj >> A[i][j];    
            }
        
        }
        
        // Fill B
        double **B = new double *[p];
        for (i = 0; i < p; ++i){
            B[i] = new double[q];
        } 
        for (i = 0; i < p; ++i){
            for (j = 0; j < q; ++j){
                B_obj >> B[i][j];
            }
        }
        
        // Fill pi
        double **pi = new double *[r];
        for (i = 0; i < r; ++i){
            pi[i] = new double[s];
        }
        for (i = 0; i < r; ++i){
            for (j = 0; j < s; ++j){
                pi_obj >> pi[i][j];
            }
        }

        if (s == m){
            double **CE = matCalc(pi, A, r, s, m, n);
            int CE_row = r;
            int CE_col = n;
            if (CE_col == p){
                double **EPD = matCalc(CE, B, CE_row, CE_col, p, q);
                int EPD_row = CE_row;
                int EPD_col = q;
        
                cout << EPD_row << " " << EPD_col << " ";
                for (i = 0; i < EPD_row; ++i){
                    for(j = 0; j < EPD_col; ++j){
                        cout << EPD[i][j] << " ";
                    }
                }       
            }
            else{cout << "Dim. Error" << endl;}
        }
        else{cout << "Dim. Error" << endl;}
    }
    return 0;
}


double **matCalc(double **A, double **B, int m, int n, int p, int q){
    if (n==p){
    int i,j,k;
    double **c = new double *[m];
    for (i = 0; i < m; ++i){
        c[i] = new double[q];
    }
            
    
        for (i = 0;i < m; ++i){
            
            for (j = 0;j < q; ++j){
                c[i][j] = 0;
                for (k = 0; k < n; ++k){
                    c[i][j] = c[i][j] + (A[i][k] * B[k][j]);
                }
            } 
        }
    return c;
    }
    else{
        double **c = 0;
        cout << "Dim. Error" << endl;
        return c;
    }
    //return c;    
}
