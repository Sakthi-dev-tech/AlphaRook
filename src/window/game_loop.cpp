#include "game_loop.hpp"

#include <raylib.h>

GameLoop::GameLoop(PLAYER_COLOUR playerColour, const int length)
    : length(length),
      playerColour(playerColour) {}

void GameLoop::run() {
    InitWindow(length, length, "AlphaRook");

    const int SQUARE_LENGTH = length / 8;

    // Main Game Loop
    while (!WindowShouldClose()) {
        // Begin Drawing
        BeginDrawing();

        // Options for RayLib Window
        SetTargetFPS(60);
        SetTraceLogLevel(LOG_WARNING);

        // Set background Colour
        ClearBackground(RAYWHITE);

        for (int row = 0; row < length; row += SQUARE_LENGTH) {
            for (int col = 0; col < length; col += SQUARE_LENGTH) {
                int row_idx = row / SQUARE_LENGTH;
                int col_idx = col / SQUARE_LENGTH;

                if (row_idx % 2 == 0 && col_idx % 2 != 0 || row_idx % 2 != 0 && col_idx % 2 == 0) {
                    DrawRectangle(row, col, SQUARE_LENGTH, SQUARE_LENGTH, RED);
                }
            }
        }

        // End Drawing
        EndDrawing();
    }

    CloseWindow();
}
