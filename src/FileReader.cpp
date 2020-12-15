#include "FileReader.h"

vector<string> FileReader::fileToVector(const string& file_name) {
    std::ifstream text(file_name);
    vector<string> out_vec;

    if (text.is_open()) {
        std::istream_iterator<string> iter(text);
        while (!text.eof()) {
            out_vec.push_back(*iter);
            ++iter;
        }
    }

    return out_vec;
}