#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

enum KEYBOARD_INPUTS {
    FORWARD,
    BACK,
    LEFT,
    RIGHT,
    QUIT,
    NUM_KEYBOARD_INPUTS
};

enum MOUSE_INPUTS {
    X,
    Y,
    DX,
    DY,
    NUM_MOUSE_INPUTS
};

extern bool keyboard_input[];
extern double mouse_input[];

void handleInput(GLFWwindow *window);

#endif // INPUT_H
