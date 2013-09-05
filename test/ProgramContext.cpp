#include <igloo/igloo_alt.h>
#include <cw/opengl/ProgramContext.hpp>

using namespace igloo;

Describe(AProgramContext)
{
  It(can_be_instantiated)
  {
    cw::opengl::ProgramContext ctx(1);
  }
};
