#include "catalog.h"

// Method to get the value of a field as a string
string CatalogEntry::getFieldAsString(const string& fieldName) const {
    auto it = fields.find(fieldName); // Find the field in the entry's fields
    if (it == fields.end()) return ""; // If field not found, return empty string

    const Field& field = it->second; // Get the field's value
    ostringstream oss;
    switch (field.type) {
    case Field::STRING: // If field type is string
        return field.strValue; // Return string value
    case Field::INTEGER: // If field type is integer
        return to_string(field.intValue); // Convert integer value to string and return
    case Field::DOUBLE: // If field type is double
        return to_string(field.doubleValue); // Convert double value to string and return
    case Field::STRING_ARRAY: // If field type is string array
        for (size_t i = 0; i < field.strArray.size(); ++i) { // Concatenate string array elements
            if (i > 0) oss << ":"; // Add delimiter between elements
            oss << field.strArray[i]; // Append element to output string stream
        }
        return oss.str(); // Return concatenated string array as string
    case Field::INTEGER_ARRAY: // If field type is integer array
        for (size_t i = 0; i < field.intArray.size(); ++i) { // Concatenate integer array elements
            if (i > 0) oss << ":"; // Add delimiter between elements
            oss << field.intArray[i]; // Append element to output string stream
        }
        return oss.str(); // Return concatenated integer array as string
    case Field::DOUBLE_ARRAY: // If field type is double array
        for (size_t i = 0; i < field.doubleArray.size(); ++i) { // Concatenate double array elements
            if (i > 0) oss << ":"; // Add delimiter between elements
            oss << field.doubleArray[i]; // Append element to output string stream
        }
        return oss.str(); // Return concatenated double array as string
    default:
        return ""; // Return empty string for unknown field types
    }
}

// Method to add an entry to the catalog
void Catalog::addEntry(const CatalogEntry& entry) {
    entries.push_back(entry); // Add the entry to the catalog's entries
}

// Function to log messages to a file
void log(const string& message) {
    ofstream logFile("output.txt", ios_base::app); // Open log file in append mode
    logFile << message << endl; // Write message to log file
}


void parseDataFile(const string& filename, Catalog& catalog) {
    ifstream infile(filename); // Open the data file for reading
    if (!infile) { // Check if file opening failed
        cout << "Cannot open data file.\n"; // Print error message
        exit(0); // Exit the program
    }

    string line;
    getline(infile, line); // Read the first line of the data file

    // Parse field names and types
    istringstream formatStream(line);
    string fieldDescriptor;
    vector<Field::Type> fieldTypes;
    while (getline(formatStream, fieldDescriptor, '|')) { // Iterate over field descriptors
        auto pos1 = fieldDescriptor.find(':'); // Find position of first colon
        auto pos2 = fieldDescriptor.rfind(':'); // Find position of last colon
        string fieldName = fieldDescriptor.substr(0, pos1); // Extract field name
        string fieldType = fieldDescriptor.substr(pos1 + 1, pos2 - pos1 - 1); // Extract field type
        string isArrayOrNot = fieldDescriptor.substr(pos2 + 1); // Extract array type

        catalog.fieldNames.push_back(fieldName); // Add field name to catalog

        // Determine field type and array type and push back to fieldTypes vector
        if (fieldType == "string" && isArrayOrNot == "single") {
            fieldTypes.push_back(Field::STRING);
        } else if (fieldType == "integer" && isArrayOrNot == "single") {
            fieldTypes.push_back(Field::INTEGER);
        } else if (fieldType == "double" && isArrayOrNot == "single") {
            fieldTypes.push_back(Field::DOUBLE);
        } else if (fieldType == "string" && isArrayOrNot == "multi") {
            fieldTypes.push_back(Field::STRING_ARRAY);
        } else if (fieldType == "integer" && isArrayOrNot == "multi") {
            fieldTypes.push_back(Field::INTEGER_ARRAY);
        } else if (fieldType == "double" && isArrayOrNot == "multi") {
            fieldTypes.push_back(Field::DOUBLE_ARRAY);
        } else {
            cout << "Unknown field type in format descriptor.\n"; // Print error message for unknown field type
            exit(0); // Exit the program
        }
    }

    // Log the field names
    ostringstream fieldNamesStream;
    for (size_t i = 0; i < catalog.fieldNames.size(); ++i) {
        fieldNamesStream << catalog.fieldNames[i];
        if (i < catalog.fieldNames.size() - 1) {
            fieldNamesStream << "|";
        }
    }
    log(fieldNamesStream.str());

    while (getline(infile, line)) { // Read each line of the data file
        CatalogEntry entry; // Create a new catalog entry
        istringstream lineStream(line);
        string fieldValue;
        bool missingField = false; // Flag to track missing fields
        bool duplicateEntry = false; // Flag to track duplicate entries

        for (size_t i = 0; i < catalog.fieldNames.size(); ++i) { // Iterate over field names
            if (!getline(lineStream, fieldValue, '|')) { // Read field value
                missingField = true; // Set missing field flag if unable to read field value
                break; // Break out of the loop
            }

            Field field; // Create a new field
            field.type = fieldTypes[i]; // Set field type
            switch (fieldTypes[i]) { // Fill the field based on its type
            case Field::STRING:
                field.strValue = fieldValue;
                break;
            case Field::INTEGER:
                field.intValue = stoi(fieldValue);
                break;
            case Field::DOUBLE:
                field.doubleValue = stod(fieldValue);
                break;
            case Field::STRING_ARRAY: {
                istringstream ss(fieldValue);
                string item;
                while (getline(ss, item, ':')) {
                    field.strArray.push_back(item);
                }
                break;
            }
            case Field::INTEGER_ARRAY: {
                istringstream ss(fieldValue);
                string item;
                while (getline(ss, item, ':')) {
                    field.intArray.push_back(stoi(item));
                }
                break;
            }
            case Field::DOUBLE_ARRAY: {
                istringstream ss(fieldValue);
                string item;
                while (getline(ss, item, ':')) {
                    field.doubleArray.push_back(stod(item));
                }
                break;
            }
            default:
                break;
            }

            entry.fields[catalog.fieldNames[i]] = field; // Add field to the entry
        }

        try {
            if (missingField) { // If missing field encountered
                throw runtime_error("Exception: missing field"); // Throw exception
            }
            // Check for duplicates based on the first field (title)
            for (const auto& existingEntry : catalog.entries) {
                if (entry.getFieldAsString(catalog.fieldNames[0]) == existingEntry.getFieldAsString(catalog.fieldNames[0])) {
                    duplicateEntry = true;
                    throw runtime_error("Exception: duplicate entry"); // Throw exception
                }
            }
        }
        catch (const exception& e) {
            log(e.what()); // Log the exception message
            string logEntry;
            for (size_t i = 0; i < catalog.fieldNames.size(); ++i) {
                logEntry += entry.getFieldAsString(catalog.fieldNames[i]);
                if (i < catalog.fieldNames.size() - 1) {
                    logEntry += "|";
                }
            }
            log(logEntry); // Log the problematic line
            continue; // Continue to the next line
        }

        if (!duplicateEntry) { // If entry is not duplicate
            catalog.addEntry(entry); // Add the entry to the catalog
        }
    }

    log(to_string(catalog.entries.size()) + " unique entries"); // Log the number of unique entries
}


