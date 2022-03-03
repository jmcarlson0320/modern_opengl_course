#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "load_shaders.h"

#define WIDTH 800
#define HEIGHT 600

enum VAO_IDS {
    TRIANGLES,
    NUM_VAOS
};

enum BUFFER_IDS {
    ARRAY_BUFFER,
    NUM_BUFFERS
};

enum ATTRIB_IDS {
    V_POSITION = 0,
    NUM_ATTRIBUTES
};

enum SHADER_IDS {
    FILL_RED,
    NUM_SHADERS
};

enum UNIFORM_IDS {
    X_MOVE,
    NUM_UNIFORMS
};

// opengl object ids
GLuint vaos[NUM_VAOS];
GLuint buffers[NUM_BUFFERS];
GLuint shaders[NUM_SHADERS];
GLuint uniforms[NUM_UNIFORMS];

// setup data and shaders for opengl draw calls
void init()
{
    // triangle data
    GLfloat vertices[] = {
        -1.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
    };

    // allocate vaos
    glGenVertexArrays(NUM_VAOS, vaos);
    glBindVertexArray(vaos[TRIANGLES]);

    // allocate vbos and load data
    glGenBuffers(NUM_BUFFERS,buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[ARRAY_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // define vertex attributes
    glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(V_POSITION);

    // unbind vao and vbo - good practice
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // load shaders
    shader_info shaders_info[] = {
        {GL_VERTEX_SHADER, "resources/shaders/uniforms.vert"},
        {GL_FRAGMENT_SHADER, "resources/shaders/fill_red.frag"},
        {GL_NONE, NULL},
    };
    shaders[FILL_RED] = load_shaders(shaders_info);
    glUseProgram(shaders[FILL_RED]);

    // setup uniforms
    uniforms[X_MOVE] = glGetUniformLocation(shaders[FILL_RED], "x_move");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// call opengl draw functions
// operates on the above global state
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // draw triangle
    glBindVertexArray(vaos[TRIANGLES]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

// glfw code in here
// creates a window and opengl context
// calls init()
// calls display() inside main loop
int main(int argc, char *argv[])
{
    // setup window and opengl context
    if (!glfwInit()) {
        printf("could not init glfw\n");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "test window", NULL, NULL);
    if (!window) {
        printf("could not create window\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    // init glew
    if(glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    init();

    // for moving triangle
    float x_offset = 0;
    float dx = 0.01;

    // main loop
    while(!glfwWindowShouldClose(window)) {
        // move triangle
        x_offset += dx;
        glUniform1f(uniforms[X_MOVE], x_offset);

        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // TODO free resources

    return 0;
}
