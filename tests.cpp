#include <iostream>
#include "AutocompleteList.h"

using namespace std;


// Tests getSize() on first constructor
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool size_test1() {
    AutocompleteList  list;  // empty list
    //checks if the size of the 0
    if (list.getSize() == 0) {
        return true; //test passed
    }
    return false; //test failed
}


// Tests getSize() on second constructor
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool size_test2() {
    int n = 10;
    AutocompleteList  list(n);  // empty list
    //checks if size of the list is equal to 'n'
    if (list.getSize() == 10) {
        return true; //test passed
    }
    return false; //test failed
}


//tests the getSortType() on the first constructor
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool getSortTypeTest(){
    AutocompleteList list;//list is initialized
    //checks if the sort type returned is "none"
    if(list.getSortType() == "none"){
        return true; //test passed
    }
    return false; //test failed
}


//tests the setSortType() function
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool setSortTypeTest(){
    AutocompleteList list;
    list.setSortType("weight");//sets the sort type to "weight"
    //checks if sort type retrieved is "weight"
    if(list.getSortType() != "weight"){
        return false;//test passed
    }
    return true;//test failed
}


// Tests getSize() and lexicographic sorting on the third constructor
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool sortTest(){
    string fileName = "pokemon.txt";
    AutocompleteList myList(fileName);//creates autcompletelist from the file "pokemon.txt"

    //checks if the size of the list matches the expected size
    bool correctSize;
    if(myList.getSize() == 729){
        correctSize = true;
    } else {
        correctSize = false;
    }
    //checks if list is sorted in a lexicographic order by query
    bool correctSort = true;
    for(int i = 1; i < myList.getSize(); i++){
        //checks that the query before IS NOT lower lexicograhpically
        if(myList[i-1].query > myList[i].query){
            correctSort = false; //if so, returns false
        }
    }
    //returns true if both size and order are correct
    return (correctSort && correctSize);
}


//tests the copy constructor
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool copyConstructorTest(){
    string fileName = "redditors.txt";
    AutocompleteList myList(fileName);//creates an autocompletelist from file

    //uses the copy constructor to copy the autocompletelist
    AutocompleteList copiedList(myList);

    //checks if the size matches between the copied and original list
    if(myList.getSize() != copiedList.getSize()){ 
        return false;
    }
    //checks if the sort type matches between the copied and original
    if(myList.getSortType() != copiedList.getSortType()){
        return false;
    }
    //checks each term between the two lists to see if they match
    for(int i = 0; i < myList.getSize(); i++){
        if(myList[i].weight != copiedList[i].weight || myList[i].query != copiedList[i].query){
            return false;//if mismatch, returns false
        }
    }
    return true; //all checks passed, returns true
}


//tests the assignment operator
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool assignmentOperatorTest(){
    string fileName = "wiktionary.txt"; 
    AutocompleteList myList(fileName);//creates an autocompletelist from file
    //creates an empty list and assigns in to the created list using the assignment operator
    AutocompleteList assignedList;
    assignedList = myList;

    //checks if the size matches between the copied and original list
    if(myList.getSize() != assignedList.getSize()){
        return false;
    }
    //checks if the sort type matches between the copied and original
    if(myList.getSortType() != assignedList.getSortType()){
        return false;
    }
    //checks each term between the two lists to see if they match
    for(int i = 0; i < myList.getSize(); i++){
        if(myList[i].weight != assignedList[i].weight || myList[i].query != assignedList[i].query){
            return false; //if mismatch, returns false
        }
    }
    return true; //all checks passed, returns true
}


//tests the operator[] function
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool testOperator(){
    string fileName = "alexa.txt";
    AutocompleteList myList(fileName);

    //accesses each valid index first
    bool valid = true;
    for(int i = 0; i < myList.getSize(); i ++){
        Term term = myList[i];
    }
    valid = false;
    //now tests for out of bound indexes
    try{
        Term term = myList[myList.getSize() + 100]; //accesses an index way out of range
    } catch(out_of_range&){
        valid = true;//verifies that the operator[] threw out an out_of_range exception
    }
    return valid; //returns true if valid index were acccesible and if invalid indexes resulted in out_of_range
}


