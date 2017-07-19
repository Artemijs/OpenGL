#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include <iostream>
#include "ShaderProgram.h"
//#include <array>
int main(){
    DisplayManager::instance();
    bool loop = true;
    Loader loader = Loader();
    Renderer renderer = Renderer();
    ShaderProgram shader = ShaderProgram("shaders/vertexShader.txt", "shaders/fragmentShader.txt");
    shader.bindAttribute(0, "position"); 
    std::vector<float> vertices;
    vertices.insert(vertices.begin(),{
        -0.5f, 0.5f, -0.0f,
        -0.5f, -0.5f, -0.0f,

        0.5f, -0.5f, -0.0f,
        0.5f, 0.5f, -0.0f,
    });
    std::vector<int> indices;
    indices.insert(indices.begin(),{
        0, 1, 3,
        3, 1, 2
    });
    renderer.prepare();
    RawModel* model = loader.loadToVAO(&vertices, &indices); 
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
