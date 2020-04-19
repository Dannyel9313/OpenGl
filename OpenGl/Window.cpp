#include "Window.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int window_width, int window_height, const std::string& window_name)
{
    InitGLFW();

    gl_window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    if (gl_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(gl_window);

    if (InitGLAD() < 0)
    {
        std::cout << "Glad is not inited !!!" << std::endl;
    }

    glViewport(0, 0, 1200, 800);

    glfwSetFramebufferSizeCallback(gl_window, framebuffer_size_callback);
}

Window::~Window()
{
}

void Window::InitGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int Window::InitGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

bool Window::IsWindowClosed()
{
    return glfwWindowShouldClose(gl_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(gl_window);
}

void Window::TerminatedWindow()
{
    glfwTerminate();
}

void Window::ProcessInput()
{
        if (glfwGetKey(gl_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(gl_window, true);
}