#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop {
  private:
    const int length;
    const char *title;

  public:
    // Init
    GameLoop(const int length, const char *title);

    // Functions to manipulate the board
    void run();
};

#endif
