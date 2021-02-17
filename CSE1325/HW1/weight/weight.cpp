
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
Ethan Chase
EGC7646 | 1001457646
*/

/*Function used to convert and output the new converted weight of the user*/
void convert(float weight, string unit, string name){
    if(unit == "kilos"){
        weight = weight*2.2046;
        unit = "pounds";
    }
    else if(unit == "pounds"){
        weight = weight/2.2046;
        unit = "kilos";
    }
    cout << "Hi " << name << "-you weigh ";
    printf("%0.1f ",weight);
    cout << unit << endl << endl;
}

/*Program that takes in the user's name and weight and returns the weight converted into another unit*/
int main(){
	int cont = 1;
    while(cont){
        string input;
        cout << "Please enter your name and weight: ";
        getline(cin, input);
        if(input == "exit"){
            cont = 0;
            break;
        }

        string name;
        string unit;
        float weight;
        stringstream ss(input);
        ss>>name>>weight>>unit;

        if((unit == "pounds") || (unit == "kilos")){
            convert(weight, unit, name);
        }
        else{
            cout << "Not enough info to convert." << endl << endl;
        }
    }
    cout << "Exiting..." << endl;
}

