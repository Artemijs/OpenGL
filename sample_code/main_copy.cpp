/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <iostream>
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Window* m_window;
//The frame rate
const int FRAMES_PER_SECOND = 60;

//Event handler
SDL_Event event;

//Rendering flag
bool renderQuad = true;

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    std::string error = SDL_GetError();
    if(error !=""){
        std::cout<<"SDL error : "<<error<<"\n";
        SDL_ClearError();
    }


    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    //Create Window
    m_window =  SDL_CreateWindow("temp_lol_name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
    if(m_window == NULL )
    {
        return false;
    }

    //Enable unicode
    //SDL_EnableUNICODE( SDL_TRUE );

    //Initialize OpenGL
    if( initGL() == false )
    {
        return false;
    }
    SDL_GL_CreateContext(m_window);
    //setGLAttribs();

    //Set caption
    //SDL_WM_SetCaption( "OpenGL Test", NULL );

    return true;
}

void handleKeys( unsigned char key, int x, int y )
{
    //Toggle quad
    if( key == 'q' )
    {
        renderQuad = !renderQuad;
    }
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Render quad
    if( renderQuad == true )
    {
        glBegin( GL_QUADS );
            glVertex2f( -0.5f, -0.5f );
            glVertex2f(  0.5f, -0.5f );
            glVertex2f(  0.5f,  0.5f );
            glVertex2f( -0.5f,  0.5f );
        glEnd();
    }

    //Update screen
    SDL_GL_SwapWindow(m_window);
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char *argv[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //The frame rate regulator
    Timer fps;

	//Wait for user exit
	while( quit == false )
	{
        //Start the frame timer
        fps.start();

        //While there are events to handle
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
                quit = true;
            }
            else if( event.type == SDL_TEXTINPUT )
            {
                //Handle keypress with current mouse position
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                handleKeys( (*event.text.text), x, y );
            }
		}

        //Run frame update
        update();

        //Render frame
        render();

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}

	//Clean up
	clean_up();

	return 0;
}i*/
#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include <iostream>
#include "ShaderProgram.h"
//#include <array>

//from vvvinglprojects
void createSquare(GLuint* vertArrObj, GLuint* vertBuffObj, GLuint* elmBuffObj);


int main(){
    DisplayManager::instance();
    bool loop = true;
    //Loader loader = Loader();
    Renderer renderer = Renderer();
   /* std::vector<std::pair<int, char*>> vertAttrbs = {std::pair<int, char*>{0, "position"}, std::pair<int, char*>{0, "color"}};

    ShaderProgram shader = ShaderProgram("shaders/vertexShader.txt", "shaders/fragmentShader.txt", &vertAttrbs);
        //shader.bindAttribute(0, "position"); 
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
    RawModel* model = loader.loadToVAO(&vertices, &indices); */
    
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



    renderer.prepare();
    while(loop){
        SDL_Event event;
        renderer.prepare();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                loop = false;
        }
        //shader.start();
        //renderer.render(model);
        glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

       /* glBegin( GL_QUADS );
            glVertex2f( -0.5f, -0.5f );
            glVertex2f(  0.5f, -0.5f );
            glVertex2f(  0.5f,  0.5f );
            glVertex2f( -0.5f,  0.5f );
        glEnd();*/

       // shader.stop();
        DisplayManager::instance()->update();
    }
   // delete model;
    //loader.cleanUp();
    //shader.cleanUp();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    DisplayManager::instance()->cleanUp();
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

