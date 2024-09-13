/*-------------------------------------------
Program: application.cpp
Course: CS 251, Summer 2024, UIC
System: Advanced zyLab system
Author: Jason Park
-------------------------------------------*/

#include <iostream>
#include "AutocompleteList.h"
using namespace std;


int main() {
    string fileName;
    cout << "Enter filename: "; //prompts user to enter the file name
    getline(cin, fileName);//gets the file name input from the user
    AutocompleteList myList(fileName); //creates an autocompletelist with the filename

    char searchLetter; //asks the user to choose between normal search vs creative search
    cout << "Enter s-search or c-creative search: ";
    cin >> searchLetter;
    cin.ignore(); //ignores the newline character left in input buffer

    //for standards search option
    if(searchLetter == 's'){
        cout << "Welcome!" << endl;
        cout << "Type your search below, press enter for autocomplete (# to stop)." << endl;
        string prefix;
        while(true){
            cout << "Search: ";
            getline(cin, prefix); //takes in the prefix from the user

            if (prefix == "#"){ //checks if the search needs to be stopped 
                break;
            }
            AutocompleteList matches = myList.allMatches(prefix);
            matches.print(); //all matches for the prefix are gathered and printed 
        }
    } 

    //for the creative search option
    if(searchLetter == 'c'){
        cout << "Welcome!" << endl;
        cout << "Type your search below, press enter for autocomplete (# to stop)." << endl;
        string prefix;
        while(true){
            cout << "Search: ";
            getline(cin, prefix); //reads the search prefix from the user

            if (prefix == "#"){ //checks if the user wants to stop the search
                break;
            }

            int lengthLimit; //asks user to enter a length limit 
            cout << "Enter length limit for queries: ";
            cin >> lengthLimit; //takes in the length limit
            cin.ignore(); //ignores the newline character left in input buffer

            AutocompleteList matches = myList.allMatches(prefix);//takes in all matches for the prefix
            bool metCondition = false;//checks to see if there are matches that met the length condition

            for(int i = 1; i < matches.getSize(); i++){
                if(matches[i].query.length() <= static_cast<size_t>(lengthLimit)){
                    cout << "        " << matches[i].query << ", " << matches[i].weight << endl;
                    metCondition = true;//if at least one match meets the condition, they are printed out and met condition is true
                }
            }

            //if no matches are met at all, let the user know that no matches are found for the length limit and prefix combination
            if(!metCondition){
                cout << "0 matches were that were shorter than " << lengthLimit << " for the prefix " << prefix << "." << endl;
            }
        }
    }

}