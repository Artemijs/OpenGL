#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include <iostream>
#include <SDL_image.h>
#include "ShaderProgram.h"

int main(){
    //init sdl window and context
    DisplayManager::instance();
    bool loop = true;
    //manages loading models into memroy, va and vbo generation
    Loader loader = Loader();
    //does the gldrawelements
    Renderer renderer = Renderer();
    ShaderProgram shader = ShaderProgram("vertex_shader.vertex", "fragment_shader.frag");
    //clears the screen
    renderer.prepare();
    
    std::vector<float> vertices;
    vertices.insert(vertices.begin(),{
        -0.5f, 0.5f, -0.0f,
        -0.5f, -0.5f, -0.0f,

        0.5f, -0.5f, -0.0f,
        0.5f, 0.5f, -0.0f,
    });
    std::vector<GLuint> indices;
    indices.insert(indices.begin(),{
        0, 1, 3,
        3, 1, 2
    }); 
    RawModel* model = loader.loadToVAO(&vertices, &indices); 

    //sdl
    //SDL_Surface* image=  IMG_Load("container.jpg");   
    
    /*GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
    
    //SOIL_free_image_data(image);
    
	glBindTexture(GL_TEXTURE_2D, 0);
    */


    renderer.prepare();
    while(loop){
        SDL_Event event;
        renderer.prepare();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                loop = false;
        }
        shader.start();
        renderer.render(model);
        shader.stop();
        DisplayManager::instance()->update();
    }
    delete model;
    loader.cleanUp();
    shader.cleanUp();
    DisplayManager::instance()->cleanUp();
    return 0;
}

