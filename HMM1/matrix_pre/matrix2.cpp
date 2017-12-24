#include <iostream>
using namespace std;

int main(){
    
    int a[5][5], b[5][5], c[5][5], m, n, p, q, i, j, k;
    
    cout << "Enters rows and columns of first matrix: ";
    cin >> m >> n;
    cout << "Enter rows and columns of second matrix: ";
    cin >> p >> q;
     
    if(n==p)
    {
        //ENTERING MATRIX
        cout << "\nEnter first matrix: \n";
        for(i=0;i<m;++i){
            for(j=0;j<n;++j)
                cin>>a[i][j];
        }
        cout << "\nEnter second matrix: \n";
        for(i=0;i<p;++i){
            for(j=0;j<q;++j)
                cin>>b[i][j];
        }

        cout << endl;

        //PRINTING MATRICES
        cout << "First matrix is: " << endl;
        for(int row=0;row<m; row++){
            for(int column=0; column<n; column++){
            cout << a[row][column] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
        cout << "Second matric is: " << endl;
        for(int row=0;row<p; row++){
            for(int column=0; column<q; column++){
            cout << b[row][column] << " ";
            }
            cout << endl;
        }
        cout << endl;

        //CALCULATING MATRIX MULTIPLICATION
        cout << "\nThe new matrix is: \n";
        for(i=0;i<m;++i)
        {
            for(j=0;j<q;++j)
            {
            c[i][j]=0;
            for(k=0;k<n;++k)
                c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
            cout << c[i][j] << " ";
            }
        cout << "\n";
        }
    }
    else
        cout << "\nSorry! Matrix multiplication can't be done";

   return 0;
}
