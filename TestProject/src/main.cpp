#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <iostream>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

constexpr uint16_t WINDOW_WIDTH = 640;
constexpr uint16_t WINDOW_HEIGHT = 480;

// must be called after SDL window creation
bool initBGFX(SDL_Window* pWindow) {
    
    void* pNativeWindow = nullptr;
    
    SDL_SysWMinfo sys_info;
    SDL_VERSION(&sys_info.version);
    if (SDL_GetWindowWMInfo(pWindow, &sys_info)) {
#if defined(__APPLE__) && defined(__MACH__)
        pNativeWindow = static_cast<void *>(sys_info.info.cocoa.window);
#elif defined(_WIN32) || defined(_WIN64)
        pNativeWindow = static_cast<void *>(sys_info.info.win.window);
#endif
    }
    
    // single threaded
    bgfx::renderFrame();
    
    bgfx::Init bgfxInit;
    
    bgfxInit.platformData.nwh = pNativeWindow;
    bgfxInit.platformData.ndt = nullptr;
    
#if defined(_WIN32) || defined(_WIN64)
    bgfxInit.type = bgfx::RendererType::Direct3D12;
#elif defined(__APPLE__) && defined(__MACH__)
    bgfxInit.type = bgfx::RendererType::Metal;
#endif
    
    auto resolution = bgfx::Resolution();
    resolution.width = WINDOW_WIDTH;
    resolution.height = WINDOW_HEIGHT;
    resolution.reset = BGFX_RESET_MSAA_X16 | BGFX_RESET_VSYNC;
    resolution.format = bgfx::TextureFormat::BGRA8;
    
    bgfxInit.resolution = resolution;
    
    bgfx::init(bgfxInit);
}

int main(int argc, char *argv[])
{
    if(SDL_WasInit(SDL_INIT_VIDEO) != 1) {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "Failed to initialize the SDL2 library\n";
            return -1;
        }
    }
    
    SDL_Window *pWindow = SDL_CreateWindow("SDL2 Window",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           680, 480, 0);
    
    if(pWindow == nullptr)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }
    
    initBGFX(pWindow);
    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    SDL_Event e;
    bool quit = false;
    while (!quit){
        
        bgfx::touch(0);
        
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
        
        bgfx::frame();
    }
    
    bgfx::shutdown();
    SDL_DestroyWindow(pWindow);
}
