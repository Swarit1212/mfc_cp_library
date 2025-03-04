#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Book {
    int id;
    string title, author;
    int year;
};
string FILE_NAME = "library.csv";
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "Error opening file or file is empty!\n";
        return books;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Book book;
        ss >> book.id;
        ss.ignore(); // Ignore comma
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        ss >> book.year;
        books.push_back(book);
    }
    return books;
}

void saveBooks(vector<Book>& books) {
    ofstream file(FILE_NAME,ios::app);
    for (int i = 0; i < books.size(); i++)
        file << books[i].id << "," << books[i].title << "," << books[i].author << "," << books[i].year << endl;
}

void addBook() {
    vector<Book> books = loadBooks();
    Book book;
    cout << "Enter ID, Title, Author, Year: ";
    cin >> book.id; cin.ignore();
    getline(cin, book.title); getline(cin, book.author); cin >> book.year;
    books.push_back(book);
    saveBooks(books);
}

void viewBooks() {
    vector<Book> books = loadBooks();
    for (int i = 0; i < books.size(); i++)
        cout << books[i].id << " | " << books[i].title << " | " << books[i].author << " | " << books[i].year << endl;
}

void updateBook() {
    vector<Book> books = loadBooks();
    int id; cout << "Enter ID to update: "; 
    cin >> id;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            cout << "Enter new Title, Author, Year: ";
            cin.ignore();
            getline(cin, books[i].title); getline(cin, books[i].author); cin >> books[i].year;
            saveBooks(books);
            return;
        }
    }
    cout << "Book not found!\n";
}

void deleteBook() {
    vector<Book> books = loadBooks();
    int id; cout << "Enter ID to delete: ";
    cin >> id;
    books.erase(remove_if(books.begin(), books.end(), [id](Book& book) { return book.id == id; }), books.end());
    saveBooks(books);
}

int main() {
    int choice;
    do {
        cout << "1. Add\n2. View\n3. Update\n4. Delete\n5. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;
        }
    } while (choice != 5);
}