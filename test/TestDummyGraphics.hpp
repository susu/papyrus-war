#ifndef TEST_DUMMY_GRAPHICS_HPP_INC
#define TEST_DUMMY_GRAPHICS_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/graph/DummyGraphics.hpp>

using namespace igloo;

Describe(a_DummyGraphics)
{
  It(should_not_do_anything_useful)
  {
    cw::graph::DummyGraphics gr;
  }
};

#endif
