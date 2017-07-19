#include "Loader.h"
#include <GL/glew.h>
#include <iostream>

RawModel* Loader::loadToVAO(std::vector<float>* positions, std::vector<int>* indices){
    int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, positions);
    unbindVAO();
    return new RawModel(vaoID, indices->size());
}

int Loader::createVAO(){
    unsigned vaoID = 0;
    glGenVertexArrays(1, &vaoID);
    m_vaos->push_back(vaoID);
    glBindVertexArray(vaoID);
    std::cout<<vaoID<<"\n";
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber,
                     std::vector<float>* data){
    unsigned vboID =0;
    glGenBuffers(1, &vboID);
    m_vbos->push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    std::cout<<"size of vector"<<sizeof(data[0])*data->size()<<"\n";
    glBufferData(GL_ARRAY_BUFFER, sizeof(data[0])*data->size(), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int>* indices){
    unsigned vboID =0;
    glGenBuffers(1, &vboID);
    m_vbos->push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indices->size(), &indices[0], GL_STATIC_DRAW);
}

void Loader::unbindVAO(){
    glBindVertexArray(0);
}

void Loader::cleanUp(){
   for(std::vector<unsigned>::iterator i = m_vaos->begin(); i != m_vaos->end(); ++i){
        glDeleteVertexArrays(1, &(*(i)));
    }
    for(std::vector<unsigned>::iterator i = m_vbos->begin(); i != m_vbos->end(); ++i){
        glDeleteVertexArrays(1, &(*i));
    }
}
