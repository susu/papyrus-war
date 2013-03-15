#ifndef CW_GRAPH_GLFW_INPUT_TRANSLATOR_HPP_INC
#define CW_GRAPH_GLFW_INPUT_TRANSLATOR_HPP_INC

#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace graph
  {
    class GlfwInputTranslator
    {
      public:
        GlfwInputTranslator( cw::core::UnifiedInputHandler & );
        ~GlfwInputTranslator();

        void mouseMoveEvent(int x, int y);
        void mouseButtonEvent(int btn, int action);
        void mouseWheelEvent(int pos);
        void keyEvent(int key, int action);
      private:
        struct MouseState
        {
          int posX;
          int posY;
          bool pressed;
          MouseState()
            : posX(-1)
            , posY(-1)
            , pressed(false)
          {}
        };
        typedef core::UnifiedInputHandler::ScrollDir ScrollDir;

        ScrollDir keyToScrollDir(int key) const;

        cw::core::UnifiedInputHandler & m_inputHandler;
        MouseState m_mouseState;
        int m_mouseWheelPos;
    };
  }
}

#endif
