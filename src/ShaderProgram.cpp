#include "ShaderProgram.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile){
    m_vertexShaderId = loadShader(vertexFile, GL_VERTEX_SHADER);
    m_fragmentShaderId = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    m_programId = glCreateProgram();
    glAttachShader(m_programId, m_vertexShaderId);
    glAttachShader(m_programId, m_fragmentShaderId);
    glLinkProgram(m_programId);
    glValidateProgram(m_programId);
    
}

/*
    load shader from filees and return shader id
*/
int ShaderProgram::loadShader(std::string filePath, int type){
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string code;
    std::ifstream file;
    // ensures ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        // Open files
        file.open(filePath);
        std::stringstream fileStream;
        // Read file's buffer contents into streams
        fileStream<< file.rdbuf();
        //close file handlers
        file.close();
        //convert stream into glchar array
        code = fileStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = code.c_str();

    //2. compile shaders
    GLuint shaderId;
    GLint success;
    GLchar infoLog[512];

    //vertexshader 
    shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &vShaderCode, NULL);
    glCompileShader(shaderId);
    //print compile errors if any
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"+filePath+"\n" << infoLog << std::endl;
    
    }
    return shaderId;
}
void ShaderProgram::start(){
    glUseProgram(m_programId);    
}
void ShaderProgram::stop(){
     glUseProgram(0);
}
void ShaderProgram::cleanUp(){
    stop();
    glDetachShader(m_programId, m_vertexShaderId);
    glDetachShader(m_programId, m_fragmentShaderId);
    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);
    glDeleteProgram(m_programId);
}

/*
    THIS IS A PROBLEM
*/
void ShaderProgram::bindAttribute(int attribute, char* variableName){
    //glBindAttribLocation(m_programId, attribute, variableName);

    GLint posLoc = glGetUniformLocation(m_programId, variableName);
    glUniform3f( posLoc, 0, 0, 1);
    GLint colorLoc = glGetUniformLocation(m_programId, variableName);
    glUniform3f( colorLoc, 1.0, 1.0, 1.0);

}
