#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 10
#define QUESTION_LENGTH 200
#define OPTION_LENGTH 50

// Structure to represent a quiz question
struct QuizQuestion {
    char question[QUESTION_LENGTH];
    char optionA[OPTION_LENGTH];
    char optionB[OPTION_LENGTH];
    char optionC[OPTION_LENGTH];
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

// Function to display user feedback based on correctness
void displayFeedback(int isCorrect) {
    if (isCorrect) {
        printf("Correct!\n");
    } else {
        printf("Incorrect. The correct answer is %c.\n", isCorrect);
    }
}

// Function to display the final quiz results
void displayResults(int score, int totalQuestions) {
    printf("\nQuiz completed! Your final score: %d out of %d\n", score, totalQuestions);
}

int main() {
    struct QuizQuestion quiz[MAX_QUESTIONS];

    // Set up quiz questions
    strcpy(quiz[0].question, "What is the capital of France?");
    strcpy(quiz[0].optionA, "Berlin");
    strcpy(quiz[0].optionB, "Madrid");
    strcpy(quiz[0].optionC, "Paris");
    quiz[0].correctOption = 'C';

    // Add more questions similarly...

    // Assuming we have 5 questions for now
    int totalQuestions = 5;
    int score = 0;
    char userAnswer;

    // Seed the random number generator for a timer
    srand(time(NULL));

    // Iterate through each question in the quiz
    for (int i = 0; i < totalQuestions; i++) {
        printf("\nQuestion %d:", i + 1);

        // Display a random question from the remaining ones
        int randomIndex = rand() % totalQuestions;
        userAnswer = askQuestion(quiz[randomIndex]);

        // Check the answer and update the score
        score += checkAnswer(quiz[randomIndex], userAnswer);

        // Display user feedback and remove the used question
        displayFeedback(checkAnswer(quiz[randomIndex], userAnswer));
        for (int j = randomIndex; j < totalQuestions - 1; j++) {
            quiz[j] = quiz[j + 1];
        }
        totalQuestions--;
    }

    // Display the final results
    displayResults(score, totalQuestions + score);

    return 0;
}
