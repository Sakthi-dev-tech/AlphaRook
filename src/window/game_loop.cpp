#include "game_loop.hpp"

#include <array>
#include <cassert>
#include <raylib.h>
#include <vector>

GameLoop::GameLoop(PLAYER_COLOUR playerColour, const int length)
    : length(length), playerColour(playerColour) {}

void GameLoop::run() {
    InitWindow(length, length, "AlphaRook");

    const int SQUARE_LENGTH = length / 8;

    // DO NOT USE THIS!
    // THIS IS JUST USED TO CREATE TEXTURES REQUIRED
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
        assert(IsImageValid(image));

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

        for (int y_coord = 0; y_coord < length; y_coord += SQUARE_LENGTH) {
            for (int x_coord = 0; x_coord < length; x_coord += SQUARE_LENGTH) {
                int row_idx = y_coord / SQUARE_LENGTH;
                int col_idx = x_coord / SQUARE_LENGTH;

                if (row_idx % 2 == 0 && col_idx % 2 != 0 ||
                    row_idx % 2 != 0 && col_idx % 2 == 0) {
                    DrawRectangle(x_coord, y_coord, SQUARE_LENGTH, SQUARE_LENGTH, RED);
                }

                // TEST RENDERING
                if (row_idx == 6) {
                    const Vector2 curr_pos = Vector2{(float)x_coord, (float)y_coord};
                    DrawTextureEx(TEXTURES[0], curr_pos, 0.0f, 0.4f, WHITE);
                }
            }
        }

        // End Drawing
        EndDrawing();
    }

    CloseWindow();
}
