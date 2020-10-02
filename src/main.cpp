#include <X11/X.h>
#include <ncurses.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "Marcher.hpp"
#include "Objects.hpp"

#define FILL_CHAR_LEN 6

char fill_char[] = {
    '#', '%', '/', '-', '.', ' '
};

bool key_is_pressed(KeySym ks) {
    Display *dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);
    return isPressed;
}

int main(int argc, char *argv[]) {
    WINDOW* game_window;
    int ch;

    initscr();
    raw();
    noecho();
    refresh();

    double fov = 1;
    double ratio = COLS / ((float)LINES * 2);

    Marcher march(fov * ratio, fov, 0, 0, -0.2);
    march.SetSettings(0.0005, 20);

    Sphere sphere(0.75, 0.5, 0.5, 0.1);
    Box box(0.25, 0.5, 0.5, 0.1, 0.1, 0.1);

    march.AddObject((BaseObject*)&sphere);
    march.AddObject((BaseObject*)&box);

    std::ofstream log;
    log.open("log.txt");

    while (!key_is_pressed(XK_c)) {
        double ratio = COLS / ((float)LINES * 2);
        march.SetFrustrum(fov*ratio, fov);

        for (int i = 0; i < COLS; ++i) {
            for (int j = 0; j < LINES; ++j) {
                double y = (float)i / COLS;
                double x = (float)j / LINES;
                Vector3 rd = march.NormToVec(x, y);
                Marcher::MarchOutput out = march.March(rd);

                float shade = FILL_CHAR_LEN*out.steps/march.GetSettings().stepMax;
                float d = 1/out.dist;
                d = d > 1 ? 1 : d;
                d = d < 0 ? 0 : d;
                shade *= d * 2;
                int c = shade >= FILL_CHAR_LEN ? FILL_CHAR_LEN-1 : shade;
                mvaddch(j, i, fill_char[FILL_CHAR_LEN-c-1]);
            }
        }

        double movSpeed = 0.02;

        if (key_is_pressed(XK_w))
            march.Offset(0, 0, movSpeed);
        if (key_is_pressed(XK_s))
            march.Offset(0, 0, -movSpeed);
        if (key_is_pressed(XK_a))
            march.Offset(movSpeed, 0, 0);
        if (key_is_pressed(XK_d))
            march.Offset(-movSpeed, 0, 0);
        if (key_is_pressed(XK_q))
            march.Offset(0, movSpeed, 0);
        if (key_is_pressed(XK_e))
            march.Offset(0,-movSpeed, 0);
        if (key_is_pressed(XK_i))
            fov += 0.1;
        if (key_is_pressed(XK_k))
            fov -= 0.1;

        refresh();
    }

    log.close();

    endwin();

    return 0;
}
