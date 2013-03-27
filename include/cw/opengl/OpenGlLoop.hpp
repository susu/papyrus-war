#ifndef CW_OPENGL_OPENGL_LOOP_HPP_INC
#define CW_OPENGL_OPENGL_LOOP_HPP_INC

#include <cw/graph/MainLoopInterface.hpp>

namespace cw
{
  namespace opengl
  {
    class OpenGlLoop : public graph::MainLoopInterface
    {
      public:
        OpenGlLoop();
        ~OpenGlLoop();

        virtual void run();
    };
  }
}

#endif
