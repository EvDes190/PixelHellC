#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "pattern.h"
#include "state.h"

#define HP_MAX 1000

// TODO: need to code function that spawns patterns according to certain rules
struct pattern choose_pattern(f_state* state) {
    struct pattern p;
    return p;
}

void update_field_top(f_state* state) {
    for (int x = 0; x < FIELD_RANGE; x++) {
        for (int y = 0; y < FIELD_RANGE; y++) {
            state->colors[y][x] = 0;
            int highest = 0;
            for (int i = 0; i < PATTERN_MAX; i++) {
                if (state->fields[i] == NULL) continue;

                // get color of highest pattern
                if (highest < state->fields[i]->pattern.height && (state->fields[i]->field[y][x] & 0x00ffffff) != 0)
                    state->colors[y][x] = state->fields[i]->field[y][x] & 0x00ffffff;

            }
        }
    }

    if (state->time != 0) {
        state->colors[state->player.y][state->player.x] = 0x0000ff00;
    }
}

void reset_state(f_state* state) {
    for (int i = 0; i < PATTERN_MAX; i++) {
        // free(state->fields[i]);
        state->fields[i] = NULL;
    }
    state->time = 0;
    state->fields_top = -1;
    update_field_top(state);

    state->game = 0;
    state->player.HP = HP_MAX;
    state->player.x = FIELD_RANGE / 2;
    state->player.y = FIELD_RANGE / 2;
}


void update_field(field_t* p_field) {
    if (p_field == NULL) return;

    p_field->pattern.pattern_function(p_field->field, ++p_field->frame);
    if (p_field->frame < p_field->pattern.max_frame) {
        free(p_field);
        p_field = NULL;
    }
}

void update_player(struct player* player, int move_x, int move_y) {
    //update player position
    player->x += move_x;
    player->y += move_y;

    if (player->x < 0) player->x = 0;
    else if (player->x >= FIELD_RANGE) player->x = FIELD_RANGE - 1;
    if (player->y < 0) player->y = 0;
    else if (player->y >= FIELD_RANGE) player->y = FIELD_RANGE - 1;
}

int update_state(f_state* state, int move_x, int move_y) {
    update_player(&state->player, move_x, move_y);
    // printf("%0.2lf", (double)state->time / CLOCKS_PER_SEC);

    for (int i = 0; i <= state->fields_top; i++) {
        // updating objects by patterns
        update_field(state->fields[i]);
        if (state->fields[i] == NULL) continue;

        // damage for collision
        // get damage in XX000000 part of number
        state->player.HP -= state->fields[i]->field[state->player.y][state->player.x] >> 24;
    }

    // update colors for rendering
    update_field_top(state);

    return state->player.HP <= 0 ? 1 : 0;
}
