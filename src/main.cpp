#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "load_shaders.h"
#include "Mesh.h"
#include "Shader.h"

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

// shape data
Mesh *mesh;
Shader *shader;

// user input
enum KEYBOARD_INPUTS {
    FORWARD,
    BACK,
    LEFT,
    RIGHT,
    QUIT,
    NUM_INPUTS
};

int KEY_MAP[NUM_INPUTS] = {
    [FORWARD] = GLFW_KEY_W,
    [BACK] = GLFW_KEY_S,
    [LEFT] = GLFW_KEY_A,
    [RIGHT] = GLFW_KEY_D,
    [QUIT] = GLFW_KEY_Q
};

bool input[NUM_INPUTS] = {0};

// setup data and shaders for opengl draw calls
void init()
{
    // position data
    GLfloat mesh_vertex_data[] = {
        -1.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };

    // index data
    unsigned int mesh_index_data[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    mesh = new Mesh(mesh_vertex_data, sizeof(mesh_vertex_data[0]) * 12, mesh_index_data, 12);

    // load shaders
    shader = new Shader();
    shader->fromFile("resources/shaders/uniforms.vert", "resources/shaders/fill_red.frag");

    /*
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
    */

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void handleInput(GLFWwindow *window)
{
    glfwPollEvents();
    for (int i = 0; i < NUM_INPUTS; i++) {
        input[i] = glfwGetKey(window, KEY_MAP[i]) == GLFW_PRESS;
    }
}

void update(float dt)
{
}

// call opengl draw functions
// operates on the above global state
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render the pyrimid
    // activate shader
    shader->use();

    // update position
    angle += d_angle;

    // model matrix
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::rotate(model, TO_RADIANS(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

    // projection matrix
    glm::mat4 projection(1.0f);
    GLfloat aspect_ratio = (GLfloat) WIDTH / (GLfloat) HEIGHT;
    projection = glm::perspective(45.0f, aspect_ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

    // draw
    mesh->render();

    // deactivate shader
    shader->clear();

}

// glfw code in here
// creates a window and opengl context
// calls init()
// calls display() inside main loop
int main(int argc, char *argv[])
{
    if (!glfwInit()) {
        printf("could not init glfw\n");
        exit(1);
    }

    // setup window and opengl context
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

    // setup triangle data and shaders
    init();

    // main loop
    // float last = get_time();
    float last = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        // float cur = get_time();
        float cur = 0.0f;
        float dt = cur - last;

        handleInput(window);
        update(dt);
        display();

        glfwSwapBuffers(window);

        last = cur;

        if (input[QUIT]) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    delete mesh;
    delete shader;

    return 0;
}
