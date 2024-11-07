#include "raylib.h"

#define MAX_COLUMNS 20
#define WIDTH 800
#define HEIGHT 600
#define MOVEMENT_SPEED 5

int main() {
    // Initialize our window
    InitWindow(WIDTH, HEIGHT, "Audio Visualizer");

    // Set our window to run at 60 frames-per-second
    SetTargetFPS(60);

    // Ball Info
    typedef struct Ball {
        double posX;
        double posY;
        Color color;
        int size;
    } Ball;

    Ball ball1 = {.color = BLUE, .posX = WIDTH / 2, .posY = HEIGHT / 2, .size = 20};

    /** SPLIT INTO 3 PARTS
     * 1. Event Handling
     * 2. Updating Positions of game objects
     * 3. Drawing Objects (draw all objects in new positions)
     * !WindowShouldClose() Checks if the X button or esc is pressed
     */
    while (!WindowShouldClose()) {
        // 1. Event Handling
        if (IsKeyDown(KEY_D)) {
            ball1.posX += MOVEMENT_SPEED;
        } if (IsKeyDown(KEY_A)) {
            ball1.posX -= MOVEMENT_SPEED;
        } if (IsKeyDown(KEY_W)) {
            ball1.posY -= MOVEMENT_SPEED;
        } if (IsKeyDown(KEY_S)) {
            ball1.posY += MOVEMENT_SPEED;
        }

        // 2. Updating Positions of game objects

        // 3. Drawing Objects
        BeginDrawing(); // creates blank canvas so we can draw game object on

        // To handle updating draw calls, we must clear the window each iteration
        // so it doesn't repeatedly leave old draw call
        ClearBackground(WHITE);

        DrawCircle(ball1.posX, ball1.posY, ball1.size, ball1.color);

        EndDrawing(); // End canvas drawing and swaps buffers
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}