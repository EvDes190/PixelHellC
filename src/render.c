#include <windows.h>
#include <unistd.h>

#include "../include/render.h"


void* render(void *args) {
    render_args* r_args = args;


    for (int x = 0; x < r_args->field_range; x++) {
        for (int y = 0; y < r_args->field_range; y++) {
            HPEN hPen = CreatePen(PS_SOLID, 2, r_args->colors[x][y]);
            HBRUSH hBrush = CreateSolidBrush(r_args->colors[x][y]);

            SelectObject(r_args->state->hdc, hPen);
            SelectObject(r_args->state->hdc, hBrush);

            Rectangle(r_args->state->hdc, r_args->state->width * x, r_args->state->height * y, 30, 30);
        }
    }

    return 0;
}