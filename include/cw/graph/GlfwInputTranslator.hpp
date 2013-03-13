#ifndef CW_GRAPH_GLFW_INPUT_TRANSLATOR_HPP_INC
#define CW_GRAPH_GLFW_INPUT_TRANSLATOR_HPP_INC

namespace cw
{
  namespace core
  {
    class UnifiedInputHandler;
  }
  namespace graph
  {
    class GlfwInputTranslator
    {
      public:
        GlfwInputTranslator( cw::core::UnifiedInputHandler & );
        ~GlfwInputTranslator();

        void mouseMoveEvent(int x, int y);
        void mouseButtonEvent(int btn, int action);
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
        cw::core::UnifiedInputHandler & m_inputHandler;
        MouseState m_mouseState;
    };
  }
}

#endif
