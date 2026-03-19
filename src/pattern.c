#include "pattern.h"
#include <state.h>

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
    int color = 0x0100ffff;

    if ((frame >= 3 && frame < 6) || (frame >= 9 && frame < 13)) color = 0x00000000;
    else if ((frame >= 1 && frame < 3) || (frame >= 6 && frame < 9)) color = 0x00008080;
    else if (frame >= 13 && frame < 17) color = 0x0100ffff;
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

        field[y][FIELD_RANGE - 1] = color;
        field[y][FIELD_RANGE - 3] = color;
        field[y][FIELD_RANGE - 4] = color;
        field[y][FIELD_RANGE - 7] = color;
        field[y][FIELD_RANGE - 8] = color;
        field[y][FIELD_RANGE - 9] = color;
        field[y][FIELD_RANGE - 13] = color;
        field[y][FIELD_RANGE - 14] = color;
    }

    return 1;
}

void Lasers_2(field_t* field) {
    field->pattern.pattern_function = update_lasers_1;
    field->pattern.height = 2;
    field->pattern.update_frames = 11;
    field->frame = 0;

    clear_field(field->field);
}
