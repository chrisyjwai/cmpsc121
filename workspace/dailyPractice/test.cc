#include <iostream>

using namespace std;

int x;

int main() {
    
    cout << "This program will calculate the perimeter of a square" << endl;
    
    cout << "Please input the length of one side" << endl;
    
    cin >> x;
    
    cout << "The perimeter of the square of length " << x << " is " << x * 4 << endl;
    
    return 0;
    
}