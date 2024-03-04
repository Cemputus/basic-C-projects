
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    int id;
};

// Function to add a book to the library
void addBook(struct Book library[], int *numBooks) {
    if (*numBooks < MAX_BOOKS) {
        printf("Enter book title: ");
        scanf("%s", library[*numBooks].title);
        
        printf("Enter author name: ");
        scanf("%s", library[*numBooks].author);
        
        library[*numBooks].id = *numBooks + 1;  // Assign a unique ID
        
        (*numBooks)++;
        printf("Book added successfully!\n");
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}

// Function to display all books in the library
void displayBooks(struct Book library[], int numBooks) {
    printf("\nLibrary Catalog:\n");
    printf("ID\tTitle\t\tAuthor\n");
    for (int i = 0; i < numBooks; i++) {
        printf("%d\t%s\t%s\n", library[i].id, library[i].title, library[i].author);
    }
    printf("\n");
}

// Function to search for a book by title
void searchBook(struct Book library[], int numBooks, char searchTitle[]) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].title, searchTitle) == 0) {
            printf("Book found!\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\n", library[i].id, library[i].title, library[i].author);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

int main() {
    struct Book library[MAX_BOOKS];
    int numBooks = 0;
    int choice;
    
    do {
        printf("Library Management System\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook(library, &numBooks);
                break;
            case 2:
                displayBooks(library, numBooks);
                break;
            case 3:
                char searchTitle[100];
                printf("Enter the title to search: ");
                scanf("%s", searchTitle);
                searchBook(library, numBooks, searchTitle);
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
