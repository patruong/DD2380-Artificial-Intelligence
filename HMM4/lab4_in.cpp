#include <iostream>
#include <fstream>
#include <stdlib.h> // atof
#include <stdio.h> // printf, fgets
#include <sstream> // stringstream
#include <math.h> // infinity st)


using namespace std;

int main(){
    //std::ifstream infile;
    //infile.open("hmm4_01.in");
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

        int m,n; // A
        int p,q; // B
        int r,s; // pi
        int k; // O
        int i,j,t; // iterator variables

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

        //BAUM-WELCH

        // 1. Initializationi *************
        int maxIters = 100;
        int iters = 0;
        double oldLogProb = -INFINITY;
        
        while (true){ 
        // 2. Compute a0[i] ************
         
        double c0 = 0;
        double *a0 = new double [s];
        for (i = 0; i < s; ++i){
            a0[i] = pi[0][i]*B[i][O[0]];
            c0 = c0 + a0[i];
        }

        // scale a0[i]
        c0 = 1/c0;
        for (i = 0; i < s; ++i){
            a0[i] = c0*a0[i];
        }

        // Compute a[t][i]
        
        /*Allocate memory for a*/
        double **a = new double *[k];
        for (i = 0; i < k; ++i){
            a[i] = new double[s];
        }
        
        /*Fill a*/
        for (i = 0; i < s; ++i){
            a[0][i] = a0[i];
        }
        
        /*Allocate memory for c*/
        double *c = new double[k];
        c[0] = c0;
        
        /*a[t][i] computation*/
        for (t = 1; t < k; ++t){
            c[t] = 0;
            for (i = 0; i < s; ++i){
                a[t][i] = 0;
                for (j = 0; j < s; ++j){
                    a[t][i] = a[t][i] + a[t-1][j]*A[j][i];
                }
                a[t][i] = a[t][i] * B[i][O[t]];
                c[t] = c[t] + a[t][i];
            }
            // scale a[t][i]
            c[t] = 1/c[t];
            for (i = 0; i < s; ++i){
                a[t][i] = c[t] *a[t][i];
            }
        }
        
        // 3. b-pass ***********
        // Let b[T-1][i] = 1, scaled by c[T-1]
        
        /*Allocate memory for b*/
        double **b = new double *[k];
        for (i = 0; i < k; ++i){
            b[i] = new double[s];
        }
                
        for (i = 0; i < s; ++i){
            b[k-1][i] = c[k-1];
        }

        /*b-pass*/
        
        for (t = k-2; t > -1; --t){
            double denom = 0; 
            for (i = 0; i < s; ++i){
                b[t][i] = 0;
                for (j = 0; j < s; ++j){
                    b[t][i] = b[t][i] + A[i][j] * B[j][O[t+1]] * b[t+1][j];
                }
                // scale b[t][i] with same scale factor as a[t][i]
                b[t][i] = c[t] * b[t][i];
            }
        }
        
        // 4. Compute g

        /*Allocate memory for g*/
        /*
        double ***g = new double **[k];
        
        for (i = 0; i < k; ++i){
            g[i] = new double *[s];
            }
        }
        
        for (t = 0; t < k; ++t){
            for (i = 0; i < s; ++i){
                g[t][i] = new double [s];
            }
        }*/

        double ***g = new double **[k];
        for (t = 0; t < k; ++t){
            g[t] = new double *[s];
            for (i = 0; i < s; ++i){
                g[t][i] = new double[s];
                for (j = 0; j < s; ++j){
                    g[t][i][j] = 0;
                }
            }
        }
        
        double **g_sum = new double *[k];
        for (t = 0; t < k; ++t){
            g_sum[t] = new double[s];
        }
        
         
        for (t = 0; t < k-1; ++t){
            double denom = 0;
            for (i = 0; i < s; ++i){
                for (j = 0; j < s; ++j){
                    denom = denom + (a[t][i] * A[i][j] * B[j][O[t+1]] * b[t+1][j]);
                }
            }
            for (i = 0; i < s; ++i){
                g_sum[t][i] = 0;
                for (j = 0; j < s; ++j){
                    g[t][i][j] = (a[t][i] * A[i][j] * B[j][O[t+1]] * b[t+1][j]) / denom;
                    g_sum[t][i] = g_sum[t][i] + g[t][i][j];
                }
            }
        }
       
        // Special Case for g[T-1][i]
        double denom = 0;
        denom = 0;
        for (i = 0; i < s; ++i){
            denom = denom + a[k-1][i];
        }
        for (i = 0; i < s; ++i){
            g_sum[k-1][i] = a[k-1][i] / denom;
        }
        
        // 5. Re-estimate A, B and pi

        // Re-estimate pi
        for (i = 0; i < s; ++i){
            pi[0][i] = g_sum[0][i];
        }
        
        // Re-estimate A
        for (i = 0; i < s; ++i){
            for (j = 0; j < s; ++j){
                double numer = 0;
                double denom = 0;
                for (t = 0; t < k-1; ++t){
                    numer = numer + g[t][i][j];
                    denom = denom + g_sum[t][i];
                }
                A[i][j] = numer / denom; 
            }
        }
         
        // Re-estimate B
        for (i = 0; i < s; ++i){
            for (j = 0; j < q; ++j){
                double numer = 0;
                double denom = 0;
                for (t = 0; t < k; ++t){
                    if (O[t] == j){
                        numer = numer + g_sum[t][i];
                    }
                    denom = denom + g_sum[t][i];
                }
                B[i][j] = numer / denom;
            }
        }
        
        // 6. Compute log[P(O|lambda)]
        double logProb = 0;
        for (i = 0; i < k; ++i){
            logProb = logProb + log(c[i]);
        }
        logProb = -logProb;

        // 7. To iterate or not iterate, that is the question...
        iters = iters + 1;
        if (iters < maxIters and logProb > oldLogProb){
            oldLogProb = logProb;
        }
        else {
            //printout - visual Format
            /*
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
            cout << endl;*/

            
            cout <<  m << " " << n << " "; 
            for (i = 0; i < m; ++i){
                for (j = 0; j < n; ++j){
                    cout << A[i][j] << " ";
                }     
            }
            cout << endl;

            cout << p << " " << q << " ";
            for (i = 0; i < p; ++i){
                for (j = 0; j < q; ++j){
                    cout << B[i][j] << " ";
                }
            }
            cout << endl;
            /*
            cout << r << " " << s << " ";
            for (i = 0; i < r; ++i){
                for (j = 0; j < s; ++j){
                    cout << pi[i][j] << " ";
                }
            }
            cout << endl;*/
            break;
        } 
    } 
    }
}

