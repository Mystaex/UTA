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

class Office{
    string officeName;
    string manager;
    vector<string> sections;

public:
    Office(string officeName, string manager, vector<string> sections){
        this->officeName = officeName;
        this->manager = manager;
        this->sections = sections;
    }
    vector<string> get_sections(){
        return this->sections;
    }
    string get_name(){
        return this->officeName;
    }
    string get_manager(){
        return this->manager;
    }
};

class Airport{
    string portName;
    vector<Office> offices;

    void createOffices(){
        string name;
        string name2;
        string manager;
        string office;
        vector<string> sections;

        for(int i = 0; i < 2; i++){
            cout << "Enter name of exchange office and manager: ";
            string input;
            getline(cin, input);
            stringstream ss(input);
            ss >> name >> name2 >> manager;
            office = name + " " + name2;
            if(office == "ABC Conversions"){
                sections.push_back("North");
                sections.push_back("East");
            }
            else if(office == "DEF Conversions"){
                sections.push_back("South");
                sections.push_back("West");
            }
            else{
                cout << "This office does not exist in XYZ Airport.";
            }
            this->offices.push_back(Office(office, manager, sections));
            sections.clear();
        }
    }

    /*Function that continuously loops asking for conversions*/
    void convertLoop(){
        bool run = true;
        while(run){
            string input;
            float totAmount;
            string office;
            string manager;
            cout << endl << "********" << endl << "Hello traveler! Where are you in the airport? ";
            getline(cin, input);
            cout << "********" << endl  << endl;
            if(input == "exit"){
                cout << "$$$Total dollars given out: $" << totAmount << endl;
                cout << "Exiting...";
                run = false;
                break;
            }
            /*Check which office handles the section of the building you're in*/
            for(int x = 0; x < 2; x++){
                for(int y = 0; y < 2; y++){
                    if(offices[x].get_sections()[y] == input){
                        office = offices[x].get_name();
                        manager = offices[x].get_manager();
                    }
                }
            }
            cout << "Welcome to " << office << ". Please contact the manager " << manager << " if you have any complaints. What currency are you converting to dollars and how much? ";
            getline(cin, input);
            int amount;
            string type;
            stringstream ss(input);
            ss >> amount >> type;

            if(type == "pesos"){
                float newAmount = amount * 0.05;
                cout << "Here you go: $" << newAmount;
                totAmount += newAmount;
            }
            else if(type == "yen"){
                float newAmount = amount * 0.0095;
                cout << "Here you go: $" << newAmount << endl;
                totAmount += newAmount;

            }
            else{
                cout << "We do not convert the " << type << " currency here. Sorry." << endl;
            }
        }
    }

public:
    Airport(string portName){
        this->portName = portName;
        createOffices();
        convertLoop();
    }
};

int main(int argc, char **argv){
    Airport("XYZ");
}