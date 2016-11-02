#include <iostream>

using namespace std;

double maxRange(); // This function will evaluate the maximum range of the mortar.
double maxHeight(); // This function will evaluate the maximum height of the rock at 8 cranks.
double sevenCranks(); // This function will evaluate the height a mortar at 7 cranks will have to raised to hit a target at exactly 750 meters.
int crankNumber(int); // This function calculates how many cranks needed before raising the mortar to reach the desired distance.
double firingHeight(int); // This function calculates how high the mortar must be raised after cranked to reach the desired distance.

double xInitial; // Variable for horizontal distance at 1 crank.
double tInitial; // Variable for time taken for 1 crank.
double v; // Variable for initial horizontal and vertical velocity at one crank.
double g; // Variable for gravitational acceleration.
double targetDistance; // Variable for the target distance.
double cranks = 1; // Variable for number of cranks.

int main() {

	cout << "How far (in meters) did the rock move after one revolution?" << endl;

	cin >> xInitial;
	
	if (xInitial >= 12 && xInitial <= 15) { // This if statement and the following else statement checks whether xInitial is in between 12 and 15.
	
	    cout << "How much time (in seconds) did it take to get there?" << endl;
	    
	    cin >> tInitial;
	    
	    v = xInitial / tInitial; //// Calculation of the initial horizontal and vertical velocity.
	    
	    g = - ((2 * v) / tInitial); // Calculation of gravitational acceleration on the planet.

    	cout << "The maximum range for this mortar seems to be " << maxRange() << " meters." << endl;

    	cout << "At 8 cranks, the projectile would be at a height of " << maxHeight() << " meters." << endl;

    	cout << "To hit at only 7 cranks requires launching from a height of " << sevenCranks() << " meters." << endl;
    	
    	cout << "The mortar is now calibrated. Please enter the distance of the target." << endl;
    	
    	cin >> targetDistance;
    	
    	if (targetDistance >= 500 && targetDistance <= 1000) { // This if statement and the following else statement checks whether targetDistance is in between 500 and 1000.
    	    
    	    cout << "The mortar should be cranked " << crankNumber(cranks) << " times and raised to a height of " << firingHeight(crankNumber(cranks)) << "." << endl;
    	    
    	    return 0;
    	    
    	}
    	
    	else {
    	    
    	    cout << "The distance of the target should be between 500 and 1000 meters. The program will now terminate." << endl;
    	    
    	    return 0;
    	    
    	}
    	
    }
	
	else {
	    
	    cout << "The value should be between 12 and 15. The program will now terminate" << endl;
	    
	    return 0;
	    
	}

}

double maxRange() {

	double t9; // Variable for time rock is in the air for 9 cranks.

	t9 = - ((9 * v) / (g / 2)); // Calculation of time rock is in the air for 9 cranks.

	return (9 * v * t9); // Function returns the value maximum range at 9 cranks.

}

double maxHeight() {

	double t8; // Variable for time rock is in the air for 8 cranks.

	t8 = - ((8 * v) / (g / 2)); // Calculation of time rock is in the air for 8 cranks.

	return (((8 * v) * (t8 / 2)) + ((g / 2) * (t8 / 2) * (t8 / 2))); // Function returns the height of the rock at the point it spends half it's time in the air.

}

double sevenCranks() {

	double tRaise; // Variable for time needed for rock to reach 750 meters horizontally.

	tRaise = (750 / (7 * v)); // Calculation of time needed for rock to reach 750 meters horizontally.

	return (- (((7 * v) * tRaise) + ((g / 2) * tRaise * tRaise))); // Function returns the negative of how much the rock has gone under 0 vertically. 

}

int crankNumber(int n) {
    
	double time; // Variable for time rock is in the air for n cranks.
	
	double distance; // Variable for distance with n cranks.

	time = - ((n * v) / (g / 2)); // Calculation of time rock is in the air for n cranks.

	distance = (n * v * time); // Function returns the value maximum range at n cranks.
    
    if (distance < targetDistance) { // The following if else statement calculates the maximum number of cranks before the target distance.
      
        return crankNumber(n + 1); // Function calls itself with an incremented crank number.
        
    }
    
    else { // Once the distance with n cranks exceeds the targetDistance, this function returns the number of cranks minus 1.
        
        return (n - 1);
        
    }
    
}

double firingHeight(int n) {
    
	double tRaise; // Variable for time needed for rock to reach the target distance in meters horizontally.

	tRaise = (targetDistance / (n * v)); // Calculation of time needed for rock to reach the target distance in meters horizontally.

	return (- (((n * v) * tRaise) + ((g / 2) * tRaise * tRaise))); // Function returns the negative of how much the rock has gone under 0 vertically.
	
}