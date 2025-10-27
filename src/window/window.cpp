#include "window.h"

namespace quant
{

Window::Window(const std::string& title, unsigned int width, unsigned int height) {

    if (!glfwInit())
        std::cout << "Couldn't initialize window" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(glfwWindow == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfwWindow);

    if(glewInit() != GLEW_OK)
        std::cout << "Failed to init GLEW" << std::endl;
}

Window::~Window() {
    glfwTerminate();
}

void Window::loop() {

    while(!glfwWindowShouldClose(glfwWindow)) {
        
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(renderingCallback)
            renderingCallback(this);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }
}

}