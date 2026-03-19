#include "pattern.h"
#include <state.h>

#include <string.h>

//TODO: code some patterns, equation or massive of frames

// _#___#___#___#___#___#___#___#_  -2
// ###_###_###_###_###_###_###_###  -1
// _#___#___#___#___#___#___#___#_   0
int process_bullets1(unsigned int (*field)[FIELD_RANGE], int frame) {
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

void bullet1(field_t* field) {
    field->pattern.pattern_function = process_bullets1;
    // field->pattern.max_updates = 32;
    field->pattern.height = 1;
    field->pattern.update_frames = 11;
    field->frame = 0;

    clear_field(field->field);
}

