#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 5
#define MAX_OPTIONS 4

// Structure to represent a question
struct Question {
    char text[200];
    char options[MAX_OPTIONS][50];
    int correctOption;
};

// Function to add a new question to the quiz
void addQuestion(struct Question questions[], int *numQuestions) {
    if (*numQuestions < MAX_QUESTIONS) {
        printf("Enter the question: ");
        scanf(" %[^\n]", questions[*numQuestions].text);

        printf("Enter the options (A B C D):\n");
        for (int i = 0; i < MAX_OPTIONS; i++) {
            printf("%c. ", 'A' + i);
            scanf(" %[^\n]", questions[*numQuestions].options[i]);
        }

        printf("Enter the correct option (A B C D): ");
        char correctOption;
        scanf(" %c", &correctOption);

        questions[*numQuestions].correctOption = correctOption - 'A';
        (*numQuestions)++;
        printf("Question added to the quiz successfully!\n");
    } else {
        printf("Cannot add more questions. Limit reached.\n");
    }
}

// Function to take the quiz and calculate the score
void takeQuiz(struct Question questions[], int numQuestions) {
    int score = 0;

    for (int i = 0; i < numQuestions; i++) {
        printf("\n%s\n", questions[i].text);

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%c. %s\n", 'A' + j, questions[i].options[j]);
        }

        char userAnswer;
        printf("Your answer (A B C D): ");
        scanf(" %c", &userAnswer);

        if (userAnswer - 'A' == questions[i].correctOption) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %c. %s\n", 'A' + questions[i].correctOption,
                   questions[i].options[questions[i].correctOption]);
        }
    }

    printf("\nQuiz completed. Your score: %d out of %d\n", score, numQuestions);
}

int main() {
    struct Question questions[MAX_QUESTIONS];
    int numQuestions = 0;
    int choice;

    do {
        printf("\nQuiz Game\n");
        printf("1. Add a question to the quiz\n");
        printf("2. Take the quiz\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addQuestion(questions, &numQuestions);
                break;
            case 2:
                if (numQuestions == 0) {
                    printf("Cannot take the quiz. No questions available.\n");
                } else {
                    takeQuiz(questions, numQuestions);
                }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
