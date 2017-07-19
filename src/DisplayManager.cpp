#include "DisplayManager.h"
#include <iostream>
#include <string>
DisplayManager* DisplayManager::m_instance = NULL;

DisplayManager::DisplayManager(){
    //initialize sdls video subsystem
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"failed to init sdl\n";
    }
    //create window
    m_window = SDL_CreateWindow("temp_lol_name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
    //check that it worked 
    if(!m_window){
        std::cout<<"unable to create window\n";
        checkSDLError(__LINE__); 
    } 
    //create opengl context and attach it to our window
    m_context = SDL_GL_CreateContext(m_window);
    setGLAttribs();
    //makes buffer swap synchronized with montinors vertical refresh
    SDL_GL_SetSwapInterval(0);
    
    #ifndef __APPLE__
        glewExperimental = GL_TRUE;
        glewInit();
    #endif
    std::cout<<"created display\n";
}

DisplayManager* DisplayManager::instance(){
    if(!m_instance)
        m_instance = new DisplayManager();
    return m_instance;
}
SDL_GLContext* DisplayManager::getContext(){
    return &m_context;    
}
SDL_Window* DisplayManager::getWindow(){
    return m_window;
}
 
bool DisplayManager::setGLAttribs(){
    //set opengl version
    //SDL_GL_CONTEXT_CORE GIVES THE NEWEST VERSION AND DISABLES DEPRICATED VERSION
    SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    //TURN ON DOUBLE BUffer with 24 bit z buffer
    //may need to change this to 16 or 32 for "your system"
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return true;

}
void DisplayManager::printSDL_GL_Attribs(){
    int value =0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout<<" SDL_GL_CONTEXT_MAJOR_VERsION : "<<value<<"\n";
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout<<" SDL_GL_CONTEXT_MINOR_VERsION : "<<value<<"\n";

}

void DisplayManager::checkSDLError(int line){
    std::string error = SDL_GetError();
    if(error !=""){
        std::cout<<"SDL error : "<<error<<"\n";
        if(line != -1){
            std::cout<<"\nLine : "<<line<<"\n";
        }
        SDL_ClearError();
    }
}

void DisplayManager::cleanUp(){
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void DisplayManager::update(){
    SDL_GL_SwapWindow(m_window);
}

