#ifndef RENDERER_H
#define RENDERER_H

#include <string>

namespace WalrusRenderer
{
    struct RendererSettings {
        std::string name;
    };

    class Renderer {
        public:
            Renderer(const RendererSettings &settings);
            void Init();
            void Run();

        private:
            RendererSettings m_settings;

        private:
            int32_t Render();
    };
}

#endif