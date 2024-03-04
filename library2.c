#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 50

// Structure to represent a book
struct Book {
    char title[100];
    char author[50];
    int ISBN;
    int isAvailable;  // 0 for not available, 1 for available
};

// Function to add a new book to the library
void addBook(struct Book books[], int *numBooks) {
    if (*numBooks < MAX_BOOKS) {
        printf("Enter book title: ");
        scanf(" %[^\n]", books[*numBooks].title);

        printf("Enter author name: ");
        scanf(" %[^\n]", books[*numBooks].author);

        printf("Enter ISBN: ");
        scanf("%d", &books[*numBooks].ISBN);

        books[*numBooks].isAvailable = 1;  // Initialize as available
        (*numBooks)++;
        printf("Book added to the library successfully!\n");
    } else {
        printf("Cannot add more books. Limit reached.\n");
    }
}

// Function to search for a book by title
void searchBook(struct Book books[], int numBooks) {
    char searchTitle[100];
    printf("Enter the title of the book to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].title, searchTitle) == 0) {
            printf("\nBook found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("ISBN: %d\n", books[i].ISBN);
            printf("Availability: %s\n", (books[i].isAvailable ? "Available" : "Not Available"));
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found in the library.\n");
    }
}

// Function to lend a book to a user
void lendBook(struct Book books[], int numBooks) {
    int ISBN;
    printf("Enter the ISBN of the book to lend: ");
    scanf("%d", &ISBN);

    int index = -1;

    for (int i = 0; i < numBooks; i++) {
        if (books[i].ISBN == ISBN) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (books[index].isAvailable) {
            books[index].isAvailable = 0;  // Mark as not available
            printf("Book lent successfully!\n");
        } else {
            printf("Book is not available for lending.\n");
        }
    } else {
        printf("Book not found in the library.\n");
    }
}

// Function to return a book
void returnBook(struct Book books[], int numBooks) {
    int ISBN;
    printf("Enter the ISBN of the book to return: ");
    scanf("%d", &ISBN);

    int index = -1;

    for (int i = 0; i < numBooks; i++) {
        if (books[i].ISBN == ISBN) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (!books[index].isAvailable) {
            books[index].isAvailable = 1;  // Mark as available
            printf("Book returned successfully!\n");
        } else {
            printf("This book is already available in the library.\n");
        }
    } else {
        printf("Book not found in the library.\n");
    }
}

// Function to display all books in the library
void displayBooks(struct Book books[], int numBooks) {
    printf("\nLibrary Book Inventory:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("ISBN: %d\n", books[i].ISBN);
        printf("Availability: %s\n\n", (books[i].isAvailable ? "Available" : "Not Available"));
    }
}

int main() {
    struct Book books[MAX_BOOKS];
    int numBooks = 0;
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add a book\n");
        printf("2. Search for a book\n");
        printf("3. Lend a book\n");
        printf("4. Return a book\n");
        printf("5. Display all books\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                searchBook(books, numBooks);
                break;
            case 3:
                lendBook(books, numBooks);
                break;
            case 4:
                returnBook(books, numBooks);
                break;
            case 5:
                displayBooks(books, numBooks);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
