#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>
class DisplayManager{
private:    
    static DisplayManager* m_instance;
    DisplayManager();
    SDL_Window* m_window;
    SDL_GLContext m_context;

    bool setGLAttribs();
    void printSDL_GL_Attribs();
    void checkSDLError(int line = -1);
public:
    void cleanUp();
    void update();

    static DisplayManager* instance();    
    SDL_Window* getWindow();
    SDL_GLContext* getContext();
};

#endif
