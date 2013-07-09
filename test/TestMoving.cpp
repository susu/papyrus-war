#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Pos.hpp>
#include <cw/core/Moving.hpp>
#include <cw/core/Timer.hpp>

using namespace igloo;
using cw::core::Moving;
using cw::core::Pos;
using cw::core::PRECISION;

// Builder
struct MakeMoving
{
  MakeMoving()
    : m_orient(0.0)
    , m_startPos(0.0, 0.0)
  {
    m_config.rotateSpeed = 1.0; //_rad_per_sec;
    m_config.travelSpeed = 1.0; //_meter_per_sec;
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
  constexpr static double PI = 3.14159265359;
  It(start_into_way_of_the_target_point_if_x_aligned)
  {
    Moving moving = MakeMoving().orientation(0.0)
                                .travelSpeed(1.0);

    moving.setTarget( Pos(10.0, 0.0) );
    moving.tick( 10 * 0.001 );

    AssertThat(moving.getCurrentPos(), Equals(Pos(0.01, 0.0)));
  }

  It(start_into_way_of_the_taget_if_not_aligned)
  {
    Moving moving = MakeMoving().orientation(PI/4.0)
                                .travelSpeed(1.2);
    moving.setTarget( Pos(5.0,5.0) );
    moving.tick( 25 * 0.001 );

    AssertThat(moving.getCurrentPos(), Equals(Pos(0.0212132,0.0212132)));
  }

  It(can_rotate_if_target_not_in_the_same_way)
  {
    Moving moving = MakeMoving().orientation(0.0).travelSpeed(1.0);
    moving.setTarget( Pos(5.0,5.0) );
    moving.tick(10 * 0.001);

    // position is the same
    AssertThat(moving.getCurrentPos(), Equals( Pos(0.0,0.0) ));

    // (1 rad/sec) / 10 ms = 0.01 rad
    AssertThat(moving.getCurrentOrientation(), EqualsWithDelta(0.01, PRECISION));
  }

  It(should_reach_final_target_after_awhile)
  {
    Moving moving = MakeMoving().orientation(0.0)
                                .travelSpeed(1.0)
                                .rotateSpeed(1.0)
                                .startPos( Pos(0.0,0.0) );
    // target orientation is PI/4
    moving.setTarget( Pos(5.0,5.0) );

    // with 1 rad/sec, orientation PI/4 will be reached within PI/4 sec
    //moving.tick( PI/4.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );

    AssertThat(moving.getCurrentOrientation(), EqualsWithDelta(PI/4, PRECISION));
  }

  It(should_rotate_into_the_other_direction)
  {
    Moving moving = MakeMoving().orientation(0.0)
                                .travelSpeed(1.0)
                                .rotateSpeed(1.0)
                                .startPos( Pos(0.0,0.0) );
    // -PI/4
    moving.setTarget( Pos(5.0, -5.0) );

    moving.tick( PI/8.0 );
    moving.tick( PI/8.0 );

    AssertThat(moving.getCurrentOrientation(), EqualsWithDelta(-PI/4, PRECISION));
  }
};
