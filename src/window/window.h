#pragma once

#include <iostream>
#include <functional>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

namespace quant
{

class Window {
public:
    using InputCallback = std::function<void(Window*)>;
    using ResizeCallback = std::function<void(Window*, int, int)>;
    using RenderingCallback = std::function<void(Window*)>;
private:
    GLFWwindow* glfwWindow;
    InputCallback inputCallback;
    ResizeCallback resizeCallback;
    RenderingCallback renderingCallback;
public:
    Window(const std::string& title, unsigned int width, unsigned int height);
    Window() = default;
    ~Window();
private:
    static void processInput(GLFWwindow* window);
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
public:
    void loop();
public:
    inline void setInputCallback(const InputCallback& InputCallback) {
        this->inputCallback = inputCallback;
    }

    inline void setResizeCallback(const ResizeCallback& resizeCallback) {
        this->resizeCallback = resizeCallback;
    }

    inline void setRenderingCallback(const RenderingCallback& renderingCallback) {
        this->renderingCallback = renderingCallback;
    }
public:
    inline GLFWwindow* getGlfwWindow() const {
        return glfwWindow;
    }
};

}