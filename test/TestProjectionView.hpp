#ifndef TEST_PROJECTION_VIEW_HPP_INC
#define TEST_PROJECTION_VIEW_HPP_INC

#include <cw/opengl/ProjectionView.hpp>

Describe(the_ProjectionView)
{
  It(can_be_instantiated)
  {
    cw::opengl::Program program;
    cw::opengl::ProjectionView projView(program);
  }
};

#endif
