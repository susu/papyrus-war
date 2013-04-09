#ifndef TEST_OPENGL_PROGRAM_HPP_INC
#define TEST_OPENGL_PROGRAM_HPP_INC

#include <cw/opengl/Program.hpp>
#include "openglstub/stubs.h"

Describe(the_Program)
{
  It(can_be_instantiated)
  {
    glewInit();
    cw::opengl::Program p;
  }
};

#endif
