#ifndef CW_GRAPH_MAIN_LOOP_INTERFACE_HPP_INC
#define CW_GRAPH_MAIN_LOOP_INTERFACE_HPP_INC

namespace cw
{
  namespace graph
  {
    class MainLoopInterface
    {
      public:
        virtual ~MainLoopInterface()
        {}

        virtual void run() = 0;
    };
  }
}

#endif
