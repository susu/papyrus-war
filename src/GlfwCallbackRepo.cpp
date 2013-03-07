#include <GL/glfw.h>

#include <cw/graph/GlfwCallbackRepo.hpp>

namespace cw
{
  namespace graph
  {
GlfwCallbackRepo* GlfwCallbackRepo::m_instance = nullptr;

// Singleton related functions
void GlfwCallbackRepo::initialize()
{
  if ( nullptr == m_instance )
  {
    m_instance = new GlfwCallbackRepo;
  }
}

void GlfwCallbackRepo::terminate()
{
  if ( nullptr != m_instance )
  {
    delete m_instance;
    m_instance = nullptr;
  }
}

// actual glfw callbacks
void GLFWCALL GlfwCallbackRepo::mouseButton( int button, int action )
{
  instance().notify( MOUSE_BUTTON, button, action );
}

// methods
GlfwCallbackRepo::GlfwCallbackRepo()
  : m_registeredCallbacks( MAX )
{
  glfwSetMouseButtonCallback( &GlfwCallbackRepo::mouseButton );
}

void GlfwCallbackRepo::notify( EventType event, int arg1, int arg2 ) const
{
  for( auto const & cbFunction : m_registeredCallbacks[ event ] )
  {
    cbFunction(arg1, arg2);
  }
}

void GlfwCallbackRepo::registerCb( EventType e, CallbackFunctionType cb )
{
  m_registeredCallbacks[ e ].push_back( cb );
}

  }
}

