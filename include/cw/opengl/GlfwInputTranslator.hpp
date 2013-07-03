#ifndef CW_OPENGL_GLFW_INPUT_TRANSLATOR_HPP_INC
#define CW_OPENGL_GLFW_INPUT_TRANSLATOR_HPP_INC

#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace opengl
  {
    class GlfwWindow;
    class GlfwInputTranslator
    {
      public:
        GlfwInputTranslator( cw::core::UnifiedInputHandler & );
        ~GlfwInputTranslator();

        void mouseMoveEvent(int x, int y);
        void mouseButtonEvent(int btn, int action);
        void mouseWheelEvent(double xOffset, double yOffset);
        void keyEvent(int key, int action);

        void registerCallbacks(GlfwWindow & window);
      private:
        GlfwInputTranslator(GlfwInputTranslator&);
        GlfwInputTranslator(GlfwInputTranslator&&);
        void operator=(GlfwInputTranslator);

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
        typedef core::ScrollDir ScrollDir;

        ScrollDir keyToScrollDir(int key) const;

        cw::core::UnifiedInputHandler & m_inputHandler;
        MouseState m_mouseState;
        double m_xMouseWheelPos;
    };
  }
}

#endif
