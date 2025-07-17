#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Bar dimensions
const int BAR_WIDTH = 20; 
const int BAR_SPACING = 5; 

// Global variables related to SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Initialize SDL
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("Visualize Bubble Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Failed to create the window! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Failed to create the renderer! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Setting background color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return 1;
}

// Clean up SDL resources when done
void close_sdl() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    SDL_Quit();
}

// Function to draw the array as a bar chart
// highlight_idx1, highlight_idx2: index of elements to highlight (-1: no highlight)
void draw_array(int arr[], int size, int highlight_idx1, int highlight_idx2) {
    // Clearing screen by filling in background color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // White
    SDL_RenderClear(gRenderer);

    // Find the maximum value to normalize bar heights
    int max_val = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    if (max_val == 0) max_val = 1; // Prevent division by zero

    for (int i = 0; i < size; i++) {
        // Bar height is proportional to the array value
        int bar_height = (int)(((double)arr[i] / max_val) * (SCREEN_HEIGHT - 50)); // Leave some margin at the bottom

        // Define bar position and size
        SDL_Rect fillRect = {
            i * (BAR_WIDTH + BAR_SPACING) + 20, // x-coordinate (offset from left)
            SCREEN_HEIGHT - bar_height,         // y-coordinate (draw from bottom up)
            BAR_WIDTH,                          // Width
            bar_height                          // Height
        };

        // Set bar color
        if (i == highlight_idx1 || i == highlight_idx2) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // Highlight in red
        } else {
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); // Default to blue
        }

        // Draw the bar
        SDL_RenderFillRect(gRenderer, &fillRect);
    }

    // Present the rendered content to the screen
    SDL_RenderPresent(gRenderer);
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Visualize Bubble Sort
void bubble_sort_visualize(int arr[], int n) {
    SDL_Event e;
    int quit = 0;

    // Draw initial state
    draw_array(arr, n, -1, -1);
    SDL_Delay(1000); // Wait 1 second for initial display

    for (int i = 0; i < n - 1 && !quit; i++) {
        for (int j = 0; j < n - i - 1 && !quit; j++) {
            // Event handling (quit if window is closed)
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = 1;
                }
            }
            if (quit) break;

            // Highlight elements being compared
            draw_array(arr, n, j, j + 1);
            SDL_Delay(20); // Display comparison state briefly

            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                // Highlight elements after swap
                draw_array(arr, n, j, j + 1);
                SDL_Delay(10); // Display swapped state briefly
            }
            // Redraw with no highlights (for next comparison)
            draw_array(arr, n, -1, -1);
            // SDL_Delay(5); // Short delay for next step
        }
    }
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (!init_sdl()) {
        printf("Failed to initialize SDL. Exiting program.\n");
        return 1;
    }

    // Prepare array for sorting (random values)
    srand(time(NULL));
    int array_size = 30; // Number of bars
    int *data = (int *)malloc(array_size * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        close_sdl();
        return 1;
    }
    for (int i = 0; i < array_size; i++) {
        data[i] = rand() % (SCREEN_HEIGHT - 100) + 50; // Adjust bar height to fit within screen
    }

    // Execute Bubble Sort visualization
    bubble_sort_visualize(data, array_size);

    // Free memory
    free(data);
    data = NULL;

    // Clean up SDL
    close_sdl();

    return 0;
}
