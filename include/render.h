//
// Created by EvDes on 15.03.2026.
//

#ifndef PIXELHELLC_WINDOWS_H
#define PIXELHELLC_WINDOWS_H

#include <time.h>

#include "state.h"
#include "pattern.h"

#define WINDOW_WIDTH 930
#define WINDOW_HEIGHT 930

#define FPS 60
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC / FPS)


typedef struct {
    clock_t *time;
    unsigned int (*colors)[FIELD_RANGE];
} render_state;

void* init_render(void* args);
void render(f_state*);

#endif //PIXELHELLC_WINDOWS_H