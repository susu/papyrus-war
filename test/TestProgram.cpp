#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/opengl/Program.hpp>
#include "OpenGlStubs.hpp"

using namespace igloo;

Describe(the_Program)
{
  It(can_be_instantiated)
  {
    glewInit();
    cw::opengl::Program p;
  }
};
