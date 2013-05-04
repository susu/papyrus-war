#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/PaperBoat.hpp>

using namespace igloo;

Describe(a_PaperBoat)
{
  It(can_be_instantiated)
  {
    auto boat = cw::core::PaperBoat(10,10);
  }
};
