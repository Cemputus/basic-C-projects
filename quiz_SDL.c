
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FONT_SIZE 24

// Structure to represent a quiz question
struct QuizQuestion {
    char question[200];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char correctOption;
};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

// Function to initialize SDL and TTF
int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Quiz Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    font = TTF_OpenFont("arial.ttf", FONT_SIZE);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

// Function to load and display a question
void displayQuestion(struct QuizQuestion question) {
    SDL_Surface *questionSurface = TTF_RenderText_Solid(font, question.question, (SDL_Color){255, 255, 255});
    SDL_Texture *questionTexture = SDL_CreateTextureFromSurface(renderer, questionSurface);

    SDL_Rect questionRect = {50, 50, SCREEN_WIDTH - 100, 50};
    SDL_RenderCopy(renderer, questionTexture, NULL, &questionRect);

    SDL_FreeSurface(questionSurface);
    SDL_DestroyTexture(questionTexture);
}

// Function to load and display options
void displayOptions(struct QuizQuestion question) {
    SDL_Surface *optionASurface = TTF_RenderText_Solid(font, question.optionA, (SDL_Color){255, 255, 255});
    SDL_Texture *optionATexture = SDL_CreateTextureFromSurface(renderer, optionASurface);

    // Similar code for optionB and optionC

    SDL_Rect optionARect = {50, 150, SCREEN_WIDTH - 100, 50};
    SDL_RenderCopy(renderer, optionATexture, NULL, &optionARect);

    // Similar code for optionB and optionC

    SDL_FreeSurface(optionASurface);
    SDL_DestroyTexture(optionATexture);

    // Add event handling for user input (selecting an option)
    // Compare the selected option with the correctOption from the struct
    // Display feedback (correct or incorrect)
}

int main() {
    if (!initSDL()) {
        printf("SDL initialization failed. Exiting.\n");
        return 1;
    }

    // Create a sample quiz question
    struct QuizQuestion sampleQuestion;
    strcpy(sampleQuestion.question, "What is the capital of France?");
    strcpy(sampleQuestion.optionA, "A) Paris");
    strcpy(sampleQuestion.optionB, "B) Madrid");
    strcpy(sampleQuestion.optionC, "C) Rome");
    sampleQuestion.correctOption = 'A';

    // Main game loop
    while (1) {
        // Clear renderer
        SDL_RenderClear(renderer);

        // Display question and options
        displayQuestion(sampleQuestion);
        displayOptions(sampleQuestion);

        // Update screen
        SDL_RenderPresent(renderer);

        // Handle events (e.g., user clicks, keyboard input)

        // Exit condition (e.g., when user quits the game)

        // Delay to control frame rate (optional)
        SDL_Delay(10);
    }

    // Clean up resources (e.g., destroy window, renderer, font)
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}