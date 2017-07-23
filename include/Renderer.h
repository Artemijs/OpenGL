#ifndef RENDERER_H
#define RENDERER_H
#include "RawModel.h"
class Renderer{
public:
    Renderer();
    void prepare();
    /*
    binds thee provided veertex array and calls glDraw
    */
    void render(RawModel* model);    
};
#endif
