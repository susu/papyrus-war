#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Pos.hpp>
#include <cw/core/Moving.hpp>
#include <cw/core/Timer.hpp>

using namespace igloo;
using cw::core::Moving;
using cw::core::Pos;

// Builder
struct MakeMoving
{
  MakeMoving()
    : m_orient(0.0_rad)
    , m_startPos(0.0, 0.0)
  {
    m_config.rotateSpeed = 1.0_rad_per_sec;
    m_config.travelSpeed = 1.0_meter_per_sec;
  }

  MakeMoving& rotateSpeed(double rotSpd)
  {
    m_config.rotateSpeed = rotSpd;
    return *this;
  }

  MakeMoving& travelSpeed(double travelSpd)
  {
    m_config.travelSpeed = travelSpd;
    return *this;
  }

  MakeMoving& orientation(double orient)
  {
    m_orient = orient;
    return *this;
  }

  MakeMoving& startPos(Pos startPos)
  {
    m_startPos = startPos;
    return *this;
  }

  operator Moving()
  {
    return Moving(m_config,m_startPos,m_orient);
  }

  Moving::Config m_config;
  double m_orient;
  Pos m_startPos;
};

Describe(AMoving)
{
  Moving createMoving()
  {
    Moving::Config config;
    config.rotateSpeed = 1.4_rad_per_sec;
    config.travelSpeed = 1.0_meter_per_sec;
    Pos startPos(0.0,0.0);
    auto startOrientation = 0.0_rad;
    return Moving(config, startPos, startOrientation);
  }

  It(start_into_way_of_the_target_point)
  {
    Moving moving = MakeMoving().orientation(0.0_rad)
                                .travelSpeed(1.0_meter_per_sec);

    moving.setTarget( Pos(10.0, 0.0) );
    moving.tick( 10_millisec );

    AssertThat(moving.getCurrentPos(), Equals(Pos(0.01_meter, 0.0)));
  }
};