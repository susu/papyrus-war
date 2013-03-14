#include <GL/glfw.h>

#include <cw/graph/GlfwInputTranslator.hpp>
#include <cw/core/UnifiedInputHandler.hpp>

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

  }
}
