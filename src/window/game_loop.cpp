#include "game_loop.hpp"

#include <raylib.h>

GameLoop::GameLoop(const int width, const int height, const char *title)
    : width(width), height(height), title(title) {}

void GameLoop::run() {
    InitWindow(width, height, title);

    // Main Game Loop
    while (!WindowShouldClose()) {
        // Begin Drawing
        BeginDrawing();

        // Set background Colour
        ClearBackground(RAYWHITE);

        DrawText("Hello World!", 350, 280, 20, BLACK);

        // End Drawing
        EndDrawing();
    }

    CloseWindow();
}
