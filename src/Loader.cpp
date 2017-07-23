#include "Loader.h"
#include <GL/glew.h>
#include <iostream>

RawModel* Loader::loadToVAO(std::vector<float>* positions, std::vector<GLuint>* indices){
    int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, positions);
    unbindVAO();
    return new RawModel(vaoID, indices->size());
}
//generates and binds vertex arrays
//returns uint id
int Loader::createVAO(){
    unsigned vaoID = 0;
    glGenVertexArrays(1, &vaoID);
    m_vaos->push_back(vaoID);
    glBindVertexArray(vaoID);
    std::cout<<vaoID<<"\n";
    return vaoID;
}
/*
creates a vbo, fills it with data and stores it in a vao at attributeNumber
*/
void Loader::storeDataInAttributeList(int attributeNumber,
                     std::vector<float>* data){
    unsigned vboID =0;
    glGenBuffers(1, &vboID);
    m_vbos->push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data->size()*sizeof(data[0]), data->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*
stores indices in vao
i dont know why it doesnt use vertex attribute pointer
*/
void Loader::bindIndicesBuffer(std::vector<GLuint>* indices){
    unsigned vboID =0;
    glGenBuffers(1, &vboID);
    m_vbos->push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(indices[0]), indices->data(), GL_STATIC_DRAW);
}

void Loader::unbindVAO(){
    glBindVertexArray(0);
}

//delete thee vaos and vbos
void Loader::cleanUp(){
   for(std::vector<unsigned>::iterator i = m_vaos->begin(); i != m_vaos->end(); ++i){
        glDeleteVertexArrays(1, &(*(i)));
    }
    for(std::vector<unsigned>::iterator i = m_vbos->begin(); i != m_vbos->end(); ++i){
        glDeleteVertexArrays(1, &(*i));
    }
}
