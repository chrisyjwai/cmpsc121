#include <iostream>

using namespace std;

int x;
int quarters(int);
int nickels(int);

int main() {
    
    cout << "This program will show how many quarters and nickels to put to gether to make an amount divisable by 5" << endl;
    
    cout << "Please input the amount you want to calculate" << endl;
    
    cin >> x;
    
    if (x % 5 != 0) {
        
        cout << "The amount is not a multiple of 5. The program will now end" << endl;
        
        return 0;
        
    }
    
    else {
    
    cout << "The number of quarters and nickels to make " << x << " is " << quarters(x) << " and " << nickels(x) << " respectively." << endl;
    
    return 0;
    
    }
    
}

int quarters(int n) {
    
    if (n % 25 == 0) {
        
        return (n / 25);
        
    }
    
    else {
        
        return quarters(n - 1);
        
    }
    
}

int nickels(int n) {
    
    if (n < 25) {
        
        return (n / 5);
        
    }
    
    else {
        
        if (n % 25 == 0) {
            
             return 0;
             
        }
        
        else {
            
            return nickels(n - 25);
            
        }
        
    }
    
}