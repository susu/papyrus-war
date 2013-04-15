#ifndef CW_CORE_COMMON_GEOMETRY_HPP_INC
#define CW_CORE_COMMON_GEOMETRY_HPP_INC

#include <cmath>

namespace cw
{
  namespace core
  {
    const double PRECISION = 1e-5;

    inline bool equals(double one, double two)
    {
      return std::abs(one-two) < PRECISION;
    }
  }
}

#endif
