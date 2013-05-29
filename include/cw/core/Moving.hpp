#ifndef CW_CORE_MOVING_HPP_INC
#define CW_CORE_MOVING_HPP_INC

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
          , m_orientation(orientation)
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
          m_pos.x += m_config.travelSpeed * diffTime;
        }
      private:
        const Config m_config;
        Pos m_pos;
        Pos m_targetPos;
        double m_orientation;
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
