#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace WalrusRenderer
{
    static void error_callback(int errorCode, const char* description)
    {
        std::cerr << "Glfw error: " << errorCode << "; " << description << std::endl;
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        std::cout << (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    Renderer::Renderer(const RendererSettings& settings)
        : m_settings{settings}
    {
        std::cout << "Created Renderer: " << m_settings.name <<  std::endl;
    }

    int32_t Renderer::Init()
    {
        std::cout << "Initialing Renderer: " << m_settings.name << std::endl;

        if (!glfwInit()) {
            return 1;
        }

        glfwSetErrorCallback(error_callback);

        std::cout << "Initialized Renderer: " << m_settings.name << std::endl;

        return 0;
    }

    int32_t Renderer::Render()
    {
        if (glfwWindowShouldClose(m_glfwWindow))
        {
            return 1;
        }

        glUseProgram(m_shaderProgram);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(m_glfwWindow);
        glfwPollEvents();
        return 0;
    }

    void Renderer::Run()
    {
        int32_t result{0};
        do
        {
            result = Render();
        }
        while(result == 0);
    }

    void Renderer::NewWindow(const std::string& name)
    {
        GLFWwindow* window = glfwCreateWindow(640, 480, name.c_str(), NULL, NULL);

        if (!window)
        {
            std::cerr << "GLFW window creation failed" << std::endl;
        }

        m_glfwWindow = window;
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSetKeyCallback(window, key_callback);

        int width, height;
        glfwGetFramebufferSize(m_glfwWindow, &width, &height);
        glViewport(0, 0, width, height);
        glfwSwapInterval(1);

        // vertex buffer stuff
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(m_vertexShader);

        int  success;
        char infoLog[512];
        glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        std::cout << "SHADER::VERTEX::COMPILATION_SUCCEEDED" << std::endl;

        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n";

        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(m_fragmentShader);

        glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        std::cout << "SHADER::FRAGMENT::COMPILATION_SUCCEEDED" << std::endl;

        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, m_vertexShader);
        glAttachShader(m_shaderProgram, m_fragmentShader);
        glLinkProgram(m_shaderProgram);

        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            std::cout << "PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        std::cout << "PROGRAM::LINKING_SUCCEEDED" << std::endl;

        glUseProgram(m_shaderProgram);
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenVertexArrays(1, &m_vao);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


    }

    void Renderer::Destroy()
    {
        if (m_glfwWindow)
            glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
    }
}
