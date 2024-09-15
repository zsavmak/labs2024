#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}
#endif

using namespace std;

struct Book {
    int number;
    int year;
    int num_pages;
    char author[100];
    char name[100];
    char publisher[100];
};

int compareBooksByAuthor(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        char c1 = tolower(*str1);
        char c2 = tolower(*str2);
        if (c1 != c2) {
            return c1 < c2 ? -1 : 1;
        }
        ++str1;
        ++str2;
    }
    return *str1 ? 1 : *str2 ? -1 : 0;
}

void quickSort(Book a[], int l, int r) {
    if (l >= r) return;
    int i = l, j = r;
    char x[100];
    strcpy(x, a[(l + r) / 2].author);

    while (i <= j) {
        while (compareBooksByAuthor(a[i].author, x) <= 0) i++;
        while (compareBooksByAuthor(a[j].author, x) >= 0) j--;
        if (i <= j) {
            Book temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(a, l, j);
    quickSort(a, i, r);
}

int main() {
    int c;
    FILE* file;
    Book book;
    while (true) {
        cout << "Create-1, View-2, Add-3, Task-4, Exit-5\n";
        cin >> c;
        cin.ignore();

        switch (c) {
        case 1:
            file = fopen("zapisi.dat", "wb");

            if (!file) {
                cout << "Error creating file" << endl;
                return 1;
            }
            #ifdef _WIN32
                system("CLS");
            #else
                system("clear");
            #endif
            fclose(file);
            break;
        case 2:
            file = fopen("zapisi.dat", "rb");

            if (!file) {
                cout << "Error opening file" << endl;
                return 1;
            }

            fseek(file, 0, SEEK_END);
            if (ftell(file) == 0) {
                cout << "File is empty.\n";
            }
            else {
                fseek(file, 0, SEEK_SET);
                int i = 0;
                while (fread(&book, sizeof(Book), 1, file) == 1) {
                    i++;
                    cout << i << ") Number: " << book.number
                        << ", Author: " << book.author
                        << ", Name: " << book.name
                        << ", Year: " << book.year
                        << ", Publisher: " << book.publisher
                        << ", Pages: " << book.num_pages << endl;
                }
            }

            cout << "Press any key to continue...\n";
            _getch();
            #ifdef _WIN32
                system("CLS");
            #else
                system("clear");
            #endif
            fclose(file);
            break;
        case 3:
            file = fopen("zapisi.dat", "ab");

            if (!file) {
                cout << "Error opening file" << endl;
                return 1;
            }
            try {
                cout << "Input book information\n";
                cout << "Number: ";
                if (!(std::cin >> book.number)) {
                    throw runtime_error(
                        "Invalid input. An integer number is required.");
                }
                cin.ignore();

                cout << "Author: ";
                cin.getline(book.author, sizeof(book.author));

                cout << "Name: ";
                cin.getline(book.name, sizeof(book.name));

                cout << "Year: ";
                if (!(std::cin >> book.year)) {
                    throw runtime_error(
                        "Invalid input. An integer number is required.");
                }
                cin.ignore();

                cout << "Publisher: ";
                cin.getline(book.publisher, sizeof(book.publisher));

                cout << "Pages: ";
                if (!(std::cin >> book.num_pages)) {
                    throw runtime_error(
                        "Invalid input. An integer number is required.");
                }
                cin.ignore();

                fwrite(&book, sizeof(Book), 1, file);
                cout << "Press any key to continue...\n";
                _getch();
                #ifdef _WIN32
                    system("CLS");
                #else
                    system("clear");
                #endif
                fclose(file);
                break;
            }
            catch (exception e) {
                exit(2);
            }
        case 4: {
            int year, k = 0;
            Book books[1000];
            file = fopen("zapisi.dat", "rb");

            if (!file) {
                cout << "Error opening file" << endl;
                return 1;
            }
            cout << "Input a year: ";
            cin >> year;
            while (fread(&book, sizeof(Book), 1, file) == 1) {
                if (book.year > year) {
                    books[k] = book;
                    k++;
                }
            }
            quickSort(books, 0, k - 1);
            for (int j = 0; j < k; j++)
                cout << j + 1 << ") Number: " << books[j].number
                << ", Author: " << books[j].author
                << ", Name: " << books[j].name
                << ", Year: " << books[j].year
                << ", Publisher: " << books[j].publisher
                << ", Pages: " << books[j].num_pages << endl;
            cout << "Press any key to continue...\n";
            _getch();
            #ifdef _WIN32
                system("CLS");
            #else
                system("clear");
            #endif
            fclose(file);
            break;
        }
        case 5:
            exit(0);
        }
    }
    return 0;
}
