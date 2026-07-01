#include "SparseVector.h"


// Default constructor
SparseVector::SparseVector() : max_index(0) {}

// Constructor with size argument
SparseVector::SparseVector(int size) : max_index(size) {}

// Constructor to read data from file
SparseVector::SparseVector(string filename) : max_index(0) {
    read_file(filename);
}

// Function to read data from file
void SparseVector::read_file(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Couldn't open file " << filename << endl;
        exit(1);
    }

    string line;
    while (!file.eof()) {
        file >> line;
        parse_the_element(line);
    }

    file.close();
}

// Function to parse each element from a line in the file
void SparseVector::parse_the_element(string item) {
    // Find the position of the colon (':') to separate index and data
    size_t pos = item.find(':');
    if (pos == string::npos) {
        cerr << "Error: Invalid input format" << endl;
        exit(1);
    }

    // Extract index and data from the string
    int index = stoi(item.substr(0, pos));
    double data = stod(item.substr(pos + 1));

    // Update max_index if necessary
    if (index > max_index)
        max_index = index;

    // Store non-zero data in the vector
    if(data != 0.0)
        vec.push_back({1, index, data});
}

// Addition operator overload
SparseVector SparseVector::operator+(const SparseVector &other) {

    SparseVector result;
    int idx1 = 0, idx2 = 0;
    int size1 = vec.size(), size2 = other.vec.size();
    // Merge both vectors while considering the same column indices
    while (idx1 < size1 && idx2 < size2) {
        const vecdata &data1 = vec[idx1];
        const vecdata &data2 = other.vec[idx2];
        // do addition if columns are same
        if (data1.index == data2.index) {
            if(data1.d + data2.d != 0) {
                result.vec.push_back({data1.row_index, data1.index, data1.d + data2.d});
            }
            ++idx1;
            ++idx2;
        } else if (data1.index < data2.index) {
            result.vec.push_back(data1);
            ++idx1;
        } else {
            result.vec.push_back(data2);
            ++idx2;
        }

    }
    // Append remaining elements from the matrices
    while (idx1 < size1) {
        result.vec.push_back(vec[idx1]);
        ++idx1;
    }
    while (idx2 < size2) {
        result.vec.push_back(other.vec[idx2]);
        ++idx2;
    }

    return result;
}

// Subtraction operator overload
SparseVector SparseVector::operator-(const SparseVector &other) {
    SparseVector result;
    int idx1 = 0, idx2 = 0;
    int size1 = vec.size(), size2 = other.vec.size();
    // Merge both vectors while considering the same column indices
    while (idx1 < size1 && idx2 < size2) {
        const vecdata &data1 = vec[idx1];
        const vecdata &data2 = other.vec[idx2];

        if (data1.index == data2.index) {
            if(data1.d - data2.d != 0) {
                result.vec.push_back({data1.row_index, data1.index, data1.d - data2.d});
            }
            ++idx1;
            ++idx2;
        } else if (data1.index < data2.index) {
            result.vec.push_back(data1);
            ++idx1;
        } else {
            result.vec.push_back({data2.row_index, data2.index, -data2.d});
            ++idx2;
        }

    }
    // Append remaining elements from the matrices
    while (idx1 < size1) {
        result.vec.push_back(vec[idx1]);
        ++idx1;
    }
    while (idx2 < size2) {
        result.vec.push_back({other.vec[idx2].row_index, other.vec[idx2].index, -other.vec[idx2].d});
        ++idx2;
    }

    return result;
}

// Unary negation operator overload
SparseVector SparseVector::operator-() {
    SparseVector result(max_index);
    for (const auto &data : vec) {
        result.vec.push_back({1, data.index, -data.d});
    }
    return result;
}

// Assignment operator overload
void SparseVector::operator=(const SparseVector &other) {
    vec = other.vec;
    max_index = other.max_index;
}

// Output stream operator overload
ostream& operator<<(ostream &outs, const SparseVector &other) {
    int i=0;
    for (const auto &data : other.vec) {
        if(i==0) {
        outs << data.index << ":" << data.d;
        i++;
        }
        else    outs << " " << data.index << ":" << data.d;
    }
    return outs;
}

// Dot product function for two sparse vectors
double dot(const SparseVector &first, const SparseVector &second) {
    double dot_product = 0.0;
    for (const auto &data1 : first.vec) {
        for (const auto &data2 : second.vec) {
            if (data1.index == data2.index) {
                dot_product += data1.d * data2.d;
                break;
            }
        }
    }
    return dot_product;
}
