#ifndef CW_CORE_MOVING_HPP_INC
#define CW_CORE_MOVING_HPP_INC

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

        double getCurrentOrientation() const
        {
          Pos xAxis( 1.0, 0.0 );
          auto dotProd = m_orientation * xAxis;
          auto cosine = dotProd / ( length(m_orientation) * length(xAxis) );
          return std::acos(cosine);
        }

        /**
         *  Updates the actual rotation/moving if needed.
         *  @param diffTime: seconds elapsed since last call
         */
        void tick(double diffTime)
        {
          if (m_targetPos == m_pos) return;
          static cw::core::Logger logger("moving");
          if ( !(m_targetPos || m_orientation ) )
          {
            // rotation needed
            // TODO check if positive or negative rotation is smaller!
            auto orientStep = m_config.rotateSpeed * diffTime;
            m_orientation = rotate(m_orientation, orientStep);
            LOG_DEBUG("difftime=",diffTime," rotation needed: ",m_orientation);
            return;
          }
          LOG_DEBUG("translation needed: targetPos=",m_targetPos," orientation=",m_orientation);
          // translation needed
          // TODO check length of translation vector to not jump over targetPos
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
