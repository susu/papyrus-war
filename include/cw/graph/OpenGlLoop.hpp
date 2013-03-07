#ifndef CW_GRAPH_OPENGL_LOOP_HPP_INC
#define CW_GRAPH_OPENGL_LOOP_HPP_INC

#include <cw/graph/MainLoopInterface.hpp>

namespace cw
{
  namespace graph
  {
    class OpenGlLoop : public MainLoopInterface
    {
      public:
        OpenGlLoop();
        ~OpenGlLoop();

        virtual void run();
    };
  }
}

#endif
