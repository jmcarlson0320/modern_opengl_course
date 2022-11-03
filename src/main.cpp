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
#include "load_obj.h"

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

VertexBuffer *vertexBuffer;
IndexBuffer *indexBuffer;
VertexArray *vertexArray;

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
GLfloat fov;
GLfloat aspect_ratio;
GLfloat near;
GLfloat far;

void update(float dt);

void calcAvgNormals(unsigned int *indices, unsigned int num_indices, GLfloat *vertices, unsigned int num_vertices, unsigned int vertex_length, unsigned int normal_offset)
{
    for (unsigned int i = 0; i < num_indices; i += 3) {
        // initialize indices to position of vertices
        unsigned int index_v0 = indices[i] * vertex_length;
        unsigned int index_v1 = indices[i + 1] * vertex_length;
        unsigned int index_v2 = indices[i + 2] * vertex_length;

        // calculate the normal of the triangle defined by v0, v1, v2
        glm::vec3 edge_01(vertices[index_v1] - vertices[index_v0], vertices[index_v1 + 1] - vertices[index_v0 + 1], vertices[index_v1 + 2] - vertices[index_v0 + 2]);
        glm::vec3 edge_02(vertices[index_v2] - vertices[index_v0], vertices[index_v2 + 1] - vertices[index_v0 + 1], vertices[index_v2 + 2] - vertices[index_v0 + 2]);
        glm::vec3 normal_012 = glm::cross(edge_01, edge_02);
        normal_012 = glm::normalize(normal_012);

        // point indices to normal of vertices
        index_v0 += normal_offset;
        index_v1 += normal_offset;
        index_v2 += normal_offset;

        // add the triangle normal to each vertex normal
        // v0
        vertices[index_v0] += normal_012.x;
        vertices[index_v0 + 1] += normal_012.y;
        vertices[index_v0 + 2] += normal_012.z;

        // v1
        vertices[index_v1] += normal_012.x;
        vertices[index_v1 + 1] += normal_012.y;
        vertices[index_v1 + 2] += normal_012.z;

        // v2
        vertices[index_v2] += normal_012.x;
        vertices[index_v2 + 1] += normal_012.y;
        vertices[index_v2 + 2] += normal_012.z;
    }

    // vertex normals now hold the sum of the normals of the surfaces dependent on that vertex
    // finally we normalize the normals
    for (unsigned int i = 0; i < num_vertices / vertex_length; i++) {
        unsigned int cur_normal_offset = i * vertex_length + normal_offset;
        glm::vec3 v(vertices[cur_normal_offset], vertices[cur_normal_offset + 1], vertices[cur_normal_offset + 2]);
        v = glm::normalize(v);
        vertices[cur_normal_offset] = v.x;
        vertices[cur_normal_offset + 1] = v.y;
        vertices[cur_normal_offset + 2] = v.z;
    }
}

// setup data and shaders
void init()
{

//    enable debug output
//    glEnable(GL_DEBUG_OUTPUT);
//    glDebugMessageCallback(MessageCallback, 0);

    // load obj file contents into vertex buffer and index buffer
    MeshData meshData = load_obj("resources/models/teapot.obj");
    vertexBuffer = new VertexBuffer(meshData.vertices.data(), meshData.vertices.size());
    indexBuffer = new IndexBuffer(meshData.indices.data(), meshData.indices.size());

    // define the vertex layout
    BufferLayout layout;
    layout.addElem(FLOAT, 3); // position
    layout.addElem(FLOAT, 3); // normal
    vertexBuffer->setLayout(layout);

    // assemble the vertex array object
    vertexArray = new VertexArray();
    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->addIndexBuffer(indexBuffer);

    simpleShader = new SimpleShader();
    simpleShader->fromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");

    texture = new Texture("resources/textures/noise.png");
    texture->use();

    glm::vec3 light_position(10.0f, 0.0f, 0.0f);
    light = new Light(1.0f, 1.0f, 1.0f, 0.2f, 1.0f, light_position);

    shinyMaterial = new Material(1.0f, 32);
    dullMaterial = new Material(0.3f, 4);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // init camera
    eye = glm::vec3(0.0f, 0.0f, 1.0f);
    dir = glm::vec3(0.0f, 0.0f, -1.0f);
    near = 0.1f;
    far = 100.0f;
    fov = 45.0f;
    aspect_ratio = (GLfloat) WIDTH / (GLfloat) HEIGHT;

    simpleShader->use();
    simpleShader->setUniformFloat("ambientIntensity", light->ambient_amount);
    simpleShader->setUniformVec3("lightColor", light->color);
    simpleShader->setUniformFloat("lightIntensity", light->intensity);
    simpleShader->setUniformVec3("lightPosition", light->position);
    simpleShader->setUniformFloat("material.specular_intensity", shinyMaterial->specular_intensity);
    simpleShader->setUniformFloat("material.shininess", shinyMaterial->shininess);

    update(0.0f);
}

void handleInput(GLFWwindow *window)
{
    glfwPollEvents();

    for (int i = 0; i < NUM_KEYBOARD_INPUTS; i++) {
        keyboard_input[i] = (glfwGetKey(window, KEY_MAP[i]) == GLFW_PRESS);
    }

    double prev_x = mouse_input[X];
    double prev_y = mouse_input[Y];
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
    
    // rotate the pyrimid
    angle += d_angle;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // build matrices
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::rotate(model, TO_RADIANS(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(eye, eye + dir, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(fov, aspect_ratio, near, far);

    // set uniforms
    simpleShader->setUniformMat4("model", model);
    simpleShader->setUniformMat4("view", view);
    simpleShader->setUniformMat4("projection", projection);

    // draw
    vertexArray->bind();
    glDrawElements(GL_TRIANGLES, indexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);
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

    // setup triangle data and shaders
    init();

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
