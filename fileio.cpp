#include "fileio.h"

using namespace std;

void write_string(ostream& os, const string& str) {
    write_pod(os, str.size());
    os.write(str.c_str(), str.size());
}

string read_string(istream& is) {
    string str;
    int size = read_pod<int>(is);
    if (size > 0) {
        char* buffer = new char[size];
        is.read(buffer, size);
        str.assign(buffer, size);
        delete[] buffer;
    }
    return str;
}