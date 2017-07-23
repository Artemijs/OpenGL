/*// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include "Shader.h"
void init();
void initGlewPTRS();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void shaderInit(GLuint* shaderProgram, const char *vertex_path, const char *fragment_path);
void createSquare(GLuint* vertArrObj, GLuint* vertBuffObj, GLuint* elmBuffObj);
//std::string readFile(const char *filePath);
int main(){
	
	init();
	
	GLFWwindow* window = glfwCreateWindow(800,600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	initGlewPTRS();
	glViewport(0, 0, 800, 600);  
	glfwSetKeyCallback(window, key_callback);

	

	Shader ourShader( "vertex_shader.vertex", "fragmentShader.fragment");
	

	
	GLuint VAO;
	GLuint VBO;//cant put these 2 in the function because need to delete them at the end
	GLuint EBO;
	createSquare(&VAO, &VBO, &EBO);
		int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, & height, 0, SOIL_LOAD_RGB);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.Use();

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue)/2)+0.5;
		GLint vertexColorLocation = glGetUniformLocation(*ourShader.getProgram(), "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}
void createSquare(GLuint* vertArrObj, GLuint* vertBuffObj, GLuint* elmBuffObj){
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	}; 
	glGenVertexArrays(1, vertArrObj);
	glBindVertexArray((*vertArrObj));
		glGenBuffers(1, vertBuffObj); 
		glGenBuffers(1, elmBuffObj); 
		
		glBindBuffer(GL_ARRAY_BUFFER, (*vertBuffObj));
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*elmBuffObj));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);
		
		glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void init(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
}
void initGlewPTRS(){
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}*/
/*std::string readFile(const char *filePath){
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	if(!fileStream.is_open()){
		std::cout<<  "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}
	std::string line = "";
	while(!fileStream.eof()){
		std::getline(fileStream, line);
		content.append(line+"\n");
	}
	fileStream.close();
	return content;
}*/

