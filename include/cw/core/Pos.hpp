#ifndef CW_CORE_POS_HPP_INC
#define CW_CORE_POS_HPP_INC

#include <ostream>

#include <cw/core/CommonGeometry.hpp>

namespace cw
{
  namespace core
  {
    constexpr static double PI = 3.14159265359;
    struct Pos
    {
      Pos() : x(0.0), y(0.0) {}
      Pos(double x_, double y_)
        : x(x_), y(y_)
      {}

      double x,y;

      static Pos createFromPolar(double radius, double angle)
      {
        Pos ret;
        ret.x = radius * cos(angle);
        ret.y = radius * sin(angle);
        return ret;
      }
    };

    inline double length(Pos const & p)
    {
      return std::sqrt( p.x*p.x + p.y*p.y );
    }

    // dot product
    inline double operator*(Pos const& l, Pos const& r)
    {
      return l.x * r.x + l.y * r.y;
    }

    // parallel?
    inline bool operator||(Pos const &l, Pos const &r)
    {
      return equals(1.0,
                    std::abs( ( l * r ) / ( length(l)*length(r) ) ) );
    }

    inline bool operator==(Pos const & l, Pos const & r)
    {
      return equals(l.x, r.x) && equals(l.y,r.y);
    }

    // difference vector
    inline Pos operator-(Pos const& l, Pos const & r)
    {
      return Pos(l.x - r.x, l.y - r.y);
    }

    inline std::ostream& operator<<(std::ostream & o, Pos const & pos)
    {
      o << "Pos(" << pos.x << "," << pos.y << ")";
      return o;
    }
  }
}
#endif
