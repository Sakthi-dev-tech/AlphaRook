#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop {
  private:
    const int width;
    const int height;
    const char *title;

  public:
    GameLoop(const int width, const int height, const char *title);
    void run();
};

#endif
