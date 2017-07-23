#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
class Shader{
public:
	GLuint m_programID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
	const GLuint* getProgram(){
		return &m_programID;
	}
};
#endif