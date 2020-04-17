#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"

void InitGLFW();
int InitGlad();
void CheckProgramLinking(unsigned int nProgramID);
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
bool ArrowUpButtonPressed(GLFWwindow* window);
bool ArrowDownButtonPressed(GLFWwindow* window);

float vertices[] = {
    -0.5, -0.5, 0.0,   1.0, 0.0, 0.0, // bottom left 
     0.0, 0.5, 0.0,    0.0, 1.0, 0.0, //  top
     0.5, -0.5, 0.0,   0.0, 0.0, 1.0 // bottom right
};

int main()
{
    InitGLFW();

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Danny's Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (InitGlad() < 0)
    {
        std::cout << "Glad is not inited !!!" << std::endl;
    }

    glViewport(0, 0, 1200, 800);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ////// creating a VBO Vertex Buffer Object/////////////////////////
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /////// creating a VAO Vertex Array Object ///////////////////////////
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    Shader shader("../vertexShader.txt", "../fragmentShader.txt");


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    shader.UseProgram();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
   
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void InitGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CheckProgramLinking(unsigned int nProgramID)
{
    int succes;
    char infoLog[512];
    glGetProgramiv(nProgramID, GL_LINK_STATUS, &succes);
    if (!succes)
    {
        glGetProgramInfoLog(nProgramID, 512, NULL, infoLog);
        std::cout << "Program with ID:" << nProgramID << " can not be linked : " << infoLog << std::endl;
    }
}

bool ArrowUpButtonPressed(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        return true;
}

bool ArrowDownButtonPressed(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        return true;
}