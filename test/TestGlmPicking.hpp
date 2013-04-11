#ifndef TEST_GLM_PICKING_HPP_INC
#define TEST_GLM_PICKING_HPP_INC

#include <cw/opengl/GlmPicking.hpp>

Describe(AGlmPicking)
{
  It(can_be_instantiated)
  {
    cw::opengl::Program prog;
    cw::opengl::ProjectionView projView(prog);

    cw::opengl::GlmPicking picking;
    std::cout << &picking << std::endl;
  }
};

#endif
