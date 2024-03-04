#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a quiz question
struct QuizQuestion {
    char question[200];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char correctOption;
};

// Function to display a quiz question and get user's answer
char askQuestion(struct QuizQuestion question) {
    char userAnswer;
    
    printf("\n%s\n", question.question);
    printf("A. %s\n", question.optionA);
    printf("B. %s\n", question.optionB);
    printf("C. %s\n", question.optionC);
    
    printf("Your answer (A/B/C): ");
    scanf(" %c", &userAnswer);  // Use a space before %c to consume the newline character
    
    return userAnswer;
}

// Function to check if the user's answer is correct
int checkAnswer(struct QuizQuestion question, char userAnswer) {
    return (userAnswer == question.correctOption);
}

int main() {
    struct QuizQuestion quiz[5];  // Assume there are 5 quiz questions

    // Set up quiz questions
    strcpy(quiz[0].question, "What is the capital of France?");
    strcpy(quiz[0].optionA, "Berlin");
    strcpy(quiz[0].optionB, "Madrid");
    strcpy(quiz[0].optionC, "Paris");
    quiz[0].correctOption = 'C';

    // Add more questions similarly...

    int score = 0;

    // Iterate through each question in the quiz
    for (int i = 0; i < 5; i++) {
        char userAnswer = askQuestion(quiz[i]);

        if (checkAnswer(quiz[i], userAnswer)) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %c.\n", quiz[i].correctOption);
        }
    }

    printf("\nQuiz completed! Your final score: %d out of 5\n", score);

    return 0;
}
