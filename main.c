#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <conio.h>
#include <stdio.h>

#import "src/state.c"
#import "render/window.c"

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
    f_state* game_state = malloc(sizeof(*game_state));
    reset_state(game_state);
    renderstate_t* renderstate = malloc(sizeof(*renderstate));
    renderstate->height = 100, renderstate->width = 100;
    renderstate->hwnd = GetForegroundWindow();
    renderstate->hdc = GetDC(renderstate->hwnd);

    pthread_t* thread = malloc(sizeof(*thread));
    struct render_args r_args = {
        .state = renderstate,
        .field_range = FIELD_RANGE,
        //TODO: fix warning
        .colors = game_state->colors};
    pthread_create(thread, NULL, render, &r_args);


    //TODO code system of restarting game
    while (1) {

    }

    free(game_state);
    free(renderstate);
    free(thread);
}