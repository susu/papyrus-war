#ifndef CW_OPENGL_GLFW_INPUT_TRANSLATOR_HPP_INC
#define CW_OPENGL_GLFW_INPUT_TRANSLATOR_HPP_INC

#include <cw/core/UnifiedInputHandler.hpp>
#include <cw/graph/CallbackRepo.hpp>

namespace cw
{
  namespace opengl
  {
    class GlfwInputTranslator
    {
      public:
        GlfwInputTranslator( cw::core::UnifiedInputHandler & );
        ~GlfwInputTranslator();

        GlfwInputTranslator(GlfwInputTranslator&) = delete;
        GlfwInputTranslator(GlfwInputTranslator&&) = delete;
        void operator=(GlfwInputTranslator) = delete;

        void mouseMoveEvent(int x, int y);
        void mouseButtonEvent(int btn, int action);
        void mouseWheelEvent(int pos);
        void keyEvent(int key, int action);

        void registerCallbacks( graph::CallbackRepo & repo );
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
        typedef core::ScrollDir ScrollDir;

        ScrollDir keyToScrollDir(int key) const;

        template<typename MemPtr>
        void regCb( graph::CallbackRepo & repo, graph::CallbackRepo::EventType a, MemPtr method );

        cw::core::UnifiedInputHandler & m_inputHandler;
        MouseState m_mouseState;
        int m_mouseWheelPos;
    };
  }
}

#endif
