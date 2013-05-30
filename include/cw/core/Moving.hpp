#ifndef CW_CORE_MOVING_HPP_INC
#define CW_CORE_MOVING_HPP_INC

#include <cw/Enforce.hpp>

namespace cw
{
  namespace core
  {
    class Moving
    {
      public:
        struct Config
        {
          double rotateSpeed;
          double travelSpeed;
        };
        Moving(const Config& config, Pos startPos, double orientation)
          : m_config(config)
          , m_pos(startPos)
          , m_targetPos(startPos) //< no moving by default
          , m_orientation(Pos::createFromPolar(1.0, orientation))
        {}

        void setTarget(Pos pos)
        {
          m_targetPos = pos;
        }

        const Pos& getCurrentPos() const
        {
          return m_pos;
        }

        void tick(double diffTime)
        {
          ENFORCE( ( m_targetPos || m_orientation ), "Implemented only for parallel vectors!" );

          Pos normalDirectionVector = normalize(m_targetPos);
          m_pos += normalDirectionVector * m_config.travelSpeed * diffTime;
        }
      private:
        const Config m_config;
        Pos m_pos;
        Pos m_targetPos;
        Pos m_orientation;
    };
  }
}

inline double operator"" _rad_per_sec(long double d)
{
  return d;
}

inline double operator"" _meter_per_sec(long double d)
{
  return d;
}

inline double operator"" _rad(long double d)
{
  return d;
}

inline double operator"" _meter(long double d)
{
  return d;
}

#endif
