#include <cw/opengl/GlfwInputTranslator.hpp>

#include <stdexcept>
#include <vector>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <cw/Enforce.hpp>
#include <cw/core/UnifiedInputHandler.hpp>
#include <cw/core/Logger.hpp>
#include <cw/opengl/GlfwWindow.hpp>
namespace
{
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
  , m_xMouseWheelPos(0)
{}

GlfwInputTranslator::~GlfwInputTranslator()
{}

void GlfwInputTranslator::registerCallbacks(GlfwWindow & window)
{
  using namespace std::placeholders;
  window.setKeyCallback(
      std::bind(&GlfwInputTranslator::keyEvent, this, _1, _2));

  window.setMouseButtonCallback(
      std::bind(&GlfwInputTranslator::mouseButtonEvent, this, _1, _2));

  window.setScrollCallback(
      std::bind(&GlfwInputTranslator::mouseWheelEvent, this, _1, _2));

  window.setCursorMovedCallback(
      std::bind(&GlfwInputTranslator::mouseMoveEvent, this, _1, _2 ));
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

void GlfwInputTranslator::mouseWheelEvent(double xOffset, double yOffset)
{
  if ( xOffset > m_xMouseWheelPos )
  {
    m_inputHandler.zoom( core::UnifiedInputHandler::ZoomDir::IN );
  }
  else if ( xOffset < m_xMouseWheelPos )
  {
    m_inputHandler.zoom( core::UnifiedInputHandler::ZoomDir::OUT );
  }
  m_xMouseWheelPos = xOffset;
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
    LOG_DEBUG("RELEASED: ", key);
    m_inputHandler.stopScroll( keyToScrollDir(key) );
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
