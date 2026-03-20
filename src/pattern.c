#include "pattern.h"

#include <math.h>
#include <state.h>
#include <stdio.h>

#include <string.h>

//TODO: code some patterns, equation or massive of frames

// _#___#___#___#___#___#___#___#_  -2
// ###_###_###_###_###_###_###_###  -1
// _#___#___#___#___#___#___#___#_   0
int update_bullets_1(unsigned int (*field)[FIELD_RANGE], int frame) {
    unsigned int red1 = 0x01ff0000;

    int start = -2 + frame;
    if (start >= FIELD_RANGE) return 0;

    // drawing  _#_ 8 times
    //          ###
    //          _#_
    for (int i = 0; i < 31; i += 4) {
        if (start > 0) field[start - 1][i + 1] = 0;
        if (start + 1 > 0) {
            field[start][i + 2] = 0;
            field[start][i] = 0;
        }
        if (start + 1 >= 0 && start + 1 < FIELD_RANGE) field[start + 1][i] = red1;
        if (start + 1 >= 0 && start + 1 < FIELD_RANGE) field[start + 1][i + 2] = red1;
        if (start + 2 < FIELD_RANGE) field[start + 2][i + 1] = red1;
    }
    return 1;
}

void Bullets_1(field_t* field) {
    field->pattern.pattern_function = update_bullets_1;
    // field->pattern.max_updates = 32;
    field->pattern.height = 1;
    field->pattern.update_frames = 11;
    field->frame = 0;

    clear_field(field->field);
}

// _#_##__###___##_##___###__##_#_
int update_lasers_1(unsigned int (*field)[FIELD_RANGE], int frame) {
    int color = 0;

    if ((frame >= 3 && frame < 6) || (frame >= 9 && frame < 13)) color = 0x00000000;
    else if ((frame >= 1 && frame < 3) || (frame >= 6 && frame < 9)) color = 0x00008080;
    else if (frame >= 13 && frame < 17) color = 0x0500ffff;
    else if (frame >= 17) return 0;

    for (int y = 0; y < FIELD_RANGE; y++) {
        field[y][1] = color;
        field[y][3] = color;
        field[y][4] = color;
        field[y][7] = color;
        field[y][8] = color;
        field[y][9] = color;
        field[y][13] = color;
        field[y][14] = color;

        field[y][FIELD_RANGE - 2] = color;
        field[y][FIELD_RANGE - 4] = color;
        field[y][FIELD_RANGE - 5] = color;
        field[y][FIELD_RANGE - 8] = color;
        field[y][FIELD_RANGE - 9] = color;
        field[y][FIELD_RANGE - 10] = color;
        field[y][FIELD_RANGE - 14] = color;
        field[y][FIELD_RANGE - 15] = color;
    }

    return 1;
}

void Lasers_1(field_t* field) {
    field->pattern.pattern_function = update_lasers_1;
    field->pattern.height = 3;
    field->pattern.update_frames = 11;
    field->frame = 0;

    clear_field(field->field);
}

// ===SPIRAL_1===

void pre_update_spiral_1(int *X, int *Y, int t) {
    // if (t == 0) {
    //     *X = FIELD_RANGE / 2;
    //     *Y = FIELD_RANGE / 2;
    //     return;
    // }

    int x = 0, y = 0;

    if (t == 0) {
        *X = 15;
        *Y = 15;
        return;
    }

    int step_len = 1;   // длина текущего отрезка
    int dir = 0;        // 0=вверх, 1=вправо, 2=вниз, 3=влево
    int steps_done = 0;
    int changes = 0;

    for (int i = 0; i < t; i++) {
        switch (dir) {
            case 0: y++; break; // вверх
            case 1: x++; break; // вправо
            case 2: y--; break; // вниз
            case 3: x--; break; // влево
        }

        steps_done++;

        if (steps_done == step_len) {
            steps_done = 0;
            dir = (dir + 1) % 4;
            changes++;

            if (changes % 2 == 0) {
                step_len++;
            }
        }
    }


    *X = x + FIELD_RANGE / 2;
    *Y = y + FIELD_RANGE / 2;
}

int update_spiral_1(unsigned int (*field)[FIELD_RANGE], int frame) {
    if (frame > FIELD_RANGE * FIELD_RANGE - 1) return 0;

    static int length = 5;
    int x, y;
    pre_update_spiral_1(&x, &y, frame);

    field[x][y] = 0x04dd00dd;
    if (frame >= length) {
        pre_update_spiral_1(&x, &y, frame - length);
        field[x][y] = 0x00000000;
    }
    return 1;
}

void Spiral_1(field_t* field) {
    field->pattern.pattern_function = update_spiral_1;
    field->pattern.height = 2;
    field->pattern.update_frames = 5;
    field->frame = 0;

    clear_field(field->field);
}
