#ifndef LOADER_H
#define LOADER_H
#include "RawModel.h"
#include <vector>
#include <GL/glew.h>

/*
    manages vbo, vao binding and deletion 
*/
class Loader{

private:
    //these store ids and uses them to delete vbos from memory
    std::vector<unsigned>* m_vaos;
    std::vector<unsigned>* m_vbos;
    //theese functions are private because the VAO neeeds to be bound for them to do thee thing properly
    //create and bind vao
    int createVAO();
    //create vbo and store as vertex attribute
    void storeDataInAttributeList(int attributeNumber, std::vector<float>* data);
    void unbindVAO();
    //create a vbo and store not using vertex attribute
    void bindIndicesBuffer(std::vector<GLuint>* indices);
public:
    Loader(){
        m_vaos = new std::vector<unsigned>();
        m_vbos = new std::vector<unsigned>();
    }
    ~Loader(){
        delete m_vaos;
        delete m_vbos;
    }
    RawModel* loadToVAO(std::vector<float>* positions, std::vector<GLuint>* indices);
    void cleanUp(); 
};
#endif
