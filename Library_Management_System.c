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

// Function to delete a book by ID
void deleteBook(struct Book library[], int *numBooks, int deleteID) {
    int found = 0;
    for (int i = 0; i < *numBooks; i++) {
        if (library[i].id == deleteID) {
            found = 1;
            // Shift remaining elements to fill the gap
            for (int j = i; j < *numBooks - 1; j++) {
                library[j] = library[j + 1];
            }
            (*numBooks)--;
            printf("Book deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", deleteID);
    }
}

// Function to update book details by ID
void updateBook(struct Book library[], int numBooks, int updateID) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == updateID) {
            found = 1;
            printf("Enter new title: ");
            scanf("%s", library[i].title);
            
            printf("Enter new author name: ");
            scanf("%s", library[i].author);
            
            printf("Book details updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", updateID);
    }
}

// Function to save library data to a file
void saveLibraryToFile(struct Book library[], int numBooks, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%d %s %s\n", library[i].id, library[i].title, library[i].author);
    }

    fclose(file);
    printf("Library data saved to %s.\n", filename);
}

int main() {
    struct Book library[MAX_BOOKS];
    int numBooks = 0;
    int choice;
    
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Delete a book\n");
        printf("5. Update book details\n");
        printf("6. Save library data to a file\n");
        printf("7. Quit\n");
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
                int deleteID;
                printf("Enter the ID of the book to delete: ");
                scanf("%d", &deleteID);
                deleteBook(library, &numBooks, deleteID);
                break;
            case 5:
                int updateID;
                printf("Enter the ID of the book to update: ");
                scanf("%d", &updateID);
                updateBook(library, numBooks, updateID);
                break;
            case 6:
                saveLibraryToFile(library, numBooks, "library_data.txt");
                break;
            case 7:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
