//
// Created by EvDes on 15.03.2026.
//

#ifndef PIXELHELLC_STATE_H
#define PIXELHELLC_STATE_H

#include <time.h>

#include "pattern.h"


struct player {
    unsigned int HP;
    int x;
    int y;
};

typedef struct field_state {
    //own field for every working pattern, maximum PATTERN_MAX
    struct field* fields[PATTERN_MAX];
    struct player player;
    unsigned int colors[FIELD_RANGE][FIELD_RANGE];
    //time elapsed after start game
    clock_t time;
    //if 1 - game is on
    int game;
} f_state;

int clear_field(unsigned int [FIELD_RANGE][FIELD_RANGE]);
void update_field_top(f_state*);
void reset_state(f_state*);
void update_field(field_t**);
void update_player(struct player*, int, int);
int update_state(f_state*, int, int);

#endif //PIXELHELLC_STATE_H