#include "catalog.h"

int main() {
    Catalog catalog;

    // Read data
    parseDataFile("data.txt", catalog);

    // Process commands
    processCommands("commands.txt", catalog);

    log("");

    return 0;
}