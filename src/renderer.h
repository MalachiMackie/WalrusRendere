#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <GLFW/glfw3.h>

namespace WalrusRenderer
{
    struct RendererSettings {
        std::string name;
    };

    class Renderer {
        public:
            Renderer(const RendererSettings &settings);
            int32_t Init();
            void Run();
            void Destroy();
            void NewWindow(const std::string& name);

        private:
            RendererSettings m_settings;
            GLFWwindow* m_glfwWindow;
            uint32_t m_vbo;
            uint32_t m_vao;
            uint32_t m_vertexShader;
            uint32_t m_fragmentShader;
            uint32_t m_shaderProgram;

        private:
            int32_t Render();
    };
}

#endif