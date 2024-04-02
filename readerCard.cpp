#include "readerCard.h"
#include "fileio.h"

void ReaderCard::write(std::ostream& os) const {
    write_pod(os, id_);
    write_pod(os, book_id_);
    write_string(os, rent_date_);
    write_string(os, return_date_);
}

void ReaderCard::read(std::istream& is) {
    id_ = read_pod<int>(is);
    book_id_ = read_pod<int>(is);
    rent_date_ = read_string(is);
    return_date_ = read_string(is);
}