// tests the allMatches function
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool testAllMatches(){
    string fileName = "alexa.txt";
    AutocompleteList myList(fileName);

    //sorts by lexicographic order
    myList.setSortType("lex");
    string prefix = "goo"; //sets prefix to search for
    AutocompleteList matches = myList.allMatches(prefix); //retrieve all matches for "goo" prefix

    bool valid = true;
    
    //checks that all returned matches start with the given prefix
    for(int i = 0; i < matches.getSize();i++){
        //prefix at the beginning of the query is compared
        if(matches[i].query.compare(0, prefix.size(), prefix) != 0){
            valid = false; //if match does not start with the prefix, not valid
            break;
        }
    }

    //checks that no matches are returned if the prefix is an empty string
    prefix = "";
    matches = myList.allMatches(prefix);
    if(matches.getSize() != 0){
        valid = false;//if matches do return for an empty prefix string, not valid
    }

    //checks that no matches are returned when the sortType is "weight"
    prefix = "goo";
    myList.setSortType("weight");
    matches = myList.allMatches(prefix);
    if(matches.getSize() != 0){
        valid = false;
    }
    return valid;
}


//tests the numberOfMatches function
// does not take in any paramters
// returns a bool based on whether the function passes the test
bool numberMatchTest(){
    string fileName = "small.txt";//file that contains "small.txt"
    AutocompleteList myList(fileName);

    myList.setSortType("lex");//sets sortType to lexicographic order
    string prefix = "jar";//prefix to test the number of matches
    int numMatches = myList.numberOfMatches(prefix); //get number of matches from the prefix

    int actualMatches = 2; //expected number of matches for prefix "jar"
    bool valid;
    //checks if the number of matches is the same as the expected number
    if(numMatches == actualMatches){
        valid = true; //test passed
    } else{
        valid = false; //test failed
    }

    prefix = ""; //tests an empty prefix 
    numMatches = myList.numberOfMatches(prefix);
    if (numMatches != 0) {
        valid = false; //it should return 0 matches, if not, fails
    }

    //checks that no matches are returned when the sortType is "weight"
    prefix = "goo";
    myList.setSortType("weight"); //sets sort type to weight
    numMatches = myList.numberOfMatches(prefix); //gets number of matches for "goo"
    if(numMatches != 0){
        valid = false; //failed since shoulud return 0 when sorted by weight
    }
    return valid;
}


//tests the print function
// does not take in any paramters
// prints two outputs, which should match correctly
void printTest(){
    string fileName = "tiny.txt";
    AutocompleteList myList(fileName); //creates autocomplete list

    //prints the output from the print function
    cout << "print function is printing:" << endl;
    myList.print();//calls the print function to display the terms
    //prints the expected correct output
    cout << "print function should print:" << endl;
    cout << "        buck, 10" << endl;
    cout << "        sad, 12" << endl;
    cout << "        smog, 5" << endl;
    cout << "        spit, 15" << endl;
    cout << "        spite, 20" << endl;
    cout << "        spy, 7" << endl;
    cout << "if outputs do not match, fix print function" << endl;
}


int main() {
    int passed = 0;
    int failed = 0;
    // Run tests
    if (size_test1()) {
        passed++;
    } else {
        cout << "size_test1 failed" << endl;
        failed++;
    }
    if (size_test2()) {
        passed++;
    } else {
        cout << "size_test2 failed" << endl;
        failed++;
    }
    if (getSortTypeTest()) {
        passed++;
    } else {
        cout << "getSortTypeTest failed" << endl;
        failed++;
    }
    if (setSortTypeTest()) {
        passed++;
    } else {
        cout << "setSortTypeTest failed" << endl;
        failed++;
    }
    if (sortTest()) {
        passed++;
    } else {
        cout << "sortTest failed" << endl;
        failed++;
    }
    if (copyConstructorTest()) {
        passed++;
    } else {
        cout << "copyConstructorTest failed" << endl;
        failed++;
    }
    if (assignmentOperatorTest()) {
        passed++;
    } else {
        cout << "assignmentOperatorTest failed" << endl;
        failed++;
    }
    if (testOperator()) {
        passed++;
    } else {
        cout << "testOperator failed" << endl;
        failed++;
    }
    if (testAllMatches()) {
        passed++;
    } else {
        cout << "testAllMatches failed" << endl;
        failed++;
    }
    if (numberMatchTest()) {
        passed++;
    } else {
        cout << "numberMatchTest failed" << endl;
        failed++;
    }
    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;
    printTest();
    return 0;
}
