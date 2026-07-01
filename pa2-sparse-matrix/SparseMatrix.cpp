// Include necessary header file
#include "SparseMatrix.h"

// Default constructor
SparseMatrix::SparseMatrix() : rowSize(0), columnSize(0) {}

// Constructor with specified row and column sizes
SparseMatrix::SparseMatrix(int rSize, int cSize) : rowSize(rSize), columnSize(cSize) {}

// Constructor to read data from file
SparseMatrix::SparseMatrix(string filename) {
    // Read data from the file
    readFile(filename);
}

// Function to read data from file and populate the matrix
void SparseMatrix::readFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // Display error message if file couldn't be opened
        cerr << "Error: Couldn't open file " << filename << endl;
        exit(1);
    }

    string line;
    rowSize = 0;
    columnSize = 0;
    // Read each line from the file
    while (!file.eof()) {
        getline(file, line);
        // Parse each element from the line and update rowSize
        rowSize = split_the_elements(line, rowSize);
    }
    file.close();
}

// Function to parse elements from a line and update rowSize
int SparseMatrix::split_the_elements(string item, int rowNumber) {
    size_t pos_end, pos_start;
    size_t pos = item.find(' ');

    if (pos == string::npos) {
        // Display error message if input format is invalid
        cerr << "Error: Invalid input format" << endl;
        exit(1);
    }

    int rowIndex = stoi(item.substr(0, pos));
    pos_start = pos + 1;
    do {
        pos_end = item.find(':', pos_start);
        int index = stoi(item.substr(pos_start, pos_end - pos_start));
        // Update columnSize if necessary
        if (columnSize < index) {
            columnSize = index;
        }
        pos_start = pos_end + 1;
        pos_end = item.find(' ', pos_start);
        double data = stod(item.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + 1;
        // Store the element in the matrix
        matrix.push_back({rowIndex, index, data});

    } while (pos_end != string::npos);

    return rowIndex;
}

// Addition operator overload
SparseMatrix SparseMatrix::operator+(const SparseMatrix &other) {
    // Check if matrices have the same dimensions
    if ((columnSize != other.columnSize) || (rowSize != other.rowSize)) {
        // Display error message and exit if dimensions are different
        cout << "Not allowed to add matrices with different sizes, exiting program.\n";
        exit(1);
    }

    SparseMatrix result(rowSize, columnSize);
    int idx1 = 0, idx2 = 0;
    int size1 = matrix.size(), size2 = other.matrix.size();
    // Merge both matrices while considering the same row indices
    while (idx1 < size1 && idx2 < size2) {
        const vecdata &data1 = matrix[idx1];
        const vecdata &data2 = other.matrix[idx2];

        if (data1.row_index == data2.row_index) {
            if (data1.index == data2.index) {
                // Add the elements if indices match and the sum is non-zero
                if (data1.d + data2.d != 0) {
                    result.matrix.push_back({data1.row_index, data1.index, data1.d + data2.d});
                }
                ++idx1;
                ++idx2;
            } else if (data1.index < data2.index) {
                result.matrix.push_back(data1);
                ++idx1;
            } else {
                result.matrix.push_back(data2);
                ++idx2;
            }
        } else if (data1.row_index < data2.row_index) {
            result.matrix.push_back(data1);
            ++idx1;
        } else {
            result.matrix.push_back(data2);
            ++idx2;
        }
    }

    // Append remaining elements from the matrices
    while (idx1 < size1) {
        result.matrix.push_back(matrix[idx1]);
        ++idx1;
    }
    while (idx2 < size2) {
        result.matrix.push_back(other.matrix[idx2]);
        ++idx2;
    }

    return result;
}

// Subtraction operator overload
SparseMatrix SparseMatrix::operator-(const SparseMatrix &other) {
    // Check if matrices have the same dimensions
    if ((columnSize != other.columnSize) || (rowSize != other.rowSize)) {
        // Display error message and exit if dimensions are different
        cout << "Not allowed to subtract matrices with different sizes, exiting program.\n";
        exit(1);
    }

    SparseMatrix result(rowSize, columnSize);
    int idx1 = 0, idx2 = 0;
    int size1 = matrix.size(), size2 = other.matrix.size();
    // Merge both matrices while considering the same row indices
    while (idx1 < size1 && idx2 < size2) {
        const vecdata &data1 = matrix[idx1];
        const vecdata &data2 = other.matrix[idx2];

        if (data1.row_index == data2.row_index) {
            if (data1.index == data2.index) {
                // Subtract the elements if indices match and the difference is non-zero
                if (data1.d - data2.d != 0) {
                    result.matrix.push_back({data1.row_index, data1.index, data1.d - data2.d});
                }
                ++idx1;
                ++idx2;
            } else if (data1.index < data2.index) {
                result.matrix.push_back(data1);
                ++idx1;
            } else {
                // Negate and append the other element if it has a larger index
                result.matrix.push_back({data2.row_index, data2.index, -data2.d});
                ++idx2;
            }
        } else if (data1.row_index < data2.row_index) {
            result.matrix.push_back(data1);
            ++idx1;
        } else {
            // Negate and append the other element if it has a larger index
            result.matrix.push_back({data2.row_index, data2.index, -data2.d});
            ++idx2;
        }
    }

    // Append remaining elements from the matrices
    while (idx1 < size1) {
        result.matrix.push_back(matrix[idx1]);
        ++idx1;
    }
    while (idx2 < size2) {
        // Negate and append the remaining elements from the other matrix
        result.matrix.push_back({other.matrix[idx2].row_index, other.matrix[idx2].index, -other.matrix[idx2].d});
        ++idx2;
    }

    return result;
}

// Unary negation operator overload for SparseMatrix
SparseMatrix SparseMatrix::operator-() {
    // Create a new SparseMatrix object to store the negated values
    SparseMatrix result(rowSize, columnSize);

    // Iterate through each element of the matrix and negate its value
    for (const auto &elem : matrix) {
        result.matrix.push_back({elem.row_index, elem.index, -elem.d});
    }

    return result; // Return the resulting SparseMatrix object
}

// Multiplication operator overload for SparseMatrix
SparseMatrix SparseMatrix::operator*(const SparseMatrix &other) {
    // Check if the number of columns in the first matrix matches the number of rows in the second matrix
    if (columnSize != other.rowSize) {
        cerr << "Error: Matrix dimensions are incompatible for multiplication" << endl;
        exit(1); // Exit the program if dimensions are incompatible
    }

    // Create a result matrix with appropriate dimensions
    SparseMatrix result(rowSize, other.columnSize);

    // Iterate over each row of the first matrix
    for (const auto &elem1 : matrix) {
        // Iterate over each column of the second matrix
        for (const auto &elem2 : other.matrix) {
            // If the column index of the first matrix matches the row index of the second matrix
            if (elem1.index == elem2.row_index) {
                // Calculate the product of the corresponding elements and add it to the result matrix
                double product = elem1.d * elem2.d;
                // Check if the result matrix already has a non-zero element at the same position
                bool found = false;
                for (auto &res_elem : result.matrix) {
                    if (res_elem.row_index == elem1.row_index && res_elem.index == elem2.index) {
                        res_elem.d += product;
                        found = true;
                        break;
                    }
                }
                // If no existing element was found, create a new one
                if (!found) {
                    result.matrix.push_back({elem1.row_index, elem2.index, product});
                }
            }
        }
    }

    return result; // Return the resulting SparseMatrix object
}

// Transpose function for SparseMatrix
SparseMatrix SparseMatrix::transpose() {
    // Use fillMatrix to copy data of the matrix to a 2D vector
    vector<vector<double>> matrixData = fillMatrix();
    
    // Take transpose of the 2D vector
    vector<vector<double>> transposedData(matrixData[0].size(), vector<double>(matrixData.size()));
    for (size_t i = 0; i < matrixData.size(); ++i) {
        for (size_t j = 0; j < matrixData[i].size(); ++j) {
            transposedData[j][i] = matrixData[i][j];
        }
    }

    // Create a SparseMatrix object according to the transposed data
    SparseMatrix transposedMatrix(columnSize, rowSize);
    for (size_t i = 0; i < transposedData.size(); ++i) {
        for (size_t j = 0; j < transposedData[i].size(); ++j) {
            if (transposedData[i][j] != 0.0) {
                transposedMatrix.matrix.push_back({static_cast<int>(i+1), static_cast<int>(j+1), transposedData[i][j]});
            }
        }
    }

    return transposedMatrix; // Return the transposed SparseMatrix object
}

// Assignment operator overload for SparseMatrix
void SparseMatrix::operator=(const SparseMatrix &other) {
    matrix = other.matrix; // Assign the matrix data
    columnSize = other.columnSize; // Assign the column size
    rowSize = other.rowSize; // Assign the row size
}

// Output stream operator overload for SparseMatrix
ostream& operator<<(ostream &outs, const SparseMatrix &other) {
    int currentRow = 0;
    for (const auto &elem : other.matrix) {
        if (elem.row_index != currentRow) {
            if (currentRow != 0) {
                outs << endl; // Move to a new line if row changes
            }
            currentRow = elem.row_index;
            outs << currentRow; // Print row_index only when it changes
        }
        outs << " " << elem.index << ":" << elem.d; // Print index and data
    }
    return outs; // Return the output stream
}

// Helper function to determine the maximum of two integers
int SparseMatrix::myMax(int a, int b) {
    return (a > b) ? a : b; // Return the maximum of the two integers
}

// Helper function to fill a 2D vector with data from the matrix
vector<vector<double>> SparseMatrix::fillMatrix() {
    // Determine the dimensions of the resulting matrix
    int rows = 0;
    int cols = 0;
    for (const auto& elem : matrix) {
        rows = myMax(rows, elem.row_index); // Update maximum row index
        cols = myMax(cols, elem.index); // Update maximum column index
    }
    // Initialize the resulting matrix with zeros
    vector<vector<double>> result(rows, vector<double>(cols, 0.0));

    // Fill the matrix with values from the sparse matrix
    for (const auto& elem : matrix) {
        result[elem.row_index-1][elem.index-1] = elem.d; // Fill the corresponding position with data
    }

    return result; // Return the filled 2D vector
}
