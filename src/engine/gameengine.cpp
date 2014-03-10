#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <engine/gameengine.h>
#include <engine/gamestate.h>
const char * title = "Ultra Game";

/*
 * Initializes the "global" data for the game.
 */
int GameEngine::Init()
{
  if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    return 1;

  window_ = SDL_CreateWindow( title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              SDL_WINDOW_OPENGL);

  context_ = SDL_GL_CreateContext(window_);
  glewExperimental = GL_TRUE;
  CheckGLSupport(glewInit());

  return 0;
}

/*
 * ChangeState deactivates and pops the state at the top of the stack.
 * It pushes a new state onto the stack and initializes it.
 */
void GameEngine::ChangeState(GameState *state)
{
  //change the top state with new one.
  if (!state_stack_.empty())
  {
    state_stack_.top()->Cleanup();
    state_stack_.pop();
  }

  //store and init new state
  state_stack_.push(state);
  state_stack_.top()->Init();
}

/*
 * PushState pauses the state on the top of the stack.
 * Then it pushes a new state onto the stack and initializes it.
 */
void GameEngine::PushState(GameState *state)
{
  //pause the current state
  if (!state_stack_.empty())
    state_stack_.top()->Pause();

  //store and init new state
  state_stack_.push(state);
  state_stack_.top()->Init();
}

/*
 * PopState deactivates the top state, and pops it off the stack.
 * The game then continues from the next state in the stack.
 */
void GameEngine::PopState()
{
  //pause the current state
  if (!state_stack_.empty())
  {
    state_stack_.top()->Cleanup();
    state_stack_.pop();
  }

  //store and init new state
  if (!state_stack_.empty())
    state_stack_.top()->Resume();
}

//The following functions wrap the game state events, update, and render
//functions.
void GameEngine::HandleEvents()
{
  state_stack_.top()->HandleEvents(this);
}

void GameEngine::Update()
{
  state_stack_.top()->Update(this);
}

void GameEngine::Render()
{
  state_stack_.top()->Render(this);
}
/*
 * Cleanup makes sure all the states, contexts, and windows are deleted
 */
void GameEngine::Cleanup()
{
  while (!state_stack_.empty())
  {
    state_stack_.top()->Cleanup();
    state_stack_.pop();
  }

  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

/*
 * Checks whether or not GLEW initialized correctly.
 * Also checks OpenGL version, shader/array/buffer support.
 * TODO GOOD LOGGING DESIGN
 */
void GameEngine::CheckGLSupport(GLenum error)
{
  if (error != GLEW_OK)
  {
    std::cout << "GLEW initialization error: " << glewGetErrorString(error)
      << "\n";
  }

  if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    std::cout << "OpenGL Shaders Supported.\n";
  else
    std::cout << "OpenGL Shaders Not Supported.\n";

  if (GLEW_ARB_vertex_array_object)
    std::cout << "OpenGL Vertex Array Objects Supported.\n";
  else
    std::cout << "OpenGL Vertex Array Objects Not Supported.\n";

  if (GLEW_ARB_vertex_buffer_object)
    std::cout << "OpenGL Vertex Buffer Objects Supported.\n";
  else
    std::cout << "OpenGL Vertex Buffer Objects Not Supported.\n";

  std::cout << "Shading Language version is: "
    << glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) << "\n";
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
}

