#include "game_loop.hpp"

#include <cassert>
#include <raylib.h>
#include <vector>

GameLoop::GameLoop(PLAYER_COLOUR playerColour, const int length)
    : length(length), playerColour(playerColour) {}

void GameLoop::run() {
    InitWindow(length, length, "AlphaRook");

    const int SQUARE_LENGTH = length / 8;

    const Image IMAGES[12] = {
        LoadImage("assets/chess/white_pawn.png"),
        LoadImage("assets/chess/white_bishop.png"),
        LoadImage("assets/chess/white_knight.png"),
        LoadImage("assets/chess/white_rook.png"),
        LoadImage("assets/chess/white_queen.png"),
        LoadImage("assets/chess/white_king.png"),

        LoadImage("assets/chess/black_pawn.png"),
        LoadImage("assets/chess/black_bishop.png"),
        LoadImage("assets/chess/black_knight.png"),
        LoadImage("assets/chess/black_rook.png"),
        LoadImage("assets/chess/black_queen.png"),
        LoadImage("assets/chess/black_king.png"),
    };

    // Load the textures of each image
    std::vector<Texture2D> TEXTURES = {};

    for (Image image : IMAGES) {
        const Texture2D imageTexture = LoadTextureFromImage(image);
        TEXTURES.push_back(imageTexture);

        UnloadImage(image);
    }
    assert(TEXTURES.size() == 12);

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

                if (row_idx % 2 == 0 && col_idx % 2 != 0 ||
                    row_idx % 2 != 0 && col_idx % 2 == 0) {
                    DrawRectangle(row, col, SQUARE_LENGTH, SQUARE_LENGTH, RED);
                }
            }
        }

        // End Drawing
        EndDrawing();
    }

    CloseWindow();
}
