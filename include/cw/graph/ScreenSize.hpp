#ifndef CW_GRAPH_SCREEN_SIZE_HPP_INC
#define CW_GRAPH_SCREEN_SIZE_HPP_INC

#include <iostream>

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
    

    inline std::ostream& operator<<(std::ostream & o, const ScreenSize & scr)
    {
      return o << "ScreenSize(" << scr.x << "x" << scr.y << ")";
    }
  }
}

#endif
