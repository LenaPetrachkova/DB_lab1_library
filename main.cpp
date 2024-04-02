#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "book.h"
#include "readerCard.h"

using namespace std;

const string BOOK_FILE = "book.bin";
const string READER_CARD_FILE = "readerCard.bin";

void addBook(vector<Book>& books);
void addRent(vector<ReaderCard>& rents, const vector<Book>& books);
void updateBook(vector<Book>& book);
void updateRent(vector<ReaderCard>& rents, const vector<Book>& books);
void deleteBook(vector<Book>& books, vector<ReaderCard>& rents);
void deleteRent(vector<ReaderCard>& rent);
void bookList(const vector<Book>& books);
void rentList(const vector<ReaderCard>& rents);

void addBook(vector<Book>& books) {
    Book book;

    cout << "\nEnter book id: ";
    cin >> book.id_;

    bool idExists = false;
    for (const auto& existingBook : books) {
        if (existingBook.id_ == book.id_) {
            idExists = true;
            break;
        }
    }

    while (idExists) {
        cout << "Book with this ID already exists. Please choose a different ID: ";
        cin >> book.id_;
        idExists = false;
        for (const auto& existingBook : books) {
            if (existingBook.id_ == book.id_) {
                idExists = true;
                break;
            }
        }
    }

    cout << "Enter book title: ";
    cin >> book.title_;
    cout << "Enter book annotation: ";
    cin >> book.annotation_;
    cout << "Enter year of publication: ";
    cin >> book.year_;
    cout << "Enter amount: ";
    cin >> book.amount_;

    books.push_back(book);

    cout << "\nBook added successfully.\n";
}

void addRent(vector<ReaderCard> &rents, const vector<Book> &books) {
    ReaderCard rent;

    cout << "\nEnter rent id: ";
    cin >> rent.id_;

    bool idExists = false;
    for (const auto& existingRent : rents) {
        if (existingRent.id_ == rent.id_) {
            idExists = true;
            break;
        }
    }

    while (idExists) {
        cout << "Rent with this ID already exists. Please choose a different ID: ";
        cin >> rent.id_;
        idExists = false;
        for (const auto& existingRent : rents) {
            if (existingRent.id_ == rent.id_) {
                idExists = true;
                break;
            }
        }
    }

    cout << "Enter book id: ";
    cin >> rent.book_id_;

    auto bookIter = find_if(books.begin(), books.end(),
                            [&rent](const Book &book) {
                                return book.id_ == rent.book_id_ && !book.deleted();
                            });

    if (bookIter == books.end()) {
        cout << "\nBook not found or deleted. Rent not added.\n";
        return;
    }

    if (count_if(rents.begin(), rents.end(),
                 [&rent](const ReaderCard &r) {
                     return r.book_id_ == rent.book_id_;
                 }) >= bookIter->amount()) {
        cout << "\nCannot add more rents for this book. Maximum amount reached.\n";
        return;
    }

    cout << "Enter rent date (DD/MM/YYYY): ";
    cin >> rent.rent_date_;
    cout << "Enter return date (DD/MM/YYYY): ";
    cin >> rent.return_date_;

    rents.push_back(rent);

    cout << "\nRent added successfully.\n";
}

void updateBook(vector<Book> &books) {
    int id;

    cout << "\nEnter book id to update: ";
    cin >> id;

    auto bookIter = find_if(books.begin(), books.end(),
                            [id](const Book& book) {
                                return book.id_ == id && !book.deleted();
                            });

    if (bookIter == books.end()) {
        cout << "\nBook not found. Update failed.\n";
        return;
    }

    cout << "\nEnter new book title: ";
    string title;
    getline(cin >> ws, title);
    if (!title.empty()) {
        bookIter->title_ = title;
    }

    cout << "Enter new book annotation: ";
    string annotation;
    getline(cin >> ws, annotation);
    if (!annotation.empty()) {
        bookIter->annotation_ = annotation;
    }

    cout << "Enter new year of publication: ";
    string year;
    getline(cin >> ws, year);
    if (!year.empty()) {
        bookIter->year_ = year;
    }

    cout << "Enter new book amount: ";
    int amount;
    cin >> amount;
    bookIter->amount_ = amount;

    cout << "\nBook updated successfully.\n";
}

void updateRent(vector<ReaderCard>& rents, const vector<Book>& books) {
    int id;
    cout << "\nEnter rent id to update: ";
    cin >> id;
    auto rentIter = find_if(rents.begin(), rents.end(),
                            [id](const ReaderCard& rent) {
                                return rent.id_ == id;
                            });
    if (rentIter == rents.end()) {
        cout << "\nRent not found. Update failed.\n";
        return;
    }
    cout << "\nEnter new book id: ";
    int book_id;
    string input;
    getline(cin >> ws, input);
    if (!input.empty()) {
        book_id = stoi(input);
        auto bookIter = find_if(books.begin(), books.end(),
                                [book_id](const Book& book) {
                                    return book.id_ == book_id;
                                });
        if (bookIter == books.end()) {
            cout << "\nBook not found. Update failed.\n";
            return;
        }
        rentIter->book_id_ = book_id;
    }
    cout << "Enter new rent date (DD/MM/YYYY): ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        rentIter->rent_date_ = input;
    }
    cout << "Enter new return date (DD/MM/YYYY): ";
    getline(cin >> ws, input);
    if (!input.empty()) {
        rentIter->return_date_ = input;
    }
    cout << "\nRent updated successfully.\n";
}

