#ifndef CW_OPENGL_OPENGL_LOOP_HPP_INC
#define CW_OPENGL_OPENGL_LOOP_HPP_INC

#include <cw/graph/MainLoopInterface.hpp>
#include <cw/opengl/GlfwWindow.hpp>

namespace cw
{
  namespace opengl
  {
    // GOD class
    class OpenGlLoop : public graph::MainLoopInterface
    {
      public:
        OpenGlLoop();
        ~OpenGlLoop();

        virtual void run();
      private:
        graph::ScreenSize m_screenSize;
        GlfwWindow m_window;

    };
  }
}

#endif
