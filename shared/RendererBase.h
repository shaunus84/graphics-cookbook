#pragma once
#include <bgfx/bgfx.h>
#include <vector>
#include <unordered_map>
#include <string>

class RendererBase {
  
public:
    
    explicit RendererBase(bgfx::TextureHandle depthTexture);
    virtual ~RendererBase();
    
    virtual void fillCommandBuffer();
    
    inline bgfx::TextureHandle getDepthTexture() const { return depthTexture_; }
    
protected:
    
    void beginRenderPass();
    bool createUniforms();
    
    uint16_t framebufferWidth_{0};
    uint16_t framebufferHeight_{0};
    
    bgfx::TextureHandle depthTexture_{bgfx::kInvalidHandle};
    std::vector<bgfx::FrameBufferHandle> framebuffers_;
    
    uint16_t passID{0};
    
    std::unordered_map<std::string, bgfx::UniformHandle> uniforms_;
};
