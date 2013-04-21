#ifndef TEST_RECTANGLE_UNIT_HPP_INC
#define TEST_RECTANGLE_UNIT_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/RectangleUnit.hpp>

struct RectStub : public cw::core::RectangleUnit
{
  RectStub(cw::core::Pos p, cw::core::Pos size)
    : cw::core::RectangleUnit(p,size)
  {}

  virtual void tick() override
  {}
};

using namespace igloo;

Describe(a_RectangleUnit)
{
  RectStub stub = RectStub( cw::core::Pos{12,43}, cw::core::Pos{10,10} );

  It(can_be_instantiated)
  {
    AssertThat( stub.hasFocus(), Equals(false) );
  }

  It(can_store_focus)
  {
    stub.setFocus(true);
    AssertThat( stub.hasFocus(), Equals(true) );

    stub.setFocus(false);
    AssertThat( stub.hasFocus(), Equals(false) );
  }

  It(has_position)
  {
    AssertThat( stub.getPos(), Equals( cw::core::Pos{12,43} ));

    AssertThat( stub.isOver(15,45), Equals(true) );
  }
};

#endif
