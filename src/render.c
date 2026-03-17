#include "raylib.h"

#include "render.h"
#include "state.h"


void render(f_state* state) {
    int tile_width = WINDOW_WIDTH / FIELD_RANGE;
    int tile_height = WINDOW_HEIGHT / FIELD_RANGE;


    BeginDrawing();
    for (int x = 0; x < FIELD_RANGE; x++) {
        for (int y = 0; y < FIELD_RANGE; y++) {
            Color clr = GetColor(state->colors[y][x] << 8);
            clr.a = 0xff;
            DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, clr);
        }
    }

    EndDrawing();

}