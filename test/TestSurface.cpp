#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Surface.hpp>

using namespace igloo;

Describe(ATestSurface)
{
  It(can_be_instantiated)
  {
    cw::core::Surface surface;
  }
};
