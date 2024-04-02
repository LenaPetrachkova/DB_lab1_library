#ifndef DB_LAB1_READERCARD_H
#define DB_LAB1_READERCARD_H

#include <string>

using namespace std;

class ReaderCard {
public:
    static int last_id_;

    ReaderCard() : id_(0), book_id_(0), rent_date_(""), return_date_(""), deleted_(false) {}
    ReaderCard(int id, int book_id, const string& rent_date, const string& return_date) :
            id_(id), book_id_(book_id), rent_date_(rent_date), return_date_(return_date), deleted_(false) {}

    int id() const { return id_; }
    void set_id(int id) { id_ = id; }

    int book_id() const { return book_id_; }
    void set_book_id(int book_id) { book_id_ = book_id; }

    string rent_date() const { return rent_date_; }
    void set_rent_date(const string& rent_date) { rent_date_ = rent_date; }

    string return_date() const { return return_date_; }
    void set_return_date(const string& return_date) { return_date_ = return_date; }

    bool deleted() const { return deleted_; }
    void set_deleted(bool deleted) { deleted_ = deleted; }

    void write(ostream& os) const;
    void read(istream& is);

    int id_;
    int book_id_;
    string rent_date_;
    string return_date_;
    bool deleted_;
};


#endif //DB_LAB1_READERCARD_H
