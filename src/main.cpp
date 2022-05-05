#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    glm::vec3 pos;
    glm::vec3 color;
} vertexData;
std::vector<vertexData> modelData;

GLuint loadVertexData()
{
    modelData.push_back({
        glm::vec3(0.0f, 3.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f)
    });
    modelData.push_back({
        glm::vec3(-3.0f, -3.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 1.0f)
    });
    modelData.push_back({
        glm::vec3(3.0f, -3.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 1.0f)
    });

    GLuint triangleVBO[0];
    glGenBuffers(1, triangleVBO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO[0]);
    int numBytes =modelData.size() * sizeof(vertexData);
    glBufferData(GL_ARRAY_BUFFER, numBytes, modelData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO[0]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *) (3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    return triangleVBO[0];
}

int main(int argc, char *argv[])
{
    // initialize glfw
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

    // initialize glew
    if(glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    // set viewport parameters
    int nx, ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // load shaders
    Shader shader;
    shader.fromFile("./resources/shaders/shader.vert", "./resources/shaders/shader.frag");
    GLuint pMatID = shader.getProjectionLocation();

    // load triangle data
    GLuint VAO = loadVertexData();

    // set projection matrix
    glm::mat4 projMatrix = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -10.0f, 10.0f);


    // main loop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

	glUniformMatrix4fv(pMatID, 1, GL_FALSE, glm::value_ptr(projMatrix));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        shader.clear();

        glfwSwapBuffers(window);

        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
