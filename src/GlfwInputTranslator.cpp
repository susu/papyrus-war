#include <stdexcept>
#include <vector>
#include <algorithm>

#include <GL/glfw.h>

#include <cw/Enforce.hpp>
#include <cw/opengl/GlfwInputTranslator.hpp>

#include <cw/core/UnifiedInputHandler.hpp>
#include <cw/core/Logger.hpp>

namespace
{
  cw::core::Logger logger("opengl");
  const std::vector<int> VALID_SCROLL_KEYS =
  {
    GLFW_KEY_LEFT,
    GLFW_KEY_RIGHT,
    GLFW_KEY_UP,
    GLFW_KEY_DOWN
  };
}

namespace cw
{
  namespace opengl
  {

GlfwInputTranslator::GlfwInputTranslator(cw::core::UnifiedInputHandler & inputHandler)
  : m_inputHandler(inputHandler)
  , m_mouseWheelPos(0)
{}

GlfwInputTranslator::~GlfwInputTranslator()
{}

template<typename MemPtr>
void GlfwInputTranslator::regCb( graph::CallbackRepo & repo,
                                 graph::CallbackRepo::EventType a,
                                 MemPtr method )
{
  using namespace std::placeholders;
  repo.registerCallback( a, std::bind( method, std::ref(*this), _1, _2 ) );
}

void GlfwInputTranslator::registerCallbacks( graph::CallbackRepo & repo )
{
  using graph::CallbackRepo;
  regCb(repo, CallbackRepo::MOUSE_BUTTON, &GlfwInputTranslator::mouseButtonEvent );
  regCb(repo, CallbackRepo::MOUSE_POS,    &GlfwInputTranslator::mouseMoveEvent );
  regCb(repo, CallbackRepo::KEY_CALLBACK, &GlfwInputTranslator::keyEvent );

  repo.registerCallback( CallbackRepo::MOUSE_WHEEL,
  [this](int wheelPos, int)
  {
    mouseWheelEvent(wheelPos);
  });
}

void GlfwInputTranslator::mouseMoveEvent(int x, int y)
{
  m_mouseState.posX = x;
  m_mouseState.posY = y;
}

void GlfwInputTranslator::mouseButtonEvent(int btn, int action)
{
  // if (m_lastMouseX < 0 || m_lastMouseY < 0)
  // {
  //   return;
  // }
  if ( GLFW_MOUSE_BUTTON_LEFT == btn )
  {
    if ( GLFW_PRESS == action )
    {
      m_mouseState.pressed = true;
    }
    if ( GLFW_RELEASE == action && m_mouseState.pressed )
    {
      m_inputHandler.clickedAt( m_mouseState.posX, m_mouseState.posY );
      //m_mouseState.pressed = false;
    }
  }
}

void GlfwInputTranslator::mouseWheelEvent(int pos)
{
  if ( pos > m_mouseWheelPos )
  {
    m_inputHandler.zoom( core::UnifiedInputHandler::ZoomDir::IN );
  }
  else if ( pos < m_mouseWheelPos )
  {
    m_inputHandler.zoom( core::UnifiedInputHandler::ZoomDir::OUT );
  }
  m_mouseWheelPos = pos;
}

bool isScrollKey(int k)
{
  return std::end(VALID_SCROLL_KEYS) !=
         std::find( std::begin(VALID_SCROLL_KEYS), std::end(VALID_SCROLL_KEYS), k );
}

void GlfwInputTranslator::keyEvent(int key, int action)
{
  if ( !isScrollKey(key) )
  {
    return;
  }
  if ( GLFW_PRESS == action )
  {
    LOG_DEBUG("PRESSED: ", key);
    m_inputHandler.startScroll( keyToScrollDir(key) );
  }
  else if ( GLFW_RELEASE == action )
  {
    m_inputHandler.stopScroll();
  }
}

GlfwInputTranslator::ScrollDir GlfwInputTranslator::keyToScrollDir(int key) const
{
  switch(key)
  {
    case GLFW_KEY_LEFT:  return ScrollDir::LEFT;
    case GLFW_KEY_RIGHT: return ScrollDir::RIGHT;
    case GLFW_KEY_UP:    return ScrollDir::UP;
    case GLFW_KEY_DOWN:  return ScrollDir::DOWN;
  }
  ENFORCE(false, "Cannot interpret key!");
  throw "unreachable";
}

  }
}
