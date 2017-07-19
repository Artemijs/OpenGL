#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>
Renderer::Renderer(){}
void Renderer::prepare(){
    glClearColor(0.1, 0.1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::render(RawModel* model){
    //std::cout<<"rednering models id "<<model->getVaoId()<<"\n";
    //std::cout<<"rednering models vcount "<<model->getVertexCount()<<"\n";
    glBindVertexArray(model->getVaoId());
    glEnableVertexAttribArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
