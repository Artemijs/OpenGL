#ifndef RAWMODEL_H
#define RAWMODEL_H
/*
    holds vao id and the vertex count
*/
class RawModel{
private:
    int m_vaoID;
    int m_vertexCount;
public:
    RawModel(int vaoID, int vertexCount);
    int getVaoId();
    void setVaoId(int id);
    int getVertexCount();
    void setVertexCount(int count);
};
#endif
