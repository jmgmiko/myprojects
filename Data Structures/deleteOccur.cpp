/*
    C++ program for 1-D array to remove all occurrences of a given integer
    and shift the elements of the arrry to the right and fill the 'left' space
    with zeros.
    
    ex. input 10,20,15, 4,20, 2,20
    output is  0, 0, 0,10,15, 4, 2
*/

#include <iostream>
using namespace std;

int main()
{
    int input[] = { 20, 10,20,15, 4,20, 2,20 };
    int num = sizeof input / sizeof input[0];
    
    int remove = 20;
    int j=0;
    for( int i = num-1; i >=0; --i )
        if(input[i] == remove)
        {
            for( int k=i; k>j; --k) input[k] = input[k-1];
            input[j++] = 0;
        }
    // show after all 20's removed ...     
    for( int i=0; i<num; ++i) cout << input[i] << " ";
    cin.get();
}
