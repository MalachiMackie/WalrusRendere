#include "renderer.h"
#include <iostream>

namespace WalrusRenderer
{
    Renderer::Renderer(const RendererSettings& settings)
        : m_settings{settings}
    {
        std::cout << "Created Renderer: " << m_settings.name <<  std::endl;
    }

    void Renderer::Init()
    {
        std::cout << "Initialized Renderer: " << m_settings.name << std::endl;
    }

    int32_t Renderer::Render()
    {
        std::cout << "Rendering" << std::endl;
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
}