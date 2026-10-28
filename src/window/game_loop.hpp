#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <array>
#include <cstdint>

enum class PLAYER_COLOUR { White, Black };

enum class BIT_BOARD_IDX {
    // White pieces indexes
    WHITE_PAWN = 0,
    WHITE_BISHOP = 1,
    WHITE_KNIGHT = 2,
    WHITE_ROOK = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,

    // Black pieces indexes
    BLACK_PAWN = 6,
    BLACK_BISHOP = 7,
    BLACK_KNIGHT = 8,
    BLACK_ROOK = 9,
    BLACK_QUEEN = 10,
    BLACK_KING = 11,
};

class GameLoop {
  private:
    const int length{};
    // Square mapping: a8 = bit 0, h8 = bit 7, a1 = bit 56, h1 = bit 63.
    // Entries follow BIT_BOARD_IDX order; rows follow White's screen view.
    // E.g. left 2 hexadecimal bits represent the last row at the bottom
    std::array<uint64_t, 12> bitBoard{
        0x00FF000000000000ULL, // White pawns: a2-h2
        0x2400000000000000ULL, // White bishops: c1, f1
        0x4200000000000000ULL, // White knights: b1, g1
        0x8100000000000000ULL, // White rooks: a1, h1
        0x0800000000000000ULL, // White queen: d1
        0x1000000000000000ULL, // White king: e1

        0x000000000000FF00ULL, // Black pawns: a7-h7
        0x0000000000000024ULL, // Black bishops: c8, f8
        0x0000000000000042ULL, // Black knights: b8, g8
        0x0000000000000081ULL, // Black rooks: a8, h8
        0x0000000000000008ULL, // Black queen: d8
        0x0000000000000010ULL, // Black king: e8
    };
    const PLAYER_COLOUR playerColour{};

  public:
    // Init
    GameLoop(const PLAYER_COLOUR playerColour, const int length);

    // Functions to manipulate the board
    void run();

    // Get the asset index at a certain coordinate
    // @returns -1 if empty 0-12 if there is a piece
    int get_asset_idx(int x_idx, int y_idx);
};

#endif
