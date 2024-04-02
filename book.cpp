#include "book.h"
#include "fileio.h"

void Book::write(std::ostream& os) const {
    write_pod(os, id_);
    write_string(os, title_);
    write_string(os, annotation_);
    write_string(os, year_);
    write_pod(os, amount_);
}

void Book::read(std::istream& is) {
    id_ = read_pod<int>(is);
    title_ = read_string(is);
    annotation_ = read_string(is);
    year_ = read_string(is);
    amount_ = read_pod<int>(is);
}