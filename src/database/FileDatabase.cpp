#include "FileDatabase.h"
#include <fstream>
#include <iostream>
#include <filesystem> // For checking file existence and creating directories

using namespace std;

// Constructor
FileDatabase::FileDatabase(const string &filePath) : filePath(filePath) {
    // Get the parent directory
    auto parentDir = filesystem::path(filePath).parent_path();

    // Create the parent directory if it doesn't exist
    if (!filesystem::exists(parentDir)) {
        if (!filesystem::create_directories(parentDir)) {
            cerr << "Error: Could not create directory " << parentDir << endl;
            return;
        }
        cout << "Directory created: " << parentDir << endl;
    }

    // Create the file if it does not exist
    if (!filesystem::exists(filePath)) {
        ofstream file(filePath); // Creates an empty file
        if (!file.is_open()) {
            cerr << "Error: Could not create file " << filePath << endl;
        } else {
            cout << "File created: " << filePath << endl;
        }
        file.close();
    }
}

// Read all lines from the file
vector<string> FileDatabase::readAllLines() const {
    vector<string> lines;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << " for reading." << endl;
        return lines;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

// Write all lines to the file (overwrites existing content)
void FileDatabase::writeAllLines(const vector<string> &lines) const {
    ofstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << " for writing." << endl;
        return;
    }

    for (const auto &line : lines) {
        file << line << endl;
    }

    file.close();
}

// Append a line to the file
void FileDatabase::appendLine(const string &line) const {
    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << " for appending." << endl;
        return;
    }

    file << line << endl;
    file.close();
}
