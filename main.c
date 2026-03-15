#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/render.h"
#include "include/state.h"

#define FPS 60
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC / FPS)


void game_during(f_state* game_state) {
    clock_t start = clock();
    int move_x = 0, move_y = 0;
    int key = 0;

    while (update_state(game_state, move_x, move_y) != 1) {
        move_x = 0, move_y = 0;
        clock_t begin = clock();
        clock_t until = 0;
        while (until < CLOCKS_PER_FRAME) {
            until = clock() - begin;

            if (kbhit()) {
                key = getch();
                switch (key) {
                    case 'w':
                        move_y = 1;
                        continue;
                    case 's':
                        move_y = -1;
                        continue;
                    case 'd':
                        move_x = 1;
                        continue;
                    case 'a':
                        move_x = -1;
                    default: ;
                }
            }
        }
    }

    game_state->time += clock() - start;

}

int main() {
    // printf("%zu", sizeof(render_state_t));
    f_state* game_state = malloc(sizeof(f_state));
    reset_state(game_state);
    render_state_t* render_state = malloc(sizeof(render_state_t));
    render_state->height = 100, render_state->width = 100;
    render_state->hwnd = GetForegroundWindow();
    render_state->hdc = GetDC(render_state->hwnd);

    pthread_t* thread = malloc(sizeof(*thread));
    render_args r_args = {
        .state = render_state,
        .field_range = FIELD_RANGE,
        .time = &game_state->time,
        .colors = game_state->colors};
    pthread_create(thread, NULL, render, &r_args);


    //TODO code system of restarting game
    while (1) {
        game_during(game_state);

        printf("Your time - %0.3lf.\nPress \"r\" to restart.", (double) game_state->time / CLOCKS_PER_FRAME);
        if (kbhit()) {
            if (getch() != 'r') {
                break;
            }
        }
    }

    free(game_state);
    free(render_state);
    free(thread);
}