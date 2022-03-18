#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "load_shaders.h"
#include "Mesh.h"

#define WIDTH 800
#define HEIGHT 600

#define TO_RADIANS(x) (x * 3.14159265f / 180.0f)

enum SHADER_IDS {
    FILL_RED,
    NUM_SHADERS
};

enum UNIFORM_IDS {
    MODEL,
    PROJECTION,
    NUM_UNIFORMS
};

// opengl object ids
GLuint shaders[NUM_SHADERS];
GLuint uniforms[NUM_UNIFORMS];

// for moving triangle
float x_offset = 0;
float dx = 0.01;
float angle = 0;
float d_angle = 0.1;

glm::vec3 *mesh_vertex_data;
unsigned int *mesh_index_data;
Mesh *mesh;

// setup data and shaders for opengl draw calls
void init()
{
    // triangle data
    mesh_vertex_data = new glm::vec3[4];
    mesh_vertex_data[0] = glm::vec3( -1.0f, -1.0f,  0.0f );
    mesh_vertex_data[1] = glm::vec3(  0.0f, -1.0f,  1.0f );
    mesh_vertex_data[2] = glm::vec3(  1.0f, -1.0f,  0.0f );
    mesh_vertex_data[3] = glm::vec3(  0.0f,  1.0f,  0.0f );

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };
    mesh_index_data = new unsigned int[12];
    for (int i = 0; i < 12; i++) {
        mesh_index_data[i] = indices[i];
    }

    mesh = new Mesh(mesh_vertex_data, 4, mesh_index_data, 12);

    // load shaders
    shader_info shaders_info[] = {
        {GL_VERTEX_SHADER, "resources/shaders/uniforms.vert"},
        {GL_FRAGMENT_SHADER, "resources/shaders/fill_red.frag"},
        {GL_NONE, NULL},
    };
    shaders[FILL_RED] = load_shaders(shaders_info);
    glUseProgram(shaders[FILL_RED]);

    // setup uniforms
    uniforms[MODEL] = glGetUniformLocation(shaders[FILL_RED], "model");
    uniforms[PROJECTION] = glGetUniformLocation(shaders[FILL_RED], "projection");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// call opengl draw functions
// operates on the above global state
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // rotate slowly
    angle += d_angle;

    // setup model matrix
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::rotate(model, TO_RADIANS(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    // send model matrix to shader
    glUniformMatrix4fv(uniforms[MODEL], 1, GL_FALSE, glm::value_ptr(model));

    // setup projection matrix
    glm::mat4 projection(1.0f);
    GLfloat aspect_ratio = (GLfloat) WIDTH / (GLfloat) HEIGHT;
    projection = glm::perspective(45.0f, aspect_ratio, 0.1f, 100.0f);

    // send projection matrix to shader
    glUniformMatrix4fv(uniforms[PROJECTION], 1, GL_FALSE, glm::value_ptr(projection));

    // draw triangle
    mesh->render();
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

    glEnable(GL_DEPTH_TEST);

    int nx;
    int ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    // init glew
    if(glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    // setup triangle data and shaders
    init();

    // main loop
    while(!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    glfwTerminate();

    return 0;
}
