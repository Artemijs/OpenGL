#include "RawModel.h"

RawModel::RawModel(int vaoID, int vertexCount):
                                    m_vaoID(vaoID),
                                    m_vertexCount(vertexCount){
    
}
int RawModel::getVaoId(){
    return m_vaoID;
}
void RawModel::setVaoId(int id){
    m_vaoID = id;
}
int RawModel::getVertexCount(){
    return m_vertexCount;    
}
void RawModel::setVertexCount(int count){
    m_vertexCount = count;
}

