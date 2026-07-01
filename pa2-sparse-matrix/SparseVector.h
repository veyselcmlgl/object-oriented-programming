#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct vecdata
{
    int row_index; // represents row
    int index;  // represents column
    double d;   // represents value
};

class SparseVector
{
public:
    SparseVector();     // Default constructor
    SparseVector(int size);     // Constructor to create an object with given size
    SparseVector(string filename);      // Constructor to create object from file
    SparseVector operator +(const SparseVector &other);     // Function to add two vectors
    SparseVector operator -(const SparseVector &other);     // Function to subtract two vectors
    SparseVector operator -();      // Function to negate elements of the vector
    void operator =(const SparseVector &other);     // Function that assigns a vector to another
    friend ostream& operator <<(ostream &outs, const SparseVector & other);     // Function to print vector data
    friend double dot(const SparseVector &first, const SparseVector &second);       // Function to multiply elements of the vectors
private:
    vector<vecdata> vec;     // Stores vector data
    int max_index;  
    void read_file(string filename);     // Function to read file and create object
    void parse_the_element(string item);     // Function to parse strings
};

#endif