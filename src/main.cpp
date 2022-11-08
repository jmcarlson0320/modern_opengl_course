#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "SimpleShader.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"
#include "BufferLayout.h"
#include "Mesh.h"

#define WIDTH 1280
#define HEIGHT 720

#define TO_RADIANS(x) (x * 3.14159265f / 180.0f)

float angle = 0;
float d_angle = 0.7;

SimpleShader *simpleShader;
Texture *texture;
Light *light;
Material *shinyMaterial;
Material *dullMaterial;

/* node */
Mesh *teapot;

/*****************************************************************************************
* User Input
****************************************************************************************/
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

void handleInput(GLFWwindow *window);

/*****************************************************************************************
* Camera
****************************************************************************************/
glm::vec3 eye;
glm::vec3 dir;
GLfloat fov;
GLfloat aspect_ratio;
GLfloat near;
GLfloat far;

// setup data and shaders
void init()
{

//    enable debug output
//    glEnable(GL_DEBUG_OUTPUT);
//    glDebugMessageCallback(MessageCallback, 0);

    /*****************************************************************************************
    * Load Mesh
    ****************************************************************************************/
    teapot = new Mesh();
    teapot->loadObj("resources/models/LibertStatue.obj");

    /*****************************************************************************************
    * Load Shaders
    ****************************************************************************************/
    simpleShader = new SimpleShader();
    simpleShader->fromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");

    /*****************************************************************************************
    * Load Textures
    ****************************************************************************************/
    texture = new Texture("resources/textures/noise.png");
    texture->use();

    /*****************************************************************************************
    * Init Light Source
    ****************************************************************************************/
    glm::vec3 light_position(10.0f, 0.0f, 0.0f);
    light = new Light(1.0f, 1.0f, 1.0f, 0.2f, 1.0f, light_position);

    /*****************************************************************************************
    * Init Materials
    ****************************************************************************************/
    shinyMaterial = new Material(1.0f, 32);
    dullMaterial = new Material(0.3f, 4);

    /*****************************************************************************************
    * Init Camera
    ****************************************************************************************/
    eye = glm::vec3(0.0f, 0.0f, 1.0f);
    dir = glm::vec3(0.0f, 0.0f, -1.0f);
    near = 0.1f;
    far = 100.0f;
    fov = 45.0f;
    aspect_ratio = (GLfloat) WIDTH / (GLfloat) HEIGHT;

    /*****************************************************************************************
    * Set Uniforms for Light and Material
    ****************************************************************************************/
    simpleShader->use();
    simpleShader->setUniformFloat("ambientIntensity", light->ambient_amount);
    simpleShader->setUniformVec3("lightColor", light->color);
    simpleShader->setUniformFloat("lightIntensity", light->intensity);
    simpleShader->setUniformVec3("lightPosition", light->position);
    simpleShader->setUniformFloat("material.specular_intensity", shinyMaterial->specular_intensity);
    simpleShader->setUniformFloat("material.shininess", shinyMaterial->shininess);

    /*****************************************************************************************
    * Set Background Color
    ****************************************************************************************/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*****************************************************************************************
    * Enable Depth Test
    ****************************************************************************************/
    glEnable(GL_DEPTH_TEST);
}

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

void update(float dt)
{
    /*****************************************************************************************
    * Update Camera Angle
    ****************************************************************************************/
    // get forward and right vectors from view direction
    glm::vec3 forward = glm::vec3(dir.x, 0.0f, dir.z); // TODO: normalize
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

    /*****************************************************************************************
    * Update Camera Position
    ****************************************************************************************/
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
    
    /*****************************************************************************************
    * Rotate the scene
    ****************************************************************************************/
    angle += d_angle;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*****************************************************************************************
    * Build MVP Matrices
    ****************************************************************************************/
    // model
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::rotate(model, TO_RADIANS(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

    // view
    glm::mat4 view = glm::lookAt(eye, eye + dir, glm::vec3(0.0f, 1.0f, 0.0f));

    // projection
    glm::mat4 projection = glm::perspective(fov, aspect_ratio, near, far);

    /*****************************************************************************************
    * Send Matrices to Shader
    ****************************************************************************************/
    simpleShader->setUniformMat4("model", model);
    simpleShader->setUniformMat4("view", view);
    simpleShader->setUniformMat4("projection", projection);

    /*****************************************************************************************
    * Draw Model
    ****************************************************************************************/
    teapot->getVertexArray()->bind();
    glDrawElements(GL_TRIANGLES, teapot->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, 0);
}

// glfw code in here
// creates a window and opengl context
// calls init()
// calls display() inside main loop
int main(int argc, char *argv[])
{
    // init glfw
    if (!glfwInit()) {
        printf("could not init glfw\n");
        exit(1);
    }

    // specify the opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // setup window and opengl context
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "test window", NULL, NULL);
    if (!window) {
        printf("could not create window\n");
        glfwTerminate();
        exit(1);
    }

    // keyboard and mouse settings
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // use the window's opengl context
    glfwMakeContextCurrent(window);

    // init glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    init();
    update(0.0f); // does this need to be called?

    // main loop
    // float last = get_time();     // timing not implemented yet
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

    delete simpleShader;
    delete texture;

    return 0;
}