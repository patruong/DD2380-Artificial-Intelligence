#include <iostream>
using namespace std;


//CONSTANTS
const int m = 2;
const int n = 3;
const int p = 3;
const int q = 2;

void MatrixMult(int a[m][n],int b[p][q]);

int main(){
    

    int a[2][3]={   {1,2,3},
                    {4,5,6}  
                };
    int b[3][2]={
                    {1,2},
                    {3,4},
                    {5,6}
                };
    int m,n,p,q,i,j,k;
    MatrixMult(a,b);
    
   return 0;
}

void MatrixMult(int a[m][n],int b[p][q]){
    
    if (n==p){
        int i,j,k;
        int c[n][p];
        for(i=0;i<m;++i){
            for(j=0;j<q;++j){
                c[i][j] = 0;
                for(k=0;k<n;++k)
                    c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
                cout << c[i][j] << " ";
                }
        cout << "\n";
            }   
        }
    else
        cout << "\nDimension error";

}

