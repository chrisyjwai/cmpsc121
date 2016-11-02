#include 

using namespace std; 

int x; 

int pennys(int); 

int nickels(int); 

int main() { 
    
    cout << "This program will show how many nickels and pennys to put to gether to make an amount" << endl; 
    
    cout << "Please input the amount you want to calculate" << endl; cin >> x; 
    
    cout << "The number of nickels and pennys to make " << x << " is " << nickels(x) << " and " << pennys(x) << " respectively." << endl; 
    
    return 0; 
    
} 
    
int nickels(int n) { 
    
    if (n % 5 == 0) { 
        
        return (n / 5); 
        
    } 
        
        else { return nickels(n - 1); } } 
        

int pennys(int n) { if (n < 5) { return n; } else { if (n % 5 == 0) { return 0; } else { return pennys(n - 5); } } }