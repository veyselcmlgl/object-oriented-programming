#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "SparseVector.h"

using namespace std;

class SparseMatrix
{
public:
    SparseMatrix();  // Default constructor
    SparseMatrix(int rSize, int cSize);  // Constructor that creates an object with given size.
    SparseMatrix(string filename);  // Constructor that reads file and creates object
    SparseMatrix operator +(const SparseMatrix &other);  // Function to add two matrices
    SparseMatrix operator -(const SparseMatrix &other);  // Function to subtract two matrices
    SparseMatrix operator -();  // This function negates elements of the matrix
    SparseMatrix operator *(const SparseMatrix &other);  // Function to multiply two matrices
    SparseMatrix transpose();  // Function to get the traspose of the matrix
    void operator =(const SparseMatrix &other);  // Assignment operator overload
    friend ostream& operator <<(ostream &outs, const SparseMatrix &other);  // This function writes the vector
    vector<vector<double>> fillMatrix();
private:
    vector<vecdata> matrix;  // Stores matrix data
    int rowSize;    // Row size
    int columnSize;     // Column size
    void readFile(string filename);    // Function to read file and create object
    int split_the_elements(string item, int rowNumber);   // Function to parse strings
    int myMax(int a, int b);
};

#endif