#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

/*
Ethan Chase
EGC7646 | 1001457646
*/

/*Function to take in the name of a shape and output information about that shape*/
void shapeInfo(string shape){
    if(shape == "Triangle"){
        cout << "Area: 1/2bh" << endl;
    }
    else if(shape == "Circle"){
        cout << "Area: pir^2" << endl;
    }
    else if(shape == "Square"){
        cout << "Area: s^2" << endl;
    }
    else{
        cout << "Sorry, information for this shape is not available." << endl;
    }
}

/*Program to run continuously taking in shape names and outputting information about that shape*/
int main(){
    int cont = 1;
    int runCount = 1;
    cout << "********" << endl << "Shapes!" << endl << "********" << endl << endl;
    while(cont){
        cout << runCount << ". Shape: ";
        string input;
        getline(cin, input);

        if(input == "exit"){
            cont = 0;
        }
        else{
            shapeInfo(input);
            runCount++;
        }
        cout << endl;
    }
    cout << (runCount-1) << " shapes entered." << endl << "Exiting..." << endl;
}