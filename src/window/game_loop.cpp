#include "game_loop.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
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
        assert(IsTextureValid(imageTexture));

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

        // (0, 0) is at the top-left corner
        for (int y_coord = 0; y_coord < length; y_coord += SQUARE_LENGTH) {
            int row_idx = y_coord / SQUARE_LENGTH;

            for (int x_coord = 0; x_coord < length; x_coord += SQUARE_LENGTH) {
                int col_idx = x_coord / SQUARE_LENGTH;

                if (row_idx % 2 == 0 && col_idx % 2 != 0 ||
                    row_idx % 2 != 0 && col_idx % 2 == 0) {
                    DrawRectangle(x_coord, y_coord, SQUARE_LENGTH,
                                  SQUARE_LENGTH, RED);
                }

                int piece_idx = GameLoop::get_asset_idx(col_idx, row_idx);

                if (piece_idx != -1) {
                    float scale = (SQUARE_LENGTH / 256.0f) * std::sqrt(0.5f);
                    float piece_x_coord =
                        x_coord +
                        (SQUARE_LENGTH - TEXTURES[piece_idx].width * scale) /
                            2.0f;

                    float piece_y_coord =
                        y_coord +
                        (SQUARE_LENGTH - TEXTURES[piece_idx].height * scale) /
                            2.0f;

                    const Vector2 asset_position =
                        Vector2{piece_x_coord, piece_y_coord};

                    DrawTextureEx(TEXTURES[piece_idx], asset_position, 0.0f,
                                  scale, WHITE);
                }
            }
        }

        // End Drawing
        EndDrawing();
    }

    // Unload each texture
    for (Texture texture : TEXTURES) {
        UnloadTexture(texture);
    }

    CloseWindow();
}

int GameLoop::get_asset_idx(int x_idx, int y_idx) {
    uint64_t mask = 1;
    mask = mask << (x_idx + y_idx * 8);

    assert(bitBoard.size() == 12);

    for (int piece_idx = 0; piece_idx < 12; piece_idx++) {
        const uint64_t piece_bit = bitBoard[piece_idx];

        if (piece_bit & mask) {
            return piece_idx;
        }
    }

    return -1;
}
