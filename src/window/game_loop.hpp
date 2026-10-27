#ifndef GAMELOOP_H
#define GAMELOOP_H

enum class PLAYER_COLOUR {
    White,
    Black
};

class GameLoop {
  private:
    const int length;
    const PLAYER_COLOUR playerColour;

  public:
    // Init
    GameLoop(const PLAYER_COLOUR playerColour, const int length);

    // Functions to manipulate the board
    void run();
};

#endif
