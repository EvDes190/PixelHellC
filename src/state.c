#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "pattern.h"
#include "state.h"

#define HP_MAX 1000
#define BASE_PATTERN_MODULE 1000


int clear_field(unsigned int field[FIELD_RANGE][FIELD_RANGE]) {
    for (int y = 0; y < FIELD_RANGE; y++) {
        memset(field[y], 0, sizeof(unsigned int) * FIELD_RANGE);
    }
    return 0;
}

// TODO: need to code function that spawns patterns according to certain rules
int choose_pattern(f_state* state) {
    srand(clock() ^ time(NULL));
    int random = rand() % BASE_PATTERN_MODULE;


    static int bullets_1_count = 5 * 11;
    static int lasers_1_count = 25 * 11;
    static int spiral_1_count = 30 * 5;
    // printf("%d %d\n", lasers_1_count, bullets_1_count);

    int i = 0;
    for (; i < PATTERN_MAX; i++) {
        if (state->fields[i] == NULL) break;
        if (i == PATTERN_MAX - 1) return 0;
    }


    bullets_1_count--;
    lasers_1_count--;
    spiral_1_count--;

    if (random < 10) {
        if (bullets_1_count > 0) return 0;
        state->fields[i] = malloc(sizeof(struct field));
        Bullets_1(state->fields[i]);

        bullets_1_count = 5 * 11;
    } else if (random < 20) {
        if (lasers_1_count > 0) return 0;
        state->fields[i] = malloc(sizeof(struct field));
        Lasers_1(state->fields[i]);

        lasers_1_count = 25 * 11;
    } else if (random < 30) {
        if (spiral_1_count > 0) return 0;
        state->fields[i] = malloc(sizeof(struct field));
        Spiral_1(state->fields[i]);

        spiral_1_count = 10 * 5;
    }

    return 1;
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

    if (state->time != 0)
        state->colors[state->player.y][state->player.x] = 0x0000ff00; //GREEN
}

void reset_state(f_state* state) {
    for (int i = 0; i < PATTERN_MAX; i++) {
        if (state->fields[i] != NULL)
            free(state->fields[i]);
        state->fields[i] = NULL;
    }
    state->time = 0;
    update_field_top(state);

    state->player.HP = HP_MAX;
    state->player.x = FIELD_RANGE / 2;
    state->player.y = FIELD_RANGE / 2;
}


void update_field(field_t** p_field) {
    if (*p_field == NULL) return;

    // end pattern working when pattern is end
    if ((*p_field)->pattern.pattern_function((*p_field)->field, ++(*p_field)->frame / (*p_field)->pattern.update_frames) == 0) {
        free(*p_field);
        *p_field = NULL;
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

    for (int i = 0; i < PATTERN_MAX; i++) {
        // updating objects by patterns
        update_field(&state->fields[i]);
        if (state->fields[i] == NULL) continue;

        // damage for collision
        // get damage in XX000000 part of number
        state->player.HP -= state->fields[i]->field[state->player.y][state->player.x] >> 24;
    }

    // spawn new objects
    choose_pattern(state);

    // update colors for rendering
    update_field_top(state);

    return state->player.HP <= 0 ? 1 : 0;
}
