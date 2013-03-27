#include <GL/glfw.h>

#include <cw/opengl/GlfwCallbackRepo.hpp>
#include <cw/core/Logger.hpp>

namespace
{
  cw::core::Logger logger("opengl");
}

namespace cw
{
  namespace opengl
  {
GlfwCallbackRepo* GlfwCallbackRepo::m_instance = nullptr;

// Singleton related functions
void GlfwCallbackRepo::initialize()
{
  if ( nullptr == m_instance )
  {
    m_instance = new GlfwCallbackRepo;
    m_instance->initGlfwCallbacks();
  }
  LOG(DEBUG) << "GlfwCallbackRepo initialized.";
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

void GLFWCALL GlfwCallbackRepo::keyCallback( int key, int action )
{
  instance().notify( KEY_CALLBACK, key, action );
}

void GLFWCALL GlfwCallbackRepo::mousePosCallback( int x, int y )
{
  instance().notify( MOUSE_POS, x, y );
}

void GLFWCALL GlfwCallbackRepo::mouseWheelCallback( int x )
{
  instance().notify( MOUSE_WHEEL, x, 0 );
}

// methods
GlfwCallbackRepo::GlfwCallbackRepo()
  : m_registeredCallbacks( MAX )
{
}

void GlfwCallbackRepo::notify( EventType event, int arg1, int arg2 ) const
{
  for( auto const & cbFunction : m_registeredCallbacks[ event ] )
  {
    cbFunction(arg1, arg2);
  }
}

void GlfwCallbackRepo::registerCallback( EventType e, CallbackFunctionType cb )
{
  m_registeredCallbacks[ e ].push_back( cb );
}

void GlfwCallbackRepo::initGlfwCallbacks() const
{
  glfwSetMouseButtonCallback( &GlfwCallbackRepo::mouseButton );
  glfwSetKeyCallback( &keyCallback );
  glfwSetMousePosCallback( &mousePosCallback );
  glfwSetMouseWheelCallback( &mouseWheelCallback );
}


  }
}

