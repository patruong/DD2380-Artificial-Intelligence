#include <iostream>
#include <fstream> // fstream
#include <sstream> // stringstream

using namespace std;
/*
double **matCalc(double **A, double **B, int m, int n, int p, int q){
    int i,j,k;
    double **c = new double *[m];
    for (i = 0; i < m; ++i){
        c[i] = new double[q];
    }
            
    if (n == p){
        for (i = 0;i < m; ++i){
            
            for (j = 0;j < q; ++j){
                c[i][j] = 0;
                for (k = 0; k < n; ++k){
                    c[i][j] = c[i][j] + (A[i][k] * B[k][j]);
                }
            } 
        }
    }
    else{
        cout << "Dim. Error" << endl;
    }
    return c;    
}*/


int main(){
    //std::ifstream infile;
    //infile.open("sample_00.in");
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
        for (i = 0; i < s; ++i){
            pi[i] = new double[s];
        }
        for (i = 0; i < r; ++i){
            for (j = 0; j < s; ++j){
                pi_obj >> pi[i][j];
            }
        }

        /*
        // Init Printout
        cout << "A " << m << "x" << n << endl; 
        for (i = 0; i < m; ++i){
            for (j = 0; j < n; ++j){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "B " << p << "x" << q << endl;
        for (i = 0; i < p; ++i){
            for (j = 0; j < q; ++j){
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
        cout << "pi " << r << "x" << s << endl;
        for (i = 0; i < r; ++i){
            for (j = 0; j < s; ++j){
                cout << pi[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        */

        /*Matrix calculation*/
        // pi x A = Current Estimates
        // (1x4) * (4x4)
        
        //cout << "pi " << r << "x" << s << endl;
        //cout << "A " << m << "x" << n << endl;
        /*
        double **CE = matCalc(pi, A, r, s, m, n);
        int CE_row = r;
        int CE_col = n;
        double **EPD = matCalc(CE, B, CE_row, CE_col, p, q);
        int EPD_row = CE_row;
        int EPD_col = q;
        */
        int k;
        double **c = new double *[r];
        for (i = 0; i < r; ++i){
            c[i] = new double[n];
        }
            
        if (s == m){
            for (i = 0;i < r; ++i){
            
                for (j = 0;j < n; ++j){
                    c[i][j] = 0;
                    for (k = 0; k < s; ++k){
                        c[i][j] = c[i][j] + (pi[i][k] * A[k][j]);
                        //cout << A[i][k]*B[k][j] << endl;
                    }
                } 
            }
        }
        else{
            cout << "Dim. Error" << endl;
        }
		
		int CE_row = r;
		int CE_col = n;
        
        double **e = new double *[CE_row];
        for (i = 0; i < CE_row; ++i){
            e[i] = new double[q];
        }
            
        if (n == p){
            for (i = 0;i < r; ++i){
            
                for (j = 0;j < q; ++j){
                    e[i][j] = 0;
                    for (k = 0; k < CE_col; ++k){
                        e[i][j] = c[i][j] + (c[i][k] * B[k][j]);
                    }
                } 
            }
        }
    else{
        cout << "Dim. Error" << endl;
    }   
    int e_row = CE_row;
    int e_col = q;
        cout << e_row << " " << e_col << " ";
        for (i = 0; i < r; ++i){
            for(j = 0; j < q; ++j){
                cout << e[i][j] << " ";
            }
        }
        cout << endl;
    }
}
