#pragma once
#include <string>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


class Window
{
public:
	Window(int window_width, int window_height, const std::string& window_name);
	virtual ~Window();

	bool IsWindowClosed();
	void SwapBuffers();
	void TerminatedWindow();
	void ProcessInput();
private:
	void InitGLFW();
	int InitGLAD();

	GLFWwindow* gl_window = nullptr;
};

