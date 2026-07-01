#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Enumeration to represent different types of fields
struct Field {
    enum Type { STRING, INTEGER, DOUBLE, STRING_ARRAY, INTEGER_ARRAY, DOUBLE_ARRAY } type;
    string strValue;
    int intValue;
    double doubleValue;
    vector<string> strArray;
    vector<int> intArray;
    vector<double> doubleArray;
};

// Class representing an entry in the catalog
class CatalogEntry {
public:
    unordered_map<string, Field> fields; // Map to store field names and their corresponding values

    CatalogEntry() = default; // Default constructor

    // Function to get a field as string for logging or comparison purposes
    string getFieldAsString(const string& fieldName) const;
};

// Class representing the catalog
class Catalog {
public:
    vector<CatalogEntry> entries; // Vector to store catalog entries
    vector<string> fieldNames; // Vector to store field names

    // Method to add an entry to the catalog
    void addEntry(const CatalogEntry& entry);
};

// Function to log messages
void log(const string& message);

// Function to parse data from a file and populate the catalog
void parseDataFile(const string& filename, Catalog& catalog);

// Function to process commands from a file and manipulate the catalog
void processCommands(const string& filename, Catalog& catalog);

#endif // CATALOG_H
