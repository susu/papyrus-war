#include <stdexcept>
#include <vector>
#include <algorithm>

#include <GL/glfw.h>

#include <cw/graph/GlfwInputTranslator.hpp>
#include <cw/core/UnifiedInputHandler.hpp>
#include <cw/core/Logger.hpp>

namespace
{
  cw::core::Logger logger("graph");
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
  namespace graph
  {

GlfwInputTranslator::GlfwInputTranslator(cw::core::UnifiedInputHandler & inputHandler)
  : m_inputHandler(inputHandler)
  , m_mouseWheelPos(0)
{}

GlfwInputTranslator::~GlfwInputTranslator()
{}

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
    LOG(DEBUG) << "PRESSED: " << key;
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
  // TODO ENFORCE();
  throw std::logic_error("Cannot interpret key");
}

  }
}
