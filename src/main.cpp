#include <iostream>
#include <vector>

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description);
void processInput(GLFWwindow *window);

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    glfwSetErrorCallback(error_callback);

    /* Set GLFW version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Apple hours */
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Detect monitor count */
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count); 
    std::cout << count << " monitor";
    if (count != 1)
        std::cout << "s";
    std::cout << " detected." << std::endl;

    if (count == 0)
    {
        std::cerr << "Exiting...\n" << std::endl;
        glfwTerminate();
        return -1;
    }

     /*
     * I'm only going to implement this for one window now, and I'll try to
     * scale it later...
     */
    std::vector<GLFWwindow*> windows;
    for (int i = 0; i < count; ++i)
    {
        GLFWmonitor* monitor = monitors[i];

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (!mode)
        {
            std::cerr << "Failed to get video mode for monitor " << i << std::endl;
            continue;
        }

        std::string title("Monitor " + std::to_string(i));
        GLFWwindow *window = glfwCreateWindow(mode->width, mode->height,
                                              title.c_str(), monitor, NULL);
        if (!window)
        {
            std::cerr << "Failed to create window for monitor " << i << std::endl;
            continue;
        }

        // Make the context current for this window
        glfwMakeContextCurrent(window);

        // Initialize GLAD for this window's context
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD for window " << i << std::endl;
            glfwDestroyWindow(window);
            continue;
        }
        else
        {
            windows.push_back(window);
        }
    }

    /* Main render loop */
    while (!windows.empty())
    {
        for (auto it = windows.begin(); it != windows.end();)
        {
            GLFWwindow *window = *it;
            processInput(window);

            if (glfwWindowShouldClose(window))
            {
                glfwDestroyWindow(window);
                it = windows.erase(it);
                continue;
            }
            else
            {
                glfwMakeContextCurrent(window);

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glfwSwapBuffers(window);
                ++it;
            }
        }
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
