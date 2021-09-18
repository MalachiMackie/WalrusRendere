#include <iostream>
#include <string>
#include <memory>

#include "renderer.h"
#include <GLFW/glfw3.h>

int main(int argc, char *argv[])
{
    std::string name {argc > 1 ? argv[1]: "WalrusRenderer"};

    const std::unique_ptr<WalrusRenderer::Renderer> renderer = std::make_unique<WalrusRenderer::Renderer>(WalrusRenderer::RendererSettings{name});

    renderer->Init();
    renderer->Run();

    return 0;
}