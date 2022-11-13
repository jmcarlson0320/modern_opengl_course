#include "Input.h"


int KEY_MAP[NUM_KEYBOARD_INPUTS] = {
    [FORWARD] = GLFW_KEY_W,
    [BACK] = GLFW_KEY_S,
    [LEFT] = GLFW_KEY_A,
    [RIGHT] = GLFW_KEY_D,
    [QUIT] = GLFW_KEY_Q
};

bool keyboard_input[NUM_KEYBOARD_INPUTS] = {0};
double mouse_input[NUM_MOUSE_INPUTS] = {0.0f};

void handleInput(GLFWwindow *window)
{
    glfwPollEvents();

    for (int i = 0; i < NUM_KEYBOARD_INPUTS; i++) {
        keyboard_input[i] = (glfwGetKey(window, KEY_MAP[i]) == GLFW_PRESS);
    }

    // save old mouse coords
    double prev_x = mouse_input[X];
    double prev_y = mouse_input[Y];

    // get new mouse coords
    glfwGetCursorPos(window, &mouse_input[X], &mouse_input[Y]);

    // calculate how far mouse has moved since last frame
    mouse_input[DX] = mouse_input[X] - prev_x;
    mouse_input[DY] = prev_y - mouse_input[Y];
}