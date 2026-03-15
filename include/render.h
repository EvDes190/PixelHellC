//
// Created by EvDes on 15.03.2026.
//

#ifndef PIXELHELLC_WINDOWS_H
#define PIXELHELLC_WINDOWS_H

#include <windows.h>
#include <time.h>

#include "pattern.h"

typedef struct RenderState {
    HWND hwnd;
    HDC hdc;

    int width;
    int height;
} render_state_t;

typedef struct render_args {
    render_state_t* state;
    int field_range;
    clock_t *time;
    unsigned int (*colors)[FIELD_RANGE];
} render_args;


void* render(void *);

#endif //PIXELHELLC_WINDOWS_H