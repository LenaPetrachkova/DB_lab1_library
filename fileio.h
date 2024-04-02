#ifndef DB_LAB1_FILEIO_H
#define DB_LAB1_FILEIO_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
void write_pod(ostream& os, const T& value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
T read_pod(istream& is) {
    T value;
    is.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

void write_string(ostream& os, const string& str);
string read_string(istream& is);

#endif //DB_LAB1_FILEIO_H
