#ifndef CW_CORE_MOVING_HPP_INC
#define CW_CORE_MOVING_HPP_INC

#include <cw/Enforce.hpp>
#include <cw/core/Logger.hpp>

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
        {
          ENFORCE(-PI <= orientation && orientation <= PI, "orientation is out of range!");
        }

        void setTarget(Pos pos)
        {
          m_targetPos = pos;
        }

        const Pos& getCurrentPos() const
        {
          return m_pos;
        }

        double getCurrentOrientation() const
        {
          return m_orientation;
        }

        // TODO move this function inline
        double countRemainingAngle(double one, double two)
        {
          double firstTry = one - two;
          if (std::abs(firstTry) > PI)
          {
            return one + 2*PI - two;
          }
          return firstTry;
        }

        /**
         *  Updates the actual rotation/moving if needed.
         *  @param diffTime: seconds elapsed since last call
         */
        void tick(double diffTime)
        {
          if (m_targetPos == m_pos) return;
          static cw::core::Logger logger("moving");
          Polar offset = m_targetPos - m_pos;

          double remainingAngle = countRemainingAngle(offset.angle, m_orientation);
          if ( !equals(remainingAngle,0.0) )
          {
            double orientStep = m_config.rotateSpeed * diffTime;
            if (std::abs(remainingAngle) < orientStep)
            {
              // difference is smaller than one step
              m_orientation += remainingAngle;
              return;
            }

            if (remainingAngle < 0.0)
            {
              orientStep *= -1;
            }
            m_orientation = std::fmod(m_orientation + orientStep, 2*PI);
            return;
          }
          LOG_DEBUG("translation needed: targetPos=",m_targetPos," currentPos=",m_pos);
          // translation needed
          // TODO check length of translation vector to not jump over targetPos
          Pos normalDirectionVector = normalize(m_targetPos - m_pos);
          m_pos += normalDirectionVector * m_config.travelSpeed * diffTime;
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
