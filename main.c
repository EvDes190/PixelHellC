#include <time.h>
#include <stdio.h>

#include "raylib.h"

#include "render.h"
#include "state.h"


void init_game(f_state* game_state) {
    clock_t start = clock();
    int move_x = 0, move_y = 0;


    // break if player is died
    while (update_state(game_state, move_x, move_y) != 1) {
        char s[100];
        sprintf(s, "HP: %d; Time: %0.3lf seconds", game_state->player.HP, (double) game_state->time / CLOCKS_PER_SEC);
        SetWindowTitle(s);

        render(game_state);

        move_x = 0, move_y = 0;
        clock_t begin = clock();
        clock_t until = 0;
        while (until < CLOCKS_PER_FRAME) {
            until = clock() - begin;

            if (IsKeyPressed('S') || IsKeyPressed(KEY_DOWN)) move_y = 1;
            if (IsKeyPressed('W') || IsKeyPressed(KEY_UP)) move_y = -1;
            if (IsKeyPressed('A') || IsKeyPressed(KEY_LEFT)) move_x = -1;
            if (IsKeyPressed('D') || IsKeyPressed(KEY_RIGHT)) move_x = 1;
        }

        // count game-time
        game_state->time = clock() - start;
    }

}

int main() {
    f_state game_state;
    reset_state(&game_state);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PixelHellC");
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        init_game(&game_state);

        char final[100];
        sprintf(final, "Your time - %0.3lf.\nPress \"r\" to restart.\n", (double) game_state.time / CLOCKS_PER_FRAME);
        SetWindowTitle(final);
        while (!IsKeyPressed('R'));
    }
    CloseWindow();
}
