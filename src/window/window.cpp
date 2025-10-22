#include "window.h"

namespace quant
{

Window::Window(const std::string& title, unsigned int width, unsigned int height) {

    if (!glfwInit())
        std::cout << "Couldn't initialize window" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(glfwWindow == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, Window::frameBufferSizeCallback);

    if(glewInit() != GLEW_OK)
        std::cout << "Failed to init GLEW" << std::endl;
}

Window::~Window() {
    glfwTerminate();
}

void Window::processInput(GLFWwindow* window) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->inputCallback) {
        self->inputCallback(self);
    }
}

void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->resizeCallback) {
        self->resizeCallback(self, width, height);
    }
}

void Window::loop() {

    while(!glfwWindowShouldClose(glfwWindow)) {

        Window::processInput(glfwWindow); 

        if(renderingCallback)
            renderingCallback(this);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }
}

}