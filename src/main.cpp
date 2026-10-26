#include <raylib.h>

int main() {
    // Init the window
    InitWindow(800, 600, "AlphaRook");

    // Main Game Loop
    while (!WindowShouldClose()) {
        // Begin Drawing
        BeginDrawing();

        // Set background Colour
        ClearBackground(RAYWHITE);

        DrawText("Hello World!", 350, 280, 20, BLACK);

        // End Drawing
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
