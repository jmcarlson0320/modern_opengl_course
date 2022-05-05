#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "load_shaders.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Light.h"

#define WIDTH 800
#define HEIGHT 600

#define TO_RADIANS(x) (x * 3.14159265f / 180.0f)

// triangle parameters
float x_offset = 0;
float dx = 0.01;
float angle = 0;
float d_angle = 0.1;

Mesh *mesh;
Shader *shader;
Texture *texture;

// user input
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

int KEY_MAP[NUM_KEYBOARD_INPUTS] = {
    [FORWARD] = GLFW_KEY_W,
    [BACK] = GLFW_KEY_S,
    [LEFT] = GLFW_KEY_A,
    [RIGHT] = GLFW_KEY_D,
    [QUIT] = GLFW_KEY_Q
};

bool keyboard_input[NUM_KEYBOARD_INPUTS] = {0};
double mouse_input[NUM_MOUSE_INPUTS] = {0.0f};

// camera
glm::vec3 eye;
glm::vec3 dir;

void MessageCallback( GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
}

// setup data and shaders for opengl draw calls
void init()
{
    // enable debug output
//    glEnable(GL_DEBUG_OUTPUT);
//    glDebugMessageCallback(MessageCallback, 0);

    // position data
    GLfloat mesh_vertex_data[] = {
    //   x      y      z     r     g     b
        -1.0f, -1.0f,  0.0f, 1.0f, 1.0f, 0.0f,
         0.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f
    };

    // index data
    unsigned int mesh_index_data[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    mesh = new Mesh(mesh_vertex_data, sizeof(mesh_vertex_data[0]) * 24, mesh_index_data, 12);

    // load shaders
    shader = new Shader();
    shader->fromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // init camera
    eye = glm::vec3(0.0f, 0.0f, 1.0f);
    dir = glm::vec3(0.0f, 0.0f, -1.0f);

    // load texture
    texture = new Texture();
    texture->fromFile("resources/textures/bluerock_texture.jpg");
    texture->use();
}

void handleInput(GLFWwindow *window)
{
    double prev_x = mouse_input[X];
    double prev_y = mouse_input[Y];

    glfwPollEvents();

    for (int i = 0; i < NUM_KEYBOARD_INPUTS; i++) {
        keyboard_input[i] = (glfwGetKey(window, KEY_MAP[i]) == GLFW_PRESS);
    }

    glfwGetCursorPos(window, &mouse_input[X], &mouse_input[Y]);
    mouse_input[DX] = mouse_input[X] - prev_x;
    mouse_input[DY] = prev_y - mouse_input[Y];
}

void update(float dt)
{
    // update camera
    // get forward and right vectors from view direction
    glm::vec3 forward = glm::vec3(dir.x, 0.0f, dir.z);
    glm::vec3 right = glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f));

    // get delta pitch and yaw from mouse input
    GLfloat delta_pitch = mouse_input[DY] * 0.001;
    GLfloat delta_yaw = mouse_input[DX] * 0.001;

    // rotation matrix for view pitch
    glm::mat4 rotate_x = glm::rotate(glm::mat4(1.0f), delta_pitch, right);

    // rotation matrix for view yaw
    glm::mat4 rotate_y = glm::rotate(glm::mat4(1.0f), delta_yaw, -glm::vec3(0.0f, 1.0f, 0.0f));

    // rotate the view direction by pitch first, then yaw
    glm::vec4 dir_homog = rotate_y * rotate_x * glm::vec4(dir, 1.0f);
    dir = glm::vec3(dir_homog);

    // move camera position
    if (keyboard_input[FORWARD]) {
        eye = eye + forward * 0.05f;
    }
    if (keyboard_input[BACK]) {
        eye = eye + forward * -0.05f;
    }
    if (keyboard_input[LEFT]) {
        eye = eye + right * -0.05f;
    }
    if (keyboard_input[RIGHT]) {
        eye = eye + right * 0.05f;
    }
}

// call opengl draw functions
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

    // view matrix
    glm::mat4 view(1.0f);
    view = glm::lookAt(eye, eye + dir, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, glm::value_ptr(view));

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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

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

        if (keyboard_input[QUIT]) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    delete mesh;
    delete shader;
    delete texture;

    return 0;
}
