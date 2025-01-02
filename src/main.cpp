#include "main.h"

int main() {
    InitWindow(800, 450, "CodingWithJamal Raylib Template");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("This is a window!", 190, 200, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}