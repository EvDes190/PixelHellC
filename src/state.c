#include <stdlib.h>

#import "pattern.c"

#define HP_MAX 1000

struct player {
    unsigned int HP;
    int x;
    int y;
};

typedef struct field_state {
    //own field for every working pattern, maximum PATTERN_MAX
    struct field* fields[PATTERN_MAX];
    struct player player;
    int fields_top;
    //time elapsed after start game
    int time;
    //if 1 - game is on
    int game;
} f_state;

// TODO: need to code function that spawns patterns according to certain rules
struct pattern choose_pattern(f_state* state) {
    struct pattern p;
    return p;
}

void reset_state(f_state* state) {
    for (int i = 0; i < PATTERN_MAX; i++) {
        free(state->fields[i]);
        state->fields[i] = NULL;
    }
    state->fields_top = -1;
    state->time = 0;
    state->game = 0;
    state->player.HP = 0;
    state->player.x = FIELD_RANGE / 2;
    state->player.y = FIELD_RANGE / 2;
}

void update_field(struct field* p_field) {
    if (p_field == NULL) return;

    p_field->pattern.pattern_function(p_field->field, ++p_field->frame);
    if (p_field->frame < p_field->pattern.max_frame) {
        free(p_field);
        p_field = NULL;
    }
}

int update_state(f_state* state, int move_x, int move_y) {

    //update player position
    state->player.x += move_x;
    state->player.y += move_y;

    if (state->player.x < 0) state->player.x = 0;
    else if (state->player.x >= FIELD_RANGE) state->player.x = FIELD_RANGE - 1;
    if (state->player.y < 0) state->player.y = 0;
    else if (state->player.y >= FIELD_RANGE) state->player.y = FIELD_RANGE - 1;

    for (int i = 0; i <= state->fields_top; i++) {
        // updating objects by patterns
        update_field(state->fields[i]);
        if (state->fields[i] == NULL) continue;

        // damage for collision
        // get damage in XX000000 part of number
        state->player.HP -= state->fields[i]->field[state->player.x][state->player.y] >> 24;
    }

    if (state->player.HP <= 0) {
        return 1;
    }

    return 0;
}

void get_field_top(unsigned int colors[FIELD_RANGE][FIELD_RANGE], f_state* state) {
    for (int x = 0; x < FIELD_RANGE; x++) {
        for (int y = 0; y < FIELD_RANGE; y++) {
            colors[x][y] = 0;

            for (int i = 0; i < PATTERN_MAX; i++) {
                if (state->fields[i] == NULL) continue;

                // get color-part
                if (colors[x][y] < (state->fields[i]->field[y][x] & 0x00ffffff)) {
                    colors[x][y] = state->fields[i]->field[y][x] & 0x00ffffff;
                }

            }
        }
    }
}

