#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>
/*
    loads shader from files located in
    : /build/

*/
class ShaderProgram{
private:
    int m_programId;
    int m_vertexShaderId;
    int m_fragmentShaderId;
    int loadShader(std::string filePath, int type);
   /*
    this is a PROBLEM because it needs to know what type to use
    uniform3f or uniform4f etc
    */ 
    void bindAttribute(int attribute, char* variableeName);

public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile);

    void start();
    void stop();
    void cleanUp();
    };
#endif
