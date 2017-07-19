#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>
class ShaderProgram{
private:
    int m_programId;
    int m_vertexShaderId;
    int m_fragmentShaderId;
    int loadShader(std::string filePath, int type);
public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile);

    void start();
    void stop();
    void cleanUp();
    void bindAttribute(int attribute, std::string variableName);
};
#endif
