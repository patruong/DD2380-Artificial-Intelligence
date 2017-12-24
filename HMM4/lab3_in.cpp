#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(){
    //std::ifstream infile;
    //infile.open("hmm3_01.in");
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
        
        //  Compute d0[i]
        double *d0 = new double [s];
        for (i = 0; i < s; ++i){
            d0[i] = pi[0][i] * B[i][O[0]];
            //cout << d0[i] << endl; page 1 OK
        }
        
        // Allocate memory for d (delta)
        double **d = new double *[k];
        for (i = 0; i < k; ++i){
            d[i] = new double[s];
        }
        
        // fill d[0]
        for (i = 0; i < s; ++i){
            d[0][i] = d0[i];
            // cout << d[0][i] << endl; page 1 OK
        }

        // Allocate memory for argmaxState
        int **argMaxState = new int *[k];
        for (i = 0; i < k; ++i){
            argMaxState[i] = new int[s];
        }

        for (t = 1; t < k; ++t){
            for (i = 0; i < s; ++i){
                d[t][i] = 0;
                argMaxState[t][i] = 0;
                for (j = 0; j < s; ++j){
                    double d_temp = d[t-1][j] * A[j][i] * B[i][O[t]];
                    int argMaxState_temp = j;
                    if (d_temp > d[t][i]){
                        d[t][i] = d_temp;
                        argMaxState[t][i] = argMaxState_temp;
                    }
                
                }
            }
        }
        /*        
        for (i=0; i < s; ++i){
            cout << d[3][i] << " "  << argMaxState[3][i] <<endl;
        }*/ //OK with deltas and states

        // Back tracking
        int *seq = new int[k];
        
        int lastState = 0;
        double temp = d[k-1][0];
        for(i = 0; i < s; ++i){
            //cout << temp << " " << d[k-1][i] << endl;
            if(d[k-1][i] > temp){
                //cout << "Im here" << endl;
                temp = d[k-1][i];
                lastState = i;
            }
        }
       
        seq[k-1] = lastState; 
        for(t = k-2; t >= 0; t--){
            lastState = argMaxState[t+1][lastState];
            seq[t] = lastState;
            //cout << seq[t] << endl;
        }
        for(t = 0; t < k; t++){
            cout << seq[t] << " ";
        }

    }
    return 0;
}

