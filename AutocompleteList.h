#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted
    

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int firstIndexOf(string prefix) {
        int prefixSize = prefix.size();
        //variables are created for the binary search(for first occurence)
        int high = size - 1;
        int low = 0;
        int indexFirst = -1;

        while(low <= high){
            int mid = low + (high - low) / 2;
            //compares the prefix with the query of the term
            //if query < prefix, search range is moved to the right
            //if query = prefix, index is recorded and search continues to the left
            if(terms[mid].query.compare(0, prefixSize, prefix) < 0){
                low = mid + 1;
            } else{
                if(terms[mid].query.compare(0, prefixSize, prefix) == 0){
                    indexFirst = mid; //index is recorded here
                }
                high = mid - 1; //continues search towards the left
            }
        }
        return indexFirst;
    }
    

    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(string prefix) {
        int prefixSize = prefix.size();
        //variables are reset for the binary search(for last occurence)
        int high = size - 1;
        int low = 0;
        int indexLast = -1;
        while(low <= high){
            int mid = low + (high - low) / 2;
            //compares the prefix with the query of the term
            //if query <= prefix, search range is moved to the right
            //if query > prefix, search range is moved to the left
            if(terms[mid].query.compare(0, prefixSize, prefix) <= 0){
                if(terms[mid].query.compare(0, prefixSize, prefix) == 0){
                    indexLast = mid;//records index of the last occurence of matching prefix
                }
                low = mid + 1; //continue towards right
            } else{
                high = mid - 1;//continues towards left
            }
        }
        return indexLast;
    }
    

    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        // TODO: Write this function (optional).
    }
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        // TODO: Write this function.(optional)
    }
    
 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        terms = nullptr; //terms array pointer is initialized to nullptr
        size = 0; //size initialized to 0
        sortType = "none"; //sortType initialized to none
    }
    

    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        terms = new Term[n]; //memory is allocated for n terms
        size = n; //size is set to n
        sortType = "none"; //sortType initialized to none
    }
    

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) {
        //input file opened and memory is allocated using size
        ifstream infile(filename);
        infile >> size;
        terms = new Term[size];

        //reads each term's weight and query from file
        for(int i = 0; i < size; i++){
            infile >> terms[i].weight; //weight is read
            infile.ignore(); //newline is ignored
            getline(infile, terms[i].query); //query is read as the entire line
        }

        //sorted in lexicographic order by the query string
        sort(terms, terms + size, [](const Term& x, const Term& y){
            if(x.query < y.query){ //Lambda function for lexicographic comparison
                return true;
            } else{
                return false;
            }
        });

        sortType = "lex";//set to lex to indicate lexicographic order
        infile.close();//closes the file
    }
    

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        if(other.size > 0){
            this -> terms = new Term[other.size];//new terms array is created with memory allocation
            for(int i = 0; i < other.size; i++){
                this->terms[i] = other.terms[i];//term is copied from other to this
            }
            this -> size = other.size;//size is set to other's size
            this -> sortType = other.sortType; //sort type is also copied over
        }else {
            this -> terms = nullptr; //if other has 0 terms, terms points to nullptr
            //size and sortType set to 0 and none
            this -> size = 0; 
            this -> sortType = "none";
        }
        
    }
    

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        if(this == &other){ //makes sure there is no self assignment
            return *this;
        }
        delete[] terms;//current terms array is deallocated
        //size and type is assigned from other
        this -> size = other.size;
        this -> sortType = other.sortType;

        if(this -> size > 0){
            //memory is allocated from terms array and each term is copied over
            this -> terms = new Term[size];
            for(int i = 0; i < this -> size;i++){
                this -> terms[i] = other.terms[i];
            }
        } else{
            this -> terms = nullptr; //if no terms, set to nullptr
        }
        return *this;//returns *this as a reference to the current object
    }
    

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        delete[] terms;//memory is deallocated for the terms array
        terms = nullptr; //pointer is set to nullptr;
    }
    

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {        
        return size; //returns the size
    }


    //
    //Public member function
    //Returns the sortType of the AutocompleteList
    //Created to aid with the test case for the copy constructor
    string getSortType(){
        return sortType; //returns the sortType
    }
    

    //
    //Public member function
    //Sets the sortType of the AutocompleteList
    //Created to aid with the test case for the allMatches function 
    void setSortType(string type){
        sortType = type; //takes in type and sets sortType to type
    }


    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        //checks if i is out of range
        if(i >= size || i < 0){
            throw out_of_range("AutocompleteList: i out of bounds"); //if so, throw an out_of_range error
        }
        return terms[i]; //returns a reference to Term at index i
    }


    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        AutocompleteList result;
        //checks if the prefix is empty or if type is "lex"
        int prefixSize = prefix.size();
        if(prefixSize == 0 || this -> sortType != "lex"){
            return result; //return empty Autocompletelist if one of the conditions is true
        }

        //lambda function that compares Terms by weight(in descending order)
        bool(*sortByWeight)(const Term&, const Term&) = [](const Term& x, const Term& y){
            if (x.weight > y.weight){
                return true;
            } else {
                return false;
            }
        };

        //calls the two private function to get the first and last matching indexes
        int indexFirst = firstIndexOf(prefix);
        int indexLast = lastIndexOf(prefix);
        
        //if no matches found at all, returns result empty
        if(indexFirst == -1 || indexLast == -1){
            return result;
        }
        
        int totalMatches = indexLast - indexFirst + 1; //gets the total number of matching terms

        //creates the AutocompleteList with the sorted matching terms
        result.sortType = "weight";
        result.size = totalMatches;
        result.terms = new Term[totalMatches];

        //matching terms are copied to the result and sorted by weight
        for(int i = 0; i < totalMatches; i++){
            result.terms[i] = terms[indexFirst + i];
        }
        sort(result.terms, result.terms + result.size, sortByWeight);

        return result;//autocompletelist with all matching terms is returned
    }


    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        AutocompleteList result;
        int prefixSize = prefix.size(); //size of prefix is determined
        //if prefix is empty or not sorted lexicographically, returns 0 
        if(prefixSize == 0 || this -> sortType != "lex"){
            return 0;
        }

        //calls the two private function to get the first and last matching indexes
        int indexFirst = firstIndexOf(prefix);
        int indexLast = lastIndexOf(prefix);
        
        //no matches found, returns 0
        if(indexFirst == -1 || indexLast == -1){
            return 0;
        }
        int matchNums = indexLast - indexFirst + 1; //calculates the total number of matching terms
        return matchNums; //returns the total number terms that start with the prefix
    }


    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {
        //iterates over each Term using a for loop in AutocompleteList
        for(int i = 0; i < size; i ++){
            //prints each term with a specific format of spaces
            cout << "        " << terms[i].query << ", " << terms[i].weight << endl;
        }
    }
};
