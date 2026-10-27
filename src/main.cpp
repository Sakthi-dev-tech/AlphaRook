#include "window/game_loop.hpp"

int main() {
    GameLoop game_window = GameLoop(800, 600, "AlphaRook");
    game_window.run();

    return 0;
}
