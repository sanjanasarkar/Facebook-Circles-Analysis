#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iterator>

using std::string;
using std::vector;

class FileReader {

public:
    static vector<string> fileToVector(const string& file_name);

};