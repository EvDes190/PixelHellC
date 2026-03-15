#include <windows.h>
#include <unistd.h>

typedef struct RenderState {
    HWND hwnd;
    HDC hdc;


    int width;
    int height;
} renderstate_t;

struct render_args {
    renderstate_t* state;
    int field_range;
    unsigned int** colors;
};

// void render(renderstate_t* state, int field_range, int colors[field_range][field_range]) {
void* render(void *args) {
    struct render_args* r_args = args;


    for (int x = 0; x < r_args->field_range; x++) {
        for (int y = 0; y < r_args->field_range; y++) {
            HPEN hPen = CreatePen(PS_SOLID, 2, r_args->colors[x][y]);
            HBRUSH hBrush = CreateSolidBrush(r_args->colors[x][y]);

            SelectObject(r_args->state->hdc, hPen);
            SelectObject(r_args->state->hdc, hBrush);

            Rectangle(r_args->state->hdc, r_args->state->width, r_args->state->height, 30, 30);
        }
    }

    return 0;
}