#ifndef TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/InputDistributor.hpp>

#include "fake/ModelStub.hpp"

using namespace igloo;

Describe(the_InputDistributor)
{
  cw::core::InputDistributor dist;
  Ref<fake::ModelStub> model;

  void SetUp()
  {
    model.reset( new fake::ModelStub );
    AssertThat( model->hasFocus(), Equals(false) );
    model->setPos( 100.0, 100.0 );
    model->setSize( 10.0, 10.0 );
    dist.registerModel( model );
  }

  It(should_set_focus_on_clicked_model)
  {
    dist.clickedAt( 105, 105 );
    AssertThat( model->hasFocus(), Equals(true) );
  }

  It(should_call_moveTo_if_model)
  {
    std::cout << "PENDING" << std::endl;
    using cw::core::Pos;
    model->setFocus(true);
    dist.clickedAt( 50, 50 );
    AssertThat( model->getMoveTarget(), Equals( Pos{50.0, 50.0} ));
  }

  It(should_remove_focus_if_clicked_on_another_model)
  {
    std::cout << "PENDING" << std::endl;
  }
};

#endif
