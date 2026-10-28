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
    // Square mapping: a1 = bit 0, h1 = bit 7, a8 = bit 56, h8 = bit 63.
    // Entries follow BIT_BOARD order; player colour only affects the view.
    std::array<uint64_t, 12> bitBoard{
        0x000000000000FF00ULL, // White pawns: a2-h2
        0x0000000000000024ULL, // White bishops: c1, f1
        0x0000000000000042ULL, // White knights: b1, g1
        0x0000000000000081ULL, // White rooks: a1, h1
        0x0000000000000008ULL, // White queen: d1
        0x0000000000000010ULL, // White king: e1

        0x00FF000000000000ULL, // Black pawns: a7-h7
        0x2400000000000000ULL, // Black bishops: c8, f8
        0x4200000000000000ULL, // Black knights: b8, g8
        0x8100000000000000ULL, // Black rooks: a8, h8
        0x0800000000000000ULL, // Black queen: d8
        0x1000000000000000ULL, // Black king: e8
    };
    const PLAYER_COLOUR playerColour{};

  public:
    // Init
    GameLoop(const PLAYER_COLOUR playerColour, const int length);

    // Functions to manipulate the board
    void run();
};

#endif
