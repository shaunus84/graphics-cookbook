#include "RendererBase.h"

RendererBase::~RendererBase() {
    
    for(auto uniform : uniforms_){
        bgfx::destroy(uniform.second);
    }
    
    for(auto framebuffer : framebuffers_) {
        bgfx::destroy(framebuffer);
    }
}

void RendererBase::beginRenderPass()
{
    //bgfx::submit(passID);
}
