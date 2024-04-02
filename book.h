#ifndef DB_LAB1_BOOK_H
#define DB_LAB1_BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book() : id_(0), title_(""), annotation_(""), year_(""), amount_(0), deleted_(false) {}
    Book(int id, const string& title, const string& annotation, const string& year, int amount) :
            id_(id), title_(title), annotation_(annotation), year_(year), amount_(amount), deleted_(false) {}

    int id() const { return id_; }
    void set_id(int id) { id_ = id; }

    string title() const { return title_; }
    void set_title(const string& title) { title_ = title; }

    string annotation() const { return annotation_; }
    void set_annotation(const string& annotation) { annotation_ = annotation; }

    string year() const { return year_; }
    void set_year(const string& year) { year_ = year; }

    int amount() const { return amount_; }
    void set_amount(int amount) { amount_ = amount; }

    bool deleted() const { return deleted_; }
    void set_deleted(bool deleted) { deleted_ = deleted; }

    void write(ostream& os) const;
    void read(istream& is);

    int id_;
    string title_;
    string annotation_;
    string year_;
    int amount_;
    bool deleted_;
};

#endif //DB_LAB1_BOOK_H
