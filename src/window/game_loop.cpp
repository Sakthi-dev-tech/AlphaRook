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

        const uint8_t bit_mask = 0b11111111;

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
            }

            assert(bitBoard.size() == 12);
            const uint8_t col_bit = 0b10000000;

            // For each piece
            for (int piece_idx = 0; piece_idx < 12; piece_idx++) {

                uint8_t curr_piece_bit =
                    (bitBoard[piece_idx] >> (8 * (7 - row_idx))) & 0xFFULL;

                for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
                    if (curr_piece_bit == 0) {
                        break;
                    }

                    if (curr_piece_bit & col_bit) {
                        const int x_coord = (bit_idx * SQUARE_LENGTH);

                        float scale =
                            (SQUARE_LENGTH / 256.0f) * std::sqrt(0.5f);
                        float texture_x_coord =
                            x_coord + (SQUARE_LENGTH -
                                       TEXTURES[piece_idx].width * scale) /
                                          2.0f;

                        float texture_y_coord =
                            y_coord + (SQUARE_LENGTH -
                                       TEXTURES[piece_idx].height * scale) /
                                          2.0f;

                        const Vector2 texture_position =
                            Vector2{texture_x_coord, texture_y_coord};
                        DrawTextureEx(TEXTURES[piece_idx], texture_position,
                                      0.0f, scale, WHITE);
                    }

                    curr_piece_bit = curr_piece_bit << 1;
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
