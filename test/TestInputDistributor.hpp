#ifndef TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/InputDistributor.hpp>

#include "fake/UnitStub.hpp"

using namespace igloo;

Describe(the_InputDistributor)
{
  cw::core::InputDistributor dist;
  fake::UnitStubRef unit;

  void SetUp()
  {
    unit.reset( new fake::UnitStub );
    AssertThat( unit->hasFocus(), Equals(false) );
    unit->setPos( 100.0, 100.0 );
    unit->setSize( 10.0, 10.0 );
    dist.registerUnit( unit );
  }

  It(should_set_focus_on_clicked_unit)
  {
    dist.clickedAt( 105, 105 );
    AssertThat( unit->hasFocus(), Equals(true) );
  }

  It(should_call_moveTo_if_unit_has_focus)
  {
    std::cout << "PENDING" << std::endl;
    // using cw::core::Pos;
    // unit->setFocus(true);
    // dist.clickedAt( 50, 50 );
    // AssertThat( unit->getMoveTarget(), Equals( Pos{50.0, 50.0} ));
  }

  It(should_remove_focus_if_clicked_on_another_unit)
  {
    std::cout << "PENDING" << std::endl;
  }
};

#endif
