//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>//file loader
//math lib
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"
float m_screenWidth = 800.0f;
float m_screenHeight = 600.0f;
GLfloat m_lastX = 400, m_lastY = 300;
GLfloat m_pitch;
GLfloat m_yaw;
GLfloat m_aspect = 45;
GLfloat m_deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat m_lastFrame = 0.0f;  	// Time of last frame
bool keys[1024];
Camera m_camera;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void createCube(GLuint* vertArrObj, GLuint* vertBuffObj);
void createTexture(char* filename,GLuint *textureId);
void doMovement();
int main(){
	//create widnow and context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //using open gl 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//idk what this does
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow * window = glfwCreateWindow(m_screenWidth, m_screenHeight, "OPEN GL LIGHTS", nullptr, nullptr);
	if(window == nullptr){
		std::cout << "failed to create GLFW window"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cout<< "failed to init GLEW"<<std::endl;
	}
	glViewport(0,0, m_screenWidth, m_screenHeight);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback); 

	//shader init
	Shader ourShader( "vertex_shader.vertex", "fragmentShader.fragment");
	//view spaces
	m_camera = Camera();
	glm::mat4 projection;
	projection = glm::perspective(m_aspect, m_screenWidth/m_screenHeight, 0.1f, 100.0f);//glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	glm::mat4 model;

	//create cube data
	GLuint VAO;//remember to delete these
	GLuint VBO;
	createCube(&VAO, &VBO);
	//create cube texture
	GLuint texture;
	createTexture("container.jpg", &texture);
	//game loop
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;  
		doMovement();
		ourShader.Use();//without this the shader wont do anything 		
		//send view spaces to shader
		GLuint modelLoc = glGetUniformLocation(*ourShader.getProgram(),"model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GLuint viewLoc = glGetUniformLocation(*ourShader.getProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera.getView()));
		GLuint projLoc = glGetUniformLocation(*ourShader.getProgram(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//send texture to our shader
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(*ourShader.getProgram(), "ourTexture1"), 0);
	
		glBindVertexArray(VAO);//use cube data
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);//stop using cube data
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
void createCube(GLuint* vertArrObj, GLuint* vertBuffObj){
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, vertArrObj);
	glBindVertexArray((*vertArrObj));
		glGenBuffers(1, vertBuffObj); 
		
		glBindBuffer(GL_ARRAY_BUFFER, (*vertBuffObj));
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);//pos
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));//tex
		glEnableVertexAttribArray(1);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
	if(action == GLFW_PRESS)
	  keys[key] = true;
	else if(action == GLFW_RELEASE)
	  keys[key] = false;  
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){

	GLfloat xoffset = xpos - m_lastX;
	GLfloat yoffset = ypos - m_lastY;
	m_lastX = xpos;
	m_lastY = ypos;
	GLfloat sensitivity = 0.05f;
	xoffset*=sensitivity;
	yoffset*=sensitivity;
	m_yaw   += xoffset;
	m_pitch += yoffset;
	if(m_pitch > 89.0f)
	  m_pitch =  89.0f;
	if(m_pitch < -89.0f)
	  m_pitch = -89.0f;
	glm::vec3 cameraFront;
	cameraFront.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	cameraFront.y = sin(glm::radians(m_pitch)) *-1;
	cameraFront.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	cameraFront = glm::normalize(cameraFront);
	m_camera.setCameraDir(cameraFront);
}
void doMovement(){
	
	if(keys[GLFW_KEY_W]){
		m_camera.move(CameraDir::FORWARD, m_deltaTime);
	}
	if(keys[GLFW_KEY_S]){
		m_camera.move(CameraDir::BACKWARD, m_deltaTime);
	}
	if(keys[GLFW_KEY_A]){
		m_camera.move(CameraDir::LEFT, m_deltaTime);
	}
	if(keys[GLFW_KEY_D]){
		m_camera.move(CameraDir::RIGHT, m_deltaTime);
	}
}
void createTexture(char* filename,GLuint *textureId){
	int width, height;
	unsigned char* image = SOIL_load_image(filename, &width, & height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, textureId);
	glBindTexture(GL_TEXTURE_2D, *textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}