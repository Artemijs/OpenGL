#ifndef LOADER_H
#define LOADER_H
#include "RawModel.h"
#include <vector>
class Loader{

private:
    std::vector<unsigned>* m_vaos;
    std::vector<unsigned>* m_vbos;
    int createVAO();
    void storeDataInAttributeList(int attributeNumber, std::vector<float>* data);
    void unbindVAO();
    void bindIndicesBuffer(std::vector<int>* indices);
public:
    Loader(){
        m_vaos = new std::vector<unsigned>();
        m_vbos = new std::vector<unsigned>();
    }
    ~Loader(){
        delete m_vaos;
        delete m_vbos;
    }
    RawModel* loadToVAO(std::vector<float>* positions, std::vector<int>* indices);
    void cleanUp(); 
};
#endif
