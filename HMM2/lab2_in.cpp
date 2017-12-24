#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

double **matCalc(double **A, double **B, int m, int n, int p, int q);

int main(){
    //std::ifstream infile;
    //infile.open("hmm2_01.in");
    std::istream &infile = std::cin;

    if(infile){
        std::string A_str;
        std::string B_str;
        std::string pi_str;
        std::string O_str;

        getline(infile, A_str);
        getline(infile, B_str);
        getline(infile, pi_str);
        getline(infile, O_str);

        std::stringstream A_obj(A_str);
        std::stringstream B_obj(B_str);
        std::stringstream pi_obj(pi_str);
        std::stringstream O_obj(O_str);

        int m,n; //A
        int p,q; //B
        int r,s; //pi
        int k; //O
        int i,j,t; //Iterators

        A_obj >> m >> n;
        B_obj >> p >> q;
        pi_obj >> r >> s;
        O_obj >> k;

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
        
        // Fill O
        int *O = new int[k];
        for (i = 0; i < k; ++i){
            O_obj >> O[i];        
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

        cout << "O" << k << endl;
        for (i = 0; i < k; ++i){
            cout << O[i] << " ";
        }
        cout << endl;
        */
        
        // 1. Compute a0[i]    
        double *a0 = new double [s];
        for (i = 0; i < s; ++i){
            a0[i] = pi[0][i] * B[i][O[0]];
        }

        // Compute a[t][i]
        /*Allocate memory for a*/
        double **a = new double *[k];
        for (i = 0; i < k; ++i){
            a[i] = new double [s];
        }

        /*Fill a*/
        for (i = 0; i < s; ++i){
            a[0][i] = a0[i];
        }

        /*a[t][i] computation*/
        for (t = 1; t < k; ++t){
            for (i = 0; i < s; ++i){
                a[t][i] = 0;
                for (j = 0; j < s; ++j){
                    a[t][i] = a[t][i] + a[t-1][j] * A[j][i];
                }
                a[t][i] = a[t][i] * B[i][O[t]];
            }
        }
        
        double a_sum = 0;
        for (i = 0; i < s; ++i){
            a_sum = a_sum + a[k-1][i];
        }
        cout << a_sum << endl;
    
        


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
