#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Window.h"

void CheckProgramLinking(unsigned int nProgramID);
bool ArrowUpButtonPressed(GLFWwindow* window);
bool ArrowDownButtonPressed(GLFWwindow* window);

float vertices[] = {
    -0.5, -0.5, 0.0,   1.0, 0.0, 0.0, // bottom left 
     0.0, 0.5, 0.0,    0.0, 1.0, 0.0, //  top
     0.5, -0.5, 0.0,   0.0, 0.0, 1.0 // bottom right
};

int main()
{
    Window main_window(1200, 800, "Danny's Window");

    ////// creating a VBO Vertex Buffer Object/////////////////////////
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /////// creating a VAO Vertex Array Object ///////////////////////////
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    Shader shader("../vertex_texture_shader.txt", "../fragment_texture__shader.txt");


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    shader.UseProgram();

    while (!main_window.IsWindowClosed())
    {
        main_window.ProcessInput();
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
   
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        main_window.SwapBuffers();
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
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