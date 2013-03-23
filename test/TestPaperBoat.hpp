#ifndef TEST_PAPER_BOAT_HPP_INC
#define TEST_PAPER_BOAT_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/PaperBoat.hpp>

Describe(a_PaperBoat)
{
  It(can_be_instantiated)
  {
    auto boat = cw::core::PaperBoat(10,10);
  }
};

#endif
