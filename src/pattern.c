#define PATTERN_MAX 10
#define FIELD_RANGE 31

typedef struct pattern {
    //pattern function draw object on a field of pattern at the every frame
    int (*pattern_function) (unsigned int field[FIELD_RANGE][FIELD_RANGE], int frame);
    //after max_frame field will not updating; this value calculate for each pattern-function
    int max_frame;
    //speed is responsible how many frames need to update field by pattern function
    //calling pattern-function, division field.frame by speed
    int speed;
    //height need to choice color for render full field
    int height;
} pattern_t;

struct field {
    //field[i][j] contains information about damage(0xXX000000) and color(0x00XXXXXX)
    unsigned int field[FIELD_RANGE][FIELD_RANGE];
    //every pattern lasts a certain number of frames
    int frame;
    //information about patter what field contain
    pattern_t pattern;
};

//TODO: code some patterns, equation or massive of frames
