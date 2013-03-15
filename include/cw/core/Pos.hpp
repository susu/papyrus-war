#ifndef CW_CORE_POS_HPP_INC
#define CW_CORE_POS_HPP_INC

namespace cw
{
  namespace core
  {
    struct Pos
    {
      Pos(double x_, double y_)
        : x(x_), y(y_)
      {}

      double x,y;
    };

    const int PRECISION = 1e-5;

    bool equals(double one, double two)
    {
      return abs(one-two) < PRECISION;
    }

    bool operator==(Pos const & l, Pos const & r)
    {
      return equals(l.x, r.x) && equals(l.y,r.y);
    }

    std::ostream& operator<<(std::ostream & o, Pos const & pos)
    {
      o << "Pos(" << pos.x << "," << pos.y << ")";
      return o;
    }
  }
}
#endif
