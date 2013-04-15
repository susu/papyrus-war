#ifndef CW_CORE_POS_HPP_INC
#define CW_CORE_POS_HPP_INC

#include <ostream>

#include <cw/core/CommonGeometry.hpp>

namespace cw
{
  namespace core
  {
    struct Pos
    {
      Pos() : x(0.0), y(0.0) {}
      Pos(double x_, double y_)
        : x(x_), y(y_)
      {}

      double x,y;
    };

    inline bool operator==(Pos const & l, Pos const & r)
    {
      return equals(l.x, r.x) && equals(l.y,r.y);
    }

    inline std::ostream& operator<<(std::ostream & o, Pos const & pos)
    {
      o << "Pos(" << pos.x << "," << pos.y << ")";
      return o;
    }
  }
}
#endif
