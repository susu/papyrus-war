#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Pos.hpp>

using cw::core::Pos;
using namespace igloo;
using cw::core::PI;
using cw::core::PRECISION;

Describe(APos)
{
  Spec(default_ctor_initializes_to_origin)
  {
    Pos pos;
    AssertThat(pos.x, EqualsWithDelta(0.0, PRECISION));
    AssertThat(pos.y, EqualsWithDelta(0.0, PRECISION));
  }

  Spec(parametered_ctor_initializes)
  {
    Pos pos(5.66,45.3);
    AssertThat(pos.x, EqualsWithDelta(5.66, PRECISION));
    AssertThat(pos.y, EqualsWithDelta(45.3, PRECISION));
  }

  It(can_be_constructed_from_polar)
  {
    Pos pos = Pos::createFromPolar(7.0,PI/4);
    AssertThat(pos.x, EqualsWithDelta( 4.94975, PRECISION));
    AssertThat(pos.y, EqualsWithDelta( 4.94975, PRECISION));
  }

  It(can_be_equalcompared)
  {
    Pos a(1.0,2.0);
    AssertThat(a == a, Equals(true));

    Pos b(4.5, 6.7);
    AssertThat(a == b, Equals(false));

    Pos c(1.0,2.1);
    AssertThat(a == c, Equals(false));

    Pos d(1.01,2.0);
    AssertThat(a == d, Equals(false));
  }

  Context(ParallelCheck)
  {
    Spec(othogonal)
    {
      Pos a(1.0, -1.0);
      Pos b(1.0, 1.0);

      AssertThat( a || b, Equals(false));
    }

    Spec(arbitrary)
    {
      Pos a(4.567,3.655);
      Pos b(1.2, -19.99);

      AssertThat( a || b, Equals(false));
    }

    Spec(points_to_one_direction)
    {
      Pos a(4.5, 6.8);
      Pos b(6.75, 10.2);

      AssertThat( a || b, Equals(true));
    }

    Spec(points_on_head)
    {
      Pos a(9.44, 1.67);
      Pos b(-1.888, -0.334);

      AssertThat( a || b, Equals(true));
    }
  };

};
