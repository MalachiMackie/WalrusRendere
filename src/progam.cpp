#include <iostream>
#include "renderer.h"
#include <string>
#include <memory>

int main(int argc, char *argv[])
{
    std::string name {argc > 1 ? argv[1]: "WalrusRenderer"};

    const std::unique_ptr<WalrusRenderer::Renderer> renderer = std::make_unique<WalrusRenderer::Renderer>(WalrusRenderer::RendererSettings{name});

    renderer->Init();
    renderer->Run();

    return 0;
}