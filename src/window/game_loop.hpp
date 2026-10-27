#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop {
  private:
    const int length;

  public:
    // Init
    GameLoop(const int length);

    // Functions to manipulate the board
    void run();
};

#endif
