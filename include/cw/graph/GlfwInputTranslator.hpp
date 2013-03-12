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
      private:
        cw::core::UnifiedInputHandler & m_inputHandler;
    };
  }
}

#endif