void processCommands(const string& filename, Catalog& catalog) {
    ifstream infile(filename); // Open the commands file for reading
    if (!infile) { // Check if file opening failed
        cout << "Cannot open commands file.\n"; // Print error message
        exit(0); // Exit the program
    }

    string line;
    while (getline(infile, line)) { // Read each line of the commands file
        istringstream lineStream(line); // Create a string stream from the line
        string command, searchValue, inKeyword, fieldName;
        try {
            lineStream >> command; // Read the command type
            if (command == "search") { // If command is search
                if (!getline(lineStream, searchValue, '\"') || !getline(lineStream, searchValue, '\"')) { // Parse search command syntax
                    throw runtime_error("Exception: command is wrong"); // Throw exception if syntax is incorrect
                }
                lineStream >> inKeyword;
                if (!getline(lineStream, fieldName, '\"') || !getline(lineStream, fieldName, '\"') || inKeyword != "in") { // Parse search command syntax
                    throw runtime_error("Exception: command is wrong"); // Throw exception if syntax is incorrect
                }
                if (find(catalog.fieldNames.begin(), catalog.fieldNames.end(), fieldName) == catalog.fieldNames.end()) { // Check if fieldName exists in catalog
                    throw runtime_error("Exception: command is wrong"); // Throw exception if field not found
                }
                log(line); // Log the command
                for (const auto& entry : catalog.entries) { // Iterate over catalog entries
                    string logEntry;
                    for (size_t i = 0; i < catalog.fieldNames.size(); ++i) { // Construct log entry string
                        logEntry += entry.getFieldAsString(catalog.fieldNames[i]);
                        if (i < catalog.fieldNames.size() - 1) {
                            logEntry += "|";
                        }
                    }
                    if (entry.getFieldAsString(fieldName).find(searchValue) != string::npos) { // If search value found in field
                        log(logEntry); // Log the entry
                    }
                }
            } else if (command == "sort") { // If command is sort
                if (!getline(lineStream, fieldName, '\"') || !getline(lineStream, fieldName, '\"')) { // Parse sort command syntax
                    throw runtime_error("Exception: command is wrong"); // Throw exception if syntax is incorrect
                }
                if (find(catalog.fieldNames.begin(), catalog.fieldNames.end(), fieldName) == catalog.fieldNames.end()) { // Check if fieldName exists in catalog
                    throw runtime_error("Exception: command is wrong"); // Throw exception if field not found
                }
                log(line); // Log the command
                sort(catalog.entries.begin(), catalog.entries.end(), [&fieldName](const CatalogEntry& a, const CatalogEntry& b) { // Sort catalog entries based on specified field
                    return a.getFieldAsString(fieldName) < b.getFieldAsString(fieldName);
                });
                for (const auto& entry : catalog.entries) { // Iterate over sorted catalog entries
                    string logEntry;
                    for (size_t i = 0; i < catalog.fieldNames.size(); ++i) { // Construct log entry string
                        logEntry += entry.getFieldAsString(catalog.fieldNames[i]);
                        if (i < catalog.fieldNames.size() - 1) {
                            logEntry += "|";
                        }
                    }
                    if (entry.getFieldAsString(fieldName).find(searchValue) != string::npos) { // If search value found in field
                        log(logEntry); // Log the entry
                    }
                }
            } else {
                throw runtime_error("Exception: command is wrong"); // Throw exception for unknown command
            }
        }
        catch(const exception& e){
            log(e.what()); // Log the exception message
            log(line); // Log the problematic line
            continue; // Continue to the next line
        }
    }
}
