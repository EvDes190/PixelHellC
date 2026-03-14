#include <windows.h>
#include <unistd.h>

typedef struct RenderState {
    HWND hwnd;
    HDC hdc;
    HPEN hPen;
    HBRUSH hBrush;

    int fps;
    int width;
    int height;
} renderstate_t;