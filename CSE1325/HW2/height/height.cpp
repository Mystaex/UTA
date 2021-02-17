#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std; 

/*
Ethan Chase
EGC7646 | 1001457646
*/

class Rider{
    string name;
    int height;

public:
    Rider(string name, int height){
        this->name = name;
        this->height = height;
    }
    Rider(int height){
        this->height = height;
    }

    int get_height(){
        return height;
    }
};

class Ride{
    int minHeight;
    string rideName;
    vector<Rider> line;

public:
    Ride(int minHeight, string rideName){
        this->minHeight = minHeight;
        this->rideName = rideName;
    }

    void add_line(Rider rider){
        if(rider.get_height() > this->minHeight){
            this->line.push_back(rider);
            cout << "-Adding rider to line." << endl << endl;
        }
        else{
            cout << "-Sorry can't add rider-too short" << endl << endl;
        }
    }
};

class Amusement_park{
    int rideCount;
    vector<Ride> rides;

    void setRides(int rideCount){
        string input;
        cout << "~~~Amusement Park Info~~~" << endl;
        for(int i = 0; i < rideCount; i++){
            cout << "Ride " << i+1 << "- Enter minimum ride height and ride name:" << endl;
            getline(cin, input);
            stringstream ss(input);
            int minHeight;
            string rideName;
            ss >> minHeight >> rideName;
            this->rides.push_back(Ride(minHeight, rideName));
        }
        cout << endl;
    }

public:
    Amusement_park(int rideCount){
        this->rideCount = rideCount;
        setRides(rideCount);
    }
    Ride get_ride(int rideNum){
        Ride ride = rides[rideNum-1];
        return ride;
}
};

int main(int argc, char **argv)
{
    Rider r1("Yaris", 45); //name, height in inches
    Rider r2(49); //height in inches
     
    Amusement_park a1(3); //3 is the number of rides in the amusement park
    a1.get_ride(1).add_line(r1); //add a rider to the line of a ride

    Amusement_park a2(2); //2 is the number of rides in the amusement park
    a2.get_ride(1).add_line(r2); //add a rider to the line of a ride

    return 0;
}