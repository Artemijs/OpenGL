#ifndef RENDERER_H
#define RENDERER_H
#include "RawModel.h"
class Renderer{
public:
    Renderer();
    void prepare();
    void render(RawModel* model);    
};
#endif