void deleteBook(vector<Book>& books, vector<ReaderCard>& rents) {
    int id;
    cout << "\nEnter book id to delete: ";
    cin >> id;

    auto bookIter = find_if(books.begin(), books.end(), [id](const Book& book) {
        return book.id() == id;
    });

    if (bookIter == books.end()) {
        cout << "\nBook not found. Deletion failed.\n";
        return;
    }

    int rentCount = count_if(rents.begin(), rents.end(), [id](const ReaderCard& rent) {
        return rent.book_id() == id;
    });

    if (rentCount == bookIter->amount()) {
        auto rentIter = find_if(rents.begin(), rents.end(), [id](const ReaderCard& rent) {
            return rent.book_id() == id;
        });

        if (rentIter != rents.end()) {
            rents.erase(rentIter);
        }
    }

    if (bookIter->amount() > 1) {
        bookIter->set_amount(bookIter->amount() - 1);
    } else {
        bookIter->set_deleted(true);
    }

    cout << "\nBook deleted successfully.\n";
}

void deleteRent(vector<ReaderCard>& rents) {
    int id;
    cout << "\nEnter rent id to delete: ";
    cin >> id;
    auto rentIter = find_if(rents.begin(), rents.end(),
                            [id](const ReaderCard& rent) {
                                return rent.id_ == id;
                            });
    if (rentIter == rents.end()) {
        cout << "\nRent not found. Deletion failed.\n";
        return;
    }

    rentIter->set_deleted(true);

    cout << "\nRent deleted successfully.\n";
}

void bookList(const vector<Book>& books) {
    bool foundBooks = false;
    for (const auto& book : books) {
        if (book.deleted() == false) {
            if (!foundBooks) {
                foundBooks = true;
                cout << "List of books:\n";
            }
            cout << "\nBook ID: " << book.id() << endl;
            cout << "Title: " << book.title() << endl;
            cout << "Annotation: " << book.annotation() << endl;
            cout << "Year of publication: " << book.year() << endl;
            cout << "Amount: " << book.amount() << endl;
        }
    }
    if (!foundBooks) {
        cout << "\nNo books found!\n";
    }
}

void rentList(const vector<ReaderCard>& rents) {
    bool foundRents = false;

    for (const auto& rent : rents) {
        if (rent.deleted() == false) {
            if (!foundRents) {
                foundRents = true;
                cout << "List of rents:\n";
            }
            cout << "\nRent ID: " << rent.id_ << endl;
            cout << "Book ID: " << rent.book_id_ << endl;
            cout << "Rent Date: " << rent.rent_date_ << endl;
            cout << "Return Date: " << rent.return_date_ << endl;
        }
    }
    if (!foundRents) {
        cout << "\nNo rents found for this book!\n" << endl;
    }
}

int main() {
    vector<Book> books;
    vector<ReaderCard> rents;

    ifstream bookInput(BOOK_FILE, ios::binary);
    if (bookInput) {
        while (bookInput) {
            Book book;
            book.read(bookInput);
            if (bookInput) {
                books.push_back(book);
            }
        }
    }

    ifstream rentInput(READER_CARD_FILE, ios::binary);
    if (rentInput) {
        while (rentInput) {
            ReaderCard rent;
            rent.read(rentInput);
            if (rentInput) {
                rents.push_back(rent);
            }
        }
    }

    int choice;
    do {
        cout << "\n1. Add book\n";
        cout << "2. Add rent\n";
        cout << "3. Update book\n";
        cout << "4. Update rent\n";
        cout << "5. Delete book\n";
        cout << "6. Delete rent\n";
        cout << "7. List of books\n";
        cout << "8. List of rents\n";
        cout << "9. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                addRent(rents, books);
                break;
            case 3:
                updateBook(books);
                break;
            case 4:
                updateRent(rents, books);
                break;
            case 5:
                deleteBook(books, rents);
                break;
            case 6:
                deleteRent(rents);
                break;
            case 7:
                bookList(books);
                break;
            case 8:
                rentList(rents);
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 9);

    ofstream bookOutput(BOOK_FILE, ios::binary);
    if (bookOutput) {
        for (const auto &book: books) {
            book.write(bookOutput);
        }
    }

    ofstream rentOutput(READER_CARD_FILE, ios::binary);
    if (rentOutput) {
        for (const auto &rent: rents) {
            rent.write(rentOutput);
        }
    }
    return 0;
}

