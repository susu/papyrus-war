#ifndef CW_GRAPH_SCREEN_SIZE_HPP_INC
#define CW_GRAPH_SCREEN_SIZE_HPP_INC

namespace cw
{
  namespace graph
  {
    struct ScreenSize
    {
      ScreenSize( unsigned int X, unsigned int Y )
        : x(X), y(Y)
      {}
      unsigned int x, y;
    };
    
  }
}

#endif
