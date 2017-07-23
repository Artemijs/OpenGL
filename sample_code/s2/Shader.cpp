#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream<< vShaderFile.rdbuf();
		fShaderStream<< fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		//convert stream into glchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//2. compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//vertexshader 
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader
	//vertexshader 
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program
	this->m_programID = glCreateProgram();
	glAttachShader(this->m_programID, vertex);
	glAttachShader(this->m_programID, fragment);
	glLinkProgram(this->m_programID);
	//print linking errors if any
	glGetProgramiv(this->m_programID, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(this->m_programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::Use(){
	glUseProgram(this->m_programID);
}