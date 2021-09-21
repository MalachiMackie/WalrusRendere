#include <iostream>
#include <string>
#include <memory>

#include "renderer.h"

int main(int argc, char *argv[])
{
    std::string name {argc > 1 ? argv[1]: "WalrusRenderer"};

    const std::unique_ptr<WalrusRenderer::Renderer> renderer = std::make_unique<WalrusRenderer::Renderer>(WalrusRenderer::RendererSettings{name});

    int32_t initResult = renderer->Init();
    if (initResult != 0)
    {
        std::cout << "Initializing Renderer Failed with code " << initResult << std::endl;
        return initResult;
    }

    renderer->NewWindow("My Window");
    renderer->Run();

    renderer->Destroy();

    return 0;
}