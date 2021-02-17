#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class some{
    string s;
    int n;

public:
    some(int n, string s){
        this->s = s;
        this->n = n;
    }
    vector<string> split(string s){
        stringstream ss(s);
        vector<string> thing;

        while(ss >> s){
            thing.push_back(s);
        }

        return thing;

    }
    string getString(){
        return s;
    }

};

int main(int argc, char **argv){

    some thing(1, "Something");
    vector<string> test;
    test = thing.split(thing.getString());

    for(int i = 0; i < test.size(); i++){
        cout << test[i] << endl;
    }

    return 0;
}