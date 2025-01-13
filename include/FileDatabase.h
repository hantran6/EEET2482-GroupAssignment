#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#include <string>
#include <vector>

using namespace std;

class FileDatabase
{
private:
    string filePath;

public:
    FileDatabase(const string &filePath);

    vector<string> readAllLines() const;                   // Read all lines from file
    void writeAllLines(const vector<string> &lines) const; // Writes all lines to the file
    void appendLine(const string &line) const;             // Appends a line to the file
};

#endif