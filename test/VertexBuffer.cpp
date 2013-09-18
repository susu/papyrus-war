#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/MeasureUnits.hpp>
#include <cw/opengl/VertexBuffer.hpp>

#include "openglstub/OpenGlMemoryStub.hpp"

using namespace igloo;

Describe(AVertexBuffer)
{
  It(can_be_instantiated_with_initial_size)
  {
    cw::opengl::VertexBuffer buffer(cw::MegaByte(10));
    auto index = buffer.getIndex();

    AssertThat(buffer.getFullSize(), Equals(cw::MegaByte(10)));
    AssertThat(OpenGlMemoryStub::instance().getVBO(index).size, Equals(cw::MegaByte(10)));
  }

  It(can_be_requested_for_memory)
  {
    cw::opengl::VertexBuffer buffer(cw::MegaByte(1));

    buffer.requestMemory(cw::KiloByte(100));
  }

};
