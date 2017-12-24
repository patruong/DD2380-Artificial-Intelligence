#include <iostream>
using namespace std;

int main()
{
    /*Test matrix*/
    int m[3][3] =
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    
    int i;
    cout << "Please enter int: ";
    cin >> i;
    cout << "Value: " << i << "\n";
    cout << "Double: " << i*2 << "\n";
    cout << "mat: " << m[3][3] << "\n";

    int b[2][3] = {{1,2,3}, {7,8,9}};
    
    for(int row=0; row<2; row++){
        
        for(int column=0; column<3; column++){
            cout << b[row][column] << " "; 
        }
        cout << endl;
    }


    return 0;
}